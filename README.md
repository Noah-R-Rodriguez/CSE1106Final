# Smart Classroom Comfort Monitor

## Project Description

We developed a simple monitoring system for our university facilities department.

The department wants to monitor classroom temperatures and identify when certain conditions fall outside an acceptable range.

This is a Raspberry Pi-based application that processes temperature readings, determines whether the classroom environment is acceptable, and provides a visible warning when a temperature is outside the specified range.

## Functionality/Requirements

* Allows the user to enter classroom temperature readings in Farenheit
* Determines whether a temp is within the acceptable range of 68F - 76F
* Displays a **NORMAL** or **WARNING** when appropriate
* Calculates the average of all recorded temperatures, when prompted
* Able to export temperature readings and their statuses to .txt file
* Use an LED connected to the Raspberry Pi to indicate a warning condiiton
* Its modularity allowd the acceptable temperature range to be changed according to a new client's requirement
