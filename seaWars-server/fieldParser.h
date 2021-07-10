#ifndef FIELDPARSER_H
#define FIELDPARSER_H

///for [begin;end) U N
#define forRange(var,begin,end) for(int var=begin;var<end;var++)

class fieldParser{
    static bool isABoat(const char* field, int length, int xa, int ya, bool sideways){
        bool *boat[3];
        //generate boat
        if(length>4 || length<0 )throw "Invalid parameter.";
        forRange(i, 0,3)
            boat[i]= new bool[length+2];
        forRange(x, 0,length+2)
            boat[0][x] = boat[2][x] = 0;
        boat[1][0] = boat[1][length+1] = 0;
        forRange(x, 1,length+1)
            boat[1][x] = 1;
        //find boat
        bool ret = true;
        forRange(y, 0,3)forRange(x, 0,length+2){
            if(!ret)break;
            if(sideways){
                if((x+ya>9||y+xa>9||x+ya<0||y+xa<0)){
                    if(boat[y][x]==1) ret = false;
                    continue;
                }
                if(boat[y][x]+'0'!=field[(x+ya)*10+(y+xa)])
                    ret = false;
            }else{
                if((y+ya>9||x+xa>9||y+ya<0||x+xa<0)){
                    if(boat[y][x]==1) ret = false;
                    continue;
                }
                if(boat[y][x]+'0'!=field[(y+ya)*10+(x+xa)])
                    ret = false;
            }
        }
        //memory leaks - no
        forRange(i, 0,3)delete boat[i];
        return ret;
    }
public:
    static bool isValid(const char boats[100]){
        short ships[4]={0,0,0,0};
        forRange(length, 1,5)forRange(x, -1,9)forRange(y, -1,9)
            if(isABoat(boats,length,x,y,false)||isABoat(boats,length,x,y,true))
                ships[length-1]++;
        return ships[0]==4&&ships[1]==3&&ships[2]==2&&ships[3]==1;
    }
};

#endif // FIELDPARSER_H
