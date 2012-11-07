#version 330

in vec3 texCoords;
uniform sampler2D texture;
out vec3 color;

void main( void )
{
    vec2 longitudeLatitude = vec2 (
                (atan(texCoords.y, texCoords.x) / 3.1415926 + 0.5),
                0.5 - acos(texCoords.z)/3.1415926);
    color = texture2D(texture, longitudeLatitude).rgb;
//    color = vec3(longitudeLatitude, 0.5);
}
