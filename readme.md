# Solis Hyperion V5 Auxiliary Control Module

## This module operates the auxiliary electronics on the car.


Devices which are commanded by this module are:
- Horn 
- Battery fan 
- Signal lights
- Taillight 
- Front light 
- Camera



Besides auto-generated code this module is split in 4 main sections (/Core/Src/tasks)
### 1. loop.c (/Core/Src/Tasks/loop.c)  
This routine serves the purpose of a heathbeat which simply blinks an LED every 1s to show that the module is working corectly.
The LED is connected to GPIO_PIN_0.

### 2. control.c (/Core/Src/Tasks/control.c)  
This is the main control routine of the module.
The state of the module is stored in the 'auxiliary' struct:
```
    typedef union
{
    uint8_t state;
    struct
    {
        uint8_t sign_left  : 1; // 0x01
        uint8_t sign_right : 1; // 0x02
        uint8_t fan        : 1; // 0x04
        uint8_t brake      : 1; // 0x08

        uint8_t horn       : 1; // 0x10
        uint8_t avarie     : 1; // 0x20
        uint8_t camera     : 1; // 0x30
        uint8_t faruri     : 1; // 0x80
    };
} aux_state;
```

The module operates in two modes:
- Offline mode  
        This mode is active if there is no data recieved from the dash for 5.6s or more or if it manually switched on.
        The behaviour of this mode is to simply control the devices according to how the switchpanel is set.
        It uses separate GPIO pins from the online mode.

- Online mode  
This mode uses the data read from the dashboard module and sets the GPIO pins accordingly to the 'auxiliary' struct.

There are two timers which help manage this section:
- Timer2 (every 56ms):
    This timer sets the correct operating mode of the module (offline or online)
        
- Timer3 (every 76ms):
        This timer handles the main event loop. It is also responsible for handling the logic for the signal lights, synchronizing the hazard lights and performing the other commands from the control unit.
  
### 3. can_recieve.c 
This routine enables online mode by reading data from the dashboard module and saving it into the 'auxilary' struct.
When data is recieved it also resets the Dash_Activity counter. Received messages are also filtered to only permit command messages from the control unit.

### 4. can_transmit.c
This routine simply sends a message to the dashboard module every 50 ms so it knows the auxiliary module is online.




