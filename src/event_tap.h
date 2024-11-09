#ifndef SKHD_EVENT_TAP_H
#define SKHD_EVENT_TAP_H

#include <stdbool.h>
#include <Carbon/Carbon.h>

struct lcmd_state {
    uint64_t last_press_time;     // Time of last press
    uint64_t last_release_time;   // Time of last release
    int press_count;              // Number of presses in sequence
    bool is_pressed;              // Current press state
};

struct event_tap
{
    CFMachPortRef handle;
    CFRunLoopSourceRef runloop_source;
    CGEventMask mask;
    struct lcmd_state lcmd;
};

#define EVENT_TAP_CALLBACK(name) \
    CGEventRef name(CGEventTapProxy proxy, \
                    CGEventType type, \
                    CGEventRef event, \
                    void *reference)
typedef EVENT_TAP_CALLBACK(event_tap_callback);

bool event_tap_enabled(struct event_tap *event_tap);
bool event_tap_begin(struct event_tap *event_tap, event_tap_callback *callback);
void event_tap_end(struct event_tap *event_tap);

#endif
