#pragma execution_character_set("utf-8")

#include "form/quiwidget.h"
#include "form/quicreator.h"
#include "demo/appinit.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setFont(QFont("Microsoft Yahei", 9));
    a.setWindowIcon(QIcon(":/main.ico"));
#if (QT_VERSION >= QT_VERSION_CHECK(5,6,0))
    a.setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    AppInit::Instance()->start();
    QUIWidget::setTranslator(":/image/qt_zh_CN.qm");
    QUIWidget::setCode();

    QUICreator *creator = new QUICreator;
    QUIWidget qui;
    QObject::connect(&qui, SIGNAL(changeStyle(QString)), creator, SLOT(changeStyle(QString)));

    //设置主窗体
    qui.setMainWidget(creator);

    //设置标题
#ifdef demo
    qui.setTitle("QUI皮肤生成器 演示版 (作者: 飞扬青云  QQ: 517216493)");
#else
    qui.setTitle("QUI皮肤生成器 (作者: 飞扬青云  QQ: 517216493)");
#endif

    //设置标题文本居中
    qui.setAlignment(Qt::AlignCenter);

    //设置窗体可拖动大小
    qui.setSizeGripEnabled(true);

    //设置换肤下拉菜单可见
    qui.setVisible(QUIWidget::BtnMenu, true);

    //设置标题栏高度
    //qui.setTitleHeight(50);

    //设置按钮宽度
    //qui.setBtnWidth(50);

    //设置左上角图标-图形字体
    //qui.setIcon(QUIWidget::Lab_Ico, QChar(0xf099));

    //设置左上角图标-图片文件
    //qui.setPixmap(QUIWidget::Lab_Ico, ":/main.ico");

    qui.show();

    return a.exec();
}
