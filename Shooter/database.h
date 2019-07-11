#ifndef DATABASE_H
#define DATABASE_H

namespace data{
  FILE *f;
  int brokenBlocks(){
    int b;
    f=fopen("shooter-data", "rb");
    fread(&b, sizeof(int), 1, f);
    fclose(f);
    return b;
  }
  int mazesComplete(){
    int b,m;
    f=fopen("shooter-data", "rb");
    fread(&b, sizeof(int), 1, f);
    fread(&m, sizeof(int), 1, f);
    fclose(f);
    return m;
  }
  void set(int blocks, int mazes){
    f=fopen("shooter-data", "wb");
    fwrite(&blocks, sizeof(int), 1, f);
    fwrite(&mazes, sizeof(int), 1, f);
    fclose(f);
  }
}

#endif // DATABASE_H
