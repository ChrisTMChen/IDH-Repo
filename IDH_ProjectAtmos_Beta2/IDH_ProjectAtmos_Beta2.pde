/* Libraries */
import gifAnimation.*;
import processing.video.*;
import jp.nyatla.nyar4psg.*;

Capture cam;
MultiMarker nya;
boolean marker_detected = false;
PFont font1, font2;

float SCALE = 0.5;
PImage logo; 
Gif myAnimation;
DigitalClock digitalClock;

HomeFeed home;
FilmFeed1 feed1;
FilmFeed2 feed2;
FilmFeed3 feed3;

float curTime, prevTime;

int timeOut = 3000;
int time = millis();

//sizes
int w = 1920; //--------------------<set w
int h = 1080; //---------------------<set h
int camW = 640;//1920; //--------------------<set camera resolution
int camH = 480;//1080; //----------------------<set camera resolution

//int w = 1280; //--------------------<set w
//int h = 720; //---------------------<set h
//int camW = 1280; //--------------------<set camera resolution
//int camH = 720; //----------------------<set camera resolution

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

PImage[] Sfilm = new PImage[7];
PImage[] UFStrip = new PImage[7];
PImage[] LFStrip = new PImage[7];

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
float frameC;

//------------------------------------------------------------setup
void setup() {
  size(1920, 1080, P3D); //needs 16:9
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

  logo = loadImage("cornerlogo.jpg");
  stroke(255);

  home = new HomeFeed();
  feed1 = new FilmFeed1();
  feed2 = new FilmFeed2();
  feed3 = new FilmFeed3();

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
  //nya.addNyIdMarker(158, 80); //id=158
  //nya.addNyIdMarker(253, 80); //id=253
  nya.addNyIdMarker(358, 80); //id=358
  cam.start();

  /* strip setup */
  fuji400 = loadImage("fuji400logo.jpg");
  { 
    for (int i = 0; i < Sfilm.length; i++) { 
      (Sfilm[i] = loadImage("Sfilm"+i+".jpg")).resize (800, 534);
    }
    y=ycentre/2;
    x=xcentre;
    SfilmSpacing = height/1.32;
    SfilmStripLength = SfilmSpacing*Sfilm.length;
    SfilmSpeed = 0.6;
  }

  size(1920, 1080);
  for (int i = 0; i < UFStrip.length; i++) { 
    (UFStrip[i] = loadImage("Sfilm"+i+".jpg")).resize (500, 333);
    (LFStrip[i] = loadImage("Tfilm"+i+".jpg")).resize (500, 333);
  }
  y=ycentre/2;
  x=xcentre;
  HStripSpacing = height/2.13;
  HStripStripLength = HStripSpacing*UFStrip.length;
  HStripSpeed = 0.8;
}

//iro200 = loadImage("iro200logo.jpg");
//ilford400 = loadImage("ilford400logo.jpg");


//------------------------------------------update
void update(){
}


//------------------------------------------------------------draw
void draw() {

  //frame.setTitle("" + frameCount);
  
  background(47, 54, 64);
  logos(); //draw logos
  drawClock();
  
  detectMarker(); // look for marker
  updateState(); 
  drawScreens(); // select screen

}


//------------------------------------------logos
void logos(){


  image(logo, 0, 980);
  
  
  
}

//------------------------------------------------------------drawClock
void drawClock()
{
  digitalClock.getTime();
  digitalClock.display(w, h);
}

//-----------------------------------------------HomeScreenTimers
void timers(){

  frame = frame + 0.005; // change for home toggle duration
  
  if (frame >= 1){
    display = 1;
    if (frame >= 2){
      display = 0;
      reset = frame;
      frame = frame - reset;
      }
  }
}

//------------------------------------------------------------drawScreens
void drawScreens() {

  if (state == 0)
  {   
    timers();
    home.draw(display);
  } else
 
  if (state == 1)
   {
     feed1.draw();
   }
}

//------------------------------------------------------------updateState
void updateState() {

  if ((state == 0) && (marker_detected == true)) {
    state = 1;
  }
}

//------------------------------------------------------------startTimer
void startTimer() {
  // reset timer
  prevTime = curTime = millis();
}

//------------------------------------------------------------updateTimer
void updateTimer() {
  curTime = millis();
  if ((curTime - prevTime) > timeOut)
  {
    println("marker timed out!");
    marker_detected = false;
    state = 0;
    println("reset timer");
  }
}


//------------------------------------------------------------detectMarker
void detectMarker() {

  updateTimer();

  if (cam.available() !=true) {
    return;
  }
  cam.read();
  nya.detect(cam);

  marker_detected = false;
  for (int i=0; i<2; i++) {
    if ((!nya.isExist(0))) {
      continue;
    }
    println("found marker"+ i);
    marker_detected = true;

    startTimer();
  }
}
