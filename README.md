# Elegoo Smart Car

## Overview

## Hardware

## Pin Assignments

Fixed by the kit's wiring; not design choices.

| Function | Pin | Notes |
|---|---|---|
| Left motor speed (ENB) | 5 | PWM, Timer0 |
| Left motor direction (IN1) | 7 | Forward = HIGH |
| Left motor direction (IN2) | 8 | Forward = LOW |
| Right motor speed (ENA) | 6 | PWM, Timer0 |
| Right motor direction (IN3) | 9 | Forward = LOW |
| Right motor direction (IN4) | 11 | Forward = HIGH |
| Servo signal | 3 | Bare literal in the vendor sketch, not a named constant |
| Ultrasonic trigger | A5 | Analogue pin used as digital I/O |
| Ultrasonic echo | A4 | Analogue pin used as digital I/O |

The enables are cross-paired relative to the L298N's own convention:
on the bare chip ENA gates the IN1/IN2 channel, but on this shield
ENB(5) drives the IN1/IN2 (left) motor and ENA(6) drives IN3/IN4
(right). Assuming the datasheet convention swaps left and right.

Forward polarity is mirrored between sides — the motors are mounted
mirror-image, so a symmetric direction helper drives the car in a
circle rather than straight.

A4 and A5 double as the Uno's I2C pins (SDA/SCL). Any future I2C
device conflicts with the ultrasonic sensor.

The Servo library takes Timer1, disabling PWM on pins 9 and 10.
Neither speed pin is on those, so there is no conflict; pin 9 is a
direction pin and only ever receives digitalWrite.

ENA and ENB both sit on Timer0, which also drives millis(). Expect
duty-cycle skew at low values and a nonlinear speed-versus-duty
curve near the bottom of the range.

Vendor sources disagree: the Robot Car IO Pin Connection Table PDF
pairs the enables correctly but swaps the left/right labels relative
to all four sketches. Lesson 5's SmartCar_Core.ino declares ENA 5 /
ENB 6, inverting the names used in Lessons 1-4 — same physical pins,
but the identifiers do not match the rest of the kit.

## Stages

### Stage 1 — Motor Primitives

### Stage 2 — Calibration

### Stage 3 — Ultrasonic Characterisation

### Stage 4 — Servo Scanning

### Stage 5 — Obstacle Avoidance

### Stage 6 — Maze Navigation

## Measurements

## Design Decisions

## Known Limitations
