#include "sglwidget.h"

SGLWidget::SGLWidget(const QGLFormat &format, QWidget *parent) :
    QGLWidget(format, parent),
    m_vertexBuffer(QGLBuffer::VertexBuffer),
    m_colorBuffer(QGLBuffer::VertexBuffer)
{
}

void SGLWidget::initializeGL()
{
    QGLFormat glFormat = QGLWidget::format();
    if ( !glFormat.sampleBuffers() )
        qWarning() << "Could not enable sample buffers";

    glEnable(GL_DEPTH_TEST);
    // Set the clear color to black
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

    // Prepare a complete shader program...
    if ( !prepareShaderProgram( ":/simple.vert", ":/simple.frag" ) )
        return;

    // a tetrahedron)
//    float points[] = { -1.0f, -1.0f, 0.0f, 1.0f,
//                        1.0f, -1.0f, 0.0f, 1.0f,
//                        0.0f,  1.0f, 0.0f, 1.0f };
    float points[] = {-1.0f, 0.0f, 0.0f, 1.0f,
                      1.0f, 0.0f, 0.0f, 1.0f,
                      0.0f, 0.0f, 1.0f, 1.0f,
                      -1.0f, 0.0f, 0.0f, 1.0f,
                      0.0f, 0.0f, 1.0f, 1.0f,
                      0.0f, 1.0f, 0.0f, 1.0f,
                      0.0f, 0.0f, 1.0f, 1.0f,
                      1.0f, 0.0f, 0.0f, 1.0f,
                      0.0f, 1.0f, 0.0f, 1.0f,
                      -1.0f, 0.0f, 0.0f, 1.0f,
                      1.0f, 0.0f, 0.0f, 1.0f,
                      0.0f, 1.0f, 0.0f, 1.0f};

    float colors[] = {
        0.583f, 0.771f, 0.014f,
        0.609f, 0.115f, 0.436f,
        0.327f, 0.483f, 0.844f,
        0.822f, 0.596f, 0.201f,
        0.435f, 0.602f, 0.223f,
        0.310f, 0.747f, 0.185f,
        0.597f, 0.770f, 0.761f,
        0.559f, 0.436f, 0.730f,
        0.359f, 0.583f, 0.152f,
        0.483f, 0.596f, 0.789f,
        0.559f, 0.861f, 0.639f,
        0.195f, 0.584f, 0.953f };

    m_vertexBuffer.create();
    m_vertexBuffer.setUsagePattern( QGLBuffer::StaticDraw );
    if ( !m_vertexBuffer.bind() )
    {
        qWarning() << "Could not bind vertex buffer to the context";
        return;
    }
    m_vertexBuffer.allocate( points, 12 * 4 * sizeof( float ) );

    m_colorBuffer.create();
    m_colorBuffer.setUsagePattern(QGLBuffer::StaticDraw);
    if (!m_colorBuffer.bind())
    {
        qWarning() << "Could not bind color buffer to the context";
        return;
    }
    m_colorBuffer.allocate(colors, 12 * 3 * sizeof(float));
    // Bind the shader program so that we can associate variables from
    // our application to the shaders
    if ( !m_shader.bind() )
    {
        qWarning() << "Could not bind shader program to context";
        return;
    }

    QMatrix4x4 projectionMatrix, viewMatrix, modelMatrix;
    projectionMatrix.perspective(45, 4.0/3.0, 0.1f, 10.0f);
    viewMatrix.lookAt(QVector3D(4, 3, 3), QVector3D(0, 0, 0), QVector3D(0,1,0));
    modelMatrix.scale(1.0);
    // Enable the "vertex" attribute to bind it to our currently bound
    // vertex buffer.
    m_vertexBuffer.bind();
    m_shader.setAttributeBuffer( "vertex", GL_FLOAT, 0, 4 );
    m_shader.enableAttributeArray( "vertex" );
    m_shader.setUniformValue("projectionMatrix", projectionMatrix);
    m_shader.setUniformValue("viewMatrix", viewMatrix);
    m_shader.setUniformValue("modelMatrix", modelMatrix);
    m_colorBuffer.bind();
    m_shader.setAttributeBuffer("vertexColor", GL_FLOAT, 0, 4);
    m_shader.enableAttributeArray("vertexColor" );
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
    glDrawArrays( GL_TRIANGLES, 0, 4*3 );
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
