class HomeFeed {
  PFont font;

int _display;

  HomeFeed() {
    font = loadFont("FuturaPT-Heavy-48.vlw");
  }

  void draw(int _display) {

    fill(255);
    textFont(font1, body);
    text("Place a film or camera in front of the orb to begin.", left, bottom);

    textFont(font2, heading);
    fill(251, 207, 24);
    text("public feed", left1, top);


  if (display == 1){
   x = x + HStripSpeed;
    for (int i = 0; i < UFStrip.length; i++) { 
      image(UFStrip[i], - (x + i * HStripSpacing) % HStripStripLength + h+1000, 140 );
      image(LFStrip[i], - (x + i * HStripSpacing) % HStripStripLength + h+1000, 550 );
    }
  }
  else if (display == 0)
  {
    image(myAnimation, 650, 250);  
  }
  }
}
