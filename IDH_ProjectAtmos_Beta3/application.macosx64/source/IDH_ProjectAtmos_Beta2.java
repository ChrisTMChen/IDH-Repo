import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import gifAnimation.*; 
import processing.video.*; 
import jp.nyatla.nyar4psg.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class IDH_ProjectAtmos_Beta2 extends PApplet {

/* Libraries */




Capture cam;
MultiMarker nya;
int numMarkers = 4;
Boolean[] markerDetected = new Boolean[numMarkers];
PFont font1, font2;

float SCALE = 0.5f;
PImage logo; 
Gif myAnimation;
DigitalClock digitalClock;

HomeFeed home;
FilmFeed1 feed1;
FilmFeed2 feed2;
FilmFeed3 feed3;
CameraFeed1 feed4;

float curTime, prevTime;

int timeOut = 3000;
int time = millis();

//sizes
int w = 1920; //--------------------<set w
int h = 1080; //---------------------<set h
int camW = 1920; //--------------------<set camera resolution
int camH = 1080; //----------------------<set camera resolution

//font sizes
int heading;
int body;
int body1;
int body2;

//ALIGN TO
int left;
int left1;
int xcentre;
int ycentre;
int right;
int right1;
int top;
int top1;
int bottom;
int bottom1;

int state = 0;

PImage fuji400; 
PImage iro200; 
PImage ilford400; 

PImage[] Sfilm = new PImage[11];
PImage[] Ilfordfilm = new PImage[11];
PImage[] Irofilm = new PImage[11];
PImage[] Fujifilm = new PImage[11];
PImage[] UFStrip = new PImage[11];
PImage[] LFStrip = new PImage[11];

float x;
float y;
float SfilmSpacing;
float SfilmStripLength;
float SfilmSpeed;

float HStripSpacing;
float HStripStripLength;
float HStripSpeed;

float frame;
float reset;
int display;

//------------------------------------------------------------setup
public void setup() {
  //size(1920, 1080, P3D); //needs 16:9
   //needs 16:9
  //size(1280, 720, P2D); //needs 16:9
  //size(1280, 720, P3D); //needs 16:9

  textAlign(LEFT);
  heading = h/15;
  body = h/30;
  body1 = h/22;
  left = w/12;
  left1 = w/38;
  right = w-w/40;
  top = h/12;
  top1 = h/16;
  bottom = h-h/25;
  bottom1 = h-h/5;
  xcentre = w/2;
  ycentre = h/2;

  logo = loadImage("FNDlogo.jpg");
  stroke(255);

  home = new HomeFeed();
  feed1 = new FilmFeed1();
  feed2 = new FilmFeed2();
  feed3 = new FilmFeed3();
  feed4 = new CameraFeed1();

  /* setup animation */
  myAnimation = new Gif(this, "test.gif");
  myAnimation.play();

  font1 = loadFont("PTSans-Regular-48.vlw");
  font2 = loadFont("FuturaPT-Heavy-48.vlw");

  frame = 0;
  display=0;
  reset = 0;

  /* setup clock */
  digitalClock = new DigitalClock(40); 

  /* camera setup */
  println(MultiMarker.VERSION);
  cam=new Capture(this, camW, camH);
  nya=new MultiMarker(this, width, height, "camera_para.dat", NyAR4PsgConfig.CONFIG_PSG);
  nya.addNyIdMarker(358, 80); //id=358
  nya.addNyIdMarker(158, 80); //id=158
  nya.addNyIdMarker(253, 80); //id=253
  nya.addNyIdMarker(365, 80); //id=365

  cam.start();

  /* strip setup */
  iro200 = loadImage("iro200logo.jpg");
  fuji400 = loadImage("fuji400logo.jpg");
  ilford400 = loadImage("ilford400logo.jpg");
  { 
    for (int i = 0; i < Sfilm.length; i++) { 
      (Irofilm[i] = loadImage("IroFilm-"+i+".jpg")).resize (1000, 667);
      (Fujifilm[i] = loadImage("FujiFilm-"+i+".jpg")).resize (1000, 667);
      (Ilfordfilm[i] = loadImage("IlfordFilm-"+i+".jpg")).resize (1000, 667);
    }
    y=ycentre/2;
    x=xcentre;
    SfilmSpacing = height/1.07f;
    SfilmStripLength = SfilmSpacing*Sfilm.length;
    SfilmSpeed = 0.6f;
  }
  for (int i = 0; i < UFStrip.length; i++) { 
    (UFStrip[i] = loadImage("UFStrip-"+i+".jpg")).resize (600, 400);
    (LFStrip[i] = loadImage("LFStrip-"+i+".jpg")).resize (600, 400);
  }
  y=ycentre/2;
  x=xcentre;
  HStripSpacing = height/1.767f;
  HStripStripLength = HStripSpacing*UFStrip.length;
  HStripSpeed = 0.5f;

}

//------------------------------------------update
public void update() {
println(frameRate);
}


//------------------------------------------------------------draw
public void draw() {

  background(47, 54, 64);
  update();
  logos(); //draw logos
  drawClock();

  detectMarker(); // look for marker
  updateState(); 
  drawScreens(); // select screen
}

//------------------------------------------logos
public void logos() {
  image(logo, 0, 980);
}

//------------------------------------------------------------drawClock
public void drawClock()
{
  digitalClock.getTime();
  digitalClock.display(w, h);
}

//-----------------------------------------------HomeScreenTimers
public void timers() {

  frame = frame + 0.005f; // change for home toggle duration

  if (frame >= 2) {
    display = 1;
    if (frame >= 6) {
      display = 0;
      reset = frame;
      frame = frame - reset;
    }
  }
}

//------------------------------------------------------------drawScreens
public void drawScreens() {
  switch(state) {

  case 0:
    timers();
    home.draw(display);
    break;

  case 1:
    feed1.draw();
    break;
  case 2:
    feed2.draw();
    break;
  case 3:
    feed3.draw();
    break;

  case 4:
    timers();
    feed4.draw();
    break;

  default:
    timers();
    home.draw(display);
    break;
  }
}

//------------------------------------------------------------updateState
public void updateState() {
  if (state != 0) return;
  state = 0;
  for (int i = 0; i < markerDetected.length; i++) {
    if (markerDetected[i])
      state = 1+i;
  }
}

//------------------------------------------------------------startTimer
public void startTimer() {

  prevTime = curTime = millis();
}

//------------------------------------------------------------updateTimer
public void updateTimer() {

  curTime = millis();
  if ((curTime - prevTime) > timeOut)
  {
    println("marker timed out!");
    for (int i = 0; i < markerDetected.length; i++) {
      markerDetected[i] = false;
    }
    state = 0;
    //println("reset timer");
  }
}


//------------------------------------------------------------detectMarker358
public void detectMarker() {

  updateTimer();

  if (cam.available() !=true) {
    return;
  }
  cam.read();
  nya.detect(cam);

  for (int i=0; i < numMarkers; i++) {
    if (nya.isExist(i)) {
      markerDetected[i] = true;
      println("found marker"+ i);
      startTimer();
    } else {
      markerDetected[i] = false;
    }
  }
}
class CameraFeed1 {
  PFont font;

  CameraFeed1() {
    font = loadFont("FuturaPT-Heavy-48.vlw");
  }

  public void draw() {

    fill(255);
    textFont(font1, body);
    text("Olympus OM-2N", left, bottom);

    textFont(font2, heading);
    fill(251, 207, 24);
    text("camera feed", left1, top);

    //image(OlympusCam, 0, 840, 100, 100);

    //x = x + SfilmSpeed;
    //for (int i = 0; i < Fujifilm.length; i++) { 
    //  image(Fujifilm[i], - (x + i * SfilmSpacing) % SfilmStripLength + h+1000, 140);
    //}
  }
}
class DigitalClock extends Clock {
  int fontSize;

  DigitalClock(int _fontSize) {
    fontSize = _fontSize;
  }

  public void getTime() {
    super.getTime();
  }

  public void display(float x, float y) {

    textSize(body1);
    textAlign(RIGHT);
    text (h + ":" + nf(m, 2), right, top1);
    textAlign(LEFT); //reset text align to left
  }
}

class Clock {
  int h, m;
  Clock() {
  }

  public void getTime() {
    h = hour();
    m = minute();
  }
}
class FilmFeed1 {
  PFont font;

  FilmFeed1() {
    font = loadFont("FuturaPT-Heavy-48.vlw");
  }

  public void draw() {

    fill(255);
    textFont(font1, body);
    text("FilmNeverDie Iro 200", left, bottom);

    textFont(font2, heading);
    fill(251, 207, 24);
    text("film feed", left1, top);
    
    image(iro200, 0, 845);

    x = x + SfilmSpeed;
    for (int i = 0; i < Irofilm.length; i++) {
      image(Irofilm[i], - (x + i * SfilmSpacing) % SfilmStripLength + h+1000, 140 );
    }
  }
}
class FilmFeed2 {
  PFont font;

  FilmFeed2() {
    font = loadFont("FuturaPT-Heavy-48.vlw");
  }

  public void draw() {

    fill(255);
    textFont(font1, body);
    text("Fujifilm Industrial 400", left, bottom);

    textFont(font2, heading);
    fill(251, 207, 24);
    text("film feed", left1, top);

    image(fuji400, 0, 845);

    x = x + SfilmSpeed;
    for (int i = 0; i < Fujifilm.length; i++) { 
      image(Fujifilm[i], - (x + i * SfilmSpacing) % SfilmStripLength + h+1000, 140);
    }
  }
}
class FilmFeed3 {
  PFont font;

  FilmFeed3() {
    font = loadFont("FuturaPT-Heavy-48.vlw");
  }

  public void draw() {

    fill(255);
    textFont(font1, body);
    text("Ilford HP5 400", left, bottom);

    textFont(font2, heading);
    fill(251, 207, 24);
    text("film feed", left1, top);
    
    image(ilford400, 0, 845);

    x = x + SfilmSpeed;
    for (int i = 0; i < Ilfordfilm.length; i++) { 
      image(Ilfordfilm[i], - (x + i * SfilmSpacing) % SfilmStripLength + h+1000, 140 );
    }
  }
}
class HomeFeed {
  PFont font;

int _display;

  HomeFeed() {
    font = loadFont("FuturaPT-Heavy-48.vlw");
  }

  public void draw(int _display) {

    fill(255);
    textFont(font1, body);
    text("Place a film or camera in front of the orb to begin.", left, bottom);

    textFont(font2, heading);
    fill(251, 207, 24);
    text("public feed", left1, top);


  if (_display == 1){
   x = x + HStripSpeed;
    for (int i = 0; i < UFStrip.length; i++) { 
      image(UFStrip[i], - (x + i * HStripSpacing) % HStripStripLength + h+1000, 140 );
      image(LFStrip[i], - (x + i * HStripSpacing) % HStripStripLength + h+1000, 550 );
    }
  }
  else if (_display == 0)
  {
    image(myAnimation, 650, 250);  
  }
  }
}
  public void settings() {  size(1920, 1080, P2D); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "--present", "--window-color=#666666", "--hide-stop", "IDH_ProjectAtmos_Beta2" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
