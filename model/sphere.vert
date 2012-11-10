#version 330

in vec3 vertex;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec3 texCoords;
void main(void)
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1.0);
    texCoords = normalize(vertex);
}
