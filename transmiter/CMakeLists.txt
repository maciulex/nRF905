add_executable(transmiter
        transmiter.cpp
    )

pico_enable_stdio_usb(transmiter 1)
pico_enable_stdio_uart(transmiter 0)

target_link_libraries(transmiter pico_stdlib hardware_spi)
pico_add_extra_outputs(transmiter)