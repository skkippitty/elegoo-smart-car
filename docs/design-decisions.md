# Design Decisions

## Motor control primitive

## Calibration approach

## Sensor filtering

## Navigation algorithm

## Rejected alternatives

---

## Motor control primitive

The chassis is differential drive: two motor groups, no steering mechanism. Every manoeuvre the car can perform is a pair of wheel speeds. Turning is unequal speeds; spinning in place is equal speeds in opposite directions.

The primitive is therefore a single function taking a signed speed for each side. Sign selects direction, magnitude sets duty cycle. Forward, reverse, spin and arc are all wrappers over that one function rather than independent implementations.

The alternative — separate uncoordinated functions for each manoeuvre — was rejected. It duplicates the direction-pin logic in every function, and the proportional wall-following controller planned for Stage 6 requires continuously variable unequal speeds, which a fixed set of named manoeuvres cannot express.

---

## Direction sense is mirrored between sides

Measured on hardware: the left motors drive the chassis forward with IN1 HIGH and IN2 LOW, while the right motors drive it forward with IN3 LOW and IN4 HIGH. The two sides are opposite because the motors are mounted mirror-image about the chassis centreline.

The consequence is that a symmetric helper of the form setMotor(pinA, pinB, forward) applying identical logic to both sides drives one side forward and the other backward, spinning the car in place. The direction logic must be written per side.

This was predicted from the vendor sketches and confirmed by observation before any movement code was written, which is the reason it did not become a debugging session.

---

## Pin pairing conflicts between vendor sources

The L298N's own convention pairs the ENA enable with the IN1/IN2 channel. This shield cross-pairs them: ENB (pin 5) enables the IN1/IN2 motor and ENA (pin 6) enables the IN3/IN4 motor.

Assuming the datasheet convention therefore swaps left and right, and does so silently — the car drives, but every turn is inverted.

Vendor sources disagree on the labelling. The Robot Car IO Pin Connection Table PDF pairs the enables correctly but labels the ENB/IN1/IN2 channel as the right motor, while all four example sketches treat it as the left. Lesson 5's SmartCar_Core.ino declares ENA as 5 and ENB as 6, inverting the identifiers used in Lessons 1–4 for the same physical pins.

Resolution: the pairing was taken from the standalone left_wheel_rotation.ino and right_wheel_rotation.ino sketches, each of which defines only one channel and is therefore unambiguous. Left and right were then confirmed by direct observation on the assembled car rather than taken from any document.

---

## Timer allocation

ENA and ENB are pins 6 and 5, both driven by Timer0, which also provides millis() and delay(). This is expected to produce duty-cycle skew at low values and a nonlinear speed-versus-duty relationship near the bottom of the range. Recorded as a prediction to be tested in Stage 2, where it could otherwise be mistaken for motor mismatch.

The Servo library claims Timer1, disabling PWM on pins 9 and 10. Neither speed pin is on those, so there is no conflict: pin 9 is IN3, a direction pin, which only ever receives digitalWrite. Pin 10 is the line-tracking right sensor, likewise digital only. Verified by checking every analogWrite call in the vendor sketches — the only arguments ever passed are ENA and ENB.

---

## Known hardware faults

**Battery pack switch is intermittent.** It makes contact only at a specific angle. Partial contact lights the L298N's indicator LED while being unable to supply motor current under load, which presents as a firmware fault: sketch runs, serial output correct, no movement.

Left in place for now. If it degrades, the switch can be bypassed or replaced — the pack is two cells in a holder. Recorded because it will recur, and because it will present mid-drive as an apparent software problem.

**USB alone cannot power the peripherals.** With the servo and ultrasonic sensor connected, USB current limiting causes the board to brown out and re-enumerate in a loop, preventing upload. The battery pack must be connected when programming.
