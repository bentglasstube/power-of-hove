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

  if (done() && input.key_pressed(Input::Button::A)) {
    index_ = counter_ = 0;

    switch (phase()) {
      case 1:
        ++state_.power_cells;
        break;
      case 3:
        state_.double_jump = true;
        break;
      case 5:
        break;
      default:
        return false;
    }
  }

  return true;
}

void ShopScreen::draw(Graphics& graphics) const {
  backdrop_.draw(graphics);
  text_.draw(graphics, dialogs_[phase()].substr(0, index_), 8, 144);
}

Screen* ShopScreen::next_screen() {
  return new OverworldScreen(state_);
}

std::string ShopScreen::get_music_track() const {
  return "";
}

int ShopScreen::phase() const {
  if (state_.collected() == 0) return 0;
  if (state_.power_cells == 4) return 1;
  if (state_.collected() < 4) return 2;
  if (!state_.double_jump) return 3;
  if (state_.collected() < 8) return 4;

  return 5;
}

bool ShopScreen::done() const {
  return index_ >= dialogs_[phase()].length();
}

const std::string ShopScreen::dialogs_[] = {

R"(Great Scott, Barty!  I have
misplaced all my plutonium
around town.  If you bring it
back here, I will be able to
improve your hoverboard.)",

R"(You found one.  I don't
know how, but you found one.
If you give it to me I will
give your board another cell.)",

R"(Bring me three more bits of
plutonium and I'll be able
to upgrade your board again.)",

R"(When I'm done with this baby,
you're gonna see some serious
shit!  You can jump in mid-air
now, but only once.)",

R"(Damn!  There are still more
missing pieces of plutonium.
Round them all up and bring
them back here.)",

R"(Run for it, Barty!        
                             
                             
             The End.)",

};
