import processing.core.*; 
import processing.xml.*; 

import processing.serial.*; 

import java.applet.*; 
import java.awt.Dimension; 
import java.awt.Frame; 
import java.awt.event.MouseEvent; 
import java.awt.event.KeyEvent; 
import java.awt.event.FocusEvent; 
import java.awt.Image; 
import java.io.*; 
import java.net.*; 
import java.text.*; 
import java.util.*; 
import java.util.zip.*; 
import java.util.regex.*; 

public class gooey extends PApplet {

PFont font;

Serial arduino; // Create object from Serial class
float val; // Data received from the serial port
int port = 0;
int commcount;
boolean menu = true;
boolean connect = false;
String arduinoPort;
String commlist[];

public void setup() 
{
  size(350, 350);
  font = loadFont("DroidSans-48.vlw");
  textFont(font);
  textSize(12);
  smooth();
}
public void draw() 
{
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
    background(230);
    textAlign(CENTER, BOTTOM);
    fill(0, 0, 0);
    text("Connected to port " + port, width/2, height);
    if (drawButton(0, 0, 60, 20))
    {
      menu = true;
      arduino.stop();
    }    
    textAlign(LEFT, TOP);
    fill(0, 0, 0);
    text("Back", 1, 0);   
    if (arduino.available() > 0)
    {
      String buffer = arduino.readString();
      textAlign(CENTER, TOP);
      text("Arduino says  " + buffer, width/2, height/2);
      long pmillis = millis();
    }
    else  
    {
      textAlign(CENTER, TOP);
      text("Arduino says no", width/2, height/2);
    }
  }
}


public void menu()
{
  background(230);
  String commlist[] = Serial.list(); 
  String gravy = join(commlist, "");
  commcount = (gravy.length() /4); // returns no. of ports 
  fill(0);
  textAlign(LEFT, TOP);
  text("Port Selection", 0, 0);
  for (int i = 0; i<commcount; i++)
  {
    fill(0);
    text(i + ".   " + commlist[i], 1, 20 + 20*i);
    if (drawButton(0, 20 + 20*i, 60, 20))
    {
      port = i;
      menu = false;
      connect = true;
    }
  }
}

public void startSerial()
{
  arduinoPort = Serial.list()[port];
  arduino = new Serial(this, arduinoPort, 9600);
  connect = false;
}

public boolean drawButton(float x, float y, float xWidth, float yHeight)
{
  stroke(0, 0, 0);
  if (mouseX>x && mouseY>y && mouseX<(x+xWidth) && mouseY<(y+yHeight) && mousePressed)
  {
    fill(200, 0, 0, 50);
    rect(x, y, xWidth, yHeight);
    return true;
  }
  fill(255, 0, 0, 50);
  rect(x, y, xWidth, yHeight);
  return false;
}

  static public void main(String args[]) {
    PApplet.main(new String[] { "--bgcolor=#F0F0F0", "gooey" });
  }
}
