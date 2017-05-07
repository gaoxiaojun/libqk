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
#include <string.h>

qk_queue_t *qk_queue_new(int size, qk_queue_type type, const char *name) {
  qk_queue_t *q = malloc(sizeof(qk_queue_t));
  if (!q)
    return NULL;

  memset(q, 0, sizeof(qk_queue_t));
  if(spsc_queue_init(&q->spsc, size)) {
      free(q);
      return NULL;
  }
  q->type = type;
  q->name = strdup(name);
  q->loop = NULL;
  return q;
}

/* donot call this function, using internal*/
void qk_queue_free(qk_queue_t *q)
{
    free(q->name);
    spsc_queue_destroy(&q->spsc);
    free(q);
}

void *qk_queue_peek(qk_queue_t *q) { return spsc_queue_peek(&q->spsc); }

void *qk_queue_pop(qk_queue_t *q) {
  void *item;
  if ((item = spsc_queue_read(&q->spsc)))
    return item;
  return NULL;
}

int qk_queue_push(qk_queue_t *q, void *data) {
  int empty = spsc_queue_is_empty(&q->spsc);
  int result = spsc_queue_write(&q->spsc, data);
  if (empty && q->loop)
    qk_wakeup(q->loop);
  return result;
}

int qk_queue_is_empty(qk_queue_t *q) { return spsc_queue_is_empty(&q->spsc); }

int qk_queue_is_full(qk_queue_t *q) { return spsc_queue_is_full(&q->spsc); }

char *qk_queue_get_name(qk_queue_t *q) { return q->name; }

void qk_queue_set_name(qk_queue_t *q, const char *name) {
  free(q->name);
  q->name = strdup(name);
}
