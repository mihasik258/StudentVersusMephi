#include "Pea.h"
#include "Constants.h"

Pea::Pea() : row(0), x_location(0), directory(C_DIRECTORY) {}

bool Pea::reachedZombie(const Zombie &zombie) const {
    return zombie.row == row && x_location + PEA_DX > zombie.x_location + 30;
}

void Pea::move() {
    x_location += PEA_DX;
}

void Pea::applyEffect(Zombie &zombie) {
    if (zombie.hasEffect("fire") && !zombie.hasEffect("ice")) {
        zombie.health -= 1;
    }
    zombie.health -= 1;
}
