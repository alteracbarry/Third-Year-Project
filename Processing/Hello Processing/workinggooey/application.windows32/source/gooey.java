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
boolean menu = true;
boolean connect = false;
String arduinoPort;
String commlist[];
String buffer = "Nothing";
String Time = "never";

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
    if (drawButton(width/2 - 30, height/2 + 20, "Refresh"))
    {
      if (arduino.available() > 0)
      {
        buffer = arduino.readString();
      }
      else  
      {
        buffer = "Nothing";
      }
      Time = hour() + ":" + minute() + ":" + second();
    }
    fill(0);
    textAlign(CENTER, TOP);
    text("Arduino says  " + buffer, width/2, height/2 - 25);
    fill(100);
    text("Last checked  " + Time, width/2, height/2 + 45);
  }
}


public void menu() // Port Selection Menu
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

public void startSerial() // Assigns the serial steam a connection to listen to
{
  arduinoPort = Serial.list()[port];
  arduino = new Serial(this, arduinoPort, 9600);
  connect = false;
}

public boolean drawButton(float x, float y, String data) // draws a button at position (x,y) that contains  
{                                                 // text and is meant for use in if statements 
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

  static public void main(String args[]) {
    PApplet.main(new String[] { "--bgcolor=#F0F0F0", "gooey" });
  }
}
