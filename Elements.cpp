#include "Elements.h"
#include "Constants.h"

Elements::Elements() = default;

void Elements::genSkySun(){
    srand(time(nullptr));
    Sun temp;
    temp.final_row = rand() % 5;
    temp.final_col = rand() % 9;
    temp.y_location = INIT_SUN_Y;
    temp.wait_seconds = 0;
    suns.push_back(temp);
}
void Elements::removeSuns(){
    for (int i = 0; i < suns.size(); i++)
        if (suns[i].wait_seconds >= 200)
            suns.erase(suns.begin() + i);
}
void Elements::genPlantSun(Plant* plant, const Map<Block> &map) {
    Sun temp;
    temp.final_col = plant->col;
    temp.final_row = plant->row;
    auto [left_bound, right_bound] = map.getVerticalLimits(plant->row, plant->col);
    temp.y_location = left_bound - 20;
    temp.wait_seconds = 0;
    suns.push_back(temp);
}
void Elements::setAllZombiesMoving() {
    for (Zombie &zombie : zombies) {
        zombie.is_moving = true;
    }
}
void Elements::addZombie(const Zombie &zombie) {
    zombies.push_back(zombie);
}
bool Elements::hasZombieReachedAnyElement(Zombie &zombie, const Map<Block> &map) {
    for (auto &plant : plants) {
        if (plant->isZombieNearby(zombie, map)) {
            zombie.is_moving = false;
            return true;
        }
    }
    zombie.is_moving = true;
    return false;
}
bool Elements::canMove(Zombie & zombie, const Map<Block> &map){
    auto [left_bound, right_bound] = map.getHorizontalLimits(0, 0);
    int zombie_new_location = zombie.x_location - STUDENT_DX;
    if (zombie_new_location < left_bound)
        return false;
    if (!zombie.is_moving)
        return false;
    if (hasZombieReachedAnyElement(zombie, map))
        return false;
    return true;
}
void Elements::moveZombies(const Map<Block> &map){
    for (auto & zombie : zombies){
        if (canMove(zombie,map))
            zombie.move();
    }
}
bool Elements::canPeaMove(Pea & pea, const Map<Block> &map){
    auto [left_bound, right_bound] = map.getHorizontalLimits(pea.row, 8);
    right_bound -= 20;
    if (pea.x_location + PEA_DX > right_bound)
        return false;
    for (auto & zombie : zombies)
        if (pea.reachedZombie(zombie))
            return false;
    return true;
}
void Elements::movePeas(const Map<Block> &map) {
    for (auto &pea : peas) {
        if (canPeaMove(*pea, map))
            pea->move();
    }
}
void Elements::moveSuns(const Map<Block> &map){
    for (auto & sun : suns){
        int row = sun.final_row;
        int col = sun.final_col;
        auto [left_bound, right_bound] = map.getVerticalLimits(row,col);
        int lower_limit = left_bound + 30;
        if (sun.y_location + SUN_DY < lower_limit)
            sun.y_location += SUN_DY;
        else
            sun.wait_seconds ++;
    }
}
[[nodiscard]] bool Elements::hasZombiesPassedBoundary(int boundary_x) const {
    for (const Zombie &zombie : zombies) {
        if (zombie.x_location < boundary_x) return true;
    }
    return false;
}
void Elements::handlePlant(const Map<Block> &map) {
    for (auto &plant : plants) {
        for (Zombie &zombie : zombies) {
            plant->handleZombie(zombie, map);
        }
    }
    plants.erase(
            std::remove_if(plants.begin(), plants.end(), [](const std::unique_ptr<Plant>& plant) {
                if (plant->is_destroyed) {
                    return true;
                }
                return false;
            }),
            plants.end());
}
void Elements::firePeas(const Map<Block> &map) {
    for (auto &plant : plants) {
        auto *shooter = dynamic_cast<Peashooter *>(plant.get());
        if (shooter) {
            shooter->fire(peas, map, zombies);
        }
    }
}
// ГОВНО ПЕРЕДЕЛАТЬ
void Elements::applyHitting(int p_ind, int z_ind) {
    if (peas[p_ind]->reachedZombie(zombies[z_ind])) {
        peas[p_ind]->applyEffect(zombies[z_ind]);
        peas.erase(peas.begin() + p_ind);
        zombies[z_ind].updateAppearance();
        if (zombies[z_ind].health == 0) {
            zombies.erase(zombies.begin() + z_ind);
        }
    }
}
void Elements::handlePea(const Map<Block> &map){
    for (int i = 0; i < zombies.size(); i++)
        for (int j = 0; j < peas.size(); j++)
            applyHitting(j, i);
}
void Elements::handleMovements(const Map<Block> &map, int clk){
    if (clk % STUDENT_TIME == 0)
        moveZombies(map);
    if (clk % PEA_TIME == 0)
        movePeas(map);
    if (clk % SUN_TIME == 0)
        moveSuns(map);
}
