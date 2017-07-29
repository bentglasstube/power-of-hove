#pragma once

#include <string>

#include "graphics.h"

class ParallaxBackdrop {
  public:
    ParallaxBackdrop(const std::string& file, double scale);

    void draw(Graphics& graphics, double xoffset, double yoffset);

  private:
    std::string file_;
    double scale_;
};
