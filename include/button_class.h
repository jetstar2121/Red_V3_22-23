#include <iostream>

// V5 Brain: 480 x 240 pixels

class square_button {
public:
  int begin_x;
  int begin_y;
  int end_x;
  int end_y;
  vex::color offColor;
  vex::color onColor;
  int width;
  int height;
  int sector;
  std::string text;
  bool isPressed;
  int current_x;
  int current_y;
  static int kPixel;
  int pixelLength;
  int centerX;
  int centerY;

  bool isPressing();
  square_button(int bx, int by, int w, int h);
  square_button();
  square_button(int bx, int by, int w, int h, std::string txt);
  void activate(vex::color off, vex::color on);
};