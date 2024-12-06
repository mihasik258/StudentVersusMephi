#pragma once


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "rsdl.hpp"
#include <memory>


#define CLK_LENGTH 5
#define SKY_SUN_TIME 2000
#define SUNFLOWER_SUN_TIME 2000
#define STUDENT_CREATE_TIME 1200
#define FIRE_PEA_TIME 300
#define BYTE_TIME 100
#define STUDENT_TIME 22
#define SUN_TIME 8
#define PEA_TIME 4

#define INIT_SUN_COUNT 200
#define PEASHOOTER_PRICE 100
#define ICESHOOTER_PRICE 150
#define FIRESHOOTER_PRICE 175
#define SUNFLOWER_PRICE 50
#define WALNUT_PRICE 50


#define STUDENT_INIT_X 900
#define STUDENT_DX 3
#define PEA_DX 15
#define SUN_DY 1
#define WALNUT_HP_LIMIT 10
#define SUNFLOWER_HP_LIMIT 5
#define PEASHOOTER_HP_LIMIT 5

#define WINDOW_WIDTH 1050
#define WINDOW_HEIGHT 600
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
#define WALNUT_CRACKED_1_DIRECTORY "./Image_Assets/byte.png"
#define WALNUT_CRACKED_2_DIRECTORY "./Image_Assets/byte.png"
#define ICON_BAR_DIRECTORY "./Image_Assets/Item_Bar.png"
#define PEASHOOTER_ICON_BRIGHT_DIRECTORY "./Image_Assets/icon_peashooter_100.png"
#define PEASHOOTER_ICON_DIM_DIRECTORY "./Image_Assets/icon_peashooter_100_dim.png"
#define ICESHOOTER_ICON_BRIGHT_DIRECTORY "./Image_Assets/Icesh.png"
#define ICESHOOTER_ICON_DIM_DIRECTORY "./Image_Assets/Icesh_black.png"
#define FIRESHOOTER_ICON_BRIGHT_DIRECTORY "./Image_Assets/Firesh.png"
#define FIRESHOOTER_ICON_DIM_DIRECTORY "./Image_Assets/Firesh_b.png"
#define SUNFLOWER_ICON_BRIGHT_DIRECTORY "./Image_Assets/icon_sunflower.png"
#define SUNFLOWER_ICON_DIM_DIRECTORY "./Image_Assets/icon_sunflower_dim.png"
#define WALNUT_ICON_BRIGHT_DIRECTORY "./Image_Assets/icon_walnut.png"
#define WALNUT_ICON_DIM_DIRECTORY "./Image_Assets/icon_walnut_dim.png"

constexpr int VERT_BLOCK_COUNT = 5;
constexpr int HORIZ_BLOCK_COUNT = 9;
constexpr int BLOCK_WIDTH = 81;
constexpr int BLOCK_HEIGHT = 101;
constexpr int X_UPPER_LEFT = 250;
constexpr int Y_UPPER_LEFT = 70;
