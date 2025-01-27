#include "Firepea.h"
#include "Constants.h"


Firepea::Firepea() {
    directory = DIRECTORY;
}
void Firepea::applyEffect(Zombie *zombie){
    zombie->addEffect("fire");
    if (zombie->hasEffect("fire") && zombie->hasEffect("ice")) {
        zombie->removeEffect("fire");
        zombie->removeEffect("ice");
    }
    else if (zombie->hasEffect("fire")) {
        zombie->applyDamage(1);
    }
    zombie->applyDamage(1);
}
