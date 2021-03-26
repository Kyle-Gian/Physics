// post-processing fragment shader
#version 410

in vec2 vTexCoord;

uniform sampler2D colourTarget;

out vec4 FragColour;
// just output the colour unchanged
vec4 Default(vec2 texCoord) 
{
    return texture( colourTarget, texCoord );
}
void main() 
{
    // calculate texel size
    vec2 texSize = textureSize( colourTarget, 0);
    vec2 texelSize = 1.0 / texSize;
    // adjust texture coordinate
    vec2 scale = (texSize - texelSize) / texSize;
    vec2 texCoord = vTexCoord / scale + texelSize * 0.5;
    // sample post effect
    FragColour = Default(texCoord);
}