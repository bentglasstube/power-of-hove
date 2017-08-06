#include "player.h"

#include <algorithm>
#include <cmath>
#include <iostream>

Player::Player(GameState state) :
  barty_("barty.png", 8, kWidth, kHeight),
  cells_("power.png", 7, 8, 8),
  max_power_(state.power_cells * 25), power_(max_power_),
  x_(0), y_(0), vx_(0), vy_(0), ax_(0),
  facing_(Facing::Right), grounded_(false),
  can_dj_(state.double_jump), did_dj_(false)
#ifndef NDEBUG
  , xcol_({0, 0, 0, 0}), ycol_({0, 0, 0, 0})
#endif
{}

void Player::update(Audio& audio, const Map& map, unsigned int elapsed) {
  updatex(audio, map, elapsed);
  updatey(audio, map, elapsed);

  // Shitty "friction"
  vx_ *= kDampen;
  vy_ *= kDampen;

  if (power_ > 0) {
    drain(audio, kIdleCost * elapsed);
  } else {
    vx_ *= kDampen * kDampen;
  }
}

void Player::draw(Graphics& graphics, int xoffset, int yoffset) const {
  const int x = x_ - kHalfWidth - xoffset;
  const int y = y_ - kHeight - yoffset;
  barty_.draw_ex(graphics, aframe(), x, y, facing_ == Facing::Left, 0, 0, 0);

#ifndef NDEBUG
  const Rect h = boxh();
  const SDL_Rect hr {
      (int)(h.left - xoffset),
      (int)(h.top - yoffset),
      (int)(h.right - h.left),
      (int)(h.bottom - h.top)
      };
  graphics.draw_rect(&hr, 0x0000ffff, false);

  const Rect v = boxv();
  const SDL_Rect vr {
      (int)(v.left - xoffset),
      (int)(v.top - yoffset),
      (int)(v.right - v.left),
      (int)(v.bottom - v.top)
      };
  graphics.draw_rect(&vr, 0x0000ffff, false);

  const SDL_Rect crx { xcol_.x - xoffset, xcol_.y - yoffset, xcol_.w, xcol_.h };
  graphics.draw_rect(&crx, 0xff0000ff, false);
  const SDL_Rect cry { ycol_.x - xoffset, ycol_.y - yoffset, ycol_.w, ycol_.h };
  graphics.draw_rect(&cry, 0x800000ff, false);
#endif
}

void Player::draw_power(Graphics& graphics, int x, int y) const {
  const int cells = std::ceil(max_power_ / kCellSize);
  for (int i = 0; i < cells; ++i) {
    const int c = std::max(0, std::min(6, (int) (6 * (power_ - i * kCellSize) / kCellSize)));
    cells_.draw(graphics, c, 8 * i + x, y);
  }
}

double Player::xpos() const {
  return x_;
}

double Player::ypos() const {
  return y_;
}

bool Player::on_ground() const {
  return grounded_;
}

bool Player::dead() const {
  return power_ <= 0;
}

void Player::set_pos(double x, double y) {
  x_ = x;
  y_ = y;
}

void Player::move_left() {
  facing_ = Facing::Left;
  ax_ = -kAccel;
}

void Player::move_right() {
  facing_ = Facing::Right;
  ax_ = kAccel;
}

void Player::stop_moving() {
  ax_ = 0;
}

void Player::jump(Audio& audio) {
  if (power_ < kJumpCost) return;

  if (!on_ground()) {
    if (can_dj_) {
      if (did_dj_) return;
      audio.play_sample("doublejump.wav");
      did_dj_ = true;
    } else {
      return;
    }
  }

  vy_ -= kJumpSpeed;
  drain(audio, kJumpCost);
}

void Player::add_power() {
  power_ = std::min(max_power_, power_ + kCellSize);
}

void Player::updatex(Audio& audio, const Map& map, unsigned int elapsed) {
  if (power_ > 0) vx_ += ax_ * elapsed;

  Map::Tile tile = map.collision(boxh(), vx_ * elapsed, 0);
  if (tile.obstruction) {
#ifndef NDEBUG
    xcol_ = {
      (int) tile.left,
      (int) tile.top,
      (int) (tile.right - tile.left),
      (int) (tile.bottom - tile.top)
    };
#endif
    if (std::abs(vx_) > 0.1) audio.play_sample("bump.wav");
    x_ = vx_ > 0 ? tile.left - kHalfWidth : tile.right + kHalfWidth;
    vx_ = -vx_;
  } else {
    x_ += vx_ * elapsed;
  }
}

void Player::updatey(Audio&, const Map& map, unsigned int elapsed) {
  vy_ += kGravity * elapsed;
  grounded_ = false;

  Map::Tile tile = map.collision(boxv(), 0, vy_ * elapsed);
  if (tile.obstruction) {
#ifndef NDEBUG
    ycol_ = {
      (int) tile.left,
      (int) tile.top,
      (int) (tile.right - tile.left),
      (int) (tile.bottom - tile.top)
    };
#endif
    if (vy_ > 0) {
      y_ = tile.top;
      grounded_ = true;
      did_dj_ = false;
    } else {
      y_ = tile.bottom + kHeight;
    }
    vy_ = 0;
  } else {
    y_ += vy_ * elapsed;
  }
}

void Player::drain(Audio& audio, double amount) {
  const int c1 = (int) (power_ / kCellSize);
  power_ -= amount;
  const int c2 = (int) (power_ / kCellSize);
  if (power_ < 0) {
    audio.play_sample("powerloss.wav");
  } else if (c2 < c1) {
    audio.play_sample("drain.wav");
  }
}

Rect Player::boxh() const {
  return Rect(x_ - kHalfWidth, y_ - kHeight + 4, x_ + kHalfWidth, y_ - 4);
}

Rect Player::boxv() const {
  return Rect(x_ - kHalfWidth + 2, y_ - kHeight, x_ + kHalfWidth - 2, y_);
}

int Player::aframe() const {
  const int f = SDL_GetTicks() / 100;
  if (power_ <= 0) return 6;
  if (vy_ >= 0.2) return 4 + f % 2;
  if (std::abs(vx_) >= 0.15) return f % 4;
  return 0;
}
