#include "overworld_screen.h"

#include "level_screen.h"
#include "shop_screen.h"

OverworldScreen::OverworldScreen(GameState state) :
  text_("text.png"), backdrop_("map.png"), state_(state) {}

bool OverworldScreen::update(const Input& input, Audio&, unsigned int) {
  if (input.key_pressed(Input::Button::A)) {
    return false;
  }

  if (input.key_pressed(Input::Button::Left)) {
    if (--state_.level < 0) state_.level = kLevelCount - 1;
  }

  if (input.key_pressed(Input::Button::Right)) {
    if (++state_.level >= kLevelCount) state_.level = 0;
  }

  return true;
}

void OverworldScreen::draw(Graphics& graphics) const {
  backdrop_.draw(graphics);

  const auto& l = levels_[state_.level];

  text_.draw(graphics, l.description, graphics.width() / 2, 224, Text::Alignment::Center);

  if (SDL_GetTicks() / 250 % 2 == 0) {
    const SDL_Rect r = { l.x, l.y, kBoxSize, kBoxSize };
    graphics.draw_rect(&r, 0xffffffff, false);
  }
}

Screen* OverworldScreen::next_screen() const {
  const auto& l = levels_[state_.level];

  if (l.file.empty()) {
    return new ShopScreen(state_);
  } else {
    LevelScreen* s = new LevelScreen(state_);
    s->load_level(l.file);
    return s;
  }
}

std::string OverworldScreen::get_music_track() const {
  return "";
}

const OverworldScreen::Level OverworldScreen::levels_[] = {
  {  68,  36, "school.lvl",       "Mill Valley High" },
  { 148,  20, "forest.lvl",       "Peabody Forest" },
  { 164, 100, "mall.lvl",         "Twin Fir Mall" },
  {  36, 148, "",                 "Toc's Garage Lab" },
  { 116, 164, "neighborhood.lvl", "Tiger Manors" },
};
