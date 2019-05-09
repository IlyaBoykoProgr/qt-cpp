#ifndef OPENER_H
#define OPENER_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QLabel>

namespace Ui {
class opener;
}

class opener : public QMainWindow
{
    Q_OBJECT

public:
    explicit opener(QWidget *parent = 0);
    void textopen(QString path);
    ~opener();
private slots:
    void on_files_doubleClicked(const QModelIndex &index);

private:
    Ui::opener *ui;
    QFileSystemModel* documents;
};

#endif // OPENER_H
