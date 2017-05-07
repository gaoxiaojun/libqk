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
#include <inttypes.h>

void qk_event_free(qk_event_t *e) { free(e); }

void process_events(qk_event_t *e)
{
    char dst[512];
    //long gmoffset = qk_get_timezone_offset();
    datetime_format(dst, sizeof(dst), e->timestamp, 0);
    printf("process_event index = %"PRIu64" %s\n", e->index, dst);
}
