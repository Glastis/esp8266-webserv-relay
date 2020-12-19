cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME esp_relais_wifi)

set(${PROJECT_NAME}_BOARD leonardo)
# set(ARDUINO_CPU)
project(${PROJECT_NAME})


include_directories(${PROJECT_NAME} PRIVATE "C:/Users/glastis/AppData/Local/Arduino15/packages/esp8266/hardware/esp8266/2.7.4/libraries/ESP8266WiFi/src")
include_directories(${PROJECT_NAME} PRIVATE "C:/Users/glastis/AppData/Local/Arduino15/packages/esp8266/hardware/esp8266/2.7.4/cores/esp8266")

### Additional static libraries to include in the target.
set(${PROJECT_NAME}_LIBS "C:/Users/glastis/AppData/Local/Arduino15/packages/esp8266/hardware/esp8266/2.7.4/libraries/ESP8266WiFi")

add_executable(${PROJECT_NAME}2
        esp_relais_wifi.ino         main.h
        wifi.cpp                    wifi.h
        router.cpp                  router.h
        request.cpp                 request.h
        relay.cpp                   relay.h
        utilities.cpp               utilities.h

        wifi_pass.h
        constants.h
        )


### Main sketch file
set(${PROJECT_NAME}_SKETCH esp_relais_wifi.ino)

### Add project directories into the build
# add_subdirectory()

### Additional settings to add non-standard or your own Arduino libraries.
# For this example (libs will contain additional arduino libraries)
# An Arduino library my_lib will contain files in libs/my_lib/: my_lib.h, my_lib.cpp + any other cpp files
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/)

# For nested library sources replace ${LIB_NAME} with library name for each library
# set(_RECURSE true)

#### Additional settings for programmer. From programmers.txt
set(${PROJECT_NAME}_PROGRAMMER avrispmkii)
set(${PROJECT_NAME}_PORT COM3)
set(leonardo.upload.speed 115200)

## Verbose build process
set(${PROJECT_NAME}_AFLAGS -v)

generate_arduino_firmware(${PROJECT_NAME})


print_board_list()
print_programmer_list()
