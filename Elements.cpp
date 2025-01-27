#include "Elements.h"
#include "Constants.h"

Elements::Elements() = default;

void Elements::genSkySun() {
    srand(time(nullptr));
    auto sun = Sun();
    sun.setFinalRow(rand() % VERT_BLOCK_COUNT);
    sun.setFinalCol(rand() % HORIZ_BLOCK_COUNT);
    sun.setYLocation(Sun::INIT_Y);
    sun.resetWaitSeconds();
    suns.push_back(std::move(sun));
}
void Elements::removeSuns() {
    suns.erase(std::remove_if(suns.begin(), suns.end(),
                              [](const Sun &sun) { return sun.getWaitSeconds() >= 200; }),
               suns.end());
}
void Elements::genPlantSun(Plant *plant, const Map<Block> &map) {
    auto sun = Sun();
    sun.setFinalRow(plant->getRow());
    sun.setFinalCol(plant->getCol());
    auto [left_bound, _] = map.getVerticalLimits(plant->getRow(), plant->getCol());
    sun.setYLocation(left_bound);
    sun.resetWaitSeconds();
    suns.push_back(std::move(sun));
}
void Elements::setAllZombiesMoving() {
    for (auto &zombie : zombies) {
        zombie->startMoving();
    }
}
void Elements::addZombie(std::unique_ptr<Zombie> zombie) {
    zombies.push_back(std::move(zombie)); 
}
bool Elements::hasZombieReachedAnyElement(Zombie *zombie, const Map<Block> &map) {
    for (auto &plant : plants) {
        if (plant->isZombieNearby(zombie, map)) {
            zombie->stopMoving();
            return true;
        }
    }
    zombie->startMoving();
    return false;
}
bool Elements::canMove(Zombie *zombie, const Map<Block> &map){
    auto [left_bound, right_bound] = map.getHorizontalLimits(0, 0);
    int zombie_new_location =zombie->xLocation() - Zombie::DX;
    if (zombie_new_location < left_bound)
        return false;
    if (!zombie->isMoving())
        return false;
    if (hasZombieReachedAnyElement(zombie, map))
        return false;
    return true;
}
void Elements::moveZombies(const Map<Block> &map){
    for (auto & zombie : zombies){
        if (canMove(zombie.get(),map))
            zombie->move();
    }
}
bool Elements::canPeaMove(Pea & pea, const Map<Block> &map){
    auto [left_bound, right_bound] = map.getHorizontalLimits(pea.row, 8);
    if (pea.x_location + Pea::DX > right_bound)
        return false;
    for (auto & zombie : zombies)
        if (pea.reachedZombie(zombie.get()))
            return false;
    return true;
}
void Elements::movePeas(const Map<Block> &map) {
    for (auto &pea : peas) {
        if (canPeaMove(*pea, map))
            pea->move();
    }
}
void Elements::moveSuns(const Map<Block> &map) {
    for (auto &sun : suns) {
        int row = sun.getFinalRow(); 
        int col = sun.getFinalCol(); 
        auto [left_bound, right_bound] = map.getVerticalLimits(row, col);
        int lower_limit = left_bound;

        if (sun.getYLocation() + Sun::DY < lower_limit) {
            sun.setYLocation(sun.getYLocation() + Sun::DY);
        } else {
            sun.incrementWaitSeconds();
        }
    }
}
[[nodiscard]] bool Elements::hasZombiesPassedBoundary(int boundary_x) const {
    for (const auto &zombie : zombies) {
        if (zombie->xLocation() < boundary_x) return true; }
    return false;
}
void Elements::handlePlant(const Map<Block> &map) {
    for (auto &plant : plants) {
        for (auto &zombie : zombies) {
            plant->handleZombie(zombie.get(), map);
        }
    }
    plants.erase(
            std::remove_if(plants.begin(), plants.end(), [](const std::unique_ptr<Plant>& plant) {
                if (plant->isDestroyed()) {
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
void Elements::applyHitting(int p_ind, int z_ind) {
    if (peas[p_ind]->reachedZombie(zombies[z_ind].get())) {
        peas[p_ind]->applyEffect(zombies[z_ind].get());
        peas.erase(peas.begin() + p_ind);
        zombies[z_ind]->updateAppearance();
        if (zombies[z_ind]->getHealth() == 0) {
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
    if (clk % Zombie::TIME == 0)
        moveZombies(map);
    if (clk % Pea::TIME == 0)
        movePeas(map);
    if (clk % Sun::TIME == 0)
        moveSuns(map);
}

