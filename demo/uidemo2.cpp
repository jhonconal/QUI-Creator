#pragma execution_character_set("utf-8")

#include "uidemo2.h"
#include "ui_uidemo2.h"
#include "quiwidget.h"

UIDemo2::UIDemo2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIDemo2)
{
    ui->setupUi(this);
    this->initForm();
    QUIWidget::setFormInCenter(this);
}

UIDemo2::~UIDemo2()
{
    delete ui;
}

void UIDemo2::initForm()
{
    this->max = false;
    this->location = this->geometry();
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

    IconHelper::Instance()->setIcon(ui->lab_Ico, QChar(0xF099), 30);
    IconHelper::Instance()->setIcon(ui->btnMenu_Min, QChar(0xF068));
    IconHelper::Instance()->setIcon(ui->btnMenu_Max, QChar(0xF067));
    IconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xF00d));

    ui->lab_Title->setText("智能访客管理平台");
    ui->lab_Title->setFont(QFont("Microsoft Yahei", 20));
    this->setWindowTitle(ui->lab_Title->text());

    ui->label->setStyleSheet("QLabel{font:30pt;}");   

    QSize icoSize(32, 32);
    int icoWidth = 85;

    //设置顶部导航按钮
    QList<QToolButton *> tbtns = ui->widget_top->findChildren<QToolButton *>();
    foreach (QToolButton *btn, tbtns) {
        btn->setIconSize(icoSize);
        btn->setMinimumWidth(icoWidth);
        btn->setCheckable(true);
        connect(btn, SIGNAL(clicked()), this, SLOT(buttonClick()));
    }

    ui->btnMain->click();

    //设置左侧导航按钮
    QList<QPushButton *> btns = ui->widget_left->findChildren<QPushButton *>();
    foreach (QPushButton *btn, btns) {
        btn->setCheckable(true);
        connect(btn, SIGNAL(clicked()), this, SLOT(btnClick()));
    }

    ui->btn1->click();    
}

void UIDemo2::buttonClick()
{
    QToolButton *btn = (QToolButton *)sender();
    QString name = btn->text();

    QList<QToolButton *> btns = ui->widget_top->findChildren<QToolButton *>();
    foreach (QToolButton *b, btns) {
        if (b == btn) {
            b->setChecked(true);
        } else {
            b->setChecked(false);
        }
    }

    ui->label->setText(QString("你单击了顶部导航菜单\n%1").arg(name));
}

void UIDemo2::btnClick()
{
    QPushButton *b = (QPushButton *)sender();
    QString name = b->text();

    QList<QPushButton *> btns = ui->widget_left->findChildren<QPushButton *>();
    foreach (QPushButton *btn, btns) {
        if (btn == b) {
            btn->setChecked(true);
        } else {
            btn->setChecked(false);
        }
    }

    ui->label->setText(QString("你单击了左侧导航菜单\n%1").arg(name));
}

void UIDemo2::on_btnMenu_Min_clicked()
{
    showMinimized();
}

void UIDemo2::on_btnMenu_Max_clicked()
{
    if (max) {
        this->setGeometry(location);
        this->setProperty("canMove", true);
    } else {
        location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
        this->setProperty("canMove", false);
    }

    max = !max;
}

void UIDemo2::on_btnMenu_Close_clicked()
{
    close();
}
