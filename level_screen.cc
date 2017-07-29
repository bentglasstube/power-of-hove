#include "level_screen.h"

void LevelScreen::init() {
  text_.reset(new Text("text.png"));
  map_.load("test.lvl");
}

bool LevelScreen::update(const Input& input, Audio&, unsigned int elapsed) {
  camera_.update(player_, map_, elapsed);
  player_.update(input, map_, elapsed);
  return true;
}

void LevelScreen::draw(Graphics& graphics) const {
  const double cx = camera_.xoffset();
  const double cy = camera_.yoffset();

  map_.draw(graphics, cx, cy);
  player_.draw(graphics, cx, cy);
}

Screen* LevelScreen::next_screen() {
  return nullptr;
}

std::string LevelScreen::get_music_track() const {
  return "";
}
