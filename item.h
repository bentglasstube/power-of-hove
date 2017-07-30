#pragma once

#include "graphics.h"
#include "spritemap.h"

class Item {
  public:

    enum class ItemType { Battery, Plutonium };

    Item(ItemType type, double x, double y);

    void draw(Graphics& graphics, int x, int y) const;
    ItemType type() const;
    double xpos() const;
    double ypos() const;

    bool operator==(const Item& other) const;

  private:

    SpriteMap sprites_;
    ItemType type_;
    double x_, y_;
};
