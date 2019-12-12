# Arduino-MIDI-Keyboard
Read distance from a ultrasonic sensor, send MIDI through MIDI-USB and play MIDI on computer.

![image](https://github.com/AzulRadio/Arduino-MIDI-Keyboard/blob/master/Resource/Lookslikethis.jpg)

**Making this keyboard is way much harder than I expected, so I upload my project and code. Hopefully it can help more people.**

## You need:
### Hardware:
+ Arduino UNO or RedBoard
+ MIDI-USB Cable
+ Analog sensor(I use Ultrasonic sensor here)
+ Resistor and Capacitor(Optional)
+ Sparkfun MIDI shield
### Software:
+ MIDI library by Forty Seven Effect https://github.com/FortySevenEffects/arduino_midi_library (If you don't know how to use Arduino Lib, use google)
+ FL Studio (To play MIDI on the computer) 
+ Hairless MIDI https://projectgus.github.io/hairless-midiserial/
+ loopMIDI https://www.tobias-erichsen.de/software/loopmidi.html

## Set up:
**After several weeks of woe and pain, here's the only way for a Arduino UNO to send MIDI to the computer:**
1. Load the program in to the Arduino and make sure it's sending MIDI out.

2. In loopMIDI, create a new port.

3. Open hairless-midi, set both MIDI IN and MIDI OUT to loopMIDI, check the Serial<->MIDI Bridge box and the light should tell you if there's signal going through.

4. Then In FL Studio, Go to Options -> MIDI setting and set your MIDI loop port. I forgot how did I set up. Try to find tutorials and common sense. It shouldn't be hard. When you hear sounds, you made it!

5. To change instruments, use channelrack in FL Studio. 
![image](https://github.com/AzulRadio/Arduino-MIDI-Keyboard/blob/master/Resource/channelracktutorial.png)


### WARNING: Arduino can't load any program with the Serial<->MIDI Bridge box checked in hairless-midi! Uncheck it before load programs!

![image](https://github.com/AzulRadio/Arduino-MIDI-Keyboard/blob/master/Resource/Circuit.png)


### How to make your own version
If you try to use a different sensor, just change the read_keyboard_value() in the program, and change pins accordingly.
Good luck and have fun.
