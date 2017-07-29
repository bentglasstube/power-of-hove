#include "camera.h"

#include <algorithm>

double window(double min, double max, double focus, double size) {
  double target = focus - size / 2;
  if (target < min) return min;
  if (target > max - size) return max - size;
  return target;
}

Camera::Camera() {}

void Camera::update(const Player& player, const Map& map, unsigned int elapsed) {
  const double px = player.posx();
  const double py = player.posy();

  double tx = window(0, map.pixel_width(), px, kWidth);
  if (ox_ > tx) ox_ = std::max(ox_ - kMaxSpeed * elapsed, tx);
  if (ox_ < tx) ox_ = std::min(ox_ + kMaxSpeed * elapsed, tx);

  if (player.on_ground()) {
    double ty = window(0, map.pixel_height(), py - kHeight / 3, kHeight);
    if (oy_ > ty) oy_ = std::max(oy_ - kMaxSpeed * elapsed, ty);
    if (oy_ < ty) oy_ = std::min(oy_ + kMaxSpeed * elapsed, ty);
  }

  // force camera to have player on screen
  if (px - kBuffer < ox_) ox_ = px - kBuffer;
  if (px + kBuffer > ox_ + kWidth) ox_ = px - kWidth + kBuffer;
  if (py - kBuffer < oy_) oy_ = py - kBuffer;
  if (py + kBuffer > oy_ + kHeight) oy_ = py - kHeight + kBuffer;
}

double Camera::xoffset() const {
  return ox_;
}

double Camera::yoffset() const {
  return oy_;
}
