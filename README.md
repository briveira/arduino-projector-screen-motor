# arduino-projector-screen-motor

This little project allows you to motorize/automate a projector screen with an IR remote. I actually use an Ikea white shade instead of a real project screen. 

This goes like this: using an IR remote, you press down, the screen goes down using the stepper motor; you press up, the screen goes up. I also light a led while the motor is working just as an added visual feedback that the remote order got heard. 

I used:

- an Arduino nano (you can use any kind of arduino)
- a stepper motor (28BYJ-48) and motor shield (ZC-A0591); connected to pins D8-D11
- an infrared reveicer (connected to D3 pin)
- a led and appropiate resistance (connected to D2)
- an infrared remote to move up & down the screen ()

This pieces came from the typical arduino sensor kit (even the remote). Of course you will also need a power source. 

Customization:

- you will have to edit the project at least to specify the "posStepperPantallaBajada" value, which depends on the lenght of your screen (it is the amount of steps/degrees to move down/up the screen

- if you're lucky and have the same remote as me (a NEC protocol one), you could use the DOWN/UP values to detect the exact keys pressed on the remote; if not, you will need to change these to the correct ones (you can find examples of how to do this all over internet, like in https://www.hackster.io/tech-duino/finding-the-ir-codes-of-any-ir-remote-using-arduino-c7a852):

#define IR_ABAJO 0xfd10ef
#define IR_ARRIBA 0xfd50af
