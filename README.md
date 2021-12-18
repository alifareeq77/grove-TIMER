# grove-TIMER
4-digit display timer that can be paused/resumed by waving to HC-SR04 sensor 


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
