/******************************************************************************
 * Quantitative Kit Library                                                   *
 *                                                                            *
 * Copyright (C) 2017 Xiaojun Gao                                             *
 *                                                                            *
 * Distributed under the terms and conditions of the BSD 3-Clause License or  *
 * (at your option) under the terms and conditions of the Boost Software      *
 * License 1.0. See accompanying files LICENSE and LICENSE_ALTERNATIVE.       *
 ******************************************************************************/

#ifndef __QK_H__
#define __QK_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
  /* Windows - set up dll import/export decorators. */
# if defined(BUILDING_QTL_SHARED)
    /* Building shared library. */
#   define QK_EXTERN __declspec(dllexport)
# elif defined(USING_QTL_SHARED)
    /* Using shared library. */
#   define QK_EXTERN __declspec(dllimport)
# else
    /* Building static library. */
#   define QK_EXTERN /* nothing */
# endif
#elif __GNUC__ >= 4
# define QK_EXTERN __attribute__((visibility("default")))
#else
# define QK_EXTERN /* nothing */
#endif

#include "qk_version.h"
#include "qk_errno.h"

#include <stddef.h>
#include <stdio.h>
#include <stdatomic.h>
#include <sys/time.h>

#if defined(_MSC_VER) && _MSC_VER < 1600
# include "stdint-msvc2008.h"
#else
# include <stdint.h>
#endif


QK_EXTERN unsigned int qk_version(void);
QK_EXTERN const char* qk_version_string(void);

/* datetime module */

/* datetime type represents a date and time.
   that stores the date and time as the number of microsecond intervals since
   12:00 AM January 1, year 1 A.D (as Day 0). in the proleptic Gregorian Calendar.
*/

typedef uint64_t datetime_t;
typedef int64_t  timespan_t;

#define EPOCH_DATE_TIME UINT64_C(62135596800000000)  /* 1970-01-01T00:00:00:00 */
#define MIN_DATE_TIME UINT64_C(0)                    /* 0001-01-01T00:00:00:00 */
#define MAX_DATE_TIME UINT64_C(315537897599999999)   /* 9999-12-31T23:59:59.999999*/

QK_EXTERN datetime_t datetime_from_ymd(uint16_t year, uint16_t month, uint16_t day);
QK_EXTERN datetime_t datetime_from_hmsu(uint16_t hour, uint16_t minute, uint16_t second, uint32_t usec);
QK_EXTERN datetime_t datetime_from_timeval(struct timeval *t);
/* result = 0 means ok, other means error */
QK_EXTERN int datetime_from_iso8601(const char *str, size_t len, datetime_t *dt);
QK_EXTERN void datetime_decode(datetime_t dt, uint16_t *year, uint16_t *month, uint16_t *day, uint16_t *hour, uint16_t *minute, uint16_t *second, uint32_t *usec);
QK_EXTERN int datetime_to_tm(const datetime_t dt, struct tm *tmp);
QK_EXTERN size_t datetime_format(char *dst, size_t len, datetime_t dt, long offset /* see timeout_offset */);
/* return timezone offset from utc, in minutes [-1439,1439] */
QK_EXTERN long qk_get_timezone_offset(void);
QK_EXTERN void qk_timezone_update(void);
QK_EXTERN datetime_t datetime_now(void);

typedef enum {
    QK_EVENT_ASK,
    QK_EVENT_BID,
    QK_EVENT_TRADE,

    QK_EVENT_QUEUECLOSE,

}qk_event_type;

#define QK_EVENT_PUBLIC_FILEDS \
    datetime_t timestamp;       \
    qk_event_type type;         \
    uint64_t  index;

typedef struct qk_event_s {
    QK_EVENT_PUBLIC_FILEDS
}qk_event_t;

typedef struct qk_tick_s {
    QK_EVENT_PUBLIC_FILEDS
    datetime_t exchange_timestamp;
    double price;
    long size;
}qk_tick_t;

typedef int (*event_filter)(qk_event_t *e);
QK_EXTERN void qk_event_free(qk_event_t *e);

/* event queue */
typedef struct event_queue_s event_queue_t;
/* event queue */
typedef struct qk_queue_s qk_queue_t;
/*typedef struct event_bus_s event_bus_t;

QK_EXTERN event_queue_t* qk_queue_new(size_t capacity, event_bus_t *bus);
QK_EXTERN void qk_queue_free(event_queue_t *q);
QK_EXTERN int qk_queue_push(event_queue_t *q, void *data);
QK_EXTERN int qk_queue_is_full(event_queue_t *q);*/

/* event bus */
/*typedef enum {
    QTL_BUS_DTAT_PIPE,
    QTL_BUS_EXECUTION_PIPE,
    QTL_BUS_HISTORICAL_PIPE,
    QTL_BUS_SERVICE_PIPE
}qk_bus_pipe_type_t;*/

/*typedef enum {
    QTL_CLOCK_LOCAL,
    QTL_CLOCK_EXCHAGE
}qk_clock_type_t;

typedef uint64_t timer_id_t;
typedef void (*timer_cb_t)(datetime_t timestamp, void *user_data);
QK_EXTERN int qk_bus_add_queue(event_bus_t *bus, event_queue_t *q, qk_bus_pipe_type_t which);
QK_EXTERN timer_id_t qk_bus_add_timer(event_bus_t *bus, qk_clock_type_t type, datetime_t, time_cb_t callback, void *data);
QK_EXTERN int qk_bus_remove_timer(event_bus_t *bus, timer_id_t id);
QK_EXTERN datetime_t qk_bus_get_time(event_bus_t *bus, qk_clock_type_t type);
QK_EXTERN void qk_bus_set_time(event_bus_t *bus, qk_clock_type_t type, datetime_t time);
*/
//typedef struct rbtree_node_s rbtree_node_t;

/*typedef struct qk_cycle_s {
    atomic_flag terminate;  // force shutdown
    atomic_flag quit;       // gracefull shutdown
    atomic_flag exiting;
    rbtree_node_t *root, *sentinel;
}qk_cycle_t;

QK_EXTERN int qk_process_events_and_timers(qk_cycle_t *cycle);*/

typedef enum {
    QK_CYCLT_STRUCT,
    QK_TIMER_STRUCT,
    QK_QUEUE_STRUCT
}qk_struct_type;

QK_EXTERN size_t qk_size(qk_struct_type type);


typedef struct qk_cycle_s qk_cycle_t;

typedef enum {
    QK_SIMULATION    = 0,
    QK_REALTIME
}qk_run_mode;

QK_EXTERN qk_cycle_t* qk_cycle_new(void *data);
QK_EXTERN int qk_cycle_free(qk_cycle_t* loop);

QK_EXTERN void qk_stop(qk_cycle_t* loop);
QK_EXTERN int qk_run(qk_cycle_t* loop, qk_run_mode mode);

QK_EXTERN qk_run_mode qk_cycle_get_mode(qk_cycle_t* loop);
QK_EXTERN void qk_cycle_set_mode(qk_cycle_t* loop, qk_run_mode mode);

QK_EXTERN datetime_t qk_get_local_clock(const qk_cycle_t* loop);
QK_EXTERN datetime_t qk_get_exchange_clock(const qk_cycle_t* loop);
QK_EXTERN void qk_set_local_clock(qk_cycle_t* loop, datetime_t time);
QK_EXTERN void qk_set_exchange_clock(qk_cycle_t* loop, datetime_t time);

QK_EXTERN int qk_add_queue(qk_cycle_t *loop, qk_queue_t *q);

typedef struct qk_timer_s qk_timer_t;

typedef enum {
    QK_LOCAL_TIMER,
    QK_EXCHANGE_TIMER
}qk_timer_type;

typedef void (*qk_timer_cb)(qk_timer_t *timer);
QK_EXTERN qk_timer_t* qk_timer_new(qk_cycle_t* cycle, qk_timer_type type);
QK_EXTERN int qk_timer_start(qk_timer_t* timer, datetime_t timeout, uint64_t repeat, qk_timer_cb cb, void *data);
QK_EXTERN int qk_timer_stop(qk_timer_t* timer);
QK_EXTERN int qk_timer_again(qk_timer_t* timer);
QK_EXTERN void qk_timer_set_repeat(qk_timer_t* timer, uint64_t repeat);
QK_EXTERN uint64_t qk_timer_get_repeat(const qk_timer_t* timer);


typedef struct qk_queue_s qk_queue_t;

typedef enum {
    QK_DATA_QUEUE,
    QK_EXECUTION_QUEUE,
    QK_HISTORICAL_QUEUE,
    QK_SERVICE_QUEUE
}qk_queue_type;

QK_EXTERN qk_queue_t *qk_queue_new(int size, qk_queue_type type, const char *name);
QK_EXTERN void* qk_queue_peek(qk_queue_t *q);
QK_EXTERN void* qk_queue_pop(qk_queue_t *q);
QK_EXTERN int qk_queue_push(qk_queue_t *q, void *data);
QK_EXTERN int qk_queue_is_empty(qk_queue_t *q);
QK_EXTERN int qk_queue_is_full(qk_queue_t *q);
QK_EXTERN char *qk_queue_get_name(qk_queue_t *q);
QK_EXTERN void qk_queue_set_name(qk_queue_t *q, const char *name);

#ifdef __cplusplus
}
#endif
#endif // __QK_H__
