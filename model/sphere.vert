#version 330

in vec3 vertex;

uniform mat4 pvmMatrix;

out vec3 texCoords;
void main(void)
{
    gl_Position = pvmMatrix * vec4(normalize(vertex), 1.0);
    texCoords = normalize(vertex);
}
