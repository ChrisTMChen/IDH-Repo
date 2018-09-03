class CameraFeed1 {
  PFont font;

  CameraFeed1() {
    font = loadFont("FuturaPT-Heavy-48.vlw");
  }

  void draw() {

    fill(255);
    textFont(font1, body);
    text("Olympus OM2N", left, bottom);

    textFont(font2, heading);
    fill(251, 207, 24);
    text("camera feed", left1, top);
    
    //image(ilford400, 0, 840);

    //x = x + SfilmSpeed;
    //for (int i = 0; i < Ilfordfilm.length; i++) { 
    //  image(Ilfordfilm[i], - (x + i * SfilmSpacing) % SfilmStripLength + h+1000, y - y/10 );
    //}
  }
}
