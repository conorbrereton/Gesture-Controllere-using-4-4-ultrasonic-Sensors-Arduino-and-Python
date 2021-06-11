import serial                                #Serial imported for Serial communication
import time                                  #Required to use delay functions
import pyautogui

ArduinoSerial = serial.Serial('com3',9600) #Create Serial port object called arduinoSerialData im using com port 3
time.sleep(2) #wait for 2 seconds for the communication to get established

while 1:
    incoming = str (ArduinoSerial.readline()) #read the serial data and print it as line
    print (incoming)
    
    if 'Play/Pause' in incoming:
        pyautogui.typewrite(['space'], 0.2)   # space function controlls pause and play

    if 'next' in incoming:                    # if incoming data is 'next'
        pyautogui.hotkey('ctrl', 'pgdn')           # perform "ctrl+pgdn" operation which moves to the next tab
        
    if 'previous' in incoming:                # if incoming data is 'previous'
        pyautogui.hotkey('ctrl', 'pgup')           # perform "ctrl+pgup" operation which moves to the previous tab

   
    if 'Volume Increased' in incoming:        # if incoming data is 'Volume Increased'
        pyautogui.hotkey('ctrl', 'down')            # performs "ctrl + down" which increases the Volume
        
    if 'Volume Decreased' in incoming:        # if incoming data is 'Volume Decreased'
        pyautogui.hotkey('ctrl', 'up')              # performs "ctrl + up" which Decreases the Volume

    

    if 'Rewind' in incoming:                   # if incoming data is 'rewind'
        pyautogui.hotkey('ctrl', 'left')           # performs "ctrl + left" operation which rewinds a video

    if 'Forward' in incoming:                   # if incoming data is 'Forward'
        pyautogui.hotkey('ctrl', 'right')           # performs "ctrl + right" operation which Forwards a video

    if 'mute' in incoming:                      # if incoming data is 'Mute'
         pyautogui.hotkey('m')                      # performs "m" operation which mutes a video

    if 'fullscreen' in incoming:                # if incoming data is 'Fullscreen'
        pyautogui.hotkey('f')                       # performs "f" operation which makes a video go fullscreen only works in youtube
    

    incoming = "";
    
