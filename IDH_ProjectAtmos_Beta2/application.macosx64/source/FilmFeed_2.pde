class FilmFeed2 {
  PFont font;

  FilmFeed2() {
    font = loadFont("FuturaPT-Heavy-48.vlw");
  }

  void draw() {

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
