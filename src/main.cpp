//============================================================================
// Name        : mainpage.h
// Author      : lisr-pcx
// MIT License (c) 2024 lisr-pcx
//
// CRIsp
// (CRIttografia senza pretese)
//============================================================================

#include "mainpage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainPage w;
    w.show();
    return a.exec();
}
