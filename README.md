Bioloid_ProbingRobot
====================

C implementation of the Robotis taskfile to control the Bioloid Probing Robot model.

This was a three day hacking project to run the Probing Robot model using C. Many features are not implemented like checking battery values, buttons or using LEDs.

Warning: The code is hacked together and is for sure not the most elegant way to do it, The aim was to learn accessing the actators/sensors and to finish within 3 days.


o Requirements:

- avr-gcc
- robotis Bioloid embedded C library ()


o Building:

- first install the robotis embedded library in your working dir
- clone the Bioloid_ProbingRobot git repo into your working dir
- cd into the Bioloid_ProbingRobot
- build the firnmware by running
    make

o Installation

- connect your cm510 with serial cable to the usb2serial adapter that came with it
- start a serial terminal application like robotis terminal on windows or gtkterm on linux
- set speed to 57600
- hold the # key pressed in th terminal
- turn on the cm510
- the bootloader screen will appear, accepting input
- type 'ld' and hit <enter>
- select the built Bioloid_ProbingRobot.hex file for robotis terminal,
 Bioloid_ProbingRbot.bin for gtkterm
- the file will be transfered to the cm510
- when done, power the robot of and on again - it should start behaving as with the default robotis task file for that model
