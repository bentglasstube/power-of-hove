#pragma once

#include "graphics.h"
#include "rect.h"
#include "spritemap.h"

class Map {
  public:

    enum class TileType { BLOCK, EMPTY };

    struct Tile {
      TileType type;
      bool obstruction;
      double top, left, right, bottom;
    };

    Map();

    void load(const std::string& file);
    void draw(Graphics& graphics, int xoffset, int yoffset) const;

    Tile tile(double x, double y) const;
    Tile collision(Rect box, double dx, double dy) const;
    int pixel_width() const;
    int pixel_height() const;

  private:

    static constexpr int kTileSize = 16;
    static constexpr Tile kNullTile {};

    SpriteMap tileset_;
    int width_, height_;
    TileType tiles_[128][1024];

    Tile itile(int x, int y) const;
    Tile check_tiles(int x1, int x2, int y1, int y2) const;
};
