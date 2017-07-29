#include "map.h"

Map::Map() : tileset_("tiles.png", 8, 16, 16) {
  height_ = 128;
  width_ = 1024;

  for (int y = 0; y < height_; ++y) {
    for (int x = 0; x < width_; ++x) {
      tiles_[y][x] = y < 12 ? TileType::EMPTY : TileType::BLOCK;
    }
  }

  tiles_[11][0] = tiles_[11][1023] = TileType::BLOCK;

  for (int i = 1; i < 5; ++i) {
    for (int j = 0; j < i; ++j) {
      tiles_[11 - j][10 * i] = TileType::BLOCK;
    }
  }
}

void Map::draw(Graphics& graphics, int xoffset, int yoffset) const {
  for (int y = 0; y < height_; ++y) {
    const int gy = kTileSize * y - yoffset;
    if (gy < -kTileSize) continue;
    if (gy > graphics.height()) break;

    for (int x = 0; x < width_; ++x) {
      const int gx = kTileSize * x - xoffset;
      if (gx < -kTileSize) continue;
      if (gx > graphics.width()) break;

      tileset_.draw(graphics, static_cast<int>(tiles_[y][x]), gx, gy);
    }
  }
}

Map::Tile Map::tile(double x, double y) const {
  return itile((int)(x / kTileSize), (int)(y / kTileSize));
}

Map::Tile Map::itile(int x, int y) const {
  TileType t = tiles_[y][x];

  Tile tile;
  tile.type = t;
  tile.obstruction = t == TileType::BLOCK;
  tile.top = y * kTileSize;
  tile.left = x * kTileSize;
  tile.right = tile.left + kTileSize;
  tile.bottom = tile.top + kTileSize;

  return tile;
}

Map::Tile Map::collision(Rect r, double dx, double dy) const {
  if (dx != 0) {
    const int x = (int) ((dx < 0 ? r.left : r.right) + dx) / kTileSize;
    return check_tiles(x, x, (int) r.top / kTileSize, (int) r.bottom / kTileSize);
  }

  if (dy != 0) {
    const int y = (int) ((dy < 0 ? r.top : r.bottom) + dy) / kTileSize;
    return check_tiles((int) r.left / kTileSize, (int) r.right / kTileSize, y, y);
  }

  return kNullTile;
}

int Map::pixel_width() const {
  return width_ * kTileSize;
}

int Map::pixel_height() const {
  return height_ * kTileSize;
}

Map::Tile Map::check_tiles(int x1, int x2, int y1, int y2) const {
  for (int y = y1; y <= y2; ++y) {
    for (int x = x1; x <= x2; ++x) {
      const Tile t = itile(x, y);
      if (t.obstruction) return t;
    }
  }

  return kNullTile;
}
