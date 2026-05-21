# mpca-auto-riskshaw-fare-calculator
The Auto-Rickshaw Fare Calculator is an embedded system project that calculates fare based on distance entered using a keypad. The fare is displayed on an LCD. Push buttons and a potentiometer are used for control and fare adjustment using an Arduino Uno.


#  **Components Used**

* Arduino Uno
* Breadboard
* Hall Effect Sensor
* 16x2 LCD Display (without I2C)
* Potentiometer (for LCD contrast)
* 2 Push Buttons (Start & Reset)
* 220Ω Resistor (LCD backlight)
* 10kΩ Resistor (if not using pull-up method)
* Connecting Wires
* Battery / Power Supply

connections

### Power

* 5V → + rail
* GND → – rail

---

### LCD Connections

* VSS → GND
* VDD → 5V
* V0 → Potentiometer middle
* RS → D7
* RW → GND
* EN → D8
* D4 → D9
* D5 → D10
* D6 → D11
* D7 → D12
* LED+ → 5V via 220Ω
* LED− → GND

---

### Potentiometer

* Left → GND
* Right → 5V
* Middle → LCD V0

---

### Hall Sensor

* VCC → 5V
* GND → GND
* OUT → D2

---

### Buttons (using INPUT_PULLUP method)

**Start Button**

* One side → D3
* Other side → GND

**Reset Button**

* One side → D4
* Other side → GND
