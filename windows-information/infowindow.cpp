#include "infowindow.h"

InfoWindow::InfoWindow(UINT_PTR hwnd) :wnd((HWND)hwnd),
    ui(new Ui::InfoWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Информация об окне номер "+QString::number((UINT_PTR)wnd));
    wchar_t className[100], title[100];
    for(int i=0;i<100;i++){className[i]=0;title[i]=0;}
    GetWindowTextW(wnd,title,100);
    GetClassNameW(wnd,className,100);
    ui->window_name->setText(
        "Имя окна: "+(title[0]==0?"(У окна нет имени)":QString::fromWCharArray(title))+'\n'+
        "Класс окна: "+QString::fromWCharArray(className)
    );
    ui->hWnd_view->display((int)(UINT_PTR)wnd);
    timer=startTimer(1);
    where = new QWidget;
    where->setWindowFlag(Qt::WindowType::Tool);
    where->setDisabled(true);
    where->show();
}

void InfoWindow::timerEvent(QTimerEvent* event){
    Q_UNUSED(event);
    ui->visibility->setChecked(IsWindowVisible(wnd));
    where->setWindowOpacity(ui->visibility->isChecked()?0.9:0.3);
    RECT size;
    GetWindowRect(wnd,&size);
    if(GetWindowLong(wnd,GWL_STYLE)&WS_CHILD){
        ui->pos_x->setText("Окно дочернее");
        ui->pos_y->setText(ui->pos_x->text());
    }else{
        ui->pos_x->setNum((int)size.left);
        ui->pos_y->setNum((int)size.top);
    }
    ui->width->setNum((int)(size.right-size.left));
    ui->height->setNum((int)(size.bottom-size.top));
    where->setGeometry(size.left,size.top,size.right-size.left,size.bottom-size.top);
}

void InfoWindow::on_minimize_wnd_clicked(){
    ui->visibility->setChecked(false);
    ShowWindow(wnd,SW_MINIMIZE);
}

void InfoWindow::on_maximize_wnd_clicked()
{
    ShowWindow(wnd,SW_MAXIMIZE);
}

void InfoWindow::on_show_wnd_clicked()
{
    ShowWindow(wnd,SW_RESTORE);
}
