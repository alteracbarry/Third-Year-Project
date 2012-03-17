import processing.core.*; 
import processing.xml.*; 

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

public class statics extends PApplet {

PFont font;
int area = 5;
public void setup() 
{
  size(480, 480);
  background(255);
  noStroke();
  font = loadFont("AndaleMono-24.vlw");
  textFont(font);
  smooth();
}
public void draw() 
{
  for(int y=0; y<height; y+=area)
  {
    for(int x=0; x<width; x+=area)
    {
      fill(random(0,255)/*,random(0,255),random(0,255)*/);
      rect(x,y,area,area);
    }
  }
  if (keyPressed)
  {
    check();
  }
  textSize(area*20);
  fill(0);
  textAlign(CENTER,CENTER);
  text(area, (width/2), (height/2));
  if(area == 1)
  {
    text("careful..", width/2, height/2 + area*20);
  }
}

public void check()
{
  if (key<':' && key>'0')
  {
    area = key - '0';
  }
}
  static public void main(String args[]) {
    PApplet.main(new String[] { "--bgcolor=#F0F0F0", "statics" });
  }
}
