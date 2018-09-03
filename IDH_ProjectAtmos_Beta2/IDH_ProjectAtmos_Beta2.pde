/* Libraries */
import gifAnimation.*;
import processing.video.*;
import jp.nyatla.nyar4psg.*;

Capture cam;
MultiMarker nya;
int numMarkers = 4;
Boolean[] markerDetected = new Boolean[numMarkers];
PFont font1, font2;

float SCALE = 0.5;
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
void setup() {
  //size(1920, 1080, P3D); //needs 16:9
  size(1920, 1080, P2D); //needs 16:9
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
    SfilmSpacing = height/1.07;
    SfilmStripLength = SfilmSpacing*Sfilm.length;
    SfilmSpeed = 0.6;
  }
  for (int i = 0; i < UFStrip.length; i++) { 
    (UFStrip[i] = loadImage("UFStrip-"+i+".jpg")).resize (600, 400);
    (LFStrip[i] = loadImage("LFStrip-"+i+".jpg")).resize (600, 400);
  }
  y=ycentre/2;
  x=xcentre;
  HStripSpacing = height/1.767;
  HStripStripLength = HStripSpacing*UFStrip.length;
  HStripSpeed = 0.5;

}

//------------------------------------------update
void update() {
println(frameRate);
}


//------------------------------------------------------------draw
void draw() {

  background(47, 54, 64);
  update();
  logos(); //draw logos
  drawClock();

  detectMarker(); // look for marker
  updateState(); 
  drawScreens(); // select screen
}

//------------------------------------------logos
void logos() {
  image(logo, 0, 980);
}

//------------------------------------------------------------drawClock
void drawClock()
{
  digitalClock.getTime();
  digitalClock.display(w, h);
}

//-----------------------------------------------HomeScreenTimers
void timers() {

  frame = frame + 0.005; // change for home toggle duration

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
void drawScreens() {
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
void updateState() {
  if (state != 0) return;
  state = 0;
  for (int i = 0; i < markerDetected.length; i++) {
    if (markerDetected[i])
      state = 1+i;
  }
}

//------------------------------------------------------------startTimer
void startTimer() {

  prevTime = curTime = millis();
}

//------------------------------------------------------------updateTimer
void updateTimer() {

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
void detectMarker() {

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
