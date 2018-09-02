class FilmFeed1 {
  PFont font;

  FilmFeed1() {
    font = loadFont("FuturaPT-Heavy-48.vlw");
  }

  void draw() {

    fill(255);
    textFont(font1, body);
    text("FilmNeverDie Iro 200", left, bottom);

    textFont(font2, heading);
    fill(251, 207, 24);
    text("film feed", left1, top);
    
    image(iro200, 0, 840);

    x = x + SfilmSpeed;
    for (int i = 0; i < Sfilm.length; i++) { 
      image(Sfilm[i], - (x + i * SfilmSpacing) % SfilmStripLength + h+1000, y - y/10 );
    }
  }
}
