# Embedded-Systems-Project


In this project, Lane Keep Assist, Control Indicators and Sound System were chosen;

1-	Lane Keep Assist

	a.	For the lane keep assist, we used two color sensors to detect each side of the lane.
    
	b.	If a side is not detected, the car steers in the other direction so it can go back in the lane.
    
	c.	The car motors work with the sensors so they can steer the car back into the lane by slowing down one wheel more than the other.
    
	d.	The Motors and the boards are powered by 3 4v batteries.

2-	Control Indicators

      a.	For the headlights, we used two LEDs connected to an LDR so their light intensity varies with the surrounding light intensity.
      
      b.	For the car gears, we used an analog 2 axis joystick with a push button. The joystick is connected to the Seven Segment Display.

3-	Sound System

      a.	For the sound system, we used an mp3 module, a speaker and a 2.8 inch TFT LCD Touch Screen.
      
      b.	The SD card was setup and the speaker was connected to the mp3 module.
      
      c.	The mp3 should work via the code but sadly it didn’t, but it still works by grounding some pins.
      
      d.	The Touch Screen ,however, runs and sends the correct input to the mega board.
<!--![image](https://user-images.githubusercontent.com/74051160/230374678-a04b8e9f-471d-4573-988a-ad9822120f36.png)-->



Libraries used and their functions

1-	<Arduino_FreeRTOS.h>

    a.	Allows the creation of tasks so we used that to define our program into 3 tasks with the correct priorities set to each.

2-	<Wire.h>

    a.	This library was used to connect the Arduino Uno and Arduino Mega boards together as master and slave. It does that by creating an I2C bus which is used to transfer data between the two boards.

3-	<SevSeg.h>

    a.	This library had quite a few useful functions for the seven segment display such as printing characters that was used for displaying the car gears.
<!--![image](https://user-images.githubusercontent.com/74051160/230375105-3d2a8737-bfe0-4fb9-a5d3-4d90ca87ce21.png)-->




Inputs and Outputs

1.	Color Sensors: 

        Output for right color sensor connected to digital pin 2 
        
        output for left sensor connected to digital pin 7
        
        S0,S1,S2,S3 are connected to digital pins 3,4,5,6 respectively
        

2.	Motors: 

        Front Motors are connected to the H-Bridge (IN1,IN2,IN3,IN4)
		
        Rear Motors are connected directly to the 12v Power supply
        

3.	H-Bridge: 

        Connected to 5v and 12v
        
        IN1 and IN2 connected to right motor
        
        IN3 and IN4 connected to left motor
        
        S0,S1,S2,S3 Connected to pins ()
        

4.	LDR: 

        Connected to 5v power supply and to pin (A0)
        
        LEDs connected to pin 9 (digital)
        
        Lane Sensing Alert LED connected to digital pin 50
        

5.	MP3: 

        RX,TX connected to pins (33,35)
        
        Mp3 connected to power and ground and the speakers are 	connected onto the mp3
        

6.	Touchscreen: Placed on Arduino Uno

7.	Seven Segment Display: 
			Segments are connected to digital pins 22,24,42,44,46,26,28,40
	
8.	Joystick:
	
	Push button input connected to digital pin 53
	X,Y axis sensors connected to analog pins A4,A5
![image](https://user-images.githubusercontent.com/74051160/230375409-608e8893-cc91-464b-a17a-d844ab085e48.png)




FreeRTOS

There are 3 Tasks in our freeRTOS implementation.

1-	Task Responsible for color sensors & motors
2-	Task for the joystick and Seven Segment Display
3-	Task responsible for LDR
	
Task 1 has the highest priority while task 2 and 3 have equal but lower 			priorities than task 1.



Problems and Limitations Faced:

	The MP3 module refused to work, even though I have changed the jumpers and rewired 	everything several times. I have also formatted the SD and set it up in the required 	settings and filenames. The MP3 module works directly by grounding some of the inputs 	but fails to read the SD card when running its code.

	Getting the touch screen to work without resetting was a hassle at first, but the 
	Instructions were followed and it worked well after that.

	Too many connections and jumpers all over the project which made it a bit hard to 
	Debug and modify especially towards the end of the project.

	The 4WD car skeleton was of very poor quality. It had very wobbly wheels which made it 	hard to even go in a straight line properly. The weight distribution was also an issue with 	the car.
![image](https://user-images.githubusercontent.com/74051160/230375725-d4cd910d-2a6b-4f26-a525-0b314564e175.png)





<img width="468" alt="image" src="https://user-images.githubusercontent.com/74051160/230376018-283af765-c0e1-4810-b382-5841907ce4f2.png">
