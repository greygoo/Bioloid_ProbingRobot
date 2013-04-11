Bioloid_ProbingRobot
====================

C implementation of the Robotis taskfile to control the Bioloid Probing Robot model.

This was a three day hacking project to run the Probing Robot model using C. Many features are not implemented like checking battery values, buttons or using LEDs.

Warning: The code is hacked together and is for sure not the most elegant way to do it, The aim was to learn accessing the actators/sensors and to finish within 3 days.

Installation:

You'll need to have avr-gcc installed to compile. To build, simply run

   make

This will produce a .hex and a .bin file. You can flash those to the cm510 controller of you Robot using teh Robotis terminal or any other terminal like e.g. gtkterm. Please not that with gtkterm you might only be able to flash the .bin file.
