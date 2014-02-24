Arduino-K3M-Controller
======================

An Arduino project to create and manipulate sounds from a Kawai K3M synthesizer !


My brother (Electronician and amateur musician) wanted to create a controller for his K3M's synthesizers, as the beast could be quite a pain to play with, so here it is.


Disclaimer (more like, Notes, really :P)
----------------------------------------

- I am no expert in C/C++, it was a fun project, and i did it the way i programm usually, i am used to OO so that's why the code is more OO than procedural
- This version is not optimal, i have another version that removes lags in midi signals, and of course code could be much better
- This one use the T6963 LCD controller, which, while being graphical, is a pain when it comes to character encoding and types (that's why there is a utility part)
- LCD can be optional, but the software must be modified against it
- The full sysEx messages is **NOT** included, this code is WIP to control a maximum of 24 potentiometers/switches and there are like 60ish sysEx messages
- It may be adapted for other old synthesizer working in sysEx only
- There shall be no memory leak, also this has been tested on a MEGA 2560 (and otherwise unit testing on Arduino is quite difficult)

The project is shared as is, fork it away if you are interested !! but it's just something i did on my free time i do not intend to improve it any more.

I may release another version though (the one more stable/optimized) as another branch sometimes ! In the mean time, happy hacking !!!

Thanks to @regisf for his invaluable inputs on some memory/optimization tricks !

Licence
=======

Released under ([MIT](LICENSE)) license.
