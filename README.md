crackmonkey's Arduino libs
==========================

This is the collection of libraries for Arduino that I have either written myself or forked and tweaks for my own amusement

Originals
---------
* AnySerial: I needed a clean way to send notifications to multiple UARTs without duplicating all the Serial.printlns as Serial1.printlns, so I made this. It also mixes input which I use to read command from either port, either the USB CDC "UART" for testing, or the hardware Serial1 on my ProMicro(atmega32u4) talking to the RN52 BlueTooth module for real use
* RN52: A simple wrapper to send commands to the RN-52 Bluetooth module. It handles the nitty-gritty of getting the module into and out of command mode so the main sketch only has to use btmodule.play()/answer()/hangup() to get the appropriate AVRCP or HFP events sent. 

Forks
-----
* MMA8452Q: The best library I could find for the MMA8452Q acceleromter was in a GitHub GIST, so I cloned it and made a few tweaks to work for me. The overwhelming majority of the work belongs to Alessandro Ghedini, and if he has a maintained version on GitHub or otherwise I'd love to know.
* HH10D: I swiped some code to drive the HH10D humidity sensor from Semyon Tushev and repacked it as a library instead of a sketch
