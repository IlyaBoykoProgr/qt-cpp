#ifndef TESTDATA_H
#define TESTDATA_H
#include <fstream>
#include <QDebug>
#include <QList>
#include <QFile>
#include <QDataStream>

enum page_type {INPUT,RADIO,CHECKBOX};

typedef struct pagedatar{
 page_type type;
 QString question;
 QList<QString> variants={};
 QList<bool> isAnswer={};
 void operator >>(QDataStream &stream){
     stream<<type<<question<<variants<<isAnswer;
 }
 void operator <<(QDataStream &stream){
     stream>>type>>question>>variants>>isAnswer;
 }
}pagedata;

#endif // TESTDATA_H
