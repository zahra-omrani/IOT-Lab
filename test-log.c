#include "contiki.h"
#include "os/sys/log.h"

PROCESS(test_log, "Test Log");
AUTOSTART_PROCESSES(&test_log);

PROCESS_THREAD(test_log, ev, data) {
    PROCESS_BEGIN();

    // Initialize the logging system
    log_init();

    // Set the log level to LOG_LEVEL_DBG to enable debug logs
    log_level_set(LOG_LEVEL_DBG);

    // Print debug log
    LOG_DBG("This is a debug log message\n");

    PROCESS_END();
}
