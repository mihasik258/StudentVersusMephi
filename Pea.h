#pragma once


#include "Zombie.h"
#include "Map.h"

//------------------------------------------------------------------------------
// Класс Pea
//------------------------------------------------------------------------------
/**
 * @brief Снаряд, выпущенный растением для атаки зомби.
 */
class Pea {
public:
    int row; ///< Ряд, где движется снаряд.
    int x_location; ///< Координата X снаряда.
    std::string directory;
    /**
     * @brief Конструктор снаряда.
     */
    Pea();
    virtual ~Pea() = default;
    /**
     * @brief Применяет эффект снаряда к зомби.
     * @param zombie Зомби, на которого воздействует снаряд.
     */
    virtual void applyEffect(Zombie *zombie);
    /**
     * @brief Проверяет, достиг ли снаряд зомби.
     * @param zombie Зомби для проверки.
     * @return true, если снаряд достиг зомби.
     */
    [[nodiscard]] bool reachedZombie(const Zombie *zombie) const;
    /**
     * @brief Двигает снаряд вперёд.
     */
    void move();
    void draw(window &win, const Map<Block> &map) const;
    static constexpr int DX = 15;
    static constexpr int WIDTH = 20;
    static constexpr int HEIGHT = 20;
    static constexpr int TIME = 20;
    static constexpr int FIRE_TIME = 300;
    static constexpr const char* DIRECTORY = "./Image_Assets/C.png";
};


