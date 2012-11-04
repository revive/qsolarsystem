#version 330

in vec3 vertex;

in vec2 vertexUV;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
out vec2 UV;

void main(void)
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1.0);
    UV = vertexUV;
}
