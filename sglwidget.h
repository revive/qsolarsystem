#ifndef SGLWIDGET_H
#define SGLWIDGET_H

#include <QGLWidget>
#include <QGLBuffer>
#include <QGLShaderProgram>

class SGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit SGLWidget(const QGLFormat &format, QWidget *parent = 0);
    explicit SGLWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
private:
    bool prepareShaderProgram( const QString& vertexShaderPath,
                               const QString& fragmentShaderPath );
    QGLShaderProgram m_shader;
    QGLBuffer m_vertexBuffer;
    QGLBuffer m_uvBuffer;
    GLuint m_texture;
};

#endif // SGLWIDGET_H
