/******************************************************************************
 * Quantitative Kit Library                                                   *
 *                                                                            *
 * Copyright (C) 2017 Xiaojun Gao                                             *
 *                                                                            *
 * Distributed under the terms and conditions of the BSD 3-Clause License or  *
 * (at your option) under the terms and conditions of the Boost Software      *
 * License 1.0. See accompanying files LICENSE and LICENSE_ALTERNATIVE.       *
 ******************************************************************************/

#include <assert.h>
#include <limits.h>

#include "tree.h"
#include <qk.h>
#include <uv.h>
#include "qk_internal.h"
#include "errno.h"

static int qk_timer_compare(qk_timer_t *lhs, qk_timer_t *rhs) {
  if (lhs->timeout < rhs->timeout)
    return -1;
  if (lhs->timeout > rhs->timeout)
    return 1;
  /*
   *  compare start_id when both has the same due. start_id is
   *  allocated with loop->timer_counter in qk_timer_start().
   */
  if (lhs->start_id < rhs->start_id)
    return -1;
  if (lhs->start_id > rhs->start_id)
    return 1;
  return 0;
}

RB_GENERATE(qk_timer_tree_s, qk_timer_s, tree_entry, qk_timer_compare)

qk_timer_t* qk_timer_new(qk_cycle_t* cycle, qk_timer_type mode) {
  qk_timer_t *timer = malloc(sizeof(qk_timer_t));
  if(!timer) return NULL;
  //timer->timeout = timeout;
  timer->timer_cb = NULL;
  timer->repeat = 0;
  timer->mode = mode;
  timer->loop = cycle;
  return 0;
}

/* donot using this function, using internal */
void qk_timer_free(qk_timer_t *t)
{
    free(t);
}

/*static uint64_t get_clamped_due_time(uint64_t loop_time, uint64_t timeout) {
  uint64_t clamped_timeout;

  clamped_timeout = loop_time + timeout;
  if (clamped_timeout < timeout)
    clamped_timeout = (uint64_t)-1;

  return clamped_timeout;
}*/

int qk_timer_start(qk_timer_t *timer, uint64_t timeout,
                   uint64_t repeat,  qk_timer_cb timer_cb, void *data) {
  qk_cycle_t *loop = timer->loop;
  qk_timer_t *old;

  if (timer_cb == NULL)
    return -1;//QK_EINVAL;

  timer->timer_cb = timer_cb;
  timer->data = data;
  timer->timeout = timeout; //get_clamped_due_time(loop->time, timeout);
  timer->repeat = repeat;

  // start_id is the second index to be compared in qk__timer_cmp()
  timer->start_id = timer->loop->timer_counter++;

  if (timer->mode == QK_LOCAL_TIMER)
    old = RB_INSERT(qk_timer_tree_s, &loop->timers[QK_LOCAL_TIMER], timer);
  else
    old = RB_INSERT(qk_timer_tree_s, &loop->timers[QK_EXCHANGE_TIMER], timer);
  assert(old == NULL);

  return 0;
}

int qk_timer_stop(qk_timer_t *timer) {
  qk_cycle_t *loop = timer->loop;

  RB_REMOVE(qk_timer_tree_s, &loop->timers[timer->mode], timer);

  return 0;
}

int qk_timer_again(qk_timer_t *timer) {
  /* If timer_cb is NULL that means that the timer was never started. */
  if (!timer->timer_cb) {
    return -1; //UV_EINVAL;
  }

  if (timer->repeat) {
    qk_timer_stop(timer);
    qk_timer_start(timer, timer->repeat, timer->repeat, timer->timer_cb, timer->data);
  }

  return 0;
}

void qk_timer_set_repeat(qk_timer_t *timer, uint64_t repeat) {
  timer->repeat = repeat;
}

uint64_t qk_timer_get_repeat(const qk_timer_t *timer) {
  return timer->repeat;
}

uint64_t qk_next_timeout(const qk_cycle_t *loop) {
  qk_timer_t *timer;
  int64_t delta;

  timer = RB_MIN(qk_timer_tree_s, (struct qk_timer_tree_s *)&loop->timers[QK_LOCAL_TIMER]);
  if (timer) {
      delta = timer->timeout - datetime_now();
    if (delta < 0) {
      /* Negative timeout values are not allowed */
      return 0;
    } else {
      return delta;
    }
  } else {
    /* No timers */
    return 0;
  }
}
