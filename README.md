# model_crossing_industrial
A basic rail crossing for low speeds, controlled by arduino code
It is made for Raspberry pi Pico

## Requrements / Optional
Optional: Raspberry pi Pico<br />
    If used with arduino change these:<br />
    - pinMode(XXX,  INPUT_PULLDOWN); to pinMode(XXX,  INPUT);<br />
    also you may need to put a resistor see:<br />
    https://docs.arduino.cc/built-in-examples/digital/Button/

### Requierd
If used with Raspberry pi Pico setup Arduino IDE<br />
    https://arduino-pico.readthedocs.io<br />
    https://github.com/earlephilhower/arduino-pico<br />

### Library needed
https://github.com/theeal/SimRealy

# How to connect
## Trackdetections
![Track sections](https://github.com/theeal/model_crossing_industrial/blob/main/over_wiev.png)<br />
The trackdetection is activly free (1) and will be (0) when trains occupy

## Local Manuver
**Br1** - Bells<br />
**Br2** - Activate Crossing (starts to blink and sound

## Outputs
**WarnRi** - Warning Car Right (flashing)<br />
**WarnLe** - Warning Car Left  (flashing)<br />
**Bells**  - Sound / Bells<br />
<br />
**VSiWh**  - Train Signal white (proceed)<br />
**VSiRe**  - Train Signal red   (Stop)<br />

# Logic
![Control Locic](https://github.com/theeal/model_crossing_industrial/blob/main/Crossing%20logic.pdf)
