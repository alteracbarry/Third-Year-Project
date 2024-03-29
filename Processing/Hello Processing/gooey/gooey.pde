PFont font;
PImage img0;
PImage img1;
import processing.serial.*;
Serial arduino; // Create object from Serial class
float val; // Data received from the serial port
int port = 0;
boolean menu = true;
boolean connect = false;
boolean tickbox = false;
String arduinoPort;
String commlist[];
String buffer = "Nothing";
String Time = "never";

void setup() 
{
  size(350, 350);
  font = loadFont("DroidSans-48.vlw");
  img0 = loadImage("unticked.png");
  img1 = loadImage("ticked.png");
  textFont(font);
  textSize(12);
  smooth();
}
void draw() 
{
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
      menu = true;
      arduino.stop();
    }
    tickbox(width/2 - 50, height/2 + 20);
    if (drawButton(width/2 - 30, height/2 + 20, "Refresh"))
    {
      delay(100);
      if (arduino.available() > 0)
      {
        buffer = arduino.readString();
      }
      else  
      {
        buffer = "Nothing";
      }
      Time();
    }
    fill(0);
    textAlign(CENTER, TOP);
    text("Arduino says:    " + '"' + buffer + '"', width/2, height/2 - 25);
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
{                                                 // text; for use in if statements 

  stroke(250, 163, 0);
  strokeWeight(1);
  fill(0);
  textAlign(CENTER, TOP);
  text(data, x+30, y+2);
  if (mouseX>x && mouseY>y && mouseX<(x+60) && mouseY<(y+20) && mousePressed)
  {
    while (mousePressed)
    {
    } 
    fill(250, 163, 0, 75);
    rect(x, y, 60, 20);
    return true;
  }
  fill(250, 163, 0, 50);
  rect(x, y, 60, 20);
  return false;
}

void tickbox(float x, float y)
{

  if (tickbox)
  {
    image(img1, x, y);
  }
  else
  {
    image(img0, x, y);
  }
  if (mouseX>x && mouseY>y && mouseX<(x+12) && mouseY<(y+12) && mousePressed)
  {
    if (!mousePressed)
    {
      tickbox = !tickbox;
    }
  }
}

void serialEvent(Serial arduino)
{
  if (tickbox)
  {
    Time();
    delay(10);
    buffer = arduino.readBytes(val);
    //arduino.setTimeout();
  }
}

void Time()
{
  Time = hour() + ":" + minute() + ":" + second();
}

