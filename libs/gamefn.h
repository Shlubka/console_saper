#include "gamefn.c"

char* cellCheck(char **START_GAME_FIELD, char **WORK_FIELD, char **FLAG_FIELD, int xi, int yj);
int confirmInput(int width, int height, const char* message, int defaultWidth, int defaultHeight);
int doureal();
void enableRawMode();
void disableRawMode();
int choseDifficulty();
void drowField(char **START_GAME_FIELD, char **WORK_FIELD, char **FLAG_FIELD, int row, int col, int corx, int cory, int diff, int *x, int *y);
void addFlag(char **FLAG_FIELD, int cory, int corx);
void genCode(char **START_GAME_FIELD, int diff, int row, int col);

