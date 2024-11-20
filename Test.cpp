#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "rsdl.hpp"
#include <memory>

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Speed properties: increase or decrease the following 9 define values to speed up or speed down entities in the game
#define CLK_LENGTH 5
#define SKY_SUN_TIME 2000
#define SUNFLOWER_SUN_TIME 2000
#define STUDENT_CREATE_TIME 1200
#define FIRE_PEA_TIME 300
#define BYTE_TIME 100
#define STUDENT_TIME 22
#define SUN_TIME 8
#define PEA_TIME 4
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Alter the 4 define values bellow to increase or decrease the price of plants and the initial sun count
#define INIT_SUN_COUNT 200
#define PEASHOOTER_PRICE 100
#define ICESHOOTER_PRICE 150
#define FIRESHOOTER_PRICE 175
#define SUNFLOWER_PRICE 50
#define WALNUT_PRICE 50
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

#define STUDENT_INIT_X 900
#define STUDENT_DX 3
#define PEA_DX 15
#define SUN_DY 1
#define WALNUT_HP_LIMIT 10
#define SUNFLOWER_HP_LIMIT 5
#define PEASHOOTER_HP_LIMIT 5

#define WINDOW_WIDTH 1050
#define WINDOW_HEIGHT 600
#define BLOCK_WIDTH 81
#define BLOCK_HEIGHT 101
#define HORIZ_BLOCK_COUNT 9
#define VERT_BLOCK_COUNT 5

#define X_UPPER_LEFT 250
#define Y_UPPER_LEFT 70
#define TAP_TO_START_X1 230
#define TAP_TO_START_X2 796
#define TAP_TO_START_Y1 520
#define TAP_TO_START_Y2 585
#define ICON_BAR_X1 20
#define ICON_BAR_X2 113
#define ICON_BAR_Y1 102
#define ICON_BAR_Y2 402

#define INIT_SUN_Y 5
#define SUNFLOWER_ICON_Y1 103
#define PEASHOOTER_ICON_Y1 167
#define WALNUT_ICON_Y1 231
#define ICESHOOTER_ICON_Y1 295
#define FIRESHOOTER_ICON_Y1 359

#define ICON_BAR_WIDTH 95
#define ICON_BAR_HEIGHT 194
#define ICON_WIDTH 89
#define ICON_HEIGHT 60
#define SUN_COUNT_WIDTH 70
#define SUN_COUNT_HEIGHT 30
#define SUN_WIDTH 80
#define SUN_HEIGHT 80
#define PEA_WIDTH 20
#define PEA_HEIGHT 20
#define ELEMENT_WIDTH 65
#define ELEMENT_HEIGHT 80

#define STARTING_SCREEN_DIRECTORY "./Image_Assets/Starting_Screen.png"
#define BACKGROUND_DIRECTORY "./Image_Assets/Frontyard.png"
#define BACKGROUND_DIM_DIRECTORY "./Image_Assets/Frontyard_dim.jpeg"
#define LOSING_MESSAGE_DIRECTORY "./Image_Assets/Losing_Message.jpg"
#define WINNING_MESSAGE_DIRECTORY "./Image_Assets/Winning_Message.jpg"
#define BLACK_SCREEN_DIRECTORY "./Image_Assets/Black_Screen.png"
#define STUDENT_HEALTHY_DIRECTORY "./Image_Assets/Zombie_healthy1.png"
#define STUDENT_MIDDLE_DIRECTORY "./Image_Assets/Zombie_healthy2.png"
#define STUDENT_INJURED_DIRECTORY "./Image_Assets/Zombie_healthy3.png"
#define STUDENT_HEALTHY_FREEZE_DIRECTORY "./Image_Assets/Zombie_healthy1_freeze.png"
#define STUDENT_MIDDLE_FREEZE_DIRECTORY "./Image_Assets/Zombie_healthy2_freeze.png"
#define STUDENT_INJURED_FREEZE_DIRECTORY "./Image_Assets/Zombie_healthy3_freeze.png"
#define STUDENT_HEALTHY_FIRE_DIRECTORY "./Image_Assets/Zombie_healthy1_fire.png"
#define STUDENT_MIDDLE_FIRE_DIRECTORY "./Image_Assets/Zombie_healthy2_fire.png"
#define STUDENT_INJURED_FIRE_DIRECTORY "./Image_Assets/Zombie_healthy3_fire.png"
#define SUN_DIRECTORY "./Image_Assets/sun(1).png"
#define SUNFLOWER_DIRECTORY "./Image_Assets/Sunflower.png"
#define PEASHOOTER_DIRECTORY "./Image_Assets/PeashooterC.png"
#define ICESHOOTER_DIRECTORY "./Image_Assets/Iceshooter.png"
#define FIRESHOOTER_DIRECTORY "./Image_Assets/Fireshooter.png"
#define C_DIRECTORY "./Image_Assets/C.png"
#define C1_DIRECTORY "./Image_Assets/C1.png"
#define C2_DIRECTORY "./Image_Assets/C2.png"
#define WALNUT_UNTOUCHED_DIRECTORY "./Image_Assets/yan.png"
#define WALNUT_CRACKED_1_DIRECTORY "./Image_Assets/hp.png"
#define WALNUT_CRACKED_2_DIRECTORY "./Image_Assets/hp.png"
#define ICON_BAR_DIRECTORY "./Image_Assets/Item_Bar.png"
//#define SUN_COUNT_TEXT_FIELD_DIRECTORY "./Image_Assets/sun_count_text_field.png"
#define PEASHOOTER_ICON_BRIGHT_DIRECTORY "./Image_Assets/icon_peashooter_100.png"
#define PEASHOOTER_ICON_DIM_DIRECTORY "./Image_Assets/icon_peashooter_100_dim.png"
#define ICESHOOTER_ICON_BRIGHT_DIRECTORY "./Image_Assets/Icesh.png"
#define ICESHOOTER_ICON_DIM_DIRECTORY "./Image_Assets/Icesh_black.png"
#define FIRESHOOTER_ICON_BRIGHT_DIRECTORY "./Image_Assets/Firesh.png"
#define FIRESHOOTER_ICON_DIM_DIRECTORY "./Image_Assets/Icesh_black.png"
#define SUNFLOWER_ICON_BRIGHT_DIRECTORY "./Image_Assets/icon_sunflower.png"
#define SUNFLOWER_ICON_DIM_DIRECTORY "./Image_Assets/icon_sunflower_dim.png"
#define WALNUT_ICON_BRIGHT_DIRECTORY "./Image_Assets/icon_walnut.png"
#define WALNUT_ICON_DIM_DIRECTORY "./Image_Assets/icon_walnut_dim.png"


class Block {
public:
    int x1, x2;
    int y1, y2;
    explicit Block(int startX1 = 0, int startX2 = 0, int startY1 = 0, int startY2 = 0)
            : x1(startX1), x2(startX2), y1(startY1), y2(startY2) {}
    static std::vector<std::vector<Block>> createBlockMap() {
        std::vector<std::vector<Block>> result(VERT_BLOCK_COUNT, std::vector<Block>(HORIZ_BLOCK_COUNT));
        for (int y = 0; y < VERT_BLOCK_COUNT; y++) {
            for (int x = 0; x < HORIZ_BLOCK_COUNT; x++) {
                result[y][x].x1 = X_UPPER_LEFT + (x * BLOCK_WIDTH);
                result[y][x].x2 = X_UPPER_LEFT + ((x + 1) * BLOCK_WIDTH);
                result[y][x].y1 = Y_UPPER_LEFT + (y * BLOCK_HEIGHT);
                result[y][x].y2 = Y_UPPER_LEFT + ((y + 1) * BLOCK_HEIGHT);
            }
        }
        return result;
    }
    static bool isClickInFrontyard(const std::vector<std::vector<Block>>& map, int mouseX, int mouseY) {
        int rightBound = map[0][8].x2;
        int leftBound = map[0][0].x1;
        int upperBound = map[0][0].y1;
        int lowerBound = map[4][0].y2;
        return (mouseX > leftBound && mouseX < rightBound && mouseY > upperBound && mouseY < lowerBound);
    }
    static void determineClickBlock(const std::vector<std::vector<Block>>& map, int mouseX, int mouseY, int &row, int &col) {
        auto it = std::find_if(map.begin(), map.end(), [&](const std::vector<Block>& rowBlocks) {
            return std::any_of(rowBlocks.begin(), rowBlocks.end(), [&](const Block& block) {
                return mouseX > block.x1 && mouseX < block.x2 && mouseY > block.y1 && mouseY < block.y2;
            });
        });
        if (it != map.end()) {
            row = std::distance(map.begin(), it);
            auto blockIt = std::find_if(it->begin(), it->end(), [&](const Block& block) {
                return mouseX > block.x1 && mouseX < block.x2 && mouseY > block.y1 && mouseY < block.y2;
            });
            col = std::distance(it->begin(), blockIt);
        }
    }
    static bool isClickWithinBlock(int row, int col, int mouseX, int mouseY, const std::vector<std::vector<Block>>& map) {
        return (mouseX > map[row][col].x1 && mouseX < map[row][col].x2 && mouseY > map[row][col].y1 && mouseY < map[row][col].y2);
    }
};

using Map = std::vector<std::vector<Block>>;


class Zombie {
public:
    int row;
    int x_location;
    int health;
    bool is_moving;
    int speed;
    std::string directory;
    std::unordered_map<std::string, bool> effects;
    explicit Zombie(int initial_x_location = STUDENT_INIT_X, int initial_health = 10, bool moving = true)
            : x_location(initial_x_location), health(initial_health), is_moving(moving), directory(STUDENT_HEALTHY_DIRECTORY), speed(STUDENT_DX) {
        row = rand() % 5;
        effects["fire"] = false;
        effects["ice"] = false;
    }
    void addEffect(const std::string &effect) {
        effects[effect] = true;
    }
    void removeEffect(const std::string &effect) {
        if (effects.find(effect) != effects.end()) {
            effects[effect] = false;
        }
    }    void move() {
        x_location -= speed;
    }
    void updateAppearance() {
        if (effects["fire"]) {
            if (health > 7) directory = STUDENT_HEALTHY_FIRE_DIRECTORY;
            else if (health > 4) directory = STUDENT_MIDDLE_FIRE_DIRECTORY;
            else directory = STUDENT_INJURED_FIRE_DIRECTORY;
        } else if (effects["ice"]) {
            if (health > 7) directory = STUDENT_HEALTHY_FREEZE_DIRECTORY;
            else if (health > 4) directory = STUDENT_MIDDLE_FREEZE_DIRECTORY;
            else directory = STUDENT_INJURED_FREEZE_DIRECTORY;
        } else {
            if (health > 7) directory = STUDENT_HEALTHY_DIRECTORY;
            else if (health > 4) directory = STUDENT_MIDDLE_DIRECTORY;
            else directory = STUDENT_INJURED_DIRECTORY;
        }
    }
    [[nodiscard]] bool hasEffect(const std::string& effect_name) const {
        auto it = effects.find(effect_name);
        return it != effects.end() && it->second;
    }
};
class Plant {
public:
    int row;
    int col;
    int hp;
    int hp_limit;
    bool is_destroyed;
    Plant(int row, int col) : row(row), col(col), hp(0), hp_limit(1), is_destroyed(false) {}
    virtual ~Plant() = default;
    bool isZombieNearby(const Zombie &zombie, Map &map) const {
        int right_limit = map[row][col].x2 - 35;
        int left_limit = map[row][col].x1;
        int zombie_new_location = zombie.x_location - STUDENT_DX;
        return zombie.row == row &&
               zombie_new_location < right_limit &&
               zombie_new_location > left_limit;
    }
    virtual void handleZombie(Zombie &zombie, Map &map){
        if (isZombieNearby(zombie, map)) {
            hp++;
            if (hp >= hp_limit) {
                zombie.is_moving = true;
                is_destroyed = true;
            }
        }
    }
};

class Walnut : public Plant {
public:
    std::string directory;
    Walnut(int row, int col) : Plant(row, col), directory(WALNUT_UNTOUCHED_DIRECTORY) {
        hp_limit = WALNUT_HP_LIMIT;
    }
    void updateAppearance() {
        if (hp <= 4)
            directory = WALNUT_UNTOUCHED_DIRECTORY;
        else if (hp > 4 && hp <= 7)
            directory = WALNUT_CRACKED_1_DIRECTORY;
        else
            directory = WALNUT_CRACKED_2_DIRECTORY;
    }
    void handleZombie(Zombie &zombie, Map &map) override {
        if (isZombieNearby(zombie, map)) {
            hp++;
            updateAppearance();
            if (hp >= hp_limit) {
                is_destroyed = true;
                zombie.is_moving = true;
            }
        }
    }
};
class Pea {
public:
    int row;
    int x_location;
    std::string directory;
    Pea() : row(0), x_location(0), directory(C_DIRECTORY) {}
    [[nodiscard]] bool reachedZombie(Zombie zombie) const{
        return zombie.row == row && x_location + PEA_DX > zombie.x_location + 30;
    }
    void move() {
        x_location += PEA_DX;
    }
    virtual void applyEffect(Zombie &zombie) {
        if (zombie.hasEffect("fire") && !zombie.hasEffect("ice")) {
            zombie.health -= 1;
        }
        zombie.health -= 1;
    }
};
class Icepea : public Pea {
public:
    Icepea() {
        directory = C1_DIRECTORY;
    }
    void applyEffect(Zombie &zombie) override {
        zombie.addEffect("ice");
        if (zombie.hasEffect("fire") && zombie.hasEffect("ice")) {
            zombie.removeEffect("fire");
            zombie.removeEffect("ice");
        }
        else if (zombie.hasEffect("ice")){
            zombie.speed = STUDENT_DX/2;
        }
        zombie.health -= 1;
    }
};
class Firepea : public Pea {
public:
    Firepea() {
        directory = C2_DIRECTORY;
    }
    void applyEffect(Zombie &zombie) override {
        zombie.addEffect("fire");
        if (zombie.hasEffect("fire") && zombie.hasEffect("ice")) {
            zombie.removeEffect("fire");
            zombie.removeEffect("ice");
        }
        else if (zombie.hasEffect("fire")) {
            zombie.health -= 1;
        }
        zombie.health -= 1;
    }
};
class Peashooter : public Plant {
public:
    std::string directory;
    Peashooter(int row, int col) : Plant(row, col), directory(PEASHOOTER_DIRECTORY) {
        hp_limit = PEASHOOTER_HP_LIMIT;
    }
    [[nodiscard]] bool zombiesInRow(const std::vector<Zombie> &zombies) const {
        return std::any_of(zombies.begin(), zombies.end(), [&](const Zombie &zombie) {
            return zombie.row == row;
        });
    }
    virtual void fire(std::vector<std::unique_ptr<Pea>> &peas, Map &map, std::vector<Zombie> &zombies) {
        if (zombiesInRow(zombies)) {
            auto new_pea = std::make_unique<Pea>();
            new_pea->row = row;
            new_pea->x_location = map[row][col].x2 - 10;
            peas.push_back(std::move(new_pea));
        }
    }
};
class Iceshooter : public Peashooter {
public:
    Iceshooter(int row, int col) : Peashooter(row, col) {
        directory = ICESHOOTER_DIRECTORY;
        hp_limit = PEASHOOTER_HP_LIMIT;
    }
    void fire(std::vector<std::unique_ptr<Pea>> &peas, Map &map, std::vector<Zombie> &zombies) override {
        if (zombiesInRow(zombies)) {
            auto new_icepea = std::make_unique<Icepea>();
            new_icepea->row = row;
            new_icepea->x_location = map[row][col].x2 - 10;
            peas.push_back(std::move(new_icepea));
        }
    }
};
class Fireshooter : public Peashooter {
public:
    Fireshooter(int row, int col) : Peashooter(row, col) {
        directory = FIRESHOOTER_DIRECTORY;
        hp_limit = PEASHOOTER_HP_LIMIT;
    }
    void fire(std::vector<std::unique_ptr<Pea>> &peas, Map &map, std::vector<Zombie> &zombies) override {
        if (zombiesInRow(zombies)) {
            auto new_firepea = std::make_unique<Firepea>();
            new_firepea->row = row;
            new_firepea->x_location = map[row][col].x2 - 10;
            peas.push_back(std::move(new_firepea));
        }
    }
};
class Sunflower : public Plant {
public:
    std::string directory;
    int last_sun_generated_time;
    Sunflower(int row, int col) : Plant(row, col), directory(SUNFLOWER_DIRECTORY), last_sun_generated_time(0) {
        hp_limit = SUNFLOWER_HP_LIMIT;
    }
    [[nodiscard]] bool canGenerate(int current_time) const {
        return current_time - last_sun_generated_time >= SUNFLOWER_SUN_TIME;
    }
    void updateTime(int current_time) {
        last_sun_generated_time = current_time;
    }
};


class Sun {
public:
    int final_row;
    int final_col;
    int y_location;
    int wait_seconds;
    explicit Sun(int row = 0, int col = 0, int y = 0, int wait = 0)
            : final_row(row), final_col(col), y_location(y), wait_seconds(wait) {}
    void move(int lower_limit) {
        if (y_location + SUN_DY < lower_limit) {
            y_location += SUN_DY;
        } else {
            wait_seconds++;
        }
    }
};

class Elements {
public:
    std::vector<Zombie> zombies;
    std::vector<std::unique_ptr<Plant>> plants;
    std::vector<std::unique_ptr<Pea>> peas;
    std::vector<Sun> suns;
    Elements() = default;
    void genSkySun(){
        srand(time(nullptr));
        Sun temp;
        temp.final_row = rand() % 5;
        temp.final_col = rand() % 9;
        temp.y_location = INIT_SUN_Y;
        temp.wait_seconds = 0;
        suns.push_back(temp);
    }
    void removeSuns(){
        for (int i = 0; i < suns.size(); i++)
            if (suns[i].wait_seconds >= 200)
                suns.erase(suns.begin() + i);
    }
    void genPlantSun(Plant* plant, Map & map) {
        Sun temp;
        temp.final_col = plant->col;
        temp.final_row = plant->row;
        temp.y_location = map[plant->row][plant->col].y1 - 20;
        temp.wait_seconds = 0;
        suns.push_back(temp);
    }
    void setAllZombiesMoving() {
        for (Zombie &zombie : zombies) {
            zombie.is_moving = true;
        }
    }
    void addZombie(const Zombie &zombie) {
        zombies.push_back(zombie);
    }
    bool hasZombieReachedAnyElement(Zombie &zombie, Map &map) {
        for (auto &plant : plants) {
            if (plant->isZombieNearby(zombie, map)) {
                zombie.is_moving = false;
                return true;
            }
        }
        zombie.is_moving = true;
        return false;
    }
    bool canMove(Zombie & zombie,Map & map){
        int left_bound = map[0][0].x1;
        int zombie_new_location = zombie.x_location - STUDENT_DX;
        if (zombie_new_location < left_bound)
            return false;
        if (!zombie.is_moving)
            return false;
        if (hasZombieReachedAnyElement(zombie, map))
            return false;
        return true;
    }
    void moveZombies(Map & map){
        for (auto & zombie : zombies){
            if (canMove(zombie,map))
                zombie.move();
        }
    }
    bool canPeaMove(Pea & pea, Map & map){
        int right_bound = map[pea.row][8].x2 - 20;
        if (pea.x_location + PEA_DX > right_bound)
            return false;
        for (auto & zombie : zombies)
            if (pea.reachedZombie(zombie))
                return false;
        return true;
    }
    void movePeas(Map &map) {
        for (auto &pea : peas) {
            if (canPeaMove(*pea, map))
                pea->move();
        }
    }
    void moveSuns(Map & map){
        for (auto & sun : suns){
            int row = sun.final_row;
            int col = sun.final_col;
            int lower_limit = map[row][col].y1 + 30;
            if (sun.y_location + SUN_DY < lower_limit)
                sun.y_location += SUN_DY;
            else
                sun.wait_seconds ++;
        }
    }
    [[nodiscard]] bool hasZombiesPassedBoundary(int boundary_x) const {
        for (const Zombie &zombie : zombies) {
            if (zombie.x_location < boundary_x) return true;
        }
        return false;
    }
    void handlePlant(Map &map) {
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
    void firePeas(Map &map) {
        for (auto &plant : plants) {
            auto* shooter = dynamic_cast<Peashooter*>(plant.get());
            if (shooter) {
                shooter->fire(peas, map, zombies);
            }
        }
    }
    // ГОВНО ПЕРЕДЕЛАТЬ
    void applyHitting(int p_ind, int z_ind) {
        if (peas[p_ind]->reachedZombie(zombies[z_ind])) {
            peas[p_ind]->applyEffect(zombies[z_ind]);
            peas.erase(peas.begin() + p_ind);
            zombies[z_ind].updateAppearance();
            if (zombies[z_ind].health == 0) {
                zombies.erase(zombies.begin() + z_ind);
            }
        }
    }
    void handlePea(Map & map){
        for (int i = 0; i < zombies.size(); i++)
            for (int j = 0; j < peas.size(); j++)
                applyHitting(j, i);
    }
    void handleMovements(Map & map, int clk){
        if (clk % STUDENT_TIME == 0)
            moveZombies(map);
        if (clk % PEA_TIME == 0)
            movePeas(map);
        if (clk % SUN_TIME == 0)
            moveSuns(map);
    }
    /*
    void removeClicked(Map &map, int mouse_x, int mouse_y) {
        for (int i = 0; i < plants.size(); i++) {
            Plant* plant = plants[i].get();
            if (Block::isClickWithinBlock(plant->row, plant->col, mouse_x, mouse_y, map)) {
                delete plant;
                plants.erase(plants.begin() + i);
                i--;
            }
        }
    }
*/
};

class Player {
public:
    int sun_count;
    bool is_first_click_made;
    std::string directory;
    explicit Player(int init_sun_count = INIT_SUN_COUNT, bool first_click = false)
            : sun_count(init_sun_count), is_first_click_made(first_click) {}
    void pick_sun_if_clicked_on(Elements & elements, Map & map, int mouse_x, int mouse_y, bool & sun_picked){
        for (int i = 0; i < elements.suns.size(); i++){
            int row = elements.suns[i].final_row; int col = elements.suns[i].final_col;
            int right_bound = map[row][col].x2;
            int left_bound = map[row][col].x1;
            int upper_bound = elements.suns[i].y_location;
            int lower_bound = elements.suns[i].y_location + ELEMENT_HEIGHT;
            if (mouse_x > left_bound && mouse_x < right_bound &&
                mouse_y > upper_bound && mouse_y < lower_bound){
                elements.suns.erase(elements.suns.begin() + i);
                sun_picked = true;
                sun_count += 50;
                return;
            }
            sun_picked = false;
        }
    }
};
class Icons {
public:
    struct IconData {
        bool is_chosen;
        int price;
        std::string icon_directory_dim;
        std::string icon_directory_bright;
        int icon_y_position;
    };
    std::map<std::string, IconData> iconData;
    Icons() {
        iconData["sunflower"] = {false, SUNFLOWER_PRICE, SUNFLOWER_ICON_DIM_DIRECTORY, SUNFLOWER_ICON_BRIGHT_DIRECTORY, SUNFLOWER_ICON_Y1};
        iconData["peashooter"] = {false, PEASHOOTER_PRICE, PEASHOOTER_ICON_DIM_DIRECTORY, PEASHOOTER_ICON_BRIGHT_DIRECTORY, PEASHOOTER_ICON_Y1};
        iconData["walnut"] = {false, WALNUT_PRICE, WALNUT_ICON_DIM_DIRECTORY, WALNUT_ICON_BRIGHT_DIRECTORY, WALNUT_ICON_Y1};
        iconData["iceshooter"] = {false, ICESHOOTER_PRICE, ICESHOOTER_ICON_DIM_DIRECTORY, ICESHOOTER_ICON_BRIGHT_DIRECTORY, ICESHOOTER_ICON_Y1};
        iconData["fireshooter"] = {false, FIRESHOOTER_PRICE, FIRESHOOTER_ICON_DIM_DIRECTORY, FIRESHOOTER_ICON_BRIGHT_DIRECTORY, FIRESHOOTER_ICON_Y1};
    }
    void updateIconSelection(int mouse_y) {
        for (auto &[type, data] : iconData) {
            data.is_chosen = false;
        }
        for (auto &[type, data] : iconData) {
            if (mouse_y > data.icon_y_position && mouse_y < data.icon_y_position + ICON_HEIGHT) {
                data.is_chosen = true;
                break;
            }
        }
    }
    void displayIconBar(window &win, Player &player) {
        for (auto &[type, data] : iconData) {
            const std::string &directory = (player.sun_count >= data.price) ? data.icon_directory_bright : data.icon_directory_dim;
            win.draw_png(directory, ICON_BAR_X1 + 3, data.icon_y_position, ICON_WIDTH, ICON_HEIGHT);
        }
    }
    void displayLayout(window &win, Player &player) {
        win.draw_bg(BLACK_SCREEN_DIRECTORY);
        win.draw_bg(BACKGROUND_DIRECTORY);
        win.draw_png(ICON_BAR_DIRECTORY, 20, 100, ICON_BAR_WIDTH, ICON_BAR_HEIGHT);
        win.draw_png(ICON_BAR_DIRECTORY, 20, 300, ICON_BAR_WIDTH, ICON_BAR_HEIGHT);
        win.draw_png(SUN_DIRECTORY, 5, 5, SUN_WIDTH, SUN_HEIGHT);
        //win.draw_png(SUN_COUNT_TEXT_FIELD_DIRECTORY, 85, 33, SUN_COUNT_WIDTH, SUN_COUNT_HEIGHT);
        //win.show_text(std::to_string(player.sun_count), 100, 33);
        displayIconBar(win, player);
    }
};

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
    explicit Level(int num = 0)
            : level_num(num), cur_wave(0), cur_sec(0), waves_finished(false), wave_count(0) {}
    void readLevelData() {
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
    void saveZombieDistribution(const std::string& zombie_seq) {
        size_t pos = zombie_seq.find(':') + 2;
        while (pos != std::string::npos) {
            size_t space_pos = zombie_seq.find(' ', pos);
            wave_zombie_count.push_back(std::stoi(zombie_seq.substr(pos, space_pos - pos)));
            pos = (space_pos == std::string::npos) ? space_pos : space_pos + 1;
        }
    }
    void saveWaveDuration(const std::string& wave_dur) {
        size_t pos = wave_dur.find(':') + 2;
        while (pos != std::string::npos) {
            size_t space_pos = wave_dur.find(' ', pos);
            wave_duration.push_back(std::stoi(wave_dur.substr(pos, space_pos - pos)));
            pos = (space_pos == std::string::npos) ? space_pos : space_pos + 1;
        }
    }
    void saveWaveCount(const std::string& wave_cnt) {
        size_t pos = wave_cnt.find(':') + 2;
        wave_count = std::stoi(wave_cnt.substr(pos));
    }
    void decideZombieCountForEachSec() {
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
    void generateWaveZombies(Elements &elements) {
        if (waves_finished) return;
        int zombie_cnt = zombie_distr_for_wave[cur_wave][cur_sec];
        Zombie temp;
        temp.x_location = STUDENT_INIT_X;
        temp.health = 10;
        temp.is_moving = true;
        temp.directory = STUDENT_HEALTHY_DIRECTORY;
        temp.row = rand() % 5;
        for (int i = 0; i < zombie_cnt; i++) {
            elements.addZombie(temp);
            temp.row = (temp.row + 1 < 4) ? temp.row + 1 : 0;
        }
        if (++cur_sec >= wave_duration[cur_wave]) {
            cur_sec = 0;
            if (++cur_wave >= wave_count) {
                waves_finished = true;
            }
        }
    }
    [[nodiscard]] bool isWaveCompleted(const Elements &elements) const {
        return waves_finished && elements.zombies.empty();
    }
    void handleChanges(Elements &elements, Map &map, int clk) {
        elements.setAllZombiesMoving();
        elements.handlePea(map);
        if (!waves_finished && clk % STUDENT_CREATE_TIME == 0) {
            generateWaveZombies(elements);
        }
        if (clk % BYTE_TIME == 0) {
            elements.handlePlant(map);
        }
        if (clk % FIRE_PEA_TIME == 0)
            elements.firePeas(map);
        if (clk % SKY_SUN_TIME == 0)
            elements.genSkySun();
        if (clk % SUNFLOWER_SUN_TIME == 0) {
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
    static void createPlant(Player &player, Map &map, Elements &elements, Icons &icons, int mouse_x, int mouse_y) {
        int row, col;
        Block::determineClickBlock(map, mouse_x, mouse_y, row, col);
        for (const auto &plant : elements.plants) {
            if (plant->row == row && plant->col == col) {
                return;
            }
        }
        if (icons.iconData["walnut"].is_chosen && player.sun_count >= icons.iconData["walnut"].price) {
            std::unique_ptr<Plant> new_plant = std::make_unique<Walnut>(row, col);
            elements.plants.push_back(std::move(new_plant));
            player.sun_count -= icons.iconData["walnut"].price;
        } else if (icons.iconData["peashooter"].is_chosen && player.sun_count >= icons.iconData["peashooter"].price) {
            std::unique_ptr<Plant> new_plant = std::make_unique<Peashooter>(row, col);
            elements.plants.push_back(std::move(new_plant));
            player.sun_count -= icons.iconData["peashooter"].price;
        } else if (icons.iconData["iceshooter"].is_chosen && player.sun_count >= icons.iconData["iceshooter"].price) {
            std::unique_ptr<Plant> new_plant = std::make_unique<Iceshooter>(row, col);
            elements.plants.push_back(std::move(new_plant));
            player.sun_count -= icons.iconData["iceshooter"].price;
        } else if (icons.iconData["fireshooter"].is_chosen && player.sun_count >= icons.iconData["fireshooter"].price) {
            std::unique_ptr<Plant> new_plant = std::make_unique<Fireshooter>(row, col);
            elements.plants.push_back(std::move(new_plant));
            player.sun_count -= icons.iconData["fireshooter"].price;
        } else if (icons.iconData["sunflower"].is_chosen && player.sun_count >= icons.iconData["sunflower"].price) {
            std::unique_ptr<Plant> new_plant = std::make_unique<Sunflower>(row, col);
            elements.plants.push_back(std::move(new_plant));
            player.sun_count -= icons.iconData["sunflower"].price;
        }
    }
};


void displayZombies(window & win, std::vector<Zombie> & zombies, Map & map){
    for (auto & zombie : zombies){
        int row = zombie.row;
        int y_location = map[row][0].y1;
        win.draw_png(zombie.directory, zombie.x_location, y_location, ELEMENT_WIDTH, ELEMENT_HEIGHT);
    }
}
void displayPeas(window & win, std::vector<Pea*> & peas, Map & map){
    for (auto & pea : peas){
        int row = pea->row;
        int y_location = map[row][0].y1 + 20;
        if (pea->x_location < (map[0][8].x2 - 35))
            win.draw_png(pea->directory, pea->x_location, y_location, PEA_WIDTH, PEA_HEIGHT);
    }
}
void displayPlants(window &win, const std::vector<std::unique_ptr<Plant>> &plants, Map &map) {
    for (const auto &plant : plants) {
        int col = plant->col;
        int row = plant->row;

        if (auto walnut = dynamic_cast<Walnut*>(plant.get())) {
            win.draw_png(walnut->directory, map[row][col].x1 + 9, map[row][col].y1 + 9, ELEMENT_WIDTH, ELEMENT_HEIGHT);
        }
        else if (auto peashooter = dynamic_cast<Peashooter*>(plant.get())) {
            win.draw_png(peashooter->directory, map[row][col].x1 + 9, map[row][col].y1 + 9, ELEMENT_WIDTH, ELEMENT_HEIGHT);
        }
        else if (auto iceshooter = dynamic_cast<Iceshooter*>(plant.get())) {
            win.draw_png(iceshooter->directory, map[row][col].x1 + 9, map[row][col].y1 + 9, ELEMENT_WIDTH, ELEMENT_HEIGHT);
        }
        else if (auto sunflower = dynamic_cast<Sunflower*>(plant.get())) {
            win.draw_png(sunflower->directory, map[row][col].x1 + 9, map[row][col].y1 + 9, ELEMENT_WIDTH, ELEMENT_HEIGHT);
        }
    }
}

void displaySuns(window & win, std::vector<Sun> suns, Map & map){
    for (auto & sun : suns){
        int col = sun.final_col;
        int x_location = map[0][col].x1;
        win.draw_png(SUN_DIRECTORY, x_location, sun.y_location, ELEMENT_WIDTH, ELEMENT_HEIGHT);
    }
}
void displayGameElements(window &win, Elements &elements, Map &map) {
    displayZombies(win, elements.zombies, map);
    displayPlants(win, elements.plants, map);
    std::vector<Pea*> pea_ptrs;
    for (const auto &pea : elements.peas) {
        pea_ptrs.push_back(pea.get());
    }
    displayPeas(win, pea_ptrs, map);
    displaySuns(win, elements.suns, map);
}

void displayLosingMessage(window & win){
    win.draw_bg(BLACK_SCREEN_DIRECTORY);
    win.draw_bg(BACKGROUND_DIM_DIRECTORY);
    win.draw_png(LOSING_MESSAGE_DIRECTORY, WINDOW_WIDTH/4, WINDOW_HEIGHT/8 - 40, 500, 500);
}

void displayWinningMessage(window & win){
    win.draw_bg(BLACK_SCREEN_DIRECTORY);
    win.draw_bg(BACKGROUND_DIM_DIRECTORY);
    win.draw_png(WINNING_MESSAGE_DIRECTORY, WINDOW_WIDTH/3, WINDOW_HEIGHT/8 - 60, 300, 550);
}

bool is_an_icon_chosen(int mouse_x, int mouse_y){
    if (mouse_x > ICON_BAR_X1 && mouse_x < ICON_BAR_X2 &&
        mouse_y > ICON_BAR_Y1 && mouse_y < ICON_BAR_Y2)
        return true;
    return false;
}

void handleClick(Player & player, Icons & icons, Level & level, Elements & elements, Map & map, int mouse_x, int mouse_y){
    bool sun_picked = false;
    if (!player.is_first_click_made){
        if (is_an_icon_chosen(mouse_x, mouse_y)){
            icons.updateIconSelection(mouse_y);
            player.is_first_click_made = true;
        }
        player.pick_sun_if_clicked_on(elements, map, mouse_x, mouse_y, sun_picked);
        /*
        if (!sun_picked && Block::isClickInFrontyard(map, mouse_x, mouse_y))
            elements.removeClicked(map, mouse_x, mouse_y);*/
    }
    else if (Block::isClickInFrontyard(map, mouse_x, mouse_y)) {
        level.createPlant(player, map, elements, icons, mouse_x, mouse_y);
        player.is_first_click_made = false;
    }
}

void readSavedata(Player & player, Level & level){
    std::string line;
    std::ifstream myfile ("savedata.txt");
    if (myfile.is_open()){
        getline (myfile,line);
        //player.name = line;
        getline (myfile, line);
        level.level_num = stoi(line);
        myfile.close();
    }
    else std::cout << "Unable to open file";
}

bool clickedStart(int mouse_x, int mouse_y){
    if (mouse_x > TAP_TO_START_X1 && mouse_y < TAP_TO_START_X2 &&
        mouse_y > TAP_TO_START_Y1 && mouse_y < TAP_TO_START_Y2)
        return true;
    return false;
}

void displayStarting(window & win){
    bool game_started = false;
    bool quit = false;
    while (quit || !game_started){
        win.draw_png(STARTING_SCREEN_DIRECTORY, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        HANDLE(
                QUIT(quit = true);
                KEY_PRESS(q, quit = true);
                LCLICK({
                               if (clickedStart(mouse_x, mouse_y))
                               game_started = true;
                       });
        );

        win.update_screen();
        DELAY(10);
    }
}
void init_game(window & win, Level & level, Player & player, Map & map){
    displayStarting(win);
    win.play_music("joke.mp3", -1);
    readSavedata(player, level);
    level.readLevelData();
    level.decideZombieCountForEachSec();
    map = Block::createBlockMap();
    player.sun_count = INIT_SUN_COUNT;
    player.is_first_click_made = false;
}



int main(){
    bool quit = false;
    long int clk = 0;
    Level level;
    Elements game_characters;
    Icons icons;
    Player player;
    Map map;
    window win(WINDOW_WIDTH, WINDOW_HEIGHT);
    init_game(win, level, player, map);
    while(!quit){
        if (game_characters.hasZombiesPassedBoundary(X_UPPER_LEFT + 5))
            displayLosingMessage(win);
        else if (level.isWaveCompleted(game_characters))
            displayWinningMessage(win);
        else {
            icons.displayLayout(win, player);
            displayGameElements(win, game_characters, map);
            game_characters.handleMovements(map, clk);
            level.handleChanges(game_characters, map,clk);
        }
        HANDLE(
                QUIT(quit = true);
                KEY_PRESS(q, quit = true);
                LCLICK({
                               handleClick(player, icons, level, game_characters, map, mouse_x, mouse_y);
                       });
        );
        clk ++;
        win.update_screen();
        DELAY(CLK_LENGTH);
    }
    return 0;
}