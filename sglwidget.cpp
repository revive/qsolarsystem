#include "sglwidget.h"
#include <GL/glext.h>

SGLWidget::SGLWidget(const QGLFormat &format, QWidget *parent) :
    QGLWidget(format, parent),
    m_vertexBuffer(QGLBuffer::VertexBuffer),
    m_uvBuffer(QGLBuffer::VertexBuffer),
    s3d_0(0),
    m_angle(0)
{

}

SGLWidget::SGLWidget(QWidget *parent) :
    QGLWidget(parent),
    m_vertexBuffer(QGLBuffer::VertexBuffer),
    m_uvBuffer(QGLBuffer::VertexBuffer),
    s3d_0(0),
    m_angle(0)
{

}

void SGLWidget::update()
{
    m_angle+=1;
    if(m_angle >=360)
        m_angle -= 360;
    s3d_0->rotate(m_angle);
    updateGL();
}

void SGLWidget::initializeGL()
{
    QGLFormat glFormat = QGLWidget::format();
    if ( !glFormat.sampleBuffers() )
        qWarning() << "Could not enable sample buffers";

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Set the clear color to black
    glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );

    // Prepare a complete shader program...
    if ( !prepareShaderProgram( ":/simple.vert", ":/simple.frag" ) )
        return;

    m_texture = bindTexture(QPixmap(":pic/t1.png"));

    // a cube
    float points[] = {
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };

    // uv data come from the opengl tutorial.
    float uv_values[] = {
        0.000059f, 1.0f-0.000004f,
        0.000103f, 1.0f-0.336048f,
        0.335973f, 1.0f-0.335903f,
        1.000023f, 1.0f-0.000013f,
        0.667979f, 1.0f-0.335851f,
        0.999958f, 1.0f-0.336064f,
        0.667979f, 1.0f-0.335851f,
        0.336024f, 1.0f-0.671877f,
        0.667969f, 1.0f-0.671889f,
        1.000023f, 1.0f-0.000013f,
        0.668104f, 1.0f-0.000013f,
        0.667979f, 1.0f-0.335851f,
        0.000059f, 1.0f-0.000004f,
        0.335973f, 1.0f-0.335903f,
        0.336098f, 1.0f-0.000071f,
        0.667979f, 1.0f-0.335851f,
        0.335973f, 1.0f-0.335903f,
        0.336024f, 1.0f-0.671877f,
        1.000004f, 1.0f-0.671847f,
        0.999958f, 1.0f-0.336064f,
        0.667979f, 1.0f-0.335851f,
        0.668104f, 1.0f-0.000013f,
        0.335973f, 1.0f-0.335903f,
        0.667979f, 1.0f-0.335851f,
        0.335973f, 1.0f-0.335903f,
        0.668104f, 1.0f-0.000013f,
        0.336098f, 1.0f-0.000071f,
        0.000103f, 1.0f-0.336048f,
        0.000004f, 1.0f-0.671870f,
        0.336024f, 1.0f-0.671877f,
        0.000103f, 1.0f-0.336048f,
        0.336024f, 1.0f-0.671877f,
        0.335973f, 1.0f-0.335903f,
        0.667969f, 1.0f-0.671889f,
        1.000004f, 1.0f-0.671847f,
        0.667979f, 1.0f-0.335851f
    };

    m_vertexBuffer.create();
    m_vertexBuffer.setUsagePattern( QGLBuffer::StaticDraw );
    if ( !m_vertexBuffer.bind() )
    {
        qWarning() << "Could not bind vertex buffer to the context";
        return;
    }
    m_vertexBuffer.allocate( points, 36 * 3 * sizeof( float ) );

    m_uvBuffer.create();
    m_uvBuffer.setUsagePattern(QGLBuffer::StaticDraw);
    if (!m_uvBuffer.bind())
    {
        qWarning() << "Could not bind color buffer to the context";
        return;
    }
    m_uvBuffer.allocate(uv_values, 36 * 2 * sizeof(float));
    // Bind the shader program so that we can associate variables from
    // our application to the shaders
    if ( !m_shader.bind() )
    {
        qWarning() << "Could not bind shader program to context";
        return;
    }

    QMatrix4x4 projectionMatrix, viewMatrix, modelMatrix;
    projectionMatrix.perspective(45, 4.0/3.0, 0.1f, 10.0f);
    viewMatrix.lookAt(QVector3D(0, 0, 5), QVector3D(0, 0, 0), QVector3D(0,1,0));
    modelMatrix.scale(1.0);
    // Enable the "vertex" attribute to bind it to our currently bound
    // vertex buffer.
    m_vertexBuffer.bind();
    m_shader.setAttributeBuffer( "vertex", GL_FLOAT, 0, 3 );
    m_shader.enableAttributeArray( "vertex" );
    m_shader.setUniformValue("projectionMatrix", projectionMatrix);
    m_shader.setUniformValue("viewMatrix", viewMatrix);
    m_shader.setUniformValue("modelMatrix", modelMatrix);
    m_uvBuffer.bind();
    m_shader.setAttributeBuffer("vertexUV", GL_FLOAT, 0, 2);
    m_shader.enableAttributeArray("vertexUV" );
    glBindTexture(GL_TEXTURE_2D, m_texture);
    m_shader.setUniformValue("myTextureSample", 0);

    s3d_0 = new SSphere3D();
    if (s3d_0->loadObj() ) {
//       s3d_0->dumpPoints();
       s3d_0->createBuffer();
       s3d_0->loadShader();
       s3d_0->setProjectionAndViewMatrix(projectionMatrix, viewMatrix);
//       s3d_0->setTexture(this);
       s3d_0->loadTexture();
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start(40);
}

void SGLWidget::resizeGL(int w, int h)
{
    glViewport( 0, 0, w, qMax( h, 1 ) );
}

void SGLWidget::paintGL()
{
    // Clear the buffer with the current clearing color
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Draw stuff
    s3d_0->draw();
//    m_shader.bind();
//    glDrawArrays( GL_TRIANGLES, 0, 12*3 );
}

bool SGLWidget::prepareShaderProgram( const QString& vertexShaderPath,
                                      const QString& fragmentShaderPath )
{
    // First we load and compile the vertex shader...
    bool result = m_shader.addShaderFromSourceFile( QGLShader::Vertex, vertexShaderPath );
    if ( !result )
        qWarning() << m_shader.log();

    // ...now the fragment shader...
    result = m_shader.addShaderFromSourceFile( QGLShader::Fragment, fragmentShaderPath );
    if ( !result )
        qWarning() << m_shader.log();

    // ...and finally we link them to resolve any references.
    result = m_shader.link();
    if ( !result )
        qWarning() << "Could not link shader program:" << m_shader.log();

    return result;
}
