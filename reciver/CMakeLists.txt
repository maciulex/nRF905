add_executable(reciver
        reciver.cpp
    )

pico_enable_stdio_usb(reciver 1)
pico_enable_stdio_uart(reciver 0)

target_link_libraries(reciver pico_stdlib hardware_spi)
pico_add_extra_outputs(reciver)