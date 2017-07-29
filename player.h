#pragma once

#include "input.h"
#include "graphics.h"
#include "sprite.h"

#include "map.h"
#include "rect.h"

class Player {
  public:

    Player();

    void update(const Input& input, const Map& map, unsigned int elapsed);
    void draw(Graphics& graphics, int xoffset, int yoffset) const;

    double posx() const;
    double posy() const;

    bool on_ground() const;

    void move_left();
    void move_right();
    void stop_moving();
    void jump();

  private:

    static constexpr double kGravity = 0.001;
    static constexpr double kJump = 0.5;
    static constexpr double kAccel = 0.001;
    static constexpr double kDampen = 0.95;

    static constexpr int kWidth = 48;
    static constexpr int kHalfWidth = kWidth / 2;
    static constexpr int kHeight = 16;

    Sprite board_;

    double power_;
    double x_, y_, vx_, vy_, ax_;
    unsigned int frames_;
    SDL_Rect col_;

    void updatex(const Map& map, unsigned int elapsed);
    void updatey(const Map& map, unsigned int elapsed);

    Rect boxh() const;
    Rect boxv() const;
};
