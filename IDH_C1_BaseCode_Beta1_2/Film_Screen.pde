class FilmScreen {
  PFont font;

  FilmScreen() {
    font = loadFont("FuturaPT-Heavy-48.vlw");
  }

  void draw() {

    fill(255);
    textFont(font1, body);
    text("Fujifilm industrial 400", left, bottom);

    textFont(font2, heading);
    fill(251, 207, 24);
    text("film feed", left1, top);
    
    image(fuji400, left, bottom1, w/10, h/10);

    x = x + SfilmSpeed;
    for (int i = 0; i < Sfilm.length; i++) { 
      image(Sfilm[i], - (x + i * SfilmSpacing) % SfilmStripLength + h, y - y/9 );
    }
  }
}
