# Measurement Plan

## Stage 1 — Motor characterisation

All readings taken on hardware with the chassis raised and all four wheels free. Duty cycle swept 0–255 in steps of 25, each step held for 1.5 seconds, with the commanded value printed to serial.

| Measurement | Node or Axis | Predicted | Measured | Notes |
|---|---|---|---|---|
| Left forward direction | IN1 / IN2 | IN1 HIGH, IN2 LOW | IN1 HIGH, IN2 LOW | Matches the vendor sketches |
| Right forward direction | IN3 / IN4 | IN3 LOW, IN4 HIGH | IN3 LOW, IN4 HIGH | Opposite sense to the left side |
| Stall threshold, left | ENB duty | — | ≤100, >75 | Wheels free, no chassis load |
| Stall threshold, right | ENA duty | — | ≤100, >75 | Identical to the left within the resolution of the sweep |
| Speed vs duty linearity, per side | ENA / ENB | Nonlinear near bottom of range | | ENA and ENB share Timer0 with millis(); predicted duty-cycle skew at low values |

### Resolution caveat

The sweep stepped in increments of 25, so a threshold reported as 100 means only that the wheels were stationary at 75 and turning at 100. The true figure lies somewhere between. A sweep in steps of 5 would resolve it properly, and should be run before these numbers are used to set the lower bound of the usable speed range.

Both sides reporting the same figure is therefore weaker evidence of matching than it first appears — two thresholds 20 apart would both report as 100 at this resolution.

### Load caveat

These thresholds were measured with the wheels free. On the floor the chassis' weight and rolling resistance both oppose rotation, so the loaded threshold will be higher. The unloaded figure is a lower bound, not the operating value, and the loaded measurement belongs in Stage 2.

---

## Stage 1 — Fault log

### Upload failure: enumeration loop

**Symptom.** avrdude reported not in sync: resp=0x00 across all ten attempts, ending in unable to open port COM5. Device Manager refreshed repeatedly on connection, the board's 5V LED pulsed on and off, and an audible tick came from the ultrasonic sensor.

**Diagnosis.** The repeating enumeration and pulsing supply LED indicated the board was browning out and re-enumerating in a loop rather than a driver or protocol fault. Disconnecting the servo and ultrasonic sensor and running on USB alone produced a stable power LED and a clean enumeration.

**Root cause.** Total peripheral current draw exceeded what the USB port would supply. The kit is designed to run its peripherals from the battery pack, with USB providing data and logic power only.

**Fix.** Connect the battery pack alongside USB when programming. USB alone is sufficient only with the servo and ultrasonic sensor disconnected.

### Motors dead: intermittent battery switch

**Symptom.** Sketch uploaded successfully and serial output printed the full duty sweep in both directions, but no motor movement at any duty. The L298N module's power LED was lit throughout.

**Diagnosis.** Serial output confirmed the firmware was running and the Arduino was driving its pins as commanded, which localised the fault downstream of the microcontroller. The L298N LED being lit initially suggested the driver was powered.

**Root cause.** The battery pack's switch makes contact only at a specific angle. Partial contact was sufficient to light the L298N's indicator LED but could not supply motor current under load.

**Fix.** Switch positioned to make contact. Recorded as a known limitation — an intermittent supply switch is likely to recur, and will present mid-drive as an apparent firmware fault.

### Diagnostic note

An indicator LED confirms that some current is reaching a board. It does not confirm the supply can deliver load current. A supply fault can therefore present with every indicator lit and every signal correct.

Serial instrumentation was decisive here: printing the commanded duty cycle proved the firmware was running and executing as written, which eliminated the entire software half of the system in one step and directed the search downstream.

---

## Stage 2 — Drive calibration

| Measurement | Node or Axis | Predicted | Measured | Notes |
|---|---|---|---|---|

---

## Stage 3 — Ultrasonic sensor

| Measurement | Node or Axis | Predicted | Measured | Notes |
|---|---|---|---|---|

---

## Stage 4 — Servo

| Measurement | Node or Axis | Predicted | Measured | Notes |
|---|---|---|---|---|

---

## Stage 5 — Obstacle avoidance

| Measurement | Node or Axis | Predicted | Measured | Notes |
|---|---|---|---|---|

---

## Stage 6 — Maze navigation

| Measurement | Node or Axis | Predicted | Measured | Notes |
|---|---|---|---|---|
