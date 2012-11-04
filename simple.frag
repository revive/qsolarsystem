#version 330

in vec2 UV;
out vec3 color;
uniform sampler2D myTextureSample;

void main( void )
{
    color = texture2D(myTextureSample, UV).rgb;
//   color = vec3(1.0, 0.0, 0.0);
}
