class FilmScreen {
  PFont font;

  FilmScreen() {
    font = loadFont("FuturaPT-Heavy-48.vlw");
  }

  void draw() {

    fill(255);
    textFont(font1, 40);
    text("Fujifilm industrial 400", 320, 1038);

    textFont(font2, 68);
    fill(251, 207, 24);
    text("film feed", 180, 90);
    
    image(fuji400, 0, 840);

    x = x + SfilmSpeed;
    for (int i = 0; i < Sfilm.length; i++) { 
      image(Sfilm[i], - (x + i * SfilmSpacing) % SfilmStripLength + height, y -120 );
    }
  }
}
