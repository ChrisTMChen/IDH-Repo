class IntroScreen {
  PFont font;

  IntroScreen() {
    font = loadFont("FuturaPT-Heavy-48.vlw");
  }

  void draw() {

    fill(255);
    textFont(font1, body);
    text("Place a film or camera infront of the orb to begin.", left, bottom);

    textFont(font2, heading);
    fill(251, 207, 24);
    text("feed", left, top);

  image(myAnimation, xcentre/2, ycentre/2, xcentre, ycentre);
  
    }
  }
