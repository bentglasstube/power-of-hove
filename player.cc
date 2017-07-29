#include "player.h"

#include <cmath>

Player::Player() : board_("board.png", 0, 0, kWidth, kHeight) {
  x_ = 60;
  y_ = 10;
}

void Player::update(const Input& input, const Map& map, unsigned int elapsed) {
  // TODO check if inputs are being pressed to control board
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

  // TODO calculate power drain
  // double drain = 0.001;
  // if jumping, use more, etc

  // TODO cap acceleration

  // some kind of shitty friction / air resistance?
  vx_ *= kDampen;
  vy_ *= kDampen;

  frames_ += elapsed;
}

void Player::draw(Graphics& graphics, int xoffset, int yoffset) const {
  const int x = x_ - kHalfWidth - xoffset;
  const int y = y_ - kHeight - yoffset /* + 3 * std::sin(frames_ / 150.0) */ ;
  board_.draw(graphics, x, y);

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
  if (on_ground()) vy_ -= kJump;
}

void Player::updatex(const Map& map, unsigned int elapsed) {
  vx_ += ax_ * elapsed;

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
    col_ = { tile.left, tile.top, tile.right - tile.left, tile.bottom - tile.top };
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
