#pragma once

#include "input.h"
#include "graphics.h"
#include "sprite.h"
#include "spritemap.h"

#include "map.h"
#include "rect.h"

class Player {
  public:

    Player();

    void update(const Map& map, unsigned int elapsed);
    void draw(Graphics& graphics, int xoffset, int yoffset) const;
    void draw_power(Graphics& graphics, int x, int y) const;

    double posx() const;
    double posy() const;

    bool on_ground() const;

    void move_left();
    void move_right();
    void stop_moving();
    void jump();

  private:

    static constexpr double kGravity = 0.001;
    static constexpr double kJumpSpeed = 0.5;
    static constexpr double kAccel = 0.001;
    static constexpr double kDampen = 0.95;

    static constexpr double kJumpCost = 2.5;
    static constexpr double kIdleCost = 0.001;

    static constexpr int kWidth = 48;
    static constexpr int kHalfWidth = kWidth / 2;
    static constexpr int kHeight = 16;
    static constexpr int kCellSize = 25;

    Sprite board_;
    SpriteMap cells_;

    double max_power_, power_;
    double x_, y_, vx_, vy_, ax_;
    unsigned int frames_;
    SDL_Rect col_;

    void updatex(const Map& map, unsigned int elapsed);
    void updatey(const Map& map, unsigned int elapsed);

    Rect boxh() const;
    Rect boxv() const;
};
