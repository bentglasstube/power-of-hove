#include "overworld_screen.h"

#include "level_screen.h"

void OverworldScreen::init() {
  backdrop_.reset(new Backdrop("map.png"));
  text_.reset(new Text("text.png"));
}

bool OverworldScreen::update(const Input& input, Audio& audio, unsigned int elapsed) {
  if (input.key_pressed(SDL_SCANCODE_SPACE)) {
    return false;
  }

  if (input.key_pressed(SDL_SCANCODE_A) || input.key_pressed(SDL_SCANCODE_W)) {
    if (--cursor_ < 0) cursor_ = kLevelCount - 1;
  }

  if (input.key_pressed(SDL_SCANCODE_D) || input.key_pressed(SDL_SCANCODE_S)) {
    if (++cursor_ >= kLevelCount) cursor_ = 0;
  }

  return true;
}

void OverworldScreen::draw(Graphics& graphics) const {
  backdrop_->draw(graphics);

  const auto& l = levels_[cursor_];

  text_->draw(graphics, l.description, graphics.width() / 2, 224, Text::Alignment::CENTER);

  if (SDL_GetTicks() / 250 % 2 == 0) {
    const SDL_Rect r = { l.x, l.y, kBoxSize, kBoxSize };
    graphics.draw_rect(&r, 0xffffffff, false);
  }
}

Screen* OverworldScreen::next_screen() {
  const auto& l = levels_[cursor_];

  if (l.file.empty()) {
    // TODO load shop
    return nullptr;
  } else {
    LevelScreen* s = new LevelScreen();
    s->load_level(l.file);
    return s;
  }
}

std::string OverworldScreen::get_music_track() const {
  return "";
}

const OverworldScreen::Level OverworldScreen::levels_[] = {
  {  68,  36, "school.lvl",       "Mill Valley High" },
  { 148,  20, "forest.lvl",       "Clever Name Forest" },
  { 164, 100, "mall.lvl",         "Twin Fir Mall" },
  {  36, 148, "",                 "Toc's Garage Lab" },
  { 116, 164, "neighborhood.lvl", "Tiger Manors" },
};
