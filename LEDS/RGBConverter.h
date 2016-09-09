#ifndef RGBCONVERTER_H
#define RGBCONVERTER_H

struct RGB
{
  unsigned char r;
  unsigned char g;
  unsigned char b;
};

class RGBConverter
{
  public:
    RGB *hsvToRgb(double h, double s, double v);

  private:
    RGB output;
};

#endif
