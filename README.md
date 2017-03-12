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
 * Control blower (on-off, speed)
 * Choose whether to use normal line following or line following with obstacles
* Sensors:
 * 14 IR light sensors for line detection
 * 2-axis accelerometer to calculate tilt angles
 * Three IR proximity sensors to detect the obstacles
 * Li-Po monitoring IC
* Arduino mini for live WiFi or bluetooth feedback of sensors (maybe include it onto main board)
 * **Reasoning:**
  - Reduces time when the main processor has to deal with things that are not related to running the main program
  - Deals with the communication with the remote
  - Can give live feedback of the sensors
   - Can be used to save the data and plot a graph of line errors

## BOM
[Google Drive spreadsheet] (https://docs.google.com/spreadsheets/d/14ZZVYrouCOKjxGVaX2KsAmJzS4HpelGW_TXLZ0HPqsI/edit#gid=0)

