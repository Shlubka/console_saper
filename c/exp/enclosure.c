struct BombCoords
{
  int x;
  int y;
  char bomb;
  struct BombCoords* next;
};

struct FlagCoords
{
  int x;
  int y;
  //char cell;
  struct FlagCoords* next;
};
struct OpenCells
{
  int x;
  int y;
  char* cell;
  struct OpenCells* next;
};

void drowField(struct BombCoords** bc, struct FlagCoords** fc, struct OpenCells* oc)
