#pragma execution_character_set("utf-8")

#include "quiwidget.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include "qtoolbutton.h"
#include "qboxlayout.h"
#include "qlineedit.h"
#include "qcombobox.h"
#include "qaction.h"
#include "qfile.h"
#include "qevent.h"
#include "qtranslator.h"
#include "qtextcodec.h"
#include "qfontdatabase.h"
#include "qapplication.h"
#include "qdesktopwidget.h"
#include "qtimer.h"
#include "qdebug.h"

QUIWidget::QUIWidget(QWidget *parent) : QDialog(parent)
{
    this->initControl();
    this->initForm();
}

QUIWidget::~QUIWidget()
{
    delete widgetMain;
}

void QUIWidget::setStyle(QUIWidget::Style style)
{
    QString qssFile = ":/qss/blue.css";

    if (style == QUIWidget::Style_Silvery) {
        qssFile = ":/qss/silvery.css";
    } else if (style == QUIWidget::Style_Blue) {
        qssFile = ":/qss/blue.css";
    } else if (style == QUIWidget::Style_LightBlue) {
        qssFile = ":/qss/lightblue.css";
    } else if (style == QUIWidget::Style_DarkBlue) {
        qssFile = ":/qss/darkblue.css";
    } else if (style == QUIWidget::Style_Gray) {
        qssFile = ":/qss/gray.css";
    } else if (style == QUIWidget::Style_LightGray) {
        qssFile = ":/qss/lightgray.css";
    } else if (style == QUIWidget::Style_DarkGray) {
        qssFile = ":/qss/darkgray.css";
    } else if (style == QUIWidget::Style_Black) {
        qssFile = ":/qss/black.css";
    } else if (style == QUIWidget::Style_LightBlack) {
        qssFile = ":/qss/lightblack.css";
    } else if (style == QUIWidget::Style_DarkBlack) {
        qssFile = ":/qss/darkblack.css";
    } else if (style == QUIWidget::Style_PSBlack) {
        qssFile = ":/qss/psblack.css";
    } else if (style == QUIWidget::Style_FlatBlack) {
        qssFile = ":/qss/flatblack.css";
    } else if (style == QUIWidget::Style_FlatWhite) {
        qssFile = ":/qss/flatwhite.css";
    }

    QFile file(qssFile);

    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}

void QUIWidget::setStyle(const QString &qssFile)
{
    QFile file(qssFile);

    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}

void QUIWidget::setFormInCenter(QWidget *frm)
{
    int frmX = frm->width();
    int frmY = frm->height();
    QDesktopWidget w;
    int deskWidth = w.availableGeometry().width();
    int deskHeight = w.availableGeometry().height();
    QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
    frm->move(movePoint);
}

void QUIWidget::getQssColor(const QString &qss, QString &textColor, QString &panelColor, QString &borderColor,
                            QString &normalColorStart, QString &normalColorEnd,
                            QString &darkColorStart, QString &darkColorEnd, QString &highColor)
{
    QString str = qss;

    QString flagTextColor = "TextColor:";
    int indexTextColor = str.indexOf(flagTextColor);

    if (indexTextColor >= 0) {
        textColor = str.mid(indexTextColor + flagTextColor.length(), 7);
    }

    QString flagPanelColor = "PanelColor:";
    int indexPanelColor = str.indexOf(flagPanelColor);

    if (indexPanelColor >= 0) {
        panelColor = str.mid(indexPanelColor + flagPanelColor.length(), 7);
    }

    QString flagBorderColor = "BorderColor:";
    int indexBorderColor = str.indexOf(flagBorderColor);

    if (indexBorderColor >= 0) {
        borderColor = str.mid(indexBorderColor + flagBorderColor.length(), 7);
    }

    QString flagNormalColorStart = "NormalColorStart:";
    int indexNormalColorStart = str.indexOf(flagNormalColorStart);

    if (indexNormalColorStart >= 0) {
        normalColorStart = str.mid(indexNormalColorStart + flagNormalColorStart.length(), 7);
    }

    QString flagNormalColorEnd = "NormalColorEnd:";
    int indexNormalColorEnd = str.indexOf(flagNormalColorEnd);

    if (indexNormalColorEnd >= 0) {
        normalColorEnd = str.mid(indexNormalColorEnd + flagNormalColorEnd.length(), 7);
    }

    QString flagDarkColorStart = "DarkColorStart:";
    int indexDarkColorStart = str.indexOf(flagDarkColorStart);

    if (indexDarkColorStart >= 0) {
        darkColorStart = str.mid(indexDarkColorStart + flagDarkColorStart.length(), 7);
    }

    QString flagDarkColorEnd = "DarkColorEnd:";
    int indexDarkColorEnd = str.indexOf(flagDarkColorEnd);

    if (indexDarkColorEnd >= 0) {
        darkColorEnd = str.mid(indexDarkColorEnd + flagDarkColorEnd.length(), 7);
    }

    QString flagHighColor = "HighColor:";
    int indexHighColor = str.indexOf(flagHighColor);

    if (indexHighColor >= 0) {
        highColor = str.mid(indexHighColor + flagHighColor.length(), 7);
    }
}

void QUIWidget::setTranslator(const QString &qmFile)
{
    QTranslator *translator = new QTranslator(qApp);
    translator->load(qmFile);
    qApp->installTranslator(translator);
}

void QUIWidget::setCode()
{
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
    QTextCodec *codec = QTextCodec::codecForName("gbk");
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
#endif
}

void QUIWidget::showMessageBoxInfo(const QString &info, int closeSec)
{
    QUIMessageBox::Instance()->setMessage(info, 0, closeSec);
    QUIMessageBox::Instance()->show();
}

void QUIWidget::showMessageBoxError(const QString &info, int closeSec)
{
    QUIMessageBox::Instance()->setMessage(info, 2, closeSec);
    QUIMessageBox::Instance()->show();
}

int QUIWidget::showMessageBoxQuestion(const QString &info)
{
    QUIMessageBox msg;
    msg.setMessage(info, 1);
    return msg.exec();
}

QString QUIWidget::showInputBox(bool &ok, const QString &title, int type, int closeSec,
                                QString defaultValue, bool pwd)
{
    QUIInputBox input;
    input.setParameter(title, type, closeSec, defaultValue, pwd);
    ok = input.exec();
    return input.getValue();
}

bool QUIWidget::eventFilter(QObject *obj, QEvent *evt)
{
    static QPoint mousePoint;
    static bool mousePressed = false;

    QMouseEvent *event = static_cast<QMouseEvent *>(evt);
    if (event->type() == QEvent::MouseButtonPress) {
        if (event->button() == Qt::LeftButton) {
            mousePressed = true;
            mousePoint = event->globalPos() - this->pos();
            return true;
        }
    } else if (event->type() == QEvent::MouseButtonRelease) {
        mousePressed = false;
        return true;
    } else if (event->type() == QEvent::MouseMove) {
        if (!max && mousePressed && (event->buttons() && Qt::LeftButton)) {
            this->move(event->globalPos() - mousePoint);
            return true;
        }
    } else if (event->type() == QEvent::MouseButtonDblClick) {
        //以下写法可以将双击识别限定在标题栏
        //if (this->btnMenu_Max->isVisible() && obj == this->widget_title) {
        if (this->btnMenu_Max->isVisible()) {
            this->on_btnMenu_Max_clicked();
            return true;
        }
    } else if (event->type() == QEvent::Hide) {
        if (obj == mainWidget) {
            this->hide();
        }
    }

    return QWidget::eventFilter(obj, evt);
}

QLabel *QUIWidget::getLabIco() const
{
    return this->lab_Ico;
}

QLabel *QUIWidget::getLabTitle() const
{
    return this->lab_Title;
}

QToolButton *QUIWidget::getBtnMenu() const
{
    return this->btnMenu;
}

QPushButton *QUIWidget::getBtnMenuMin() const
{
    return this->btnMenu_Min;
}

QPushButton *QUIWidget::getBtnMenuMax() const
{
    return this->btnMenu_Max;
}

QPushButton *QUIWidget::getBtnMenuMClose() const
{
    return this->btnMenu_Close;
}

QString QUIWidget::getTitle() const
{
    return this->title;
}

Qt::Alignment QUIWidget::getAlignment() const
{
    return this->alignment;
}

QSize QUIWidget::sizeHint() const
{
    return QSize(600, 450);
}

QSize QUIWidget::minimumSizeHint() const
{
    return QSize(200, 150);
}

void QUIWidget::initControl()
{
    this->setObjectName(QString::fromUtf8("QUIWidget"));
    this->resize(900, 750);
    verticalLayout1 = new QVBoxLayout(this);
    verticalLayout1->setSpacing(0);
    verticalLayout1->setContentsMargins(11, 11, 11, 11);
    verticalLayout1->setObjectName(QString::fromUtf8("verticalLayout1"));
    verticalLayout1->setContentsMargins(1, 1, 1, 1);
    widgetMain = new QWidget(this);
    widgetMain->setObjectName(QString::fromUtf8("widgetMain"));
    widgetMain->setStyleSheet(QString::fromUtf8(""));
    verticalLayout2 = new QVBoxLayout(widgetMain);
    verticalLayout2->setSpacing(0);
    verticalLayout2->setContentsMargins(11, 11, 11, 11);
    verticalLayout2->setObjectName(QString::fromUtf8("verticalLayout2"));
    verticalLayout2->setContentsMargins(0, 0, 0, 0);
    widget_title = new QWidget(widgetMain);
    widget_title->setObjectName(QString::fromUtf8("widget_title"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(widget_title->sizePolicy().hasHeightForWidth());
    widget_title->setSizePolicy(sizePolicy);
    widget_title->setMinimumSize(QSize(0, 30));
    horizontalLayout4 = new QHBoxLayout(widget_title);
    horizontalLayout4->setSpacing(0);
    horizontalLayout4->setContentsMargins(11, 11, 11, 11);
    horizontalLayout4->setObjectName(QString::fromUtf8("horizontalLayout4"));
    horizontalLayout4->setContentsMargins(0, 0, 0, 0);
    lab_Ico = new QLabel(widget_title);
    lab_Ico->setObjectName(QString::fromUtf8("lab_Ico"));
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(lab_Ico->sizePolicy().hasHeightForWidth());
    lab_Ico->setSizePolicy(sizePolicy1);
    lab_Ico->setMinimumSize(QSize(30, 0));
    lab_Ico->setAlignment(Qt::AlignCenter);

    horizontalLayout4->addWidget(lab_Ico);

    lab_Title = new QLabel(widget_title);
    lab_Title->setObjectName(QString::fromUtf8("lab_Title"));
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(lab_Title->sizePolicy().hasHeightForWidth());
    lab_Title->setSizePolicy(sizePolicy2);
    lab_Title->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);

    horizontalLayout4->addWidget(lab_Title);

    widget_menu = new QWidget(widget_title);
    widget_menu->setObjectName(QString::fromUtf8("widget_menu"));
    sizePolicy1.setHeightForWidth(widget_menu->sizePolicy().hasHeightForWidth());
    widget_menu->setSizePolicy(sizePolicy1);
    horizontalLayout = new QHBoxLayout(widget_menu);
    horizontalLayout->setSpacing(0);
    horizontalLayout->setContentsMargins(11, 11, 11, 11);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    btnMenu = new QToolButton(widget_menu);
    btnMenu->setObjectName(QString::fromUtf8("btnMenu"));
    QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Expanding);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(btnMenu->sizePolicy().hasHeightForWidth());
    btnMenu->setSizePolicy(sizePolicy3);
    btnMenu->setMinimumSize(QSize(30, 0));
    btnMenu->setMaximumSize(QSize(30, 16777215));
    btnMenu->setFocusPolicy(Qt::NoFocus);
    btnMenu->setPopupMode(QToolButton::InstantPopup);

    horizontalLayout->addWidget(btnMenu);

    btnMenu_Min = new QPushButton(widget_menu);
    btnMenu_Min->setObjectName(QString::fromUtf8("btnMenu_Min"));
    QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Expanding);
    sizePolicy4.setHorizontalStretch(0);
    sizePolicy4.setVerticalStretch(0);
    sizePolicy4.setHeightForWidth(btnMenu_Min->sizePolicy().hasHeightForWidth());
    btnMenu_Min->setSizePolicy(sizePolicy4);
    btnMenu_Min->setMinimumSize(QSize(30, 0));
    btnMenu_Min->setMaximumSize(QSize(30, 16777215));
    btnMenu_Min->setCursor(QCursor(Qt::ArrowCursor));
    btnMenu_Min->setFocusPolicy(Qt::NoFocus);

    horizontalLayout->addWidget(btnMenu_Min);

    btnMenu_Max = new QPushButton(widget_menu);
    btnMenu_Max->setObjectName(QString::fromUtf8("btnMenu_Max"));
    sizePolicy3.setHeightForWidth(btnMenu_Max->sizePolicy().hasHeightForWidth());
    btnMenu_Max->setSizePolicy(sizePolicy3);
    btnMenu_Max->setMinimumSize(QSize(30, 0));
    btnMenu_Max->setMaximumSize(QSize(30, 16777215));
    btnMenu_Max->setCursor(QCursor(Qt::ArrowCursor));
    btnMenu_Max->setFocusPolicy(Qt::NoFocus);

    horizontalLayout->addWidget(btnMenu_Max);

    btnMenu_Close = new QPushButton(widget_menu);
    btnMenu_Close->setObjectName(QString::fromUtf8("btnMenu_Close"));
    sizePolicy3.setHeightForWidth(btnMenu_Close->sizePolicy().hasHeightForWidth());
    btnMenu_Close->setSizePolicy(sizePolicy3);
    btnMenu_Close->setMinimumSize(QSize(30, 0));
    btnMenu_Close->setMaximumSize(QSize(30, 16777215));
    btnMenu_Close->setCursor(QCursor(Qt::ArrowCursor));
    btnMenu_Close->setFocusPolicy(Qt::NoFocus);

    horizontalLayout->addWidget(btnMenu_Close);
    horizontalLayout4->addWidget(widget_menu);
    verticalLayout2->addWidget(widget_title);

    widget = new QWidget(widgetMain);
    widget->setObjectName(QString::fromUtf8("widget"));
    verticalLayout3 = new QVBoxLayout(widget);
    verticalLayout3->setSpacing(0);
    verticalLayout3->setContentsMargins(11, 11, 11, 11);
    verticalLayout3->setObjectName(QString::fromUtf8("verticalLayout3"));
    verticalLayout3->setContentsMargins(0, 0, 0, 0);

    verticalLayout2->addWidget(widget);
    verticalLayout1->addWidget(widgetMain);

    connect(this->btnMenu_Min, SIGNAL(clicked(bool)), this, SLOT(on_btnMenu_Min_clicked()));
    connect(this->btnMenu_Max, SIGNAL(clicked(bool)), this, SLOT(on_btnMenu_Max_clicked()));
    connect(this->btnMenu_Close, SIGNAL(clicked(bool)), this, SLOT(on_btnMenu_Close_clicked()));
}

void QUIWidget::initForm()
{
    //设置图形字体
    setIcon(QUIWidget::Lab_Ico, 0xf072, 11);
    setIcon(QUIWidget::BtnMenu, 0xf0d7);
    setIcon(QUIWidget::BtnMenu_Min, 0xf068);
    setIcon(QUIWidget::BtnMenu_Max, 0xf067);
    setIcon(QUIWidget::BtnMenu_Close, 0xf00d);

    //设置标题及对齐方式
    setTitle("QUI Demo");
    setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    setVisible(QUIWidget::BtnMenu, false);

    mainWidget = 0;
    max = false;
    location = this->geometry();
    this->setProperty("form", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

    //绑定事件过滤器监听鼠标移动
    this->installEventFilter(this);
    this->widget_title->installEventFilter(this);

    //添加换肤菜单
    QStringList name;
    name << "银色" << "蓝色" << "浅蓝色" << "深蓝色" << "灰色" << "浅灰色" << "深灰色" << "黑色"
         << "浅黑色" << "深黑色" << "PS黑色" << "黑色扁平" << "白色扁平";

    foreach (QString str, name) {
        QAction *action = new QAction(str, this);
        this->btnMenu->addAction(action);
        connect(action, SIGNAL(triggered(bool)), this, SLOT(changeStyle()));
    }
}

void QUIWidget::changeStyle()
{
    QAction *act = (QAction *)sender();
    QString name = act->text();
    QString qssFile = ":/qss/blue.css";

    if (name == "银色") {
        qssFile = ":/qss/silvery.css";
        setStyle(QUIWidget::Style_Silvery);
    } else if (name == "蓝色") {
        qssFile = ":/qss/blue.css";
        setStyle(QUIWidget::Style_Blue);
    } else if (name == "浅蓝色") {
        qssFile = ":/qss/lightblue.css";
        setStyle(QUIWidget::Style_LightBlue);
    } else if (name == "深蓝色") {
        qssFile = ":/qss/darkblue.css";
        setStyle(QUIWidget::Style_DarkBlue);
    } else if (name == "灰色") {
        qssFile = ":/qss/gray.css";
        setStyle(QUIWidget::Style_Gray);
    } else if (name == "浅灰色") {
        qssFile = ":/qss/lightgray.css";
        setStyle(QUIWidget::Style_LightGray);
    } else if (name == "深灰色") {
        qssFile = ":/qss/darkgray.css";
        setStyle(QUIWidget::Style_DarkGray);
    } else if (name == "黑色") {
        qssFile = ":/qss/black.css";
        setStyle(QUIWidget::Style_Black);
    } else if (name == "浅黑色") {
        qssFile = ":/qss/lightblack.css";
        setStyle(QUIWidget::Style_LightBlack);
    } else if (name == "深黑色") {
        qssFile = ":/qss/darkblack.css";
        setStyle(QUIWidget::Style_DarkBlack);
    } else if (name == "PS黑色") {
        qssFile = ":/qss/psblack.css";
        setStyle(QUIWidget::Style_PSBlack);
    } else if (name == "黑色扁平") {
        qssFile = ":/qss/flatblack.css";
        setStyle(QUIWidget::Style_FlatBlack);
    } else if (name == "白色扁平") {
        qssFile = ":/qss/flatwhite.css";
        setStyle(QUIWidget::Style_FlatWhite);
    }

    emit changeStyle(qssFile);
}

void QUIWidget::setIcon(QUIWidget::Widget widget, QChar str, quint32 size)
{
    if (widget == QUIWidget::Lab_Ico) {
        IconHelper::Instance()->setIcon(this->lab_Ico, str, size);
    } else if (widget == QUIWidget::BtnMenu) {
        IconHelper::Instance()->setIcon(this->btnMenu, str, size);
    } else if (widget == QUIWidget::BtnMenu_Min) {
        IconHelper::Instance()->setIcon(this->btnMenu_Min, str, size);
    } else if (widget == QUIWidget::BtnMenu_Max) {
        IconHelper::Instance()->setIcon(this->btnMenu_Max, str, size);
    } else if (widget == QUIWidget::BtnMenu_Close) {
        IconHelper::Instance()->setIcon(this->btnMenu_Close, str, size);
    }
}

void QUIWidget::setPixmap(QUIWidget::Widget widget, const QString &file, const QSize &size)
{
    QPixmap pix = QPixmap(file);
    //按照宽高比自动缩放
    pix = pix.scaled(size, Qt::KeepAspectRatio);

    if (widget == QUIWidget::Lab_Ico) {
        this->lab_Ico->setPixmap(pix);
    } else if (widget == QUIWidget::BtnMenu) {
        this->btnMenu->setIcon(QIcon(file));
    } else if (widget == QUIWidget::BtnMenu_Min) {
        this->btnMenu_Min->setIcon(QIcon(file));
    } else if (widget == QUIWidget::BtnMenu_Max) {
        this->btnMenu_Max->setIcon(QIcon(file));
    } else if (widget == QUIWidget::BtnMenu_Close) {
        this->btnMenu_Close->setIcon(QIcon(file));
    }
}

void QUIWidget::setVisible(QUIWidget::Widget widget, bool visible)
{
    if (widget == QUIWidget::Lab_Ico) {
        this->lab_Ico->setVisible(visible);
    } else if (widget == QUIWidget::BtnMenu) {
        this->btnMenu->setVisible(visible);
    } else if (widget == QUIWidget::BtnMenu_Min) {
        this->btnMenu_Min->setVisible(visible);
    } else if (widget == QUIWidget::BtnMenu_Max) {
        this->btnMenu_Max->setVisible(visible);
    } else if (widget == QUIWidget::BtnMenu_Close) {
        this->btnMenu_Close->setVisible(visible);
    }
}

void QUIWidget::setOnlyCloseBtn()
{
    this->btnMenu->setVisible(false);
    this->btnMenu_Min->setVisible(false);
    this->btnMenu_Max->setVisible(false);
}

void QUIWidget::setTitleHeight(int height)
{
    this->widget_title->setFixedHeight(height);
}

void QUIWidget::setBtnWidth(int width)
{
    this->lab_Ico->setFixedWidth(width);
    this->btnMenu->setFixedWidth(width);
    this->btnMenu_Min->setFixedWidth(width);
    this->btnMenu_Max->setFixedWidth(width);
    this->btnMenu_Close->setFixedWidth(width);
}

void QUIWidget::setTitle(const QString &title)
{
    if (this->title != title) {
        this->title = title;
        this->lab_Title->setText(title);
        this->setWindowTitle(this->lab_Title->text());
    }
}

void QUIWidget::setAlignment(Qt::Alignment alignment)
{
    if (this->alignment != alignment) {
        this->alignment = alignment;
        this->lab_Title->setAlignment(alignment);
    }
}

void QUIWidget::setMainWidget(QWidget *mainWidget)
{
    //一个QUI窗体对象只能设置一个主窗体
    if (this->mainWidget == 0) {
        //将子窗体添加到布局
        this->widget->layout()->addWidget(mainWidget);
        //自动设置大小
        resize(mainWidget->width(), mainWidget->height() + this->widget_title->height());

        this->mainWidget = mainWidget;
        this->mainWidget->installEventFilter(this);
    }
}

void QUIWidget::on_btnMenu_Min_clicked()
{
    showMinimized();
}

void QUIWidget::on_btnMenu_Max_clicked()
{
    if (max) {
        this->setGeometry(location);
    } else {
        location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
    }

    max = !max;
}

void QUIWidget::on_btnMenu_Close_clicked()
{
    close();
}



QUIMessageBox *QUIMessageBox::self = 0;
QUIMessageBox::QUIMessageBox(QWidget *parent) : QDialog(parent)
{
    this->initControl();
    this->initForm();
}

QUIMessageBox::~QUIMessageBox()
{
    delete widgetMain;
}

void QUIMessageBox::initControl()
{
    this->setObjectName(QString::fromUtf8("QUIMessageBox"));
    this->resize(280, 150);
    verticalLayout1 = new QVBoxLayout(this);
    verticalLayout1->setSpacing(0);
    verticalLayout1->setObjectName(QString::fromUtf8("verticalLayout1"));
    verticalLayout1->setContentsMargins(1, 1, 1, 1);
    widget_title = new QWidget(this);
    widget_title->setObjectName(QString::fromUtf8("widget_title"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(widget_title->sizePolicy().hasHeightForWidth());
    widget_title->setSizePolicy(sizePolicy);
    widget_title->setMinimumSize(QSize(0, 30));
    horizontalLayout3 = new QHBoxLayout(widget_title);
    horizontalLayout3->setSpacing(0);
    horizontalLayout3->setObjectName(QString::fromUtf8("horizontalLayout3"));
    horizontalLayout3->setContentsMargins(0, 0, 0, 0);
    lab_Ico = new QLabel(widget_title);
    lab_Ico->setObjectName(QString::fromUtf8("lab_Ico"));
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(lab_Ico->sizePolicy().hasHeightForWidth());
    lab_Ico->setSizePolicy(sizePolicy1);
    lab_Ico->setMinimumSize(QSize(31, 0));
    lab_Ico->setAlignment(Qt::AlignCenter);

    horizontalLayout3->addWidget(lab_Ico);

    lab_Title = new QLabel(widget_title);
    lab_Title->setObjectName(QString::fromUtf8("lab_Title"));
    lab_Title->setStyleSheet(QString::fromUtf8(""));
    lab_Title->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);

    horizontalLayout3->addWidget(lab_Title);

    labTime = new QLabel(widget_title);
    labTime->setObjectName(QString::fromUtf8("labTime"));
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(labTime->sizePolicy().hasHeightForWidth());
    labTime->setSizePolicy(sizePolicy2);
    labTime->setAlignment(Qt::AlignCenter);

    horizontalLayout3->addWidget(labTime);

    widget_menu = new QWidget(widget_title);
    widget_menu->setObjectName(QString::fromUtf8("widget_menu"));
    sizePolicy1.setHeightForWidth(widget_menu->sizePolicy().hasHeightForWidth());
    widget_menu->setSizePolicy(sizePolicy1);
    horizontalLayout4 = new QHBoxLayout(widget_menu);
    horizontalLayout4->setSpacing(0);
    horizontalLayout4->setObjectName(QString::fromUtf8("horizontalLayout4"));
    horizontalLayout4->setContentsMargins(0, 0, 0, 0);
    btnMenu_Close = new QPushButton(widget_menu);
    btnMenu_Close->setObjectName(QString::fromUtf8("btnMenu_Close"));
    QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(btnMenu_Close->sizePolicy().hasHeightForWidth());
    btnMenu_Close->setSizePolicy(sizePolicy3);
    btnMenu_Close->setMinimumSize(QSize(30, 0));
    btnMenu_Close->setMaximumSize(QSize(30, 16777215));
    btnMenu_Close->setCursor(QCursor(Qt::ArrowCursor));
    btnMenu_Close->setFocusPolicy(Qt::NoFocus);
    btnMenu_Close->setFlat(true);

    horizontalLayout4->addWidget(btnMenu_Close);
    horizontalLayout3->addWidget(widget_menu);
    verticalLayout1->addWidget(widget_title);

    widgetMain = new QWidget(this);
    widgetMain->setObjectName(QString::fromUtf8("widgetMain"));
    widgetMain->setStyleSheet(QString::fromUtf8(""));
    verticalLayout2 = new QVBoxLayout(widgetMain);
    verticalLayout2->setSpacing(5);
    verticalLayout2->setObjectName(QString::fromUtf8("verticalLayout2"));
    verticalLayout2->setContentsMargins(5, 5, 5, 5);
    frame = new QFrame(widgetMain);
    frame->setObjectName(QString::fromUtf8("frame"));
    frame->setFrameShape(QFrame::Box);
    frame->setFrameShadow(QFrame::Sunken);
    verticalLayout4 = new QVBoxLayout(frame);
    verticalLayout4->setObjectName(QString::fromUtf8("verticalLayout4"));
    verticalLayout4->setContentsMargins(-1, 9, -1, -1);
    horizontalLayout1 = new QHBoxLayout();
    horizontalLayout1->setObjectName(QString::fromUtf8("horizontalLayout1"));
    labIcoMain = new QLabel(frame);
    labIcoMain->setObjectName(QString::fromUtf8("labIcoMain"));
    labIcoMain->setMinimumSize(QSize(30, 30));
    labIcoMain->setMaximumSize(QSize(30, 30));
    labIcoMain->setStyleSheet(QString::fromUtf8("border-image: url(:/image/msg_info.png);"));

    horizontalLayout1->addWidget(labIcoMain);

    horizontalSpacer1 = new QSpacerItem(5, 0, QSizePolicy::Minimum, QSizePolicy::Minimum);

    horizontalLayout1->addItem(horizontalSpacer1);

    labInfo = new QLabel(frame);
    labInfo->setObjectName(QString::fromUtf8("labInfo"));
    QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy4.setHorizontalStretch(0);
    sizePolicy4.setVerticalStretch(0);
    sizePolicy4.setHeightForWidth(labInfo->sizePolicy().hasHeightForWidth());
    labInfo->setSizePolicy(sizePolicy4);
    labInfo->setMinimumSize(QSize(0, 33));
    labInfo->setScaledContents(false);
    labInfo->setWordWrap(true);

    horizontalLayout1->addWidget(labInfo);


    verticalLayout4->addLayout(horizontalLayout1);

    horizontalLayout2 = new QHBoxLayout();
    horizontalLayout2->setObjectName(QString::fromUtf8("horizontalLayout2"));
    horizontalSpacer2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout2->addItem(horizontalSpacer2);

    btnOk = new QPushButton(frame);
    btnOk->setObjectName(QString::fromUtf8("btnOk"));
    btnOk->setMinimumSize(QSize(80, 0));
    btnOk->setFocusPolicy(Qt::StrongFocus);
    btnOk->setStyleSheet(QString::fromUtf8(""));
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/image/btn_ok.png"), QSize(), QIcon::Normal, QIcon::Off);
    btnOk->setIcon(icon);

    horizontalLayout2->addWidget(btnOk);

    btnCancel = new QPushButton(frame);
    btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
    btnCancel->setMinimumSize(QSize(80, 0));
    btnCancel->setFocusPolicy(Qt::StrongFocus);
    btnCancel->setStyleSheet(QString::fromUtf8(""));
    QIcon icon1;
    icon1.addFile(QString::fromUtf8(":/image/btn_close.png"), QSize(), QIcon::Normal, QIcon::Off);
    btnCancel->setIcon(icon1);

    horizontalLayout2->addWidget(btnCancel);
    verticalLayout4->addLayout(horizontalLayout2);
    verticalLayout2->addWidget(frame);
    verticalLayout1->addWidget(widgetMain);

    widget_title->raise();
    widgetMain->raise();
    frame->raise();

    this->btnOk->setText("确定");
    this->btnCancel->setText("取消");

    connect(this->btnOk, SIGNAL(clicked()), this, SLOT(on_btnOk_clicked()));
    connect(this->btnMenu_Close, SIGNAL(clicked(bool)), this, SLOT(on_btnMenu_Close_clicked()));
    connect(this->btnCancel, SIGNAL(clicked()), this, SLOT(on_btnMenu_Close_clicked()));
}

void QUIMessageBox::initForm()
{
    IconHelper::Instance()->setIcon(this->lab_Ico, QChar(0xf072), 11);
    IconHelper::Instance()->setIcon(this->btnMenu_Close, QChar(0xf00d), 9);

    this->setProperty("form", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint | Qt::WindowStaysOnTopHint);
    this->setFixedSize(280, 150);
    this->setWindowTitle(this->lab_Title->text());

    int width = 80;
    int iconWidth = 18;
    int iconHeight = 18;
    this->labIcoMain->setFixedSize(30, 30);

    QList<QPushButton *> btns1 = this->frame->findChildren<QPushButton *>();

    foreach (QPushButton *btn, btns1) {
        btn->setMinimumWidth(width);
        btn->setIconSize(QSize(iconWidth, iconHeight));
    }

    closeSec = 0;
    currentSec = 0;

    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkSec()));
    timer->start();

    this->installEventFilter(this);
}

void QUIMessageBox::checkSec()
{
    if (closeSec == 0) {
        return;
    }

    if (currentSec < closeSec) {
        currentSec++;
    } else {
        this->close();
    }

    QString str = QString("关闭倒计时 %1 s").arg(closeSec - currentSec + 1);
    this->labTime->setText(str);
}

void QUIMessageBox::setMessage(const QString &msg, int type, int closeSec)
{
    this->closeSec = closeSec;
    this->currentSec = 0;
    this->labTime->clear();

    checkSec();

    if (type == 0) {
        this->labIcoMain->setStyleSheet("border-image: url(:/image/msg_info.png);");
        this->btnCancel->setVisible(false);
        this->lab_Title->setText("提示");
    } else if (type == 1) {
        this->labIcoMain->setStyleSheet("border-image: url(:/image/msg_question.png);");
        this->lab_Title->setText("询问");
    } else if (type == 2) {
        this->labIcoMain->setStyleSheet("border-image: url(:/image/msg_error.png);");
        this->btnCancel->setVisible(false);
        this->lab_Title->setText("错误");
    }

    this->labInfo->setText(msg);
    this->setWindowTitle(this->lab_Title->text());
}

void QUIMessageBox::closeEvent(QCloseEvent *)
{
    closeSec = 0;
    currentSec = 0;
}

bool QUIMessageBox::eventFilter(QObject *obj, QEvent *evt)
{
    static QPoint mousePoint;
    static bool mousePressed = false;

    QMouseEvent *event = static_cast<QMouseEvent *>(evt);
    if (event->type() == QEvent::MouseButtonPress) {
        if (event->button() == Qt::LeftButton) {
            mousePressed = true;
            mousePoint = event->globalPos() - this->pos();
            return true;
        }
    } else if (event->type() == QEvent::MouseButtonRelease) {
        mousePressed = false;
        return true;
    } else if (event->type() == QEvent::MouseMove) {
        if (mousePressed && (event->buttons() && Qt::LeftButton)) {
            this->move(event->globalPos() - mousePoint);
            return true;
        }
    }

    return QWidget::eventFilter(obj, evt);
}

void QUIMessageBox::on_btnOk_clicked()
{
    done(1);
    close();
}

void QUIMessageBox::on_btnMenu_Close_clicked()
{
    close();
}



QUIInputBox *QUIInputBox::self = 0;
QUIInputBox::QUIInputBox(QWidget *parent) : QDialog(parent)
{
    this->initControl();
    this->initForm();
}

QUIInputBox::~QUIInputBox()
{
    delete widgetMain;
}

void QUIInputBox::initControl()
{
    this->setObjectName(QString::fromUtf8("QUIInputBox"));
    this->resize(260, 166);
    verticalLayout1 = new QVBoxLayout(this);
    verticalLayout1->setSpacing(0);
    verticalLayout1->setObjectName(QString::fromUtf8("verticalLayout1"));
    verticalLayout1->setContentsMargins(1, 1, 1, 1);
    widget_title = new QWidget(this);
    widget_title->setObjectName(QString::fromUtf8("widget_title"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(widget_title->sizePolicy().hasHeightForWidth());
    widget_title->setSizePolicy(sizePolicy);
    widget_title->setMinimumSize(QSize(0, 30));
    horizontalLayout1 = new QHBoxLayout(widget_title);
    horizontalLayout1->setSpacing(0);
    horizontalLayout1->setObjectName(QString::fromUtf8("horizontalLayout1"));
    horizontalLayout1->setContentsMargins(0, 0, 0, 0);
    lab_Ico = new QLabel(widget_title);
    lab_Ico->setObjectName(QString::fromUtf8("lab_Ico"));
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(lab_Ico->sizePolicy().hasHeightForWidth());
    lab_Ico->setSizePolicy(sizePolicy1);
    lab_Ico->setMinimumSize(QSize(31, 0));
    lab_Ico->setAlignment(Qt::AlignCenter);

    horizontalLayout1->addWidget(lab_Ico);

    lab_Title = new QLabel(widget_title);
    lab_Title->setObjectName(QString::fromUtf8("lab_Title"));
    lab_Title->setStyleSheet(QString::fromUtf8(""));
    lab_Title->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);

    horizontalLayout1->addWidget(lab_Title);

    labTime = new QLabel(widget_title);
    labTime->setObjectName(QString::fromUtf8("labTime"));
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(labTime->sizePolicy().hasHeightForWidth());
    labTime->setSizePolicy(sizePolicy2);
    labTime->setAlignment(Qt::AlignCenter);

    horizontalLayout1->addWidget(labTime);

    widget_menu = new QWidget(widget_title);
    widget_menu->setObjectName(QString::fromUtf8("widget_menu"));
    sizePolicy1.setHeightForWidth(widget_menu->sizePolicy().hasHeightForWidth());
    widget_menu->setSizePolicy(sizePolicy1);
    horizontalLayout2 = new QHBoxLayout(widget_menu);
    horizontalLayout2->setSpacing(0);
    horizontalLayout2->setObjectName(QString::fromUtf8("horizontalLayout2"));
    horizontalLayout2->setContentsMargins(0, 0, 0, 0);
    btnMenu_Close = new QPushButton(widget_menu);
    btnMenu_Close->setObjectName(QString::fromUtf8("btnMenu_Close"));
    QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(btnMenu_Close->sizePolicy().hasHeightForWidth());
    btnMenu_Close->setSizePolicy(sizePolicy3);
    btnMenu_Close->setMinimumSize(QSize(30, 0));
    btnMenu_Close->setMaximumSize(QSize(30, 16777215));
    btnMenu_Close->setCursor(QCursor(Qt::ArrowCursor));
    btnMenu_Close->setFocusPolicy(Qt::NoFocus);
    btnMenu_Close->setFlat(true);

    horizontalLayout2->addWidget(btnMenu_Close);
    horizontalLayout1->addWidget(widget_menu);
    verticalLayout1->addWidget(widget_title);

    widgetMain = new QWidget(this);
    widgetMain->setObjectName(QString::fromUtf8("widgetMain"));
    widgetMain->setStyleSheet(QString::fromUtf8(""));
    verticalLayout2 = new QVBoxLayout(widgetMain);
    verticalLayout2->setSpacing(5);
    verticalLayout2->setObjectName(QString::fromUtf8("verticalLayout2"));
    verticalLayout2->setContentsMargins(5, 5, 5, 5);
    frame = new QFrame(widgetMain);
    frame->setObjectName(QString::fromUtf8("frame"));
    frame->setFrameShape(QFrame::Box);
    frame->setFrameShadow(QFrame::Sunken);
    verticalLayout3 = new QVBoxLayout(frame);
    verticalLayout3->setObjectName(QString::fromUtf8("verticalLayout3"));
    labInfo = new QLabel(frame);
    labInfo->setObjectName(QString::fromUtf8("labInfo"));
    labInfo->setScaledContents(false);
    labInfo->setWordWrap(true);

    verticalLayout3->addWidget(labInfo);

    txtValue = new QLineEdit(frame);
    txtValue->setObjectName(QString::fromUtf8("txtValue"));

    verticalLayout3->addWidget(txtValue);

    cboxValue = new QComboBox(frame);
    cboxValue->setObjectName(QString::fromUtf8("cboxValue"));

    verticalLayout3->addWidget(cboxValue);

    lay = new QHBoxLayout();
    lay->setObjectName(QString::fromUtf8("lay"));
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    lay->addItem(horizontalSpacer);

    btnOk = new QPushButton(frame);
    btnOk->setObjectName(QString::fromUtf8("btnOk"));
    btnOk->setMinimumSize(QSize(80, 0));
    btnOk->setStyleSheet(QString::fromUtf8(""));
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/image/btn_ok.png"), QSize(), QIcon::Normal, QIcon::Off);
    btnOk->setIcon(icon);

    lay->addWidget(btnOk);

    btnCancel = new QPushButton(frame);
    btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
    btnCancel->setMinimumSize(QSize(80, 0));
    btnCancel->setStyleSheet(QString::fromUtf8(""));
    QIcon icon1;
    icon1.addFile(QString::fromUtf8(":/image/btn_close.png"), QSize(), QIcon::Normal, QIcon::Off);
    btnCancel->setIcon(icon1);

    lay->addWidget(btnCancel);
    verticalLayout3->addLayout(lay);
    verticalLayout2->addWidget(frame);
    verticalLayout1->addWidget(widgetMain);

    setTabOrder(txtValue, btnOk);
    setTabOrder(btnOk, btnCancel);

    this->lab_Title->setText("输入框");
    this->btnOk->setText("确定");
    this->btnCancel->setText("取消");

    connect(this->btnOk, SIGNAL(clicked()), this, SLOT(on_btnOk_clicked()));
    connect(this->btnMenu_Close, SIGNAL(clicked(bool)), this, SLOT(on_btnMenu_Close_clicked()));
    connect(this->btnCancel, SIGNAL(clicked()), this, SLOT(on_btnMenu_Close_clicked()));
}

void QUIInputBox::initForm()
{
    //设置图形字体作为图标
    IconHelper::Instance()->setIcon(this->lab_Ico, QChar(0xf072), 11);
    IconHelper::Instance()->setIcon(this->btnMenu_Close, QChar(0xf00d), 9);

    this->setProperty("form", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint | Qt::WindowStaysOnTopHint);
    this->setFixedSize(280, 150);
    this->setWindowTitle(this->lab_Title->text());

    int width = 80;
    int iconWidth = 18;
    int iconHeight = 18;

    QList<QPushButton *> btns  = this->frame->findChildren<QPushButton *>();

    foreach (QPushButton *btn, btns) {
        btn->setMinimumWidth(width);
        btn->setIconSize(QSize(iconWidth, iconHeight));
    }

    closeSec = 0;
    currentSec = 0;

    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkSec()));
    timer->start();

    this->installEventFilter(this);
}

void QUIInputBox::checkSec()
{
    if (closeSec == 0) {
        return;
    }

    if (currentSec < closeSec) {
        currentSec++;
    } else {
        this->close();
    }

    QString str = QString("关闭倒计时 %1 s").arg(closeSec - currentSec + 1);
    this->labTime->setText(str);
}

void QUIInputBox::setParameter(const QString &title, int type, int closeSec,
                               QString defaultValue, bool pwd)
{
    this->closeSec = closeSec;
    this->currentSec = 0;
    this->labTime->clear();
    this->labInfo->setText(title);

    checkSec();

    if (type == 0) {
        this->cboxValue->setVisible(false);
        this->txtValue->setPlaceholderText(defaultValue);

        if (pwd) {
            this->txtValue->setEchoMode(QLineEdit::Password);
        }
    } else if (type == 1) {
        this->txtValue->setVisible(false);
        this->cboxValue->addItems(defaultValue.split("|"));
    }
}

QString QUIInputBox::getValue() const
{
    return this->value;
}

void QUIInputBox::closeEvent(QCloseEvent *)
{
    closeSec = 0;
    currentSec = 0;
}

bool QUIInputBox::eventFilter(QObject *obj, QEvent *evt)
{
    static QPoint mousePoint;
    static bool mousePressed = false;

    QMouseEvent *event = static_cast<QMouseEvent *>(evt);
    if (event->type() == QEvent::MouseButtonPress) {
        if (event->button() == Qt::LeftButton) {
            mousePressed = true;
            mousePoint = event->globalPos() - this->pos();
            return true;
        }
    } else if (event->type() == QEvent::MouseButtonRelease) {
        mousePressed = false;
        return true;
    } else if (event->type() == QEvent::MouseMove) {
        if (mousePressed && (event->buttons() && Qt::LeftButton)) {
            this->move(event->globalPos() - mousePoint);
            return true;
        }
    }

    return QWidget::eventFilter(obj, evt);
}

void QUIInputBox::on_btnOk_clicked()
{
    if (this->txtValue->isVisible()) {
        value = this->txtValue->text();
    } else if (this->cboxValue->isVisible()) {
        value = this->cboxValue->currentText();
    }

    done(1);
    close();
}

void QUIInputBox::on_btnMenu_Close_clicked()
{
    close();
}


IconHelper *IconHelper::self = 0;
IconHelper::IconHelper(QObject *) : QObject(qApp)
{
    int fontId = QFontDatabase::addApplicationFont(":/image/fontawesome-webfont.ttf");
    QStringList fontName = QFontDatabase::applicationFontFamilies(fontId);

    if (fontName.count() > 0) {
        iconFont = QFont(fontName.at(0));
    } else {
        qDebug() << "load fontawesome-webfont.ttf error";
    }

}

void IconHelper::setIcon(QLabel *lab, QChar c, quint32 size)
{
    iconFont.setPointSize(size);
    lab->setFont(iconFont);
    lab->setText(c);
}

void IconHelper::setIcon(QAbstractButton *btn, QChar c, quint32 size)
{
    iconFont.setPointSize(size);
    btn->setFont(iconFont);
    btn->setText(c);
}
