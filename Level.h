#pragma once


#include "Icons.h"

//------------------------------------------------------------------------------
// Класс Level
//------------------------------------------------------------------------------
/**
 * @brief Класс Level
 * 
 * Управляет уровнем игры, включая волны зомби и длительность каждого этапа.
 */
class Level {
public:
    int level_num;               /**< Номер текущего уровня */
    int wave_count;              /**< Количество волн на уровне */
    int cur_wave;                /**< Текущая волна */
    int cur_sec;                 /**< Текущая секунда в рамках волны */
    bool waves_finished;         /**< Флаг, указывающий, завершены ли все волны */
    std::vector<std::vector<int>> zombie_distr_for_wave; /**< Распределение зомби по волнам */
    std::vector<int> wave_zombie_count; /**< Количество зомби в каждой волне */
    std::vector<int> wave_duration;    /**< Длительность каждой волны */
    /**
     * @brief Конструктор Level.
     * @param num Номер уровня.
     */
    explicit Level(int num = 0);
    /**
     * @brief Читает данные уровня из файла.
     * Загружает количество волн, распределение зомби и длительность волн.
     */
    void readLevelData();
    /**
     * @brief Сохраняет распределение зомби для каждой волны.
     * @param zombie_seq Строка, содержащая последовательность зомби для каждой волны.
     */
    void saveZombieDistribution(const std::string& zombie_seq);
    /**
     * @brief Сохраняет длительность волн.
     * @param wave_dur Строка с длительностью каждой волны.
     */
    void saveWaveDuration(const std::string& wave_dur);
    /**
     * @brief Сохраняет количество волн.
     * @param wave_cnt Строка с количеством волн.
     */
    void saveWaveCount(const std::string& wave_cnt);
    /**
     * @brief Определяет количество зомби, которое должно появиться в каждую секунду.
     */
    void decideZombieCountForEachSec();
    /**
     * @brief Генерирует зомби для текущей волны.
     * @param elements Коллекция игровых объектов.
     */
    void generateWaveZombies(Elements &elements);
    /**
     * @brief Проверяет, завершена ли волна.
     * @param elements Коллекция игровых объектов.
     * @return true, если волна завершена, иначе false.
     */
    [[nodiscard]] bool isWaveCompleted(const Elements &elements) const;
    /**
     * @brief Обрабатывает изменения на уровне.
     * Генерирует зомби, обновляет состояние растений и управляет другими игровыми событиями.
     * @param elements Коллекция игровых объектов.
     * @param map Карта игрового поля.
     * @param clk Текущее время в секундах.
     */
    void handleChanges(Elements &elements, const Map<Block> &map, int clk);
    /**
     * @brief Создает растение на игровом поле.
     * @param player Игрок, который оплачивает создание растения.
     * @param map Карта игрового поля.
     * @param elements Коллекция игровых объектов.
     * @param icons Панель иконок для выбора растений.
     * @param mouse_x Координата X мыши.
     * @param mouse_y Координата Y мыши.
     * @param icon_name Название растения, которое будет создано.
     */
    template <typename PlantType>
    static void createPlant(Player &player, const Map<Block> &map, Elements &elements, Icons &icons,
                            int mouse_x, int mouse_y, const std::string &icon_name) {
        int row, col;
        map.determineClickBlock(mouse_x, mouse_y, row, col);
        for (const auto &plant : elements.plants) {
            if (plant->getRow() == row && plant->getCol() == col) {
                return;
            }
        }
        if (icons.iconData[icon_name].is_chosen &&
            player.sun_count >= icons.iconData[icon_name].price) {
            std::unique_ptr<Plant> new_plant = std::make_unique<PlantType>(row, col);
            elements.plants.push_back(std::move(new_plant));
            player.sun_count -= icons.iconData[icon_name].price;
        }
    }
};

