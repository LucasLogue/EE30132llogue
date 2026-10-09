#ifndef HAL_EVENTS_H
#define HAL_EVENTS_H
//M6:
/// @brief Puts the CPU to sleep until an event occurs: an interrupt, or an
///        explicit hal_events_signal(). Returns as soon as that happens.
void hal_events_wait(void);

/// @brief Sets the CPU event register so a core waiting in hal_events_wait()
///        wakes up. Safe to call from an interrupt handler.
void hal_events_signal(void);
#endif // HAL_EVENTS_H
