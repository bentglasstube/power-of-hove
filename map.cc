#include "map.h"

#include <iostream>
#include <fstream>

Map::Map(GameState state) :
  state_(state), tileset_("tiles.png", 8, 16, 16),
  width_(0), height_(0), sx_(0), sy_(0) {}

#define COORD(n) (kTileSize * n + kTileSize / 2)
#define SET_TILE(t) tiles_[height_][x] = TileType::t
#define ADD_ITEM(i) items_.emplace_back(Item::ItemType::i, COORD(x), COORD(height_))

void Map::load(const std::string& file) {
  std::ifstream reader("content/" + file);

  // fuck you alan
  width_ = height_ = 0;

  std::string line;
  while (reader) {
    std::getline(reader, line);
    const size_t l = line.length();
    if (width_ == 0) width_ = l;
    for (size_t x = 0; x < l; ++x) {
      SET_TILE(Empty);

      switch (line[x]) {
        case '+':
          ADD_ITEM(Battery);
          break;

        case '*':
          if (!state_.grabbed(COORD(x), COORD(height_))) ADD_ITEM(Plutonium);
          break;

        case 'S':
          sx_ = COORD(x);
          sy_ = COORD(height_);
          break;

        case 'x': SET_TILE(Block);      break;
        case 'o': SET_TILE(Window);     break;
        case '[': SET_TILE(LogLeft);    break;
        case '=': SET_TILE(LogMid);     break;
        case ']': SET_TILE(LogRight);   break;
        case 'd': SET_TILE(Dirt);       break;
        case 'g': SET_TILE(Grass);      break;

        case 'I': SET_TILE(BeamStart);  break;
        case 'i': SET_TILE(BeamRest);   break;
        case '^': SET_TILE(DoorTop);    break;
        case 'v': SET_TILE(DoorBottom); break;
        case 'c': SET_TILE(Chair);      break;
        case 'f': SET_TILE(Flower);     break;
        case 'r': SET_TILE(Register);   break;
        case 'p': SET_TILE(Fence);      break;
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
    const double dy = item.ypos() - y + kTileSize / 2;
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

bool Map::out_of_bounds(double x, double y) const {
  const int px = x / kTileSize;
  return px < 0 || px > width_ || y / kTileSize > height_;
}

Map::Tile Map::itile(int x, int y) const {
  Tile tile;

  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    tile.type = TileType::Empty;
  } else {
    tile.type = tiles_[y][x];
  }

  tile.obstruction = tile.type >= TileType::Block && tile.type <= TileType::BeamRest;
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

const Map::Tile Map::kNullTile;
