#include "player.h"

#include <algorithm>
#include <cmath>
#include <iostream>

Player::Player() :
  board_("board.png", 0, 0, kWidth, kHeight),
  cells_("power.png", 7, 8, 8),
  max_power_(100), power_(max_power_), x_(64), y_(64)
{}

void Player::update(const Input& input, const Map& map, unsigned int elapsed) {
  // TODO move to screen class
  if (input.key_held(SDL_SCANCODE_A)) {
    move_left();
  } else if (input.key_held(SDL_SCANCODE_D)) {
    move_right();
  } else {
    stop_moving();
  }

  if (input.key_pressed(SDL_SCANCODE_SPACE)) {
    jump();
  }

  updatex(map, elapsed);
  updatey(map, elapsed);

  // Shitty "friction"
  vx_ *= kDampen;
  vy_ *= kDampen;

  if (power_ > 0) {
    power_ -= kIdleCost * elapsed;
  } else {
    vx_ *= kDampen * kDampen;
  }

  frames_ += elapsed;
}

void Player::draw(Graphics& graphics, int xoffset, int yoffset) const {
  const int yo = power_ > 0 ? 3 * std::sin(frames_ / 150.0) : 5;

  const int x = x_ - kHalfWidth - xoffset;
  const int y = y_ - kHeight - yoffset + yo;
  board_.draw(graphics, x, y);

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

  const SDL_Rect cr { col_.x - xoffset, col_.y - yoffset, col_.w, col_.h };
  graphics.draw_rect(&cr, 0xff0000ff, false);
#endif
}

void Player::draw_power(Graphics& graphics, int x, int y) const {
  const int cells = std::ceil(max_power_ / kCellSize);
  for (int i = 0; i < cells; ++i) {
    const int c = std::max(0, std::min(6, (int) (6 * (power_ - i * kCellSize) / kCellSize)));
    cells_.draw(graphics, c, 8 * i, y);
  }
}

double Player::posx() const {
  return x_;
}

double Player::posy() const {
  return y_;
}

bool Player::on_ground() const {
  return vy_ == 0;
}

void Player::move_left() {
  ax_ = -kAccel;
}

void Player::move_right() {
  ax_ = kAccel;
}

void Player::stop_moving() {
  ax_ = 0;
}

void Player::jump() {
  if (on_ground() && power_ > kJumpCost) {
    vy_ -= kJumpSpeed;
    power_ -= kJumpCost;
    // TODO play jump sound
  }
}

void Player::updatex(const Map& map, unsigned int elapsed) {
  if (power_ > 0) vx_ += ax_ * elapsed;

  Map::Tile tile = map.collision(boxh(), vx_ * elapsed, 0);
  if (tile.obstruction) {
    if (vx_ > 0) x_ = tile.left - kHalfWidth;
    else x_ = tile.right + kHalfWidth;
    vx_ = -vx_;
  } else {
    x_ += vx_ * elapsed;
  }
}

void Player::updatey(const Map& map, unsigned int elapsed) {
  vy_ += kGravity * elapsed;

  Map::Tile tile = map.collision(boxv(), 0, vy_ * elapsed);
  if (tile.obstruction) {
    col_ = {
      (int) tile.left,
      (int) tile.top,
      (int) (tile.right - tile.left),
      (int) (tile.bottom - tile.top)
    };
    if (vy_ > 0) {
      y_ = tile.top;
    } else {
      y_ = tile.bottom + kHeight;
    }
    vy_ = 0;
  } else {
    y_ += vy_ * elapsed;
  }
}

Rect Player::boxh() const {
  return Rect(x_ - kHalfWidth, y_ - kHeight + 4, x_ + kHalfWidth, y_ - 4);
}

Rect Player::boxv() const {
  return Rect(x_ - kHalfWidth + 2, y_ - kHeight, x_ + kHalfWidth - 2, y_);
}
