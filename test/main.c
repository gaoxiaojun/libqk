#include <qk.h>
#include <uv.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	qk_cycle_t *loop = qk_cycle_new(NULL);
    if (!loop)
    {
        printf("malloc loop error\n");
        return -1;
    }
    qk_queue_t *q = qk_queue_new(1000, QK_DATA_QUEUE, "test q");
    if(!q) {
        printf("malloc queue error\n");
        return -1;
    }

    qk_tick_t* ticks[10];
    for(size_t i=0; i< 10;i++) {
        ticks[i] = malloc(sizeof(qk_tick_t));
        ticks[i]->type = QK_EVENT_ASK;
        ticks[i]->timestamp = datetime_now();
        ticks[i]->index = i;
        qk_queue_push(q, ticks[i]);
    }
    qk_event_t *close = malloc(sizeof(qk_event_t));
    close->type = QK_EVENT_QUEUECLOSE;
    close->timestamp = MIN_DATE_TIME;
    close->index = 10;
    qk_queue_push(q, close);
	qk_run(loop, QK_REALTIME);
    qk_add_queue(loop, q);

    sleep(5);
	qk_stop(loop);

    return 0;
}
