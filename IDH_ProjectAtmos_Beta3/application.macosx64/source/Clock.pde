class DigitalClock extends Clock {
  int fontSize;

  DigitalClock(int _fontSize) {
    fontSize = _fontSize;
  }

  void getTime() {
    super.getTime();
  }

  void display(float x, float y) {

    textSize(body1);
    textAlign(RIGHT);
    text (h + ":" + nf(m, 2), right, top1);
    textAlign(LEFT); //reset text align to left
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
