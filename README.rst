
Servomotor 2-Channels
##########

Overview
********

This app drives two servomotors using PWM signals of variable duty cycle but constant and equal time period.

Code can be uncommented to vary the duty cycle of the signals.

The corresponding PWM pulse range are 1000 to 2000 microseconds.
Different servomotors may require different PWM pulse widths, and you may need
to modify the source code if you are using a different servomotor.


Wiring
******

You will need to connect the motors' red wires to external 5V, the black wires to
ground and the white wire to P0.04 and P0.05.

Building and Running
********************

The sample has a devicetree overlay for the nRF5340 DK.

