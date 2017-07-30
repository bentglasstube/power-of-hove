#include "map.h"

#include <iostream>
#include <fstream>

Map::Map() : tileset_("tiles.png", 8, 16, 16) {}

#define COORD(n) (kTileSize * n + kTileSize / 2)
#define SET_TILE(t) tiles_[height_][x] = TileType::t
#define ADD_ITEM(i) items_.emplace_back(Item::ItemType::i, COORD(x), COORD(height_))

void Map::load(const std::string& file) {
  std::ifstream reader("content/" + file);

  std::string line;
  while (reader) {
    std::getline(reader, line);
    const size_t l = line.length();
    if (width_ == 0) width_ = l;
    for (size_t x = 0; x < l; ++x) {
      switch (line[x]) {
        case 'x':
          SET_TILE(Block);
          break;

        case '+':
          ADD_ITEM(Battery);
          break;

        case '*':
          ADD_ITEM(Plutonium);
          break;

        case '^':
          SET_TILE(SpikeBottom);
          break;

        case 'v':
          SET_TILE(SpikeTop);
          break;

        case '>':
          SET_TILE(SpikeLeft);
          break;

        case '<':
          SET_TILE(SpikeRight);
          break;

        case 'S':
          sx_ = COORD(x);
          sy_ = COORD(height_);
          break;
      }
    }
    ++height_;
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

  for (const auto& item : items_) {
    const int gx = item.xpos() - xoffset;
    const int gy = item.ypos() - yoffset;

    if (gx < -kTileSize || gx > graphics.width()) continue;
    if (gy < -kTileSize || gy > graphics.height()) continue;

    item.draw(graphics, gx, gy);
  }
}

const Item* Map::item(double x, double y) const {
  for (const auto& item : items_) {
    const double dx = item.xpos() - x;
    const double dy = item.ypos() - y;
    const double d2 = dx * dx + dy * dy;
    if (d2 < kTileSize * kTileSize) return &item;
  }
  return nullptr;
}

void Map::remove_item(const Item* item) {
  auto i = items_.begin();
  while (i != items_.end()) {
    if (*item == *i) {
      i = items_.erase(i);
      break;
    } else {
      i = std::next(i);
    }
  }
}

Map::Tile Map::tile(double x, double y) const {
  return itile((int)(x / kTileSize), (int)(y / kTileSize));
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

double Map::startx() const {
  return sx_;
}

double Map::starty() const {
  return sy_;
}

Map::Tile Map::itile(int x, int y) const {
  Tile tile;

  if (x < 0 || x >= width_ || y >= height_) {
    tile.type = TileType::Block;
  } else if (y < 0) {
    tile.type = TileType::Empty;
  } else {
    tile.type = tiles_[y][x];
  }

  tile.obstruction = tile.type >= TileType::Block && tile.type <= TileType::SpikeRight;
  tile.top = y * kTileSize;
  tile.left = x * kTileSize;
  tile.right = tile.left + kTileSize;
  tile.bottom = tile.top + kTileSize;

  return tile;
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
