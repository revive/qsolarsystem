#version 330

in vec4 vertex;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main(void)
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vertex;
}
