# pico-debounce-button-test
A simple program for testing some debounce circuitry.

Uses the Raspberry Pi Pico.

Basic operation:
* The debounced button will raise a GPIO IRQ on INPUT_PIN.  
* The handler will then send a short clock pulse out the OUTPUT_PIN.

Output pulse can be used to clock a shift register, for example.


# Build
Install the [Raspberry Pi Pico SDK](google.com) in a fitting manner.
```bash
$> export PICO_SDK_PATH=/path/to/sdk
$> cmake -S. -Bbuild
$> cmake --build build
```