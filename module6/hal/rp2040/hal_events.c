#include "hal_events.h"
#include "hardware/sync.h"

void hal_events_wait(void){
    __wfe(); //M6: "wait for event" core stops until interrupt becomes pending or event signalled
}

void hal_events_signal(void){
    __sev(); //M6:"send event" sets a hardware event register
             //if sev happens before wfe, event register set so wfe returns immediately
             //instead of sleeping thru wakeup
}
