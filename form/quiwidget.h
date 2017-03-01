#ifndef QUIWIDGET_H
#define QUIWIDGET_H

/**
 * QUI无边框窗体控件 作者:feiyangqingyun(QQ:517216493)
 * 1:内置 N > 9 套精美样式,可直接切换,也可自定义样式路径
 * 2:可设置部件(左上角图标/最小化按钮/最大化按钮/关闭按钮)的图标或者图片及是否可见
 * 3:可集成设计师插件,直接拖曳使用,所见即所得
 * 4:如果需要窗体可拖动大小,设置 setSizeGripEnabled(true);
 * 5:可设置全局样式 setStyle
 * 6:可弹出消息框 showMessageBoxInfo
 * 7:可弹出错误框 showMessageBoxError
 * 8:可弹出询问框 showMessageBoxError
 * 9:可弹出输入框 showInputBox
 * 10:集成图形字体设置方法
 */

#include <QDialog>
#include <QMutex>

class QLabel;
class QPushButton;
class QToolButton;
class QVBoxLayout;
class QHBoxLayout;
class QFrame;
class QSpacerItem;
class QLineEdit;
class QComboBox;
class QAbstractButton;

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT QUIWidget : public QDialog
        #else
class QUIWidget : public QDialog
        #endif

{
    Q_OBJECT
    Q_ENUMS(Style)
    Q_PROPERTY(QString title READ getTitle WRITE setTitle)
    Q_PROPERTY(Qt::Alignment alignment READ getAlignment WRITE setAlignment)

public:
    //将部分对象作为枚举值暴露给外部
    enum Widget {
        Lab_Ico = 0,                //左上角图标
        BtnMenu = 1,                //下拉菜单按钮
        BtnMenu_Min = 2,            //最小化按钮
        BtnMenu_Max = 3,            //最大化按钮
        BtnMenu_Close = 4           //关闭按钮
    };

    //样式枚举
    enum Style {
        Style_Silvery = 0,          //银色样式
        Style_Blue = 1,             //蓝色样式
        Style_LightBlue = 2,        //淡蓝色样式
        Style_DarkBlue = 3,         //深蓝色样式
        Style_Gray = 4,             //灰色样式
        Style_LightGray = 5,        //浅灰色样式
        Style_DarkGray = 6,         //深灰色样式
        Style_Black = 7,            //黑色样式
        Style_LightBlack = 8,       //浅黑色样式
        Style_DarkBlack = 9,        //深黑色样式
        Style_PSBlack = 10,         //PS黑色样式
        Style_FlatBlack = 11,       //黑色扁平样式
        Style_FlatWhite = 12        //白色扁平样式
    };

    explicit QUIWidget(QWidget *parent = 0);
    ~QUIWidget();

public:
    //设置全局样式
    static void setStyle(QUIWidget::Style style);
    static void setStyle(const QString &qssFile);

    //设置窗体居中显示
    static void setFormInCenter(QWidget *frm);

    //根据QSS样式获取对应颜色值
    static void getQssColor(const QString &qss,
                            QString &textColor,
                            QString &panelColor,
                            QString &borderColor,
                            QString &normalColorStart,
                            QString &normalColorEnd,
                            QString &darkColorStart,
                            QString &darkColorEnd,
                            QString &highColor);

    //设置翻译文件
    static void setTranslator(const QString &qmFile);
    //设置编码
    static void setCode();

    //弹出消息框
    static void showMessageBoxInfo(const QString &info, int closeSec = 0);
    //弹出错误框
    static void showMessageBoxError(const QString &info, int closeSec = 0);
    //弹出询问框
    static int showMessageBoxQuestion(const QString &info);

    //弹出输入框
    static QString showInputBox(bool &ok, const QString &title, int type = 0, int closeSec = 0,
                                QString defaultValue = QString(), bool pwd = false);

protected:
    bool eventFilter(QObject *obj, QEvent *evt);

private:
    QVBoxLayout *verticalLayout1;
    QWidget *widgetMain;
    QVBoxLayout *verticalLayout2;
    QWidget *widget_title;
    QHBoxLayout *horizontalLayout4;
    QLabel *lab_Ico;
    QLabel *lab_Title;
    QWidget *widget_menu;
    QHBoxLayout *horizontalLayout;
    QToolButton *btnMenu;
    QPushButton *btnMenu_Min;
    QPushButton *btnMenu_Max;
    QPushButton *btnMenu_Close;
    QWidget *widget;
    QVBoxLayout *verticalLayout3;

private:        
    bool max;                       //是否处于最大化状态
    QRect location;                 //鼠标移动窗体后的坐标位置
    QWidget *mainWidget;            //主窗体对象

    QString title;                  //标题
    Qt::Alignment alignment;        //标题文本对齐

public:
    QLabel *getLabIco()             const;
    QLabel *getLabTitle()           const;
    QToolButton *getBtnMenu()       const;
    QPushButton *getBtnMenuMin()    const;
    QPushButton *getBtnMenuMax()    const;
    QPushButton *getBtnMenuMClose() const;

    Style getStyle()                const;
    QString getTitle()              const;
    Qt::Alignment getAlignment()    const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

private slots:
    void initControl();             //初始化控件
    void initForm();                //初始化窗体
    void changeStyle();             //更换样式

private slots:
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();

public Q_SLOTS:
    //设置部件图标
    void setIcon(QUIWidget::Widget widget, QChar str, quint32 size = 9);
    //设置部件图片
    void setPixmap(QUIWidget::Widget widget, const QString &file, const QSize &size = QSize(16, 16));
    //设置部件是否可见
    void setVisible(QUIWidget::Widget widget, bool visible = true);
    //设置只有关闭按钮
    void setOnlyCloseBtn();

    //设置标题栏高度
    void setTitleHeight(int height);
    //设置按钮统一宽度
    void setBtnWidth(int width);

    //设置标题及文本样式
    void setTitle(const QString &title);
    void setAlignment(Qt::Alignment alignment);

    //设置主窗体
    void setMainWidget(QWidget *mainWidget);

Q_SIGNALS:
    void changeStyle(const QString &qssFile);
};


class QUIMessageBox : public QDialog
{
    Q_OBJECT

public:
    explicit QUIMessageBox(QWidget *parent = 0);
    ~QUIMessageBox();

    static QUIMessageBox *Instance()
    {
        static QMutex mutex;

        if (!self) {
            QMutexLocker locker(&mutex);

            if (!self) {
                self = new QUIMessageBox;
            }
        }

        return self;
    }

protected:
    void closeEvent(QCloseEvent *);
    bool eventFilter(QObject *obj, QEvent *evt);

private:
    static QUIMessageBox *self;

    QVBoxLayout *verticalLayout1;
    QWidget *widget_title;
    QHBoxLayout *horizontalLayout3;
    QLabel *lab_Ico;
    QLabel *lab_Title;
    QLabel *labTime;
    QWidget *widget_menu;
    QHBoxLayout *horizontalLayout4;
    QPushButton *btnMenu_Close;
    QWidget *widgetMain;
    QVBoxLayout *verticalLayout2;
    QFrame *frame;
    QVBoxLayout *verticalLayout4;
    QHBoxLayout *horizontalLayout1;
    QLabel *labIcoMain;
    QSpacerItem *horizontalSpacer1;
    QLabel *labInfo;
    QHBoxLayout *horizontalLayout2;
    QSpacerItem *horizontalSpacer2;
    QPushButton *btnOk;
    QPushButton *btnCancel;

private:    
    int closeSec;                   //总显示时间
    int currentSec;                 //当前已显示时间

private slots:
    void initControl();             //初始化控件
    void initForm();                //初始化窗体
    void checkSec();                //校验倒计时

private slots:
    void on_btnOk_clicked();
    void on_btnMenu_Close_clicked();

public:
    void setMessage(const QString &msg, int type, int closeSec = 0);
};


class QUIInputBox : public QDialog
{
    Q_OBJECT

public:
    explicit QUIInputBox(QWidget *parent = 0);
    ~QUIInputBox();

    static QUIInputBox *Instance()
    {
        static QMutex mutex;

        if (!self) {
            QMutexLocker locker(&mutex);

            if (!self) {
                self = new QUIInputBox;
            }
        }

        return self;
    }

protected:
    void closeEvent(QCloseEvent *);
    bool eventFilter(QObject *obj, QEvent *evt);

private:
    static QUIInputBox *self;

    QVBoxLayout *verticalLayout1;
    QWidget *widget_title;
    QHBoxLayout *horizontalLayout1;
    QLabel *lab_Ico;
    QLabel *lab_Title;
    QLabel *labTime;
    QWidget *widget_menu;
    QHBoxLayout *horizontalLayout2;
    QPushButton *btnMenu_Close;
    QWidget *widgetMain;
    QVBoxLayout *verticalLayout2;
    QFrame *frame;
    QVBoxLayout *verticalLayout3;
    QLabel *labInfo;
    QLineEdit *txtValue;
    QComboBox *cboxValue;
    QHBoxLayout *lay;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOk;
    QPushButton *btnCancel;

private:    
    int closeSec;                   //总显示时间
    int currentSec;                 //当前已显示时间
    QString value;                  //当前值

private slots:
    void initControl();             //初始化控件
    void initForm();                //初始化窗体
    void checkSec();                //校验倒计时

private slots:
    void on_btnOk_clicked();
    void on_btnMenu_Close_clicked();

public:
    void setParameter(const QString &title, int type = 0, int closeSec = 0,
                      QString defaultValue = QString(), bool pwd = false);

    QString getValue()const;

};


class IconHelper : public QObject
{
public:
    explicit IconHelper(QObject *parent = 0);
    static IconHelper *Instance()
    {
        static QMutex mutex;

        if (!self) {
            QMutexLocker locker(&mutex);

            if (!self) {
                self = new IconHelper;
            }
        }

        return self;
    }

    void setIcon(QLabel *lab, QChar c, quint32 size = 9);
    void setIcon(QAbstractButton *btn, QChar c, quint32 size = 9);

private:
    static IconHelper *self;    //对象自身
    QFont iconFont;             //图形字体
};

#endif // QUIWIDGET_H
