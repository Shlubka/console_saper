#include "gamefn.c"

char* cellCheck(struct BombCoords* bc, struct FlagCoords* fc, struct OpenCells* oc, int xi, int yj);
int confirmInput(int width, int height, const char* message, int defaultWidth, int defaultHeight);
int doureal();
void enableRawMode();
void disableRawMode();
int choseDifficulty();
void drowField(struct BombCoords** bc, struct FlagCoords** fc, struct OpenCells** oc, int row, int col, int corx, int cory, int diff, int num, int *x, int *y);
void addFlag(struct FlagCoords** bc, int cory, int corx);
int genCode(struct BombCoords** bc, int diff, int row, int col);

