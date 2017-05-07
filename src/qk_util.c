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

size_t size_of_struct[] = {sizeof(qk_cycle_t), sizeof(qk_timer_t),
                           sizeof(qk_queue_t)};

size_t size_of_event[] = {

};

size_t qk_size(qk_struct_type type) {
  return size_of_struct[type];
}
