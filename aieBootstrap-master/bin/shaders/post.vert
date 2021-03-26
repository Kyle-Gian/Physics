// simple post-processing vertex shader
#version 410

layout( location = 0 )  in vec2 Position;

out vec2 vTexCoord;


void main() 
{
    // generate texture coordinates
    vTexCoord = Position * 0.5 + 0.5;
    gl_Position = vec4(Position, 0, 1);


}