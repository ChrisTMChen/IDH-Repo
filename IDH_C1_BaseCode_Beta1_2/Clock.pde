class DigitalClock extends Clock {
  int fontSize;

  DigitalClock(int _fontSize) {
    fontSize = _fontSize;
  }

  void getTime() {
    super.getTime();
  }

  void display(float x, float y) {
    textSize(fontSize);
    textAlign(CENTER);
    text (h + ":" + nf(m, 2), 1840, 60);
  }
}

class Clock {
  int h, m;
  Clock() {
  }

  void getTime() {
    h = hour();
    m = minute();
  }
}
