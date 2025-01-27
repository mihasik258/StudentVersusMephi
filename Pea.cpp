#include "Pea.h"
#include "Constants.h"

Pea::Pea() : row(0), x_location(0), directory(DIRECTORY) {}

bool Pea::reachedZombie(const Zombie *zombie) const {
    return (zombie->getRow() == row) && 
           ((x_location + DX) >= (zombie->xLocation() + 30));
}

void Pea::move() {
    x_location += DX;
}

void Pea::applyEffect(Zombie *zombie) {
    if (zombie->hasEffect("fire") && !zombie->hasEffect("ice")) {
        zombie->applyDamage(1);
    }
    zombie->applyDamage(1);
}
void Pea::draw(window &win, const Map<Block> &map) const{
	auto [left_bound, right_bound] = map.getHorizontalLimits(0, 8);
	auto [upper_bound, lower_bound] = map.getVerticalLimits(row, 0);
	int y_location = upper_bound + HEIGHT;
	if (x_location < (right_bound))
		win.draw_png(directory, x_location, y_location, WIDTH, HEIGHT);
}
