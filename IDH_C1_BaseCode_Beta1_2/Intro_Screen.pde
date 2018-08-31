class IntroScreen {
  PFont font;

  IntroScreen() {
    font = loadFont("FuturaPT-Heavy-48.vlw");
  }

  void draw() {

    fill(255);
    textFont(font1, 40);
    text("Place a film or camera infront of the orb to begin.", 560, 1038);

    textFont(font2, 68);
    fill(251, 207, 24);
    text("feed", 110, 90);

  image(myAnimation, 650,250);
  
    }
  }
