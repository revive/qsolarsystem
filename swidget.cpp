#include "swidget.h"
#include "ui_swidget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QGLFormat glFormat;
//    glFormat.setVersion( 3, 3 );
//    glFormat.setProfile( QGLFormat::CoreProfile ); // Requires >=Qt-4.8.0
    glFormat.setSampleBuffers( true );
    sgl = new SGLWidget(glFormat);
//    sgl = new SGLWidget();
    ui->vLayout->addWidget(sgl);
}

Widget::~Widget()
{
    delete ui;
}
