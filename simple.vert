#version 330

in vec4 vertex;
//layout(location = 0)
in vec3 vertexColor;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
out vec3 fragmentColor;

void main(void)
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vertex;
    fragmentColor = vertexColor;
}
