# kursach

Структура:
[saper](#SAPER)
[decoration](#decoration)
[gamefn](#GAMEFN)
[term_tools](#TERM_TOOLS)
# TO-DO
- [x] заставка
- [x] базовое отображение
- [x] динамическое поле
- [ ] декорации
- [ ] система очков
- [ ] система сохранений
- [ ] нормальная генерация 
- [ ] юнит тесты и др проверки
- [ ] многопоточность 
- [ ] таймер
- [ ] рефакторинг 

> Возможно переписать на rust

> Возможно в будущем перенос некоторых функций в разные бинарники


# Доки
Компиляция командой `gcc saper`
В названии библиотек указаны задачи, которые они выполняют

## Завтсимости
- ОС linux (рабочая станция arch )


# *DECORATION*
## TO-DO
- [x] welcome
- [ ] printd

## Функции:
- [welcome](###WELCOME)
- [printd](###PRINTD)


### WELCOME 
Функция вывода приветствия. В зависимости от размера терминала выводит разное приветствие

### PRINTD
Функция обёртывания вывода в рамку. Пока не до конца представляю реализацию 

# *GAMEFN*
## TODO
- [ ] доделать логику genCode (генерация бомб)
- [ ] доделать логику open_open_cell (открытие клеток)

## Функции:
- [cellCheck](###cellCheck)
- [confirmInput](###confirmInput)
- [doureal](###doureal)
- [enableRawMode](###enableRawMode)
- [disableRawMode](###disableRawMode)
- [choseDifficulty](###choseDifficulty)
- [drowField](###drowField)
- [addFlag](###addFlag)
- [genCode](###genCode)

### cellCheck
```c

char* cellCheck(struct BombCoords* bc, struct FlagCoords* fc, struct OpenCells* oc, int xi, int yj) {}
```
Принимает *структуру бомб*, *структуру флагов*, *структуру открытых клеток*

### confirmInput
(int width, int height, const char* message, int defaultWidth, int defaultHeight);
### doureal();
### choseDifficulty();
### drowField
(struct BombCoords** bc, struct FlagCoords** fc, struct OpenCells* oc, int row, int col, int corx, int cory, int diff, int num, int *x, int *y);
### addFlag
(struct FlagCoords** bc, int cory, int corx);
### genCode
(struct BombCoords** bc, int diff, int row, int col);






# *TERM_TOOLS*