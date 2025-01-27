#pragma once

#include "Zombie.h"
#include "Pea.h"

//------------------------------------------------------------------------------
// Класс Icepea
//------------------------------------------------------------------------------
/**
 * @brief Класс Icepea
 * 
 * Снаряд, замедляющий зомби.
 */
class Icepea : public Pea {
public:
    /**
     * @brief Конструктор Icepea.
     */
    Icepea();
    /**
     * @brief Применяет эффект заморозки к зомби.
     * @param zombie Зомби, на которого воздействует снаряд.
     */
    void applyEffect(Zombie *zombie) override;
    static constexpr const char* DIRECTORY = "./Image_Assets/C1.png";
};

