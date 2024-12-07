#pragma once


#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include "Zombie.h"
#include "Plant.h"
#include "Pea.h"
#include "Sun.h"
#include "Sunflower.h"
#include "Walnut.h"
#include "Icepea.h"
#include "Firepea.h"
#include "Fireshooter.h"
#include "Iceshooter.h"
#include "Map.h"

class Elements {
public:
    std::vector<Zombie> zombies;
    std::vector<std::unique_ptr<Plant>> plants;
    std::vector<std::unique_ptr<Pea>> peas;
    std::vector<Sun> suns;
    Elements();
    void genSkySun();
    void removeSuns();
    void genPlantSun(Plant* plant, const Map<Block> &map);
    void setAllZombiesMoving();
    void addZombie(const Zombie &zombie);
    bool hasZombieReachedAnyElement(Zombie &zombie, const Map<Block> &map);
    bool canMove(Zombie & zombie, const Map<Block> &map);
    void moveZombies(const Map<Block> &map);
    bool canPeaMove(Pea & pea, const Map<Block> &map);
    void movePeas(const Map<Block> &map);
    void moveSuns(const Map<Block> &map);
    [[nodiscard]] bool hasZombiesPassedBoundary(int boundary_x) const;
    void handlePlant(const Map<Block> &map);
    void firePeas(const Map<Block> &map);
    void applyHitting(int p_ind, int z_ind);
    void handlePea(const Map<Block> &map);
    void handleMovements(const Map<Block> &map, int clk);
    void updateAll(const Map<Block>& map, bool& gameOver, int clk) {
        std::mutex gameOverMutex; 
        std::thread zombiesThread(&Elements::updateZombies, this, std::cref(map), std::ref(gameOver), std::ref(gameOverMutex), clk);
        std::thread peasThread(&Elements::updatePeas, this, std::cref(map), clk);
        std::thread sunsThread(&Elements::updateSuns, this, std::cref(map), clk);
        
        zombiesThread.join(); 
        peasThread.join();
        sunsThread.join();
    }
private:
	void updateZombies(const Map<Block>& map, bool& gameOver, std::mutex& gameOverMutex, int clk) {
		if (clk % STUDENT_TIME == 0) {
		    for (Zombie& zombie : zombies) {
		        if (!canMove(zombie, map)) {
		            std::lock_guard<std::mutex> lock(gameOverMutex);
		            gameOver = true;
		            return;
		        }
		        zombie.move();
		    }
		}
	}
	void updatePeas(const Map<Block>& map, int clk) {
	    if (clk % PEA_TIME == 0) {
	        movePeas(map);
	    }
	}
	void updateSuns(const Map<Block>& map, int clk) {
		if (clk % SUN_TIME == 0) {
	    	moveSuns(map);
	    }
	}
};

