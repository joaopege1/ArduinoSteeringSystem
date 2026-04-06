# ArduinoSteeringSystem
This system is an **interactive positional controller with directional indicators**. You can think of it as a simplified simulation of a car's steering wheel and dashboard, or a dial-controlled pointing device. 

The system uses a potentiometer (a dial or knob) as the primary input to directly control the physical angle of a servo motor. It provides real-time data feedback on a screen and uses two LEDs to act as directional turn signals based on the position of the dial.

Here is a breakdown of the system's hardware and behavioral logic:

### **Hardware Components**
Based on the pin declarations and libraries, this system requires:
* **Microcontroller:** An Arduino-compatible board.
* **Input:** 1x Potentiometer connected to analog pin `A0`.
* **Outputs:**
    * **Movement:** 1x Servo motor connected to digital pin `9`.
    * **Visual Display:** 1x I2C 16x2 LCD screen (address `0x27`).
    * **Indicators:** 2x LEDs ("Left" on pin `7` and "Right" on pin `2`).

---

### **System Behavior**

**1. Initialization (Startup)**
When powered on, the LCD screen initializes, turns on its backlight, and permanently displays a custom title—**"Johnny The Maker"**—on the top row. 

**2. Positional Control (The Servo)**
The system constantly reads the position of the potentiometer, which provides a value between `0` and `1023`. It maps this value directly to an angle between **0° and 180°** and commands the servo to move to that exact angle. 

**3. Telemetry (The LCD)**
The bottom row of the LCD continuously updates to display the raw numerical value of the potentiometer (e.g., "Pot: 512"). 

**4. Directional Indicators (The LEDs)**
The code establishes a "center deadzone" between the values of 480 and 540 (roughly the middle of the dial). The LEDs react to where the dial is pointed:
* **Turned Left (Value < 480):** The Left LED blinks on and off every 300 milliseconds. The Right LED stays off.
* **Turned Right (Value > 540):** The Right LED blinks on and off every 300 milliseconds. The Left LED stays off.
* **Centered (Value 480 - 540):** Both the Left and Right LEDs remain solidly on, indicating the system is in a neutral resting state.

---

### **Technical Highlight: Non-Blocking Delays**
One of the best design choices in this code is the use of `millis()` instead of `delay()` for the LED blinking logic. 

Because `delay()` completely pauses a microcontroller, using it would cause the servo movement and LCD updates to stutter every time an LED blinked. By tracking `currentTime` and `previousTime` to check if 300 milliseconds have passed, the code achieves **multitasking**. The system instantly updates the servo and screen on every loop while the LEDs blink smoothly in the background.
