PFont font;
import processing.serial.*;
Serial arduino; // Create object from Serial class
float val; // Data received from the serial port
int port = 0;
int milsec = 0;
int frames = 0;
boolean menu = true;
boolean connect = false;
String arduinoPort;
String commlist[];
String buffer = "Nothing";
String Time = "never";

void setup() 
{
  size(350, 300);
  frame.setResizable(true);
  font = loadFont("DroidSans-48.vlw");
  textFont(font);
  textSize(12);
  smooth();
  Time();
}
void draw() 
{
  //println(frameRate);
  background(245);
  if (menu)
  {
    menu();
  }
  else
  {
    if (connect)
    {
      startSerial();
    } 
    textAlign(CENTER, BOTTOM);
    fill(0);
    text("Connected to " + Serial.list()[port], width/2, height);
    if (drawButton(0, 0, "Back")) // "Back" button
    {
      Time = "Never";
      menu = true;
      arduino.stop();
    }
    if (drawButtonwtimer(width/2 - 30, height/2 + 20, "Refresh"))
    {
      delay(100);
      if (arduino.available() > 0)
      {
        buffer = "'" + arduino.readString() + "'";
      }
      else  
      {
        buffer = "Nothing";
      }
      Time();
    }
    fill(0);
    textAlign(CENTER, TOP);
    text("Arduino says:    " + buffer, width/2, height/2 - 25);
    fill(100);
    text("Last checked  " + Time, width/2, height/2 + 45);
  }
}


void menu() // Port Selection Menu
{
  String commlist[] = Serial.list(); 
  String gravy = join(commlist, "");
  int commcount = (gravy.length() /4); // returns no. of ports 
  fill(0);
  textAlign(LEFT, TOP);
  text("Port Selection", 0, 0);
  for (int i = 0; i<commcount; i++)
  {
    if (drawButton(0, 20 + 20*i, i + ".   " + commlist[i]))
    {
      port = i;
      menu = false;
      connect = true;
    }
  }
}

void startSerial() // Assigns the serial steam a connection to listen to
{
  arduinoPort = Serial.list()[port];
  arduino = new Serial(this, arduinoPort, 19200);
  connect = false;
}

boolean drawButton(float x, float y, String data) // draws a button at position (x,y) containing  
{                                                 // text; for use inside if parameters 
  stroke(250, 163, 0);
  strokeWeight(1);
  fill(0);
  textAlign(CENTER, TOP);
  text(data, x+30, y+2);
  if (mouseX>x && mouseY>y && mouseX<(x+60) && mouseY<(y+20) && mousePressed)
  {
    fill(250, 163, 0, 75);
    rect(x, y, 60, 20);
    return true;
  }
  fill(250, 163, 0, 50);
  rect(x, y, 60, 20);
  return false;
}

boolean drawButtonwtimer(float x, float y, String data) // same as drawButton() but called only between
{                                                       // intervals, hits framerate so used sparsely
  stroke(250, 163, 0);
  strokeWeight(1);
  fill(0);
  textAlign(CENTER, TOP);
  text(data, x+30, y+2);
  if (mouseX>x && mouseY>y && mouseX<(x+60) && mouseY<(y+20) && mousePressed)
  {
    if (millis() - milsec >= 1000)
    {
      //frames = frameCount;
      fill(250, 163, 0, 75);
      rect(x, y, 60, 20);
      return true;
    }
  }
  fill(250, 163, 0, 50);
  rect(x, y, 60, 20);
  return false;
}

void Time() // Prints elapsed time since last called
{
  milsec = millis() - milsec;
  //Time =  milsec/1000 + " seconds ago";
  Time = hour() + ":" + minute() + ":" + second();
  milsec = millis();
}

