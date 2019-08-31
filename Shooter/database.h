#ifndef DATABASE_H
#define DATABASE_H
#include <stdio.h>
#include <fstream>

class bin{
public:
  static const char* path(){
    std::ifstream savePath("path");
    std::string p;
    savePath>>p;
    savePath.close();
    return p.data();
  }
  static int brokenBlocks(){
    int b;
    FILE *f;
    f=fopen(path(), "rb");
    fread(&b, sizeof(int), 1, f);
    fclose(f);
    return b;
  }
  static int mazesComplete(){
    int b,m;
    FILE *f;
    f=fopen(path(), "rb");
    fread(&b, sizeof(int), 1, f);
    fread(&m, sizeof(int), 1, f);
    fclose(f);
    return m;
  }
  static void set(int blocks, int mazes){
    FILE *f;
    f=fopen(path(), "wb");
    fwrite(&blocks, sizeof(int), 1, f);
    fwrite(&mazes, sizeof(int), 1, f);
    fclose(f);
  }
};

#endif // DATABASE_H
