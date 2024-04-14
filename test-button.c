#include "contiki.h"
#include "os/dev/button-hal.h"
#include "dev/leds.h" // Include the header file for LEDs
#include <stdio.h>
#include <string.h>

PROCESS(button_test, "test_button");
AUTOSTART_PROCESSES(&button_test);

PROCESS_THREAD(button_test, ev, data) {
    button_hal_button_t *btn; // Pointer to the button

    PROCESS_BEGIN();

    btn = button_hal_get_by_index(0); // Returns the button of index 0, since we only have one button
    printf("Device button count: %u.\n", button_hal_button_count); // Counts the number of buttons

    if(btn) { // Prints all the information about the button
        printf("%s on pin %u with ID=0, Logic=%s, Pull=%s\n",
            BUTTON_HAL_GET_DESCRIPTION(btn), btn->pin,
            btn->negative_logic ? "Negative" : "Positive",
            btn->pull == GPIO_HAL_PIN_CFG_PULL_UP ? "Pull Up" : "Pull Down");
    }

    while(1) {
        PROCESS_YIELD();
        if(ev == button_hal_press_event) {
            btn = (button_hal_button_t *)data; // In the data field there is a pointer to the button
            // Turn on the yellow LED
            leds_on(LEDS_BLUE);
            printf("Press event (%s)\n", BUTTON_HAL_GET_DESCRIPTION(btn));
        }
        if(ev == button_hal_release_event) {
            btn = (button_hal_button_t *)data; // In the data field there is a pointer to the button
            // Turn off the yellow LED
            leds_off(LEDS_BLUE);
            printf("Release event (%s)\n", BUTTON_HAL_GET_DESCRIPTION(btn));
        }
    }

    PROCESS_END();
}
