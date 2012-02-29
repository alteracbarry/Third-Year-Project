PFont font;
int area = 5;
void setup() 
{
  size(480, 480);
  background(255);
  noStroke();
  font = loadFont("AndaleMono-24.vlw");
  textFont(font);
  smooth();
}
void draw() 
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

void check()
{
  if (key<':' && key>'0')
  {
    area = key - '0';
  }
}
