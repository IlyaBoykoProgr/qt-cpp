#ifndef BIN_FILE
#define BIN_FILE
#include <fstream>
class bstream{
	fstream* bfile;
public:
	bstream(char file[]){
		bfile=new fstream(file,ios_base::binary);
	}
	template <typename T>
	void operator<<(T what){
		bfile<<sizeof(what);
	}
	template <typename T>
	void operator>>(T &where){
		int bug;
		bfile>>bug>>where;
	}
};
#endif
