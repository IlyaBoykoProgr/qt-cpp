#ifndef THEWINDOW_H
#define THEWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QDropEvent>
#include <QMimeData>
#include <thread>
#include <QDirIterator>
#include <QMovie>
#include <thread>
#include "testData.h"
#include "pagecreationdialog.h"
#include "testingdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TheWindow; }
QT_END_NAMESPACE
using namespace std;

class TheWindow : public QMainWindow
{
    Q_OBJECT
public:
    TheWindow(QWidget *parent = nullptr);
    ~TheWindow();
public slots:
    void on_test_open_triggered();
    void onFrameChanged(){
        setWindowIcon(QIcon(iconGif->currentPixmap()));
    }
private slots:
    void on_test_create_triggered();
    void on_result_open_triggered();
    void on_listTests_itemDoubleClicked(QListWidgetItem *item);
    void on_butt_research_clicked();
private:
    void closeEvent(QCloseEvent* event){
        Q_UNUSED(event);
        for(int curX=x();curX>-width();curX--)move(curX,y());
    };
    void dropEvent(QDropEvent* event);
    void dragEnterEvent(QDragEnterEvent* event);
    void openTest(QString path);
    void openResult(QString path);
    void saveResult(QString path,uint64_t points, uint64_t page_count);
    Ui::TheWindow *ui;
    QMovie* iconGif;
};
#endif // THEWINDOW_H
