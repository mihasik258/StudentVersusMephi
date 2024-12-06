#include "Icepea.h"
#include "Constants.h"


Icepea::Icepea() {
    directory = C1_DIRECTORY;
}
void Icepea::applyEffect(Zombie &zombie){
    zombie.addEffect("ice");
    if (zombie.hasEffect("fire") && zombie.hasEffect("ice")) {
        zombie.removeEffect("fire");
        zombie.removeEffect("ice");
    }
    else if (zombie.hasEffect("ice")){
        zombie.speed = STUDENT_DX/2;
    }
    zombie.health -= 1;
}
