# line-follower

## Team

* Gromet Spaal
* Juhan Raedov

## Description

Goal is to develop a line follower robot that would be able to compete and
complete the track of Robotex line following with obstacles and regular line
following. The emphasis will be on line following with obstacles. 

The design will be based on [Jarek Korus'es Thunderstorm] (https://www.youtube.com/watch?v=a7_z5ovXjRw)

## Main Requirements

* Max Dimensions:  25x25x25 cm
* Max Weight: 1 kg
* Must have a start/stop button or remote
* Voltage up to 24V

## Features

* Remote which can be used to:
 * Start and stop the line following program
 * Monitor battery voltage
 * Change PID constants
 * Choose whether to use normal line following or line following with obstacles
* Sensors:
 * n IR light sensors for line detection
 * G-sensor for detecting if the robot is on a ramp
 * Two IR proximity sensors to detect the obstacles
 * Li-Po monitoring IC
* Arduino mini for live WiFi or bluetooth feedback of sensors
 * **Reasoning:**
  - Reduces time when the main processor has to deal with things that are not related to running the main program
  - Deals with the communication with the remote
  - Can give life feedback of the sensors
   - Can be used to save the data and plot a graph of line errors

