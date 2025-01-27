#pragma once


#include <vector>
#include <memory>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>
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
#include "ThreadPool.h"

 
//------------------------------------------------------------------------------
// Класс Elements
//------------------------------------------------------------------------------
/**
 * @brief Класс Elements
 * 
 * Управляет всеми игровыми объектами: зомби, растениями, снарядами и солнцами.
 */
class Elements {
public:
    std::vector<std::unique_ptr<Zombie>> zombies; ///< Список зомби на поле.
    std::vector<std::unique_ptr<Plant>> plants; ///< Список растений на поле.
    std::vector<std::unique_ptr<Pea>> peas; ///< Список снарядов на поле.
    std::vector<Sun> suns; ///< Список солнц на поле.
    Elements();
    /**
     * @brief Генерирует солнце на небе.
     */
    void genSkySun();
    /**
     * @brief Удаляет солнца, которые слишком долго находятся на поле.
     */
    void removeSuns();
    /**
     * @brief Генерирует солнце над растением.
     * @param plant Растение, создающее солнце.
     * @param map Карта игрового поля.
     */
    void genPlantSun(Plant* plant, const Map<Block> &map);
    /**
     * @brief Устанавливает всех зомби в движущееся состояние.
     */
    void setAllZombiesMoving();
    /**
     * @brief Добавляет нового зомби на поле.
     * @param zombie Зомби для добавления.
     */
    void addZombie(std::unique_ptr<Zombie>zombie);
    /**
     * @brief Проверяет, достиг ли зомби растения.
     * @param zombie Зомби для проверки.
     * @param map Карта игрового поля.
     * @return true, если зомби достиг растения.
     */
    bool hasZombieReachedAnyElement(Zombie *zombie, const Map<Block> &map);
    /**
     * @brief Проверяет, может ли зомби двигаться.
     * @param zombie Зомби для проверки.
     * @param map Карта игрового поля.
     * @return true, если зомби может двигаться.
     */
    bool canMove(Zombie * zombie, const Map<Block> &map);
    /**
     * @brief Двигает всех зомби, которые могут двигаться.
     * @param map Карта игрового поля.
     */
    void moveZombies(const Map<Block> &map);
    /**
     * @brief Проверяет, может ли снаряд двигаться.
     * @param pea Снаряд для проверки.
     * @param map Карта игрового поля.
     * @return true, если снаряд может двигаться.
     */
    bool canPeaMove(Pea & pea, const Map<Block> &map);
    /**
     * @brief Двигает все снаряды, которые могут двигаться.
     * @param map Карта игрового поля.
     */
    void movePeas(const Map<Block> &map);
    /**
     * @brief Двигает солнца на игровом поле.
     * @param map Карта игрового поля.
     */
    void moveSuns(const Map<Block> &map);
    /**
     * @brief Проверяет, пересекли ли зомби заданную границу.
     * @param boundary_x Координата X границы.
     * @return true, если хотя бы один зомби пересёк границу.
     */
    [[nodiscard]] bool hasZombiesPassedBoundary(int boundary_x) const;
    /**
     * @brief Обрабатывает взаимодействие растений с зомби.
     * @param map Карта игрового поля.
     */
    void handlePlant(const Map<Block> &map);
    /**
     * @brief Выполняет выстрелы растений по зомби.
     * @param map Карта игрового поля.
     */
    void firePeas(const Map<Block> &map);
    /**
     * @brief Применяет эффект снаряда к зомби.
     * @param p_ind Индекс снаряда.
     * @param z_ind Индекс зомби.
     */
    void applyHitting(int p_ind, int z_ind);
    /**
     * @brief Обрабатывает взаимодействие снарядов с зомби.
     * @param map Карта игрового поля.
     */
    void handlePea(const Map<Block> &map);
    /**
     * @brief Обрабатывает движения зомби, снарядов и солнц.
     * @param map Карта игрового поля.
     * @param clk Текущее время.
     */
    void handleMovements(const Map<Block> &map, int clk);
    /**
     * @brief Обновляет все игровые объекты (зомби, снаряды, солнца) в отдельных потоках.
     * @param map Карта игрового поля.
     * @param gameOver Флаг завершения игры.
     * @param clk Текущее время.
     */
	void updateAll(const Map<Block>& map, bool& gameOver, int clk) {
	    std::mutex gameOverMutex; 
	    ThreadPool pool(std::thread::hardware_concurrency());
	    auto zombieFuture = pool.enqueue([this, &map, &gameOver, &gameOverMutex, clk] {
	        updateZombies(map, gameOver, gameOverMutex, clk); 
	    });
	    auto peaFuture = pool.enqueue([this, &map, clk] {
	        updatePeas(map, clk);
	    });
	    auto sunFuture = pool.enqueue([this, &map, clk] {
	        updateSuns(map, clk); 
	    });
	    zombieFuture.get();
	    peaFuture.get();
	    sunFuture.get();
	}
private:
    /**
     * @brief Обновляет состояние зомби.
     * @param map Карта игрового поля.
     * @param gameOver Флаг завершения игры.
     * @param gameOverMutex Мьютекс для безопасного изменения gameOver.
     * @param clk Текущее время.
     */
	void updateZombies(const Map<Block>& map, bool& gameOver, std::mutex& gameOverMutex, int clk) {
		if (clk % Zombie::TIME == 0) {
		    for (auto & zombie : zombies) {
		        if (!canMove(zombie.get(), map)) {
		            std::lock_guard<std::mutex> lock(gameOverMutex);
		            gameOver = true;
		            return;
		        }
		        zombie->move();
		    }
		}
	}
	/**
	 * @brief Обновляет состояние снарядов.
	 * @param map Карта игрового поля.
	 * @param clk Текущее время.
	 */
	void updatePeas(const Map<Block>& map, int clk) {
	    if (clk % Pea::TIME == 0) {
	        movePeas(map);
	    }
	}
	/**
	 * @brief Обновляет состояние солнц.
	 * @param map Карта игрового поля.
	 * @param clk Текущее время.
	 */
	void updateSuns(const Map<Block>& map, int clk) {
		if (clk % Sun::TIME == 0) {
	    	moveSuns(map);
	    }
	}
};

