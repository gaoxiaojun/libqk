/******************************************************************************
 * Quantitative Kit Library                                                   *
 *                                                                            *
 * Copyright (C) 2017 Xiaojun Gao                                             *
 *                                                                            *
 * Distributed under the terms and conditions of the BSD 3-Clause License or  *
 * (at your option) under the terms and conditions of the Boost Software      *
 * License 1.0. See accompanying files LICENSE and LICENSE_ALTERNATIVE.       *
 ******************************************************************************/

#include "qk_internal.h"
#include <assert.h>
#include <memory.h>
#include <inttypes.h>
static int qk_queue_compare(qk_queue_t *lhs, qk_queue_t *rhs) {
  qk_event_t *lhs_e = qk_queue_peek(lhs);
  qk_event_t *rhs_e = qk_queue_peek(rhs);

  datetime_t lhs_time = lhs_e ? lhs_e->timestamp : MAX_DATE_TIME;
  datetime_t rhs_time = rhs_e ? rhs_e->timestamp : MAX_DATE_TIME;

  if (lhs_time < rhs_time)
    return -1;
  if (lhs_time > rhs_time)
    return 1;

  if (lhs->queue_id < rhs->queue_id)
    return -1;
  if (lhs->queue_id > rhs->queue_id)
    return 1;
  return 0;
}
RB_GENERATE_STATIC(qk_queue_tree_s, qk_queue_s, tree_entry, qk_queue_compare)

static inline void *get_event_and_update_queue(qk_cycle_t *loop,
                                               qk_queue_type type) {
  qk_queue_t *q = RB_MIN(qk_queue_tree_s, &loop->pipes[type]);
  if (!q)
    return NULL;

  RB_REMOVE(qk_queue_tree_s, &loop->pipes[type], q);
  qk_event_t *e = spsc_queue_read(&q->spsc);
  if (e && e->type == QK_EVENT_QUEUECLOSE) {
      printf("free queue %s\n", q->name);
    qk_event_free(e);
    qk_queue_free(q);
    return NULL;
  }
  q->queue_id = loop->queue_count++;
  RB_INSERT(qk_queue_tree_s, &loop->pipes[type], q);
  return e;
}

static inline datetime_t get_data_pipe_exchange_time(qk_cycle_t *loop) {
  qk_queue_t *q = RB_MIN(qk_queue_tree_s, &loop->pipes[QK_DATA_QUEUE]);
  if (q) {
    qk_event_t *e = spsc_queue_peek(&q->spsc);
    if (e && (e->type == QK_EVENT_ASK || e->type == QK_EVENT_BID ||
              e->type == QK_EVENT_TRADE))
      return ((qk_tick_t *)e)->exchange_timestamp;
  }

  return MIN_DATE_TIME;
}

static void *realtime_run(qk_cycle_t *loop) {
  qk_timer_t *local_timer = RB_MIN(qk_timer_tree_s, &loop->timers[QK_LOCAL_TIMER]);
  if (local_timer && local_timer->timeout <= loop->datetime[QK_LOCAL_TIMER]) {
    RB_REMOVE(qk_timer_tree_s, &loop->timers[QK_LOCAL_TIMER], local_timer);
    return local_timer;
  }

  datetime_t exchange_timestamp = get_data_pipe_exchange_time(loop);
  qk_timer_t *exchange_timer = RB_MIN(qk_timer_tree_s, &loop->timers[QK_EXCHANGE_TIMER]);
  if (exchange_timer && exchange_timer->timeout <= exchange_timestamp) {
    RB_REMOVE(qk_timer_tree_s, &loop->timers[QK_EXCHANGE_TIMER], exchange_timer);
    return exchange_timer;
  }

  qk_event_t *e;
  if ((e = get_event_and_update_queue(loop, QK_EXECUTION_QUEUE)))
    return e;

  if ((e = get_event_and_update_queue(loop, QK_SERVICE_QUEUE)))
    return e;

  if ((e = get_event_and_update_queue(loop, QK_DATA_QUEUE))) {
      process_events(e);
    return e;
  }

  return NULL;
}

static int add_queue(qk_cycle_t *loop, qk_queue_t *q) {
  assert(q->type <= 3);
  q->queue_id = loop->queue_count++;
  RB_INSERT(qk_queue_tree_s, &loop->pipes[q->type], q);
  return 0;
}

static void loop_run(void *arg) {
  qk_cycle_t *loop = (qk_cycle_t *)arg;
  qk_queue_t *q;
  while (loop->stop_flag == 0) {
#ifndef NDENUG
      printf("iter count %"PRIu64"\n", loop->iter_count++);
#endif
    // add pending queue
    while ((q = spsc_queue_read(&loop->pending)))
      add_queue(loop, q);

    qk_event_t *e = realtime_run(loop);

    if (e)
      process_events(e);
    /*else {
      qk_timer_t *local_timer = RB_MIN(qk_timer_tree_s, &loop->local_timers);
      uint64_t timeout = 0;
      if (local_timer)
        timeout = local_timer->timeout - datetime_now();

      if (loop->mode == QK_REALTIME) {
        uv_mutex_lock(&loop->mutex);
        uv_cond_timedwait(&loop->cond, &loop->mutex, timeout);
        uv_mutex_unlock(&loop->mutex);
      } else {
        // simulation mode
        uv_mutex_lock(&loop->mutex);
        uv_cond_wait(&loop->cond, &loop->mutex);
        uv_mutex_unlock(&loop->mutex);
      }
    }*/
  }
}

int qk_run(qk_cycle_t *loop, qk_run_mode mode) {
  loop->mode = mode;
  int err = uv_thread_create(&loop->self, &loop_run, loop);
  if (!err)
    loop->running = 1;
  return err;
}

qk_cycle_t *qk_cycle_new(void *data) {
  qk_cycle_t *loop = malloc(sizeof(qk_cycle_t));
  if (!loop)
    return NULL;

  memset(loop, 0, sizeof(qk_cycle_t));
  loop->data = data;

  loop->stop_flag = 0;
  RB_INIT(&loop->timers[QK_LOCAL_TIMER]);
  RB_INIT(&loop->timers[QK_EXCHANGE_TIMER]);
  loop->timer_counter = 0;

  for (int i = 0; i < 4; i++)
    RB_INIT(&loop->pipes[i]);

  spsc_queue_init(&loop->pending, 10000);
#ifndef NDEBUG
  loop->iter_count = 0;
#endif
  uv_mutex_init(&loop->mutex);
  uv_cond_init(&loop->cond);
  return loop;
}

int qk_cycle_free(qk_cycle_t *loop) {

  // free timer
  // free queues
  uv_mutex_destroy(&loop->mutex);
  uv_cond_destroy(&loop->cond);

  free(loop);
  return 0;
}

void qk_stop(qk_cycle_t *loop) { loop->stop_flag = 1; }

qk_run_mode qk_cycle_get_mode(qk_cycle_t *loop) { return loop->mode; }

void qk_cycle_set_mode(qk_cycle_t *loop, qk_run_mode mode) {}

datetime_t qk_get_local_clock(const qk_cycle_t *loop) {
    return loop->datetime[QK_LOCAL_TIMER];
}

datetime_t qk_get_exchange_clock(const qk_cycle_t *loop) {
    return loop->datetime[QK_EXCHANGE_TIMER];
}

void qk_set_local_clock(qk_cycle_t *loop, datetime_t time) {}

void qk_set_exchange_clock(qk_cycle_t *loop, datetime_t time) {}

void qk_wakeup(qk_cycle_t *loop) {
  uv_mutex_lock(&loop->mutex);
  uv_cond_signal(&loop->cond);
  uv_mutex_unlock(&loop->mutex);
}

/* return 0 means successful, other means queue is full */
int qk_add_queue(qk_cycle_t *loop, qk_queue_t *q) {
  q->loop = loop;
  uv_thread_t this_thread = uv_thread_self();
  if (uv_thread_equal(&loop->self, &this_thread)) {
    return add_queue(loop, q);
  } else {
    int err = spsc_queue_write(&loop->pending, q);

    if (!err) {
      qk_wakeup(loop);
    }
    return err;
  }
}
