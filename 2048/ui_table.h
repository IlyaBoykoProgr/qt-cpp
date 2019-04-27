/********************************************************************************
** Form generated from reading UI file 'table.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLE_H
#define UI_TABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_table
{
public:
    QAction *Up;
    QAction *Down;
    QAction *Left;
    QAction *Right;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *table)
    {
        if (table->objectName().isEmpty())
            table->setObjectName(QStringLiteral("table"));
        table->resize(272, 246);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/gem5.png"), QSize(), QIcon::Normal, QIcon::Off);
        table->setWindowIcon(icon);
        Up = new QAction(table);
        Up->setObjectName(QStringLiteral("Up"));
        Down = new QAction(table);
        Down->setObjectName(QStringLiteral("Down"));
        Down->setEnabled(true);
        Left = new QAction(table);
        Left->setObjectName(QStringLiteral("Left"));
        Right = new QAction(table);
        Right->setObjectName(QStringLiteral("Right"));
        centralWidget = new QWidget(table);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        table->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(table);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        table->addToolBar(Qt::BottomToolBarArea, mainToolBar);

        mainToolBar->addAction(Up);
        mainToolBar->addAction(Down);
        mainToolBar->addAction(Left);
        mainToolBar->addAction(Right);

        retranslateUi(table);

        QMetaObject::connectSlotsByName(table);
    } // setupUi

    void retranslateUi(QMainWindow *table)
    {
        table->setWindowTitle(QApplication::translate("table", "2048", Q_NULLPTR));
        Up->setText(QApplication::translate("table", "Up", Q_NULLPTR));
        Up->setShortcut(QApplication::translate("table", "Up", Q_NULLPTR));
        Down->setText(QApplication::translate("table", "Down", Q_NULLPTR));
        Down->setShortcut(QApplication::translate("table", "Down", Q_NULLPTR));
        Left->setText(QApplication::translate("table", "Left", Q_NULLPTR));
        Left->setShortcut(QApplication::translate("table", "Left", Q_NULLPTR));
        Right->setText(QApplication::translate("table", "Right", Q_NULLPTR));
        Right->setShortcut(QApplication::translate("table", "Right", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class table: public Ui_table {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLE_H
