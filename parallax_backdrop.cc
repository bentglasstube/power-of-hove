#include "parallax_backdrop.h"

ParallaxBackdrop::ParallaxBackdrop(const std::string& file, double scale) : file_(file), scale_(scale) {}

void ParallaxBackdrop::draw(Graphics& graphics, double xoffset, double yoffset) {
  const SDL_Rect src = {
    (int) (xoffset / scale_),
    (int) (yoffset / scale_),
    graphics.width(),
    graphics.height()
  };
  graphics.blit(file_, &src, NULL);
}
