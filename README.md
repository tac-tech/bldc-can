BLDC-CAN Library
========================================

Library to make remote control of the VESC easy on a linux computer equiped with a CAN device (SocketCAN).

Use make to build project

VS Code configured for testing and debug

Install instructions
----------------------------------------
1. cd into project directory
2. run make
3. cd build
4. run test programs:
⋅⋅* ./testspeed
⋅⋅* ./testduty
⋅⋅* ./bldclog can0 1.log 6

Clean build folder
----------------------------------------
1. cd into project directory
2. run make clean

Run or debug from VS Code
----------------------------------------
Go to testspeed.c or testduty.c and press <F5>

