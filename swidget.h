#ifndef SWIDGET_H
#define SWIDGET_H

#include <QWidget>
#include "sglwidget.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    
private:
    Ui::Widget *ui;
    SGLWidget * sgl;
};

#endif // SWIDGET_H
