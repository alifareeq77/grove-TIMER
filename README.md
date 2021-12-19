# grove-TIMER
4-digit display timer that can be paused/resumed by waving to HC-SR04 sensor 

the value of the resistors  are 220 ohm's 

<b>the red light indicates that the timer is runnig</b>

<b>
the blue light indicates that the sensor is running 
</b>

<img src="https://github.com/alifareeq77/grove-TIMER/blob/main/cctDiagram.jpg" width= 600/>

*note if you are using a 7-segmant display  you should change the function [display_timer()] and insert your code
for your display 

EX:-

```
void display_timer(int a, int b, int c, int d, int t){

// your code here
...
// display (the first digit of display,a);

// display (the second digit of display,b);
          .
          .

// display (dot,t);
          .

//end of the function
}
```
