#include "contiki.h"
#include "os/net/netstack.h"
#include "os/net/nullnet/nullnet.h"
#include <string.h>
#include <stdio.h>
#include "os/sys/log.h"

#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO

#define SEND_INTERVAL_BRO (13 * CLOCK_SECOND)

static int bro_period = 0;

PROCESS(comm_proc, "broadcast example");

AUTOSTART_PROCESSES(&comm_proc);

static void input_callback(const void *data, uint16_t len, const linkaddr_t *src, const linkaddr_t *dest) {
    char received_data[strlen((char *)data) + 1];
    if(len == strlen((char *)data) + 1) {
        memcpy(&received_data, data, strlen((char *)data) + 1);
        LOG_INFO("TIMESTAMP: %lu, Received \"%s\" from ", clock_seconds(), received_data);
        LOG_INFO_LLADDR(src);
        LOG_INFO_("\n");
    }
}

PROCESS_THREAD(comm_proc, ev, data) {
    static struct etimer broadcast_periodic_timer;
    static char bro_msg[70];
    sprintf(bro_msg, "Hello, I am an annoying spammer, time: %d", bro_period);

    PROCESS_BEGIN();
    
    nullnet_set_input_callback(input_callback);
    etimer_set(&broadcast_periodic_timer, SEND_INTERVAL_BRO);
    
    while(1) {
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&broadcast_periodic_timer));
        
        LOG_INFO("TIMESTAMP: %lu, Broadcasting \"%s\"\n", clock_seconds(), bro_msg);
        
        nullnet_buf = (uint8_t *)bro_msg;
        nullnet_len = strlen(bro_msg) + 1;
        
        NETSTACK_NETWORK.output(NULL);
        
        etimer_reset(&broadcast_periodic_timer);
        bro_period += 13;
    }
    
    PROCESS_END();
}
