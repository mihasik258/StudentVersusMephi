#pragma once


#include "Icons.h"

class Level {
public:
    int level_num;
    int wave_count;
    int cur_wave;
    int cur_sec;
    bool waves_finished;
    std::vector<std::vector<int> > zombie_distr_for_wave;
    std::vector<int> wave_zombie_count;
    std::vector<int> wave_duration;
    explicit Level(int num = 0);
    void readLevelData();
    void saveZombieDistribution(const std::string& zombie_seq);
    void saveWaveDuration(const std::string& wave_dur);
    void saveWaveCount(const std::string& wave_cnt);
    void decideZombieCountForEachSec();
    void generateWaveZombies(Elements &elements);
    [[nodiscard]] bool isWaveCompleted(const Elements &elements) const;
    void handleChanges(Elements &elements, const Map<Block> &map, int clk);
    template <typename PlantType>
    static void createPlant(Player &player, const Map<Block> &map, Elements &elements, Icons &icons,
                            int mouse_x, int mouse_y, const std::string &icon_name) {
        int row, col;
        map.determineClickBlock(mouse_x, mouse_y, row, col);
        for (const auto &plant : elements.plants) {
            if (plant->row == row && plant->col == col) {
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

