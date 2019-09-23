# Foamcutter

## Calebrating the laser
1. open de settings file
2. move the machine with a block of isolation as close to the laser sensor as posible (with the sensor giving a valid reading)
   Put in the **MinDist** with the value on the sensor. Put in the **minDistInput** the raw value (you find the raw value in the app underneath the main reading)


3.  move the machine with a block of isolation as far from the laser sensor as posible (with the sensor giving a valid reading)
   Put in the **MaxDist** with the value on the sensor. Put in the **maxDistInput** the raw value (you find the raw value in the app underneath the main reading)
 ## Calebrating the zero points of the cutter
 
Fill in the **topOffset** with the sensor value in the app(next to the raw value) when the block is at zero possition at the top cutter
Fill in the **bottomOffset** with the sensor value in the app(next to the raw value) when the block is at zero possition at the bottom cutter
 
   
 ## Calebrating the the motor
 
**fastSpeed:** Max motor speed 
 max speed of the motor. Make lower if motor losses steps, Make higher if its to slow.
 
 **maxAxel:** Max motor acceleration
  
**controllerP:** Proportional control 
 make bigger if approach is to slow, make smaller if overshoot is to big
   
