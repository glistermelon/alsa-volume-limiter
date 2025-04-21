cmake_minimum_required(VERSION 3.10)
project(AlsaVolumeLimiter C)

set(CMAKE_C_STANDARD 11)

find_package(ALSA REQUIRED)

find_path(CONFIG_INCLUDE_DIR NAMES libconfig.h PATHS /usr/include /usr/local/include)
find_library(CONFIG_LIBRARY NAMES config PATH /usr/lib /usr/local/lib) 

add_executable(
    alsa-volume-limiter
    src/service.c
    src/conf.c
)
target_include_directories(alsa-volume-limiter PRIVATE ${ALSA_INCLUDE_DIRS} ${CONFIG_INCLUDE_DIR})
target_link_libraries(alsa-volume-limiter ${ALSA_LIBRARIES} ${CONFIG_LIBRARY})

add_executable(
    alsa-volume-limiter-config
    src/set_limit.c
    src/conf.c
)
target_include_directories(alsa-volume-limiter-config PRIVATE ${ALSA_INCLUDE_DIRS} ${CONFIG_INCLUDE_DIR})
target_link_libraries(alsa-volume-limiter-config ${ALSA_LIBRARIES} ${CONFIG_LIBRARY})