import processing.serial.*;

Serial myPort;      // serial port
int xPos = 1;    // horizontal position of graph

void setup(){
  // set window size
  size(1000,600);
  
  //list all available serial ports
  println(Serial.list());
  
  myPort = new Serial(this, Serial.list()[0], 57600);
  myPort.bufferUntil('\n');
  
  // set initial background
  background(0);
}

void draw(){
  // everything happens in serial event 
}

void serialEvent(Serial myPort){
  // get ASCII string
 String inString = myPort.readStringUntil('\n');

  if(inString != null){
    //trim off white space
    inString = trim(inString);
    //convert to int and map to screen height
    float inByte = float(inString);
    
    inByte = map(inByte, 0, 900, 0, height);
    
    // draw line
    stroke(0,255,60);
    line(xPos, height, xPos, height - inByte);
    
    // at edge of screen go back to beginning
    if (xPos >= width){
      xPos = 0;
      background(0);
    } else {
      xPos++;  
    }
  } 
}
