add_executable(${NAME}
        main.cpp
        RingChaser.cpp
        RingAnimation.cpp
        TriTurn.cpp
        DialUpDown.cpp
        RotEncAgent.cpp
        RotEncObserver.cpp
        AnimationsCtr.cpp
        SwitchMgr.cpp
        SwitchObserver.cpp
        ColourPicker.cpp
        )

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(${NAME} pico_stdlib PicoLed)

# create map/bin/hex file etc.
pico_add_extra_outputs(${NAME})

# enable usb output, disable uart output
pico_enable_stdio_usb(${NAME} 1)
pico_enable_stdio_uart(${NAME} 0)