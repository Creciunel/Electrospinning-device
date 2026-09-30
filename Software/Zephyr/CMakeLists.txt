cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(Electrospinning_device)

target_include_directories(app PRIVATE include)

target_sources(app PRIVATE
    src/main.c
    src/core0_comms.c
    src/core1_control.c
    lib/cli_shell/cli_shell.c
    src/display_task.c
)