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

public class sketch_feb27a extends PApplet {

int x;
int y;
float r;
int i=0;
int radius = 12;
public void setup() {
size(1920, 1080);
smooth();
ellipseMode(RADIUS);
background(255);

}
public void draw() {
  r = dist(x,y,mouseX,mouseY);
  if (!mousePressed)
  {
  i++;
  }
  fill(((sin(i))*255),((-sin(0.7f*i))*255),((cos(2*i))*255));
  if (r == 0)
  {
    noFill();
  }
  ellipse(x, y, r, r);
  x = mouseX;
  y = mouseY;
}
  static public void main(String args[]) {
    PApplet.main(new String[] { "--bgcolor=#F0F0F0", "sketch_feb27a" });
  }
}
