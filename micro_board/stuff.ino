/*
L298 Pin config: (from left)
1 - current sense A
2 - out 1
3 - out 2
4 - 12V
5 - in1
6 - enable A
7 - in2
8 - gnd
9 - 5V
10 - in3
11 - enable B
12 - in4
13 - out3
14 - out4
15 - current sense B



PINS on the Board
Motors :     4, 5
Motor pwm :  6
Actuation :  
  Towards l298 - A5
  Away from l29813 --------------- 13 doesnt work for some reason
Trips :      
  Trip1 - 10 (mid), 
  Trip2 - 11 (home), 
Autonic :    7



Sensors :
CLAMP L
1. Home trip switch
2. Middle trip switch
3. AVS
CLAMP R
1. Home trip switch
2. Ladder trip switch
3. AVS 
GEN
1. Comm trip switch


Actuations :
CLAMP L
1. Piston
2. Motor
3. 
CLAMP R
1. Piston
2. Motor
3. Servo
GEN
1. Peepee


UI :
CLAMP L
1. Autonic
2. 1 trip
3. HALL x2
4. Servo
CLAMP R
1. Autonic
2. 1 trip
3. HALL x2



(7)
*/

