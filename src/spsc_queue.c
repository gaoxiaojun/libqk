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
#include <stdlib.h>

#include <stdatomic.h>
#include <stdint.h>

#include "spsc_queue.h"

int spsc_queue_init(spsc_queue_t *q, unsigned int capacity) {
  assert(capacity >= 2);
  q->records = malloc(capacity * sizeof(void *));
  if (!q->records)
    return -1;

  q->capacity = capacity;
  q->read_pos = 0;
  q->write_pos = 0;

  return 0;
}

void spsc_queue_destroy(spsc_queue_t *q) { free(q->records); }

int spsc_queue_write(spsc_queue_t *q, void *e) {
  unsigned int current_write =
      atomic_load_explicit(&q->write_pos, memory_order_relaxed);
  unsigned int next_record = current_write + 1;
  if (next_record == q->capacity)
    next_record = 0;

  if (next_record != atomic_load_explicit(&q->read_pos, memory_order_acquire)) {
    q->records[current_write] = e;
    atomic_store_explicit(&q->write_pos, next_record, memory_order_release);
    return 0;
  }

  // queue if full
  return -1;
}

void *spsc_queue_read(spsc_queue_t *q) {
  unsigned int current_read =
      atomic_load_explicit(&q->read_pos, memory_order_relaxed);
  if (current_read ==
      atomic_load_explicit(&q->write_pos, memory_order_acquire)) {
    // queue is empty
    return NULL;
  }

  unsigned int next_record = current_read + 1;
  if (next_record == q->capacity)
    next_record = 0;

  atomic_store_explicit(&q->read_pos, next_record, memory_order_release);
  return q->records[current_read];
}

void* spsc_queue_peek(spsc_queue_t *q) {
  unsigned int current_read =
      atomic_load_explicit(&q->read_pos, memory_order_relaxed);
  if (current_read ==
      atomic_load_explicit(&q->write_pos, memory_order_acquire)) {
    // queue is empty
    return NULL;
  }

  return q->records[current_read];
}

int spsc_queue_is_empty(spsc_queue_t *q) {
  return atomic_load_explicit(&q->read_pos, memory_order_acquire) ==
         atomic_load_explicit(&q->write_pos, memory_order_acquire);
}

int spsc_queue_is_full(spsc_queue_t *q) {
  unsigned int next_record =
      atomic_load_explicit(&q->write_pos, memory_order_acquire) + 1;
  if (next_record == q->capacity)
    next_record = 0;

  if (next_record != atomic_load_explicit(&q->read_pos, memory_order_acquire)) {
    return 1;
  }

  // queue is full
  return 0;
}

unsigned int spsc_queue_size(spsc_queue_t *q) {
  int ret = atomic_load_explicit(&q->write_pos, memory_order_acquire) -
            atomic_load_explicit(&q->read_pos, memory_order_acquire);
  if (ret < 0)
    ret += q->capacity;
  return ret;
}

unsigned int spsc_queue_capacity(spsc_queue_t *q) { return q->capacity; }
