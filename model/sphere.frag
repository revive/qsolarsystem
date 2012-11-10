#version 330

in vec3 texCoords;
uniform sampler2D texture;
out vec4 color;

void main( void )
{
    vec2 longitudeLatitude = vec2 (
                (atan(texCoords.x/texCoords.z) / 3.1415926 + 0.5),
                -texCoords.y*0.5 + 0.5);
    color = vec4(texture2D(texture, longitudeLatitude).rgb, 1.0);
//    color = vec3(longitudeLatitude, 0.5);
}
