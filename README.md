# model_crossing_industrial
A basic rail crossing for low speeds, controlled by arduino code
It is made for Raspberry pi Pico

## Requrements / Optional
Optional: Raspberry pi Pico

    If used with arduino change these:
    
    - pinMode(XXX,  INPUT_PULLDOWN); to pinMode(XXX,  INPUT);
    
    also you may need to put a resistor see:
    
    https://docs.arduino.cc/built-in-examples/digital/Button/

### Requierd
If used with Raspberry pi Pico setup Arduino IDE
    https://arduino-pico.readthedocs.io
    https://github.com/earlephilhower/arduino-pico

### Library needed
https://github.com/theeal/SimRealy


# How to connect
## Trackdetections
![Track sections](https://github.com/theeal/model_crossing_industrial/blob/main/over_wiev.png)

 
The trackdetection is activly free (1) and will be (0) when trains occupy

## Local Manuver
Br1 Bells
Br2 Activate Crossing (starts to blink and sound

## Outputs
WarnRi Warning Car Right (flashing)
WarnLe Warning Car Left  (flashing)
Bells  Sound / Bells

VSiWh  Train Signal white (proceed)
VSiRe  Train Signal red   (Stop)

# Logic
[!NOTE]
Logic will soon be added
<!--
  Vv = Br2 || (Iv && IIv || Akv && Sv) && (Vv || Sv)
 #Vv relay off delayed

  Br2     Iv      IIv     Vv      Vv
--| |--+--| |-----| |--+--| |--+--( )--
       |               |       |
	   |  Akv     Sv   |  Sv   |
	   +--| |-----| |--+--| |--+

  Akv = (!Iv && IIv || Iv && !IIv) && (!Sv || Akv)

  Iv      IIv     Sv      Akv
--|/|-----| |--+--|/|--+--( )--
               |       |
  Iv      IIv  |  Akv  |
--| |-----| |--+--| |--+


  VSiRe = (!(!Akv || !Sv) && !Vv)
  VSiWh = !Akv || !Sv) && !Vv

  Akv     Vv      VS
--| |--+--|/|-----( )--
       |
  Sv   |
--| |--+


VarnRi = (!Vv && blink(bl80,80)
VarnLe = (!Vv && !blink(bl80,80)

  Vv     Bl80    VarnRi
--|/|--+--| |-----( )--
       |
       | Bl80    VarnLe
       +--|/|-----( )--


  Bells = !Vv && Br1
  Vv      Br1    Bells
--|/|-----|/|-----( )--
-->
