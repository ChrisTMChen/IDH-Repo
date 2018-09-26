class Feed
{
  int type; // e.g. home = 1, filmFeed = 2, cameraFeed = 3;
  String name;
  String description;
  PFont font;
  PImage icon;
  
  ArrayList<Photo> feed = new ArrayList<Photo>();
  
  Feed() 
  {
    font = loadFont("FuturaPT-Heavy-48.vlw");
  }
  
  Feed(String new_name, String desc, String new_icon) 
  {
    font = loadFont("FuturaPT-Heavy-48.vlw");
    name = new_name;
    icon = loadImage(new_icon);
    description = desc;
  }
  
  void setFont(PFont myfont) 
  {
   font = myfont; 
  }
  
  void addPhoto(Photo p)
  {
    feed.add(p);
  }
  
  void draw() 
  {
    textFont(font1, body);
    text(description, left, bottom); //"FilmNeverDie Iro 200"
  
    textFont(font2, heading);
    fill(251, 207, 24);
    text(name, left1, top);
    
    image(icon, 0, 840);
  
    x = x + SfilmSpeed;
    for (int i = 0; i < feed.size(); i++) {
      Photo photo = feed.get(i);
      image(photo.image, - (x + i * SfilmSpacing) % SfilmStripLength + h+1000, 140 );
    }    
  }
  
}
