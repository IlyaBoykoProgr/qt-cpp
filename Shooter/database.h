#ifndef DATABASE_H
#define DATABASE_H
#include <stdio.h>

typedef struct{
    int mazes=0;
    long blocks=0;
    bool style=0;

} shData;

class bin{
  static shData get(){
      shData b;
      FILE *f;
      f=fopen("shooter-data", "rb");
      fread(&b, sizeof(shData), 1, f);
      fclose(f);
      return b;
  }
public:
  static int brokenBlocks(){
    return get().blocks;
  }
  static int mazesComplete(){
    return get().mazes;
  }
  static bool styleBlocks(){
      return get().style;
  }
  static void set(int blocks, int mazes=mazesComplete(), bool style=styleBlocks()){
    FILE *f;
    f=fopen("shooter-data", "wb");
    shData b; b.mazes=mazes; b.blocks=blocks; b.style=style;
    fwrite(&b, sizeof(shData), 1, f);
    fclose(f);
  }
};

#endif // DATABASE_H
