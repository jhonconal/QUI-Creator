#ifndef UIDEMO4_H
#define UIDEMO4_H

#include <QDialog>

namespace Ui {
class UIDemo4;
}

class UIDemo4 : public QDialog
{
    Q_OBJECT

public:
    explicit UIDemo4(QWidget *parent = 0);
    ~UIDemo4();

private:
    Ui::UIDemo4 *ui;
};

#endif // UIDEMO4_H
