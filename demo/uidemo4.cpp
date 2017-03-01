#pragma execution_character_set("utf-8")

#include "uidemo4.h"
#include "ui_uidemo4.h"

UIDemo4::UIDemo4(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIDemo4)
{
    ui->setupUi(this);
}

UIDemo4::~UIDemo4()
{
    delete ui;
}
