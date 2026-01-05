/**
 * @file mtestserver_watchdog.h
 * @author Julles
 * @brief  watchdog api for mtest
 * @version 1.0
 * @date 2024-10-28
 *
 * @History
 * @author Julles
 * @date 2025-04-30
 * @version 1.1
 * @Update Add function description, add wd_get_from_name function
 *
 * @History
 * @author Julles
 * @date 2025-09-01
 * @version 1.1.1
 * @Update Add version and optimize efficiency
 */


#ifndef MTESTSERVER_WATCHDOG_H
#define MTESTSERVER_WATCHDOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#ifdef _WIN32
#   ifdef MTESTSERVER_WATCHDOG_EXPORT
#       define WATCHDOG_API __declspec(dllexport)
#   else
#       define WATCHDOG_API __declspec(dllimport)
#   endif
#else
#   define WATCHDOG_API __attribute__ ((visibility("default")))
#endif

//watchdog

/**
 * create a watchdog
 * @param name variable name
 * @param accuracy millisecond precision, which indicates how often the watchdog's current value is written into a variable
 * @param wdv return the watchdog pointer
 * @return 0 success, otherwise error
 */
WATCHDOG_API int32_t wd_create(const char* name, int32_t accuracy, void** wdv);

/**
 * remove a watchdog
 * @param wdv watchdog pointer
 * @return 0 success, otherwise error
 */
WATCHDOG_API int32_t wd_remove(void* wdv);

/**
 * read watchdog current value
 * @param wdv watchdog pointer
 * @param timeCount current value
 * @return 0 success, otherwise error
 */
WATCHDOG_API int32_t wd_read_time(void *wdv, uint32_t *timeCount);

/**
 * reset watchdog
 * @param wdv watchdog pointer
 * @param reset 1 is reset, 0 is not reset
 * @return 0 success, otherwise error
 */
WATCHDOG_API int32_t wd_reset(void *wdv, uint8_t reset);

/**
 * read watchdog variable name
 * @param wdv watchdog pointer
 * @param name watchdog variable name, buffer size is 128
 * @return 0 success, otherwise error
 */
WATCHDOG_API int32_t wd_read_name(void *wdv, char *name);

/**
 * read watchdog accuracy
 * @param wdv watchdog pointer
 * @param accuracy watchdog accuracy
 * @return 0 success, otherwise error
 */
WATCHDOG_API int32_t wd_read_accuracy(void *wdv, uint32_t *accuracy);

/**
 * get watchdog pointer by name
 * @param name variable name
 * @param wdv watchdog pointer
 * @return 0 success, otherwise error
 */
WATCHDOG_API int32_t wd_get_from_name(const char *name, void **wdv);

//watchdogVarDaemon

/**
 * init watchdog daemon
 * @param con variable container pointer
 * @return 0 success, otherwise error
 */
WATCHDOG_API int32_t wd_init(void *con);

/**
 * free watchdog daemon
 * @return 0 success, otherwise error
 */
WATCHDOG_API int32_t wd_free();

/**
 * update all watchdog variable value
 * @return 0 success, otherwise error
 */
WATCHDOG_API int32_t wd_write_var();

/**
 * get current watchdog size
 * @param size watchdog size
 * @return 0 success, otherwise error
 */
WATCHDOG_API int32_t wd_get_size(uint32_t *size);

/**
 * test
 */
WATCHDOG_API void wd_say_hello();

#ifdef  __cplusplus
}
#endif

#endif //MTESTSERVER_WATCHDOG_H
