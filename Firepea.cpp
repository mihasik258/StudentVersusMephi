#include "Firepea.h"
#include "Constants.h"


Firepea::Firepea() {
    directory = C2_DIRECTORY;
}
void Firepea::applyEffect(Zombie &zombie){
    zombie.addEffect("fire");
    if (zombie.hasEffect("fire") && zombie.hasEffect("ice")) {
        zombie.removeEffect("fire");
        zombie.removeEffect("ice");
    }
    else if (zombie.hasEffect("fire")) {
        zombie.health -= 1;
    }
    zombie.health -= 1;
}