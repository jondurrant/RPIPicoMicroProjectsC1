# RPIPicoMicroProjectsC1
Source files for the Udemy course [Raspberry PI PICO Micro Projects (C++)](https://www.udemy.com/course/draft/4775268/?referralCode=2F48111FD8290C72D4C7).

Each folder contains a set of example projects for that section of the course:
- Section 2 Pico Setup
	- cJDBlink1
	- PicoWBlink
- Section 3 LED
	- JDBlinkExt
	- LEDBrightness
	- LEDFader
	- LEDSensor
	- RGBLEDAssign
- Section 4 WS2812B LEDs
	- RainbowWS2812B
	- RingAnimation
	- Animations
	- AssignmentChaserTail
- Section 5 Switch
	- PollLatchedLed
	- IntLatchedLed
	- AssignmentLongPress
- Section 6 Rotary Encoder
	- RotRing
	- AssignRotDial
- Section 7 PIR
	- PIRLED
	- PIRTimer
- Section 8 Project
	- LEDRingProject
	- LEDRIngTimer
	- ProjectAssignment
	
# Dependencies
1. Raspberry PI Pico SDK
2. [ForsakenNGS PicoLED Library](https://github.com/ForsakenNGS/PicoLED)

# Build Instructions
In each project folder:

	mkdir build
	cd build
	cmake ..
	make
	

