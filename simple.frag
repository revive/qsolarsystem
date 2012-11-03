#version 330

in vec3 fragmentColor;
out vec3 color;
void main( void )
{
  color = fragmentColor;
//   color = vec3(1.0, 0.0, 0.0);
}
