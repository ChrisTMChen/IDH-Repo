class HomeFeed {
  PFont font;

  HomeFeed() {
    font = loadFont("FuturaPT-Heavy-48.vlw");
  }

  void draw() {

    fill(255);
    textFont(font1, body);
    text("Place a film or camera in front of the orb to begin.", left, bottom);

    textFont(font2, heading);
    fill(251, 207, 24);
    text("home feed", left1, top);

  image(myAnimation, 650, 250);
  
    }
  }
