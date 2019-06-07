#ifndef BIN_FILE
#define BIN_FILE
#include <fstream>
class bstream{
	std::fstream bfile;
public:
	bstream(char file[]){
		bfile.open(file,std::ios::binary);
		if(!bfile.is_open()){
		 std::ofstream creat("shooter_data",std::ios::binary);
		 creat<<sizeof(1);
		 creat.close();
		}
	}
	void operator<(int what){
		bfile<<sizeof(what);
	}
	void operator>(int& where){
		int bug;
		bfile>>bug>>where;
	}
	~bstream(){
	   bfile.close();
	}
};
#endif
