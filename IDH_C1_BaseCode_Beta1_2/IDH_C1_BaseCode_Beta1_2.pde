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
FilmScreen screen1;
IntroScreen intro;

float curTime, prevTime;

int timeOut = 5000;

//sizes
int w = 1280; //--------------------<set w
int h = 720; //---------------------<set h
int camW = 640; //--------------------<set camera resolution
int camH = 480; //--------------------<set camera resolution

//font sizes
int heading;
int body;
int body1;
int body2;

//ALIGN TO
int left;
int left1;
int xcentre;
int right;
int right1;
int top;
int top1;
int bottom;
int bottom1;
int ycentre;
int state = 0;

PImage fuji400; 
PImage[] Sfilm = new PImage[7];
float x; 
float y;
float SfilmSpacing;
float SfilmStripLength;
float SfilmSpeed;

//------------------------------------------------------------setup
void setup() {

  size(1280, 720, P3D); //needs 16:9
  
  textAlign(LEFT);
  heading = h/15;
  body = h/30;
  body1 = h/45;
  left = w/10;
  right = w-w/10;
  top = h/10;
  top1 = h/5;
  bottom = h-h/10;
  bottom1 = h-h/5;
  xcentre = w/2;
  ycentre = h/2;
  
  logo = loadImage("cornerlogo.jpg");
  stroke(255);

  intro = new IntroScreen();
  screen1 = new FilmScreen();

  /* setup animation */
  myAnimation = new Gif(this, "test.gif");
  myAnimation.play();

  // The font must be located in the sketch's 
  // "data" directory to load successfully
  font1 = loadFont("PTSans-Regular-48.vlw");
  font2 = loadFont("FuturaPT-Heavy-48.vlw");


  /* setup clock */
  digitalClock = new DigitalClock(40); 

  /* camera setup */
  println(MultiMarker.VERSION);
  cam=new Capture(this, camW, camH);
  nya=new MultiMarker(this, width, height, "camera_para.dat", NyAR4PsgConfig.CONFIG_PSG);
  nya.addARMarker("patt.hiro", 80);//id=0
  nya.addARMarker("patt.kanji", 80);//id=1
  cam.start();

  /* strip setup */
  fuji400 = loadImage("fuji400logo.jpg");
  { 
    for (int i = 0; i < Sfilm.length; i++) { 
      (Sfilm[i] = loadImage("Sfilm"+i+".jpg")).resize(w/2, h/2);
    }
    y=ycentre/2;
    x=xcentre;
    SfilmSpacing = w/2;
    SfilmStripLength = SfilmSpacing*Sfilm.length;
    SfilmSpeed = 1;
  }
}

//------------------------------------------------------------drawClock
void drawClock()
{
  digitalClock.getTime();
  digitalClock.display(w, h);
}

//------------------------------------------------------------drawScreens
void drawScreens() {

  if (state == 0)
  {
    intro.draw();
  } else
    if (state == 1)
    {
      screen1.draw();
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

//------------------------------------------------------------Draw
void draw() {
  
  println(frameRate);
   background(47, 54, 64);
  image(logo, 0, 980);

  detectMarker();
  updateState();

  drawClock();  
  drawScreens();
}

//------------------------------------------------------------detectMarker
void detectMarker()
{

  updateTimer();

  if (cam.available() !=true) {
    return;
  }
  cam.read();
  nya.detect(cam);

  marker_detected = false;
  for (int i=0; i<2; i++) {
    if ((!nya.isExist(i))) {
      continue;
    }
    println("found marker"+ i);
    marker_detected = true;

    startTimer();
  }
}
