#ifndef BIN_FILE
#define BIN_FILE
#include <fstream>
class bstream{
	std::fstream bfile;
public:
	bstream(char file[]){
		bfile.open(file,std::ios::binary);
	}
	void operator<(int what){
		bfile<<sizeof(what);
	}
	void operator>(int& where){
		int bug;
		bfile>>bug>>where;
	}
	bool is_open(){
	   return bfile.is_open();
	}
	~bstream(){
	   bfile.close();
	}
};
#endif
