#include "Level.h"
#include "Constants.h"

Level::Level(int num)
        : level_num(num), cur_wave(0), cur_sec(0), waves_finished(false), wave_count(0) {}
void Level::readLevelData() {
    std::string file_name = std::to_string(level_num) + ".level.txt";
    std::ifstream myfile(file_name);
    if (!myfile.is_open()) {
        std::cout << "Unable to open level file: " << file_name << std::endl;
        return;
    }
    std::string wave_cnt, zombie_seq, wave_dur;
    std::getline(myfile, wave_cnt);
    std::getline(myfile, zombie_seq);
    std::getline(myfile, wave_dur);
    saveWaveCount(wave_cnt);
    saveZombieDistribution(zombie_seq);
    saveWaveDuration(wave_dur);
    myfile.close();
}
void Level::saveZombieDistribution(const std::string& zombie_seq) {
    size_t pos = zombie_seq.find(':') + 2;
    while (pos != std::string::npos) {
        size_t space_pos = zombie_seq.find(' ', pos);
        wave_zombie_count.push_back(std::stoi(zombie_seq.substr(pos, space_pos - pos)));
        pos = (space_pos == std::string::npos) ? space_pos : space_pos + 1;
    }
}
void Level::saveWaveDuration(const std::string& wave_dur) {
    size_t pos = wave_dur.find(':') + 2;
    while (pos != std::string::npos) {
        size_t space_pos = wave_dur.find(' ', pos);
        wave_duration.push_back(std::stoi(wave_dur.substr(pos, space_pos - pos)));
        pos = (space_pos == std::string::npos) ? space_pos : space_pos + 1;
    }
}
void Level::saveWaveCount(const std::string& wave_cnt) {
    size_t pos = wave_cnt.find(':') + 2;
    wave_count = std::stoi(wave_cnt.substr(pos));
}
void Level::decideZombieCountForEachSec() {
    srand(time(nullptr));
    for (int wave = 0; wave < wave_count; ++wave) {
        std::vector<int> temp;
        int total_zombies = 0;
        for (int sec = 0; sec < wave_duration[wave]; ++sec) {
            int z_count = rand() % 5 + 1;
            total_zombies += z_count;
            if (total_zombies > wave_zombie_count[wave]) {
                temp.push_back(wave_zombie_count[wave] - total_zombies + z_count);
                break;
            }
            temp.push_back(z_count);
        }
        zombie_distr_for_wave.push_back(temp);
    }
}
void Level::generateWaveZombies(Elements &elements) {
    if (waves_finished) return;
    int zombie_cnt = zombie_distr_for_wave[cur_wave][cur_sec];
    Zombie temp;
    for (int i = 0; i < zombie_cnt; i++) {
        elements.addZombie(std::make_unique<Zombie>(temp));
        temp.setRow((temp.getRow() + 1 < 4) ? temp.getRow() + 1 : 0);
    }
    if (++cur_sec >= wave_duration[cur_wave]) {
        cur_sec = 0;
        if (++cur_wave >= wave_count) {
            waves_finished = true;
        }
    }
}
[[nodiscard]] bool Level::isWaveCompleted(const Elements &elements) const {
    return waves_finished && elements.zombies.empty();
}
void Level::handleChanges(Elements &elements, const Map<Block> &map, int clk) {
    elements.setAllZombiesMoving();
    elements.handlePea(map);
    if (!waves_finished && clk % Zombie::CREATE_TIME == 0) {
        generateWaveZombies(elements);
    }
    if (clk % Zombie::BYTE_TIME == 0) {
        elements.handlePlant(map);
    }
    if (clk % Pea::FIRE_TIME == 0)
        elements.firePeas(map);
    if (clk % Sun::SKY_TIME == 0)
        elements.genSkySun();
    if (clk % Sun::SUNFLOWER_TIME == 0) {
        for (const auto &plant : elements.plants) {
            auto* sunflower = dynamic_cast<Sunflower*>(plant.get());
            if (sunflower != nullptr && sunflower->canGenerate(clk)) {
                elements.genPlantSun(sunflower, map);
                sunflower->updateTime(clk);
            }
        }
    }
    elements.removeSuns();
}
