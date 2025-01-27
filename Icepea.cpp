#include "Icepea.h"
#include "Constants.h"


Icepea::Icepea() {
    directory = DIRECTORY;
}
void Icepea::applyEffect(Zombie *zombie){
    zombie->addEffect("ice");
    if (zombie->hasEffect("fire") && zombie->hasEffect("ice")) {
        zombie->removeEffect("fire");
        zombie->removeEffect("ice");
    }
    else if (zombie->hasEffect("ice")){
        zombie->setSpeed(Zombie::DX/2);
    }
    zombie->applyDamage(1);
}
