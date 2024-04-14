#include "contiki.h"
#include <stdio.h>
#include "os/dev/serial-line.h"
#include "dev/leds.h" // Include the header file for LEDs

PROCESS(test_LED,"Test LED");
AUTOSTART_PROCESSES(&test_LED);

PROCESS_THREAD(test_LED,ev,data)
{
  PROCESS_BEGIN();
 

  while (1){
    PROCESS_WAIT_EVENT_UNTIL(ev == serial_line_event_message);
    printf("Received: %s\n", (char *)data);
    fflush(stdout); // Flush the output buffer
    if(strcmp((char *)data, "GREEN") == 0){ // Compare the received message with "GREEN"
      leds_toggle(LEDS_NUM_TO_MASK(LEDS_GREEN));
    }
  }

  PROCESS_END();
}
