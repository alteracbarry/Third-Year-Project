int x;
int y;
float r;
int i=0;
int radius = 12;
void setup() {
size(1920, 1080);
smooth();
ellipseMode(RADIUS);
background(255);

}
void draw() {
  r = dist(x,y,mouseX,mouseY);
  if (!mousePressed)
  {
  i++;
  }
  fill(((sin(i))*255),((-sin(0.7*i))*255),((cos(2*i))*255));
  if (r == 0)
  {
    noFill();
  }
  ellipse(x, y, r, r);
  x = mouseX;
  y = mouseY;
}
