/**
 * @file mtestserver_watchdog.hpp
 * @brief C++ wrapper for the Watchdog C library
 *
 * This header provides a C++ wrapper class for the Watchdog C library,
 * making it easier to use in C++ applications with automatic memory
 * management and object-oriented interface.
 *
 * @par Example Usage:
 * @code
 * // Initialize the watchdog system (required when not running in mtest environment)
 * void* container;
 * create_container(&container);
 * wd_init(container);
 *
 * // Create and use watchdogs
 * ServerWatchdog watchdog;
 * watchdog.Create("my_watchdog", 100);
 *
 * // Periodically reset the watchdog to prevent it from triggering
 * watchdog.Reset();
 *
 * // Periodically call wd_write_var to write watchdog values to variables (required when not running in mtest environment)
 * wd_write_var();
 *
 * // Get current watchdog time
 * uint32_t time = watchdog.ReadTime();
 *
 * // Cleanup (required when not running in mtest environment)
 * wd_free();
 * free_container(container);
 * @endcode
 *
 * @note When running outside of the mtest environment, you must call wd_init() once
 *       at the beginning of your program and wd_free() at the end to properly
 *       initialize and cleanup the watchdog system. Additionally, you should
 *       periodically call wd_write_var() to write watchdog values to variables.
 *
 *
 * @author Julles
 * @date 2025-09-17
 * @version 1.0.0
 *
 * @copyright ITIMotor Copyright (c) 2025
 */

#pragma once

#include <string>

#include "mtestserver_watchdog.h"

/**
 * @class ServerWatchdog
 * @brief C++ wrapper class for the Watchdog C library
 *
 * Provides object-oriented interface for the Watchdog C library with
 * automatic resource management using RAII principles. Each instance
 * represents an independent watchdog object.
 */
class ServerWatchdog {
public:
    /**
     * @brief Default constructor
     *
     * Initializes an empty watchdog object without creating actual watchdog resources.
     */
    ServerWatchdog() = default;

    /**
     * @brief Constructor with name and accuracy
     *
     * Creates a new watchdog instance with the given name and accuracy.
     *
     * @param name The name of the watchdog
     * @param accuracy_ms The accuracy in milliseconds (default: 10)
     */
     explicit ServerWatchdog(const std::string &name, int accuracy_ms = 10) { Create(name, accuracy_ms); }

    /**
     * @brief Delete copy constructor
     *
     * Prevents copying of watchdog objects to avoid double-free issues
     * and resource ownership conflicts.
     */
    ServerWatchdog(const ServerWatchdog &) = delete;

    /**
     * @brief Delete copy assignment operator
     *
     * Prevents copying of watchdog objects to avoid double-free issues
     * and resource ownership conflicts.
     */
    ServerWatchdog &operator=(const ServerWatchdog &) = delete;

    /**
     * @brief Move constructor
     *
     * Transfers ownership of the watchdog resource from another object.
     *
     * @param other The source object to move from
     */
    ServerWatchdog(ServerWatchdog &&other) noexcept: wd(other.wd) { other.wd = nullptr; }

    /**
     * @brief Move assignment operator
     *
     * Transfers ownership of the watchdog resource from another object.
     * Properly releases the current resource before taking ownership.
     *
     * @param other The source object to move from
     * @return Reference to this object
     */
    ServerWatchdog &operator=(ServerWatchdog &&other) noexcept {
        if (this != &other) {
            if (wd && wd != other.wd)
                wd_remove(wd);
            wd = other.wd;
            other.wd = nullptr;
        }
        return *this;
    }

    /**
     * @brief Destructor
     *
     * Automatically releases the watchdog resource when the object is destroyed.
     * Ensures proper cleanup using RAII principles.
     */
    ~ServerWatchdog() {
        if (wd) {
            wd_remove(wd);
            wd = nullptr;
        }
    }

    /**
     * @brief Create a new watchdog with the specified name and accuracy
     *
     * Creates a new watchdog instance with the given parameters.
     * If a watchdog with the same name already exists, both will exist at the same time,
     * the variable values may change alternately,
     * and it can be checked if it already exists by calling the CheckExits function.
     *
     * @param name The name of the watchdog
     * @param accuracy_ms The accuracy in milliseconds (default: 10)
     */
    void Create(const std::string &name, int accuracy_ms = 10) {
        if (wd) {
            wd_remove(wd);
            wd = nullptr;
        }
        if (name.empty()) return;
        wd_create(name.c_str(), accuracy_ms, &wd);
    }

    /**
     * @brief Read the current time of the watchdog
     *
     * Retrieves the current time value from the watchdog.
     *
     * @return The current time value of the watchdog
     */
    uint32_t ReadTime() {
        uint32_t time{};
        wd_read_time(wd, &time);
        return time;
    }

    /**
     * @brief Reset the watchdog
     *
     * Resets the watchdog timer to prevent it from triggering.
     */
    void Reset() { wd_reset(wd, 1); }

    /**
     * @brief Check if a watchdog with the specified name exists
     *
     * Queries whether a watchdog with the given name already exists.
     *
     * @param name The name to check
     * @return true if a watchdog with the given name exists, false otherwise
     */
    static bool CheckExits(const std::string &name) {
        void *wd{};
        wd_get_from_name(name.c_str(), &wd);
        return wd != nullptr;
    }

    /**
     * @brief Get the total number of watchdogs
     *
     * Returns the current count of all active watchdogs.
     *
     * @return The number of active watchdogs
     */
    static uint32_t Size() {
        uint32_t size{};
        wd_get_size(&size);
        return size;
    }

private:
    /**
     * @brief Pointer to the underlying C watchdog structure
     *
     * Holds the pointer to the actual watchdog resource managed by the C library.
     */
    void *wd{};
};
