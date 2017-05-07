/******************************************************************************
 * Quantitative Kit Library                                                   *
 *                                                                            *
 * Copyright (C) 2017 Xiaojun Gao                                             *
 *                                                                            *
 * Distributed under the terms and conditions of the BSD 3-Clause License or  *
 * (at your option) under the terms and conditions of the Boost Software      *
 * License 1.0. See accompanying files LICENSE and LICENSE_ALTERNATIVE.       *
 ******************************************************************************/

#ifndef CTF_SPSC_QUEUE_H
#define CTF_SPSC_QUEUE_H

#include <stdatomic.h>

/*
 * lock-free spsc queue
 */

#if defined(__clang__) || defined(__GNUC__)
#define ALIGNED(size) __attribute__((__aligned__(size)))
#elif defined(__MSC_VER)
#define ALIGNED(size) __declspec(align(size))
#else
#error Cannot define ALIGNED on this platform
#endif

#define kCacheLineSize 128
#define ALIGN_TO_AVOID_FALSE_SHARING ALIGNED(kCacheLineSize)

typedef struct spsc_queue_s {
  uint32_t capacity;
  void **records;
  ALIGN_TO_AVOID_FALSE_SHARING atomic_uint read_pos;
  ALIGN_TO_AVOID_FALSE_SHARING atomic_uint write_pos;
  char pad[kCacheLineSize - sizeof(atomic_uint)];
} spsc_queue_t;

extern int spsc_queue_init(spsc_queue_t *q, unsigned int capacity);

extern void spsc_queue_destroy(spsc_queue_t *q);

/* return 0 successful, other means queue if full */
extern int spsc_queue_write(spsc_queue_t *q, void *e);

/* return 0 successful, other means queue if empty */
extern void* spsc_queue_read(spsc_queue_t *q);

/* return NULL means queue is empty*/
extern void *spsc_queue_peek(spsc_queue_t *q);

extern int spsc_queue_is_empty(spsc_queue_t *q);

extern int spsc_queue_is_full(spsc_queue_t *q);

extern unsigned int spsc_queue_size(spsc_queue_t *q);

extern unsigned int spsc_queue_capacity(spsc_queue_t *q);


#endif // CTF_SPSC_QUEUE_H
