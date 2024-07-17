//============================================================================
// Name        : mainpage.h
// Author      : lisr-pcx
// MIT License (c) 2024 lisr-pcx
//
// CRIsp
// (CRIttografia senza pretese)
//============================================================================

#include "mainpage.h"
#include "ui_mainpage.h"

MainPage::MainPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainPage)
{
    ui->setupUi(this);
}

MainPage::~MainPage()
{
    delete ui;
}

