#include <iostream>
#include <windows.h>
#include <vector>
#include <math.h>
using namespace std;

#define HIGH_QUALITY 0

vector<HWND> windows;
int screen_w,screen_h;

bool isWindowOn(HWND h){
    WINDOWPLACEMENT wp;
    wp.length=sizeof(wp);
    GetWindowPlacement(h,&wp);
    return !((wp.showCmd==SW_MAXIMIZE)||(wp.showCmd==SW_MINIMIZE));
}

void moveAnim(HWND handle,int x, int y, int w, int h){
    RECT rect;
    for(;;){
        GetWindowRect(handle,&rect);
        RECT newrect(rect);
        long rectwidth=rect.right-rect.left;
        long rectheight=rect.bottom-rect.top;
        if(rect.left<x)newrect.left+=1;
        if(rect.left>x)newrect.left-=1;
        if(rect.top<y)newrect.top+=1;
        if(rect.top>y)newrect.top-=1;
        MoveWindow(handle,newrect.left,newrect.top,rectwidth,rectheight,HIGH_QUALITY);
        if(rect.top==y && rect.left==x)break;
    }
    for(;;){
        GetWindowRect(handle,&rect);
        RECT newrect(rect);
        long rectwidth=rect.right-rect.left;
        long rectheight=rect.bottom-rect.top;
        if(rectwidth<w)newrect.right+=10;
        if(rectwidth>w)newrect.right-=1;
        if(rectheight<h)newrect.bottom+=10;
        if(rectheight>h)newrect.bottom-=1;
        long newrectwidth=newrect.right-newrect.left;
        long newrectheight=newrect.bottom-newrect.top;
        MoveWindow(handle,x,y,newrectwidth,newrectheight,HIGH_QUALITY);
        if(rectwidth>=w && rectheight>=h)break;
    }
    MoveWindow(handle,x,y,w,h,HIGH_QUALITY);
}

BOOL CALLBACK addWindow(HWND wnd,LPARAM lparm){
    (void)lparm;
    if(IsWindow(wnd)&&IsWindowVisible(wnd)&&isWindowOn(wnd)){
        if(GetDesktopWindow()==wnd)return 0;
        char Class[100];
        RealGetWindowClassA(wnd,Class,100);
        cout<<Class<<"\n";
        if(strcmp("CabinetWClass",Class)==0){
            windows.insert(windows.end(),wnd);
        }
    }
    return 1;
}

int main()
{
    {
        RECT rect;
        GetWindowRect(GetDesktopWindow(),&rect);
        screen_w=rect.right-rect.left;
        screen_h=rect.bottom-rect.top;
    }

    begin:

    EnumWindows(addWindow,0);
    int c=0;
    for(auto w : windows){(void)w;c++;}
    for(int w=0;w<c;w++){
        if(c==1)moveAnim(windows[0],0,0,screen_w,screen_h);
        if(c%2==0&&c>1){
            moveAnim(windows[w],
                     w+1==c?0:round((double)w/2.0)*screen_w/(c/2),
                     w%2*screen_h/2,
                     screen_w/(c/2),
                     screen_h/2);
        }
        if(c%2==1&&c>1){
            moveAnim(windows[w],
                     w==c?0:round((double)w/2.0)*screen_w/(c/2+1),
                     w%2*screen_h/2,
                     screen_w/(c/2+1),
                     screen_h/2);
        }
    }
    if(c>0){
        ShowWindow(GetConsoleWindow(),SW_MINIMIZE);
    }else
        ShowWindow(GetConsoleWindow(),SW_SHOWNORMAL);

    windows.clear();
    system("cls");
    goto begin;

    return 0;
}
