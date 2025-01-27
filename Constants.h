#pragma once


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "rsdl.hpp"
#include <memory>

//------------------------------------------------------------------------------
// Константы для управления игровыми параметрами
//------------------------------------------------------------------------------

#define CLK_LENGTH 5
#define ELEMENT_WIDTH 65
#define ELEMENT_HEIGHT 80

/** 
 * @brief Картинки
 */
#define STARTING_SCREEN_DIRECTORY "./Image_Assets/Starting_Screen.png"
#define BACKGROUND_DIRECTORY "./Image_Assets/Frontyard.png"
#define BACKGROUND_DIM_DIRECTORY "./Image_Assets/Frontyard_dim.jpeg"
#define LOSING_MESSAGE_DIRECTORY "./Image_Assets/Losing_Message.png"
#define WINNING_MESSAGE_DIRECTORY "./Image_Assets/Winning_Message.png"
#define BLACK_SCREEN_DIRECTORY "./Image_Assets/Black_Screen.png"

/** 
 * @brief Размеры поля
 */
constexpr int VERT_BLOCK_COUNT = 5;
constexpr int HORIZ_BLOCK_COUNT = 9;
constexpr int BLOCK_WIDTH = 81;
constexpr int BLOCK_HEIGHT = 101;
constexpr int X_UPPER_LEFT = 250;
constexpr int Y_UPPER_LEFT = 70;
