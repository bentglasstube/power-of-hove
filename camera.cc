#include "camera.h"

double bound(double min, double value, double max) {
  if (value < min) return min;
  if (value > max) return max;
  return value;
}

Camera::Camera() {}

void Camera::update(const Player& player, const Map& map, unsigned int elapsed) {
  const double px = player.posx();
  const double py = player.posy();
  const double delta = kMaxSpeed * elapsed;

  // try to keep the player centered
  ox_ = bound(ox_ - delta, px - kWidth / 2, ox_ + delta);
  if (player.on_ground()) oy_ = bound(oy_ - delta, py - 5 * kHeight / 6, oy_ + delta);

  // force camera to have player on screen
  ox_ = bound(px + kBuffer - kWidth, ox_, px - kBuffer);
  oy_ = bound(py + kBuffer - kHeight, oy_, py - kBuffer);

  // force camera within bounds
  ox_ = bound(0, ox_, map.pixel_width() - kWidth);
  oy_ = bound(0, oy_, map.pixel_height() - kHeight);
}

double Camera::xoffset() const {
  return ox_;
}

double Camera::yoffset() const {
  return oy_;
}
