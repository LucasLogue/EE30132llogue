Firstly, I've added minmea from previous kinda working hwrk3, which should be fine
However, I now need to update my root CMakeLists to include this

!!! I'm linking minmea as a submodule, so it'll be downloaded from their main repository.
!!! However I changed the CMakeLists.txt to one provided by Prof Howard that makes it work more easily with our project. Here it is
//////////
add_library(minmea STATIC)
target_sources(minmea
    PRIVATE
        minmea.c
    PUBLIC
        minmea.h
)

target_include_directories(minmea PUBLIC .)
target_compile_options(minmea PRIVATE -Wall -Wextra -std=c99)
target_compile_definitions(minmea PRIVATE _POSIX_C_SOURCE=199309L timegm=mktime)
///////////

holy fuck it finally worked!

$GNVTG,,T,,M,1.799,N,3.331,K,A*39
$GNGGA,024923.00,4141.73671,N,08613.40171,W,1,05,3.02,206.6,M,-34.0,M,,*79
[GPS] time=02:49:23 lat=41.695610 lon=-86.223358                                <----- right here!
$GNGSA,A,3,01,30,14,22,17,,,,,,,,5.43,3.02,4.51,1*03
$GNGSA,A,3,,,,,,,,,,,,,5.43,3.02,4.51,3*00
$GNGSA,A,3,,,,,,,,,,,,,5.43,3.02,4.51,5*06
$GPGSV,2,1,08,01,40,057,23,02,20,044,19,03,14,107,13,14,79,073,12,1*6F
$GPGSV,2,2,08,17,74,295,21,19,42,257,18,22,72,330,14,30,37,191,13,1*6F
$GPGSV,1,1,02,06,15,198,,07,09,167,,0*6B
$GAGSV,1,1,00,0*74
$GQGSV,1,1,00,0*64
$GNGLL,4141.73671,N,08613.40171,W,024923.00,A,A*60
