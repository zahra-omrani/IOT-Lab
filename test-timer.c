#include "contiki.h"
#include "sys/timer.h"
#include <stdio.h>

PROCESS(example_timer_process, "Example Timer Process");
AUTOSTART_PROCESSES(&example_timer_process);

PROCESS_THREAD(example_timer_process, ev, data)
{
    static struct timer my_timer;

    PROCESS_BEGIN();

    // Set the timer to expire after 5 seconds
    timer_set(&my_timer, CLOCK_SECOND * 5);

    while (1) {
        // Check if the timer has expired
        if (timer_expired(&my_timer)) {
            printf("Timer expired!\n");

            // Reset the timer for the next interval
            timer_reset(&my_timer);
        }

        // Do other processing here
        //PROCESS_YIELD();
    }

    PROCESS_END();
}
