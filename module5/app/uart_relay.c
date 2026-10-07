#include "uart_relay.h"
#include <stdio.h>
#include "hal_timer.h"
#include "hal_gpio.h"
#include "hal_uart.h"

#include "minmea.h"

//typedef struct {
//    hal_gpio_id_t heartbeat; //time interval led
//    hal_gpio_id_t activity; //event occurence led
//    uint32_t period_ms; //time interval
//    uint32_t activity_idle_ms; //time window where activity led on
//} uart_relay_config_t;
//

/// @brief parses one complete NMEA sentence and prints the relevant selected fields
static void nmea_report(const char *sentence){ //since static doesnt go the .h
    switch (minmea_sentence_id(sentence, false)){ //tells us what sentence type it is, and false says no checksum if not needed
        case MINMEA_SENTENCE_GGA:{ //this is the sentence that would provide all the info we need for the assignment
            struct minmea_sentence_gga frame;
            if ((!minmea_parse_gga(&frame, sentence)) || (frame.fix_quality == 0)){ //so this frame structure type shi we tryna parse and fill it from sentence
                                                                                    //fix quality is when the satellite quality is shit and the sentence has no useful info
                //so if we couldnt parse or shit quality we returning nothing
                return;
            }
            float lat = minmea_tocoord(&frame.latitude);
            float lon = minmea_tocoord(&frame.longitude);
            if((!isfinite(lat)) || !isfinite(lon)){ return; } //if lat or lon nan return since its boofed
            //but if we've made it here then we're good to go, so print out the information
            printf("[GPS] time=%02d:%02d:%02d lat=%.6f lon=%.6f\n",
                   frame.time.hours,
                   frame.time.minutes,
                   frame.time.seconds,
                   lat,
                   lon);
            break;
        } default: break;} //end of the switch
} //nmea_report end

//Since we've just added nmea_report, which will take a sentence, we'll need to make changes to
//declare the string, and locate the end of the sentence '\0' or a newline char '\n'
void uart_relay_run(const uart_relay_config_t *cfg){
    hal_gpio_init(cfg->heartbeat);
    hal_gpio_init(cfg->activity);
    // initialize the heartbeat and activity leds
    // presumably heartbeat = HAL_WHITE_LED and the RED led somewhere
    hal_uart_init();
    //M5: keep these guys, gpio and uart init still the same

    uint64_t next_us = hal_timer_get_time_us() + (uint64_t)cfg->period_ms * 1000;
    //M5: we're now initializing without counting the init as activity, so initializing to 0
    //this will let us see when we've started taking characters after launch, but really it didnt make sense before either
    //since we initialized the red to 0 anyways...
    uint64_t activity_until_us = 0;
        //hal_timer_get_time_us() + (uint64_t)cfg->activity_idle_ms * 1000;
    //scale 32 bit ms values to 64bit microsecs
    
    //M5: we now need to be storing a string, to send to NMEA report 
    char line[MINMEA_MAX_SENTENCE_LENGTH]; //maybe wasteful, but its embedded so no malloc
    size_t line_len = 0; //keep track of where we are in string
   
    while(true){ //essentially 
        while(hal_uart_is_readable()){
            //M5: since the nmea_report takes an entire sentence, and we need to detect newline and end of line
            //we need to save the char for logic
            char c = hal_uart_getc();
            putchar(c); //put the char into the stdout M5: still, might comment out at some point
            if(c == '\n'){//newline
                line[line_len] = '\0'; //terminate line for nmea
                nmea_report(line);
                line_len = 0; //reset index
            } else if((c != '\r') && (line_len < (sizeof(line) - 1u))){ //if line hasn't been dropped, the '\r' case
                                                                        //and our string has space, aka the current position isn't before the last position
                                                                        //which is reserved for null terminator
                line[line_len] = c;
                line_len++;
            }else { //for the dropped '\r' or filled string cases or anything else that mightve gone wrong
            }
            //still marking activity and setting red light on interval
            hal_gpio_set(cfg->activity, true); //set activity led on
            activity_until_us = hal_timer_get_time_us() + (uint64_t)cfg->activity_idle_ms * 1000;
        }
        //if the red led interval has ended, turn it off
        if(hal_timer_get_time_us() >= activity_until_us){
            hal_gpio_set(cfg->activity, false);
        }
        //keep white_led heartbeat pulsing
        if(hal_timer_get_time_us() >= next_us){
            bool h_state = hal_gpio_get(cfg->heartbeat);
            hal_gpio_set(cfg->heartbeat, !h_state);
            next_us = hal_timer_get_time_us() + (uint64_t)cfg->period_ms * 1000U;
        }
    }
}


