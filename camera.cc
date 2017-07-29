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
  double tx = window(0, map.pixel_width(), player.posx(), kWidth);
  if (ox_ > tx) ox_ = std::max(ox_ - kMaxSpeed * elapsed, tx);
  if (ox_ < tx) ox_ = std::min(ox_ + kMaxSpeed * elapsed, tx);

  double ty = window(0, map.pixel_height(), player.posy(), kHeight);
  if (oy_ > ty) oy_ = std::max(oy_ - kMaxSpeed * elapsed, ty);
  if (oy_ < ty) oy_ = std::min(oy_ + kMaxSpeed * elapsed, ty);
}

double Camera::xoffset() const {
  return ox_;
}

double Camera::yoffset() const {
  return oy_;
}
