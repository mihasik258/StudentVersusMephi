#pragma once

#include "rsdl.hpp"
#include "Constants.h"
#include "Level.h"

/**
 * @brief Отображает всех зомби на экране.
 * 
 * Итерация по вектору зомби и отрисовка каждого в его соответствующем местоположении 
 * в зависимости от его строки и вертикальных ограничений карты.
 * 
 * @param win Объект окна, в котором будут отрисовываться зомби.
 * @param zombies Вектор объектов Zombie, которые нужно отобразить.
 * @param map Ссылка на объект Map<Block>, который используется для определения вертикальных ограничений для каждого зомби.
 * 
 * @return void
 * 
 * @note Нет
 */
void displayZombies(window & win, std::vector<Zombie> & zombies, const Map<Block> &map);
/**
 * @brief Отображает все горохи на экране.
 * 
 * Итерация по вектору указателей на объекты Pea и отрисовка каждого в его соответствующем местоположении на экране.
 * Горохи отображаются только если они находятся в пределах горизонтальных границ карты и на определенном расстоянии от края.
 * 
 * @param win Объект окна, в котором будут отрисовываться горохи.
 * @param peas Вектор указателей на объекты Pea, которые нужно отобразить.
 * @param map Ссылка на объект Map<Block>, который используется для определения горизонтальных и вертикальных ограничений для каждого гороха.
 */
void displayPeas(window & win, std::vector<Pea*> & peas, const Map<Block> &map);
/**
 * @brief Отображает все растения на экране.
 * Итерация по вектору уникальных указателей на объекты Plant и отрисовка каждого растения в его соответствующем местоположении 
 * в зависимости от его строки, столбца и границ карты. Функция различает типы растений (например, Walnut, Peashooter, Iceshooter, Sunflower)
 * и отрисовывает соответствующее изображение для каждого типа.
 * @param win Объект окна, в котором будут отрисовываться растения.
 * @param plants Константная ссылка на вектор уникальных указателей на объекты Plant, которые нужно отобразить.
 * @param map Ссылка на объект Map<Block>, который используется для определения горизонтальных и вертикальных ограничений для каждого растения.
 * 
 * @return void
 */
void displayPlants(window &win, const std::vector<std::unique_ptr<Plant>> &plants, const Map<Block> &map);
/**
 * @brief Отображает все солнца на экране.
 * Итерация по вектору объектов Sun и отрисовка каждого в его соответствующем местоположении в зависимости от его столбца 
 * и горизонтальных ограничений карты.
 * @param win Объект окна, в котором будут отрисовываться солнца.
 * @param suns Вектор объектов Sun, которые нужно отобразить.
 * @param map Ссылка на объект Map<Block>, который используется для определения горизонтальных ограничений для каждого солнца.
 * @return void
 */
void displaySuns(window & win, std::vector<Sun> suns, const Map<Block> &map);
/**
 * @brief Отображает все элементы игры (зомби, растения, горохи и солнца) на экране.
 * Эта функция вызывает функции отображения для зомби, растений, горохов и солнц последовательно, чтобы отобразить 
 * все элементы игры сразу.
 * @param win Объект окна, в котором будут отрисовываться элементы игры.
 * @param elements Ссылка на объект Elements, содержащий все элементы игры, которые нужно отобразить.
 * @param map Ссылка на объект Map<Block>, который используется для определения ограничений для каждого элемента игры.
 * @return void
 */
void displayGameElements(window &win, Elements &elements, const Map<Block> &map);
/**
 * @brief Отображает сообщение о поражении, когда игра завершена.
 * Эта функция отображает сообщение о поражении, затемняющее экран и показывающее соответствующее изображение.
 * @param win Объект окна, в котором будет отображаться сообщение о поражении.
 * @return void
 */
void displayLosingMessage(window & win);
/**
 * @brief Отображает сообщение о победе, когда игрок выигрывает.
 * Эта функция отображает сообщение о победе, затемняющее экран и показывающее соответствующее изображение.
 * @param win Объект окна, в котором будет отображаться сообщение о победе.
 * @return void
 */
void displayWinningMessage(window & win);
/**
 * @brief Проверяет, было ли нажато на иконку в панели иконок.
 * Эта функция проверяет, был ли клик мыши в пределах границ панели иконок.
 * @param mouse_x Координата x клика мыши.
 * @param mouse_y Координата y клика мыши.
 * @return true, если клик произошел в пределах панели иконок, иначе false.
 */
bool is_an_icon_chosen(int mouse_x, int mouse_y);
/**
 * @brief Обрабатывает события кликов во время игры.
 * В зависимости от клика мыши эта функция обновляет выбор иконки игрока, подбирает солнца или размещает растения на карте
 * в соответствии с выбранной иконкой.
  * @param player Игрок, действия которого будут обновляться в зависимости от клика.
 * @param icons Объект Icons, который управляет данными иконок.
 * @param level Уровень игры, который содержит логику, специфичную для уровня.
 * @param elements Объект Elements, который хранит все элементы игры.
 * @param map Объект Map<Block>, который определяет расположение элементов игры.
 * @param mouse_x Координата x клика мыши.
 * @param mouse_y Координата y клика мыши.
 * @return void
 */
void handleClick(Player & player, Icons & icons, Level & level, Elements & elements, Map<Block> &map, int mouse_x, int mouse_y);
/**
 * @brief Читает сохраненные данные игры и обновляет информацию об игроке и уровне.
 * Эта функция читает сохраненные данные из файла и обновляет уровень игрока.
 * @param player Игрок, чьи данные будут обновляться.
 * @param level Уровень игры, который будет обновлен в зависимости от сохраненных данных.
 * @return void
 * @note Если файл не найден, выводится сообщение об ошибке.
 */
void readSavedata(Player & player, Level & level);
/**
 * @brief Проверяет, был ли кликнут на кнопку "Старт" на начальном экране.
 * Эта функция проверяет, был ли клик мыши внутри границ кнопки "Старт".
 * @param mouse_x Координата x клика мыши.
 * @param mouse_y Координата y клика мыши.
 * @return true, если клик был в пределах кнопки "Старт", иначе false.
 */
bool clickedStart(int mouse_x, int mouse_y);
/**
 * @brief Отображает начальный экран и ожидает взаимодействия с пользователем.
 * Эта функция отображает начальный экран и ожидает клика или нажатия клавиши для начала игры или выхода.
 * @param win Объект окна, в котором будет отображаться начальный экран.
 * @return void
 */
void displayStarting(window & win);
/**
 * @brief Инициализирует игру, показывая начальный экран, воспроизводя музыку и загружая сохраненные данные.
 * Эта функция настраивает начальное состояние игры, включая отображение начального экрана, загрузку сохраненных данных,
 * инициализацию элементов игры и определение количества зомби для каждой секунды.
 * @param win Объект окна, используемого для отображения игры.
 * @param level Уровень игры, содержащий логику уровня.
 * @param player Игрок, чьи данные и состояние будут инициализированы.
 * @param map Карта игры, которая будет использована для настройки блоков.
 * @return void
 */
void init_game(window & win, Level & level, Player & player, Map<Block> &map);
void processEvents(bool &quit, bool &game_started, bool &mouse_click, int &mouse_x, int &mouse_y);
