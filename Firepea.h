#pragma once


#include "Zombie.h"
#include "Pea.h"

//------------------------------------------------------------------------------
// Класс Firepea
//------------------------------------------------------------------------------
/**
 * @brief Класс Firepea
 * 
 * Специализированный снаряд, наносящий дополнительный урон.
 */
class Firepea : public Pea {
public:
    /**
     * @brief Конструктор Firepea.
     */
    Firepea();
    /**
     * @brief Применяет огненный эффект к зомби.
     * @param zombie Зомби, на которого воздействует снаряд.
     */
    void applyEffect(Zombie *zombie) override;
    static constexpr const char* DIRECTORY = "./Image_Assets/C2.png";
};
