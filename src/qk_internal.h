/******************************************************************************
 * Quantitative Kit Library                                                   *
 *                                                                            *
 * Copyright (C) 2017 Xiaojun Gao                                             *
 *                                                                            *
 * Distributed under the terms and conditions of the BSD 3-Clause License or  *
 * (at your option) under the terms and conditions of the Boost Software      *
 * License 1.0. See accompanying files LICENSE and LICENSE_ALTERNATIVE.       *
 ******************************************************************************/
#ifndef QK_INTERNAL_H
#define QK_INTERNAL_H

#include "spsc_queue.h"
#include "tree.h"
#include <qk.h>
#include <stddef.h>
#include <stdlib.h>
#include <uv.h>

struct qk_timer_s;
struct qk_queue_s;

RB_HEAD(qk_timer_tree_s, qk_timer_s);
RB_HEAD(qk_queue_tree_s, qk_queue_s);

struct qk_cycle_s {
  void *data;
  qk_run_mode mode;
  uv_thread_t self;
  unsigned int running;
  volatile unsigned int stop_flag;
  struct qk_timer_tree_s timers[2];
  uint64_t timer_counter;

  datetime_t datetime[2];
  datetime_t real_datetime;

  struct qk_queue_tree_s pipes[4];

  spsc_queue_t pending;

  uint64_t queue_count;

  uv_mutex_t mutex;
  uv_cond_t cond;

#ifndef NDEBUG
  uint64_t iter_count;
#endif
};

struct qk_timer_s {
  void *data;
  qk_cycle_t *loop;
  RB_ENTRY(qk_timer_s) tree_entry;
  datetime_t timeout;
  uint64_t repeat;
  uint64_t start_id;
  qk_timer_cb timer_cb;
  qk_timer_type mode;
};
RB_PROTOTYPE(qk_timer_tree_s, qk_timer_s, tree_entry, qk_timer_compare)

extern uint64_t qk_next_timeout(const qk_cycle_t *loop);
extern void qk_timer_free(qk_timer_t *t);

struct qk_queue_s {
  RB_ENTRY(qk_queue_s) tree_entry;
  uint64_t queue_id;
  spsc_queue_t spsc;
  qk_queue_type type;
  char *name;
  qk_cycle_t *loop;
};

void qk_queue_free(qk_queue_t *q);

extern void qk_wakeup(qk_cycle_t *loop);

extern void process_events(qk_event_t *e);

#endif // QK_INTERNAL_H
