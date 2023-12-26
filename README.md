### Objective
This program tests PID controls in a somewhat simulated control loop.
### How to run
1. Download/clone all 4 files
2. Compile using the make file
3. Run the program
### Changeable
- The variables setpoint, measured, rows, and cols can be changed to preference
- The parameters in the function calls to PIDControllerSetLimits and PIDControllerSetTerms are also all changeable
### Other things
- The simulation is right now the PID return squared divided by 2, but if the PID return is negative, the increment is also negative
  - It is not a perfect simulation because there is no lag or windup for the PID to deal with
- This is just to practice running PID in real situations using C. This was never meant to be user friendly