#include "contiki.h"
#include <stdio.h>
#include "os/dev/serial-line.h"
#include "usb/usb-serial.h"

PROCESS(serial_line_test, "Test serial line");
AUTOSTART_PROCESSES(&serial_line_test);

PROCESS_THREAD(serial_line_test, ev, data)
{
    PROCESS_BEGIN();

    // Initialize USB serial
    usb_serial_init();
    usb_serial_set_input(serial_line_input_byte);

    while (1) {
        PROCESS_WAIT_EVENT_UNTIL(ev == serial_line_event_message);
        printf("Received: %s\n", (char *)data);
        fflush(stdout); // Flush the output buffer
    }

    PROCESS_END();
}