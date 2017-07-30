#include "shop_screen.h"

#include "overworld_screen.h"

ShopScreen::ShopScreen(GameState state) :
  text_("text.png"), backdrop_("shopkeeper.png"),
  state_(state), counter_(0), index_(0) {}

bool ShopScreen::update(const Input& input, Audio& audio, unsigned int elapsed) {
  counter_ += elapsed;
  if (counter_ >= kTextRate) {
    ++index_;
    counter_ -= kTextRate;
  }

  if (done() && input.key_pressed(SDL_SCANCODE_SPACE)) return false;
  return true;
}

void ShopScreen::draw(Graphics& graphics) const {
  backdrop_.draw(graphics);
  text_.draw(graphics, dialog().substr(0, index_), 8, 144);
}

Screen* ShopScreen::next_screen() {
  return new OverworldScreen(state_);
}

std::string ShopScreen::get_music_track() const {
  return "";
}

std::string ShopScreen::dialog() const {
  if (state_.plutonium == 0) return dialogs_[0];
  return dialogs_[1];
}

bool ShopScreen::done() const {
  return index_ >= dialog().length();
}

const std::string ShopScreen::dialogs_[] = {

R"(Great Scott, Barty!  I have
misplaced all my plutonium
around town.  If you bring it
back here, I will be able to
improve your hoverboard.)",

R"(Damn, you found one of the
plutoniums I lost.  I don't
know how, but you found it.
If you give it to me I will
give your board another cell.)",

};
