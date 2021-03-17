// Phong shader for simple game lighting
#version 410
in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;
in vec3 vTangent;
in vec3 vBiTangent;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;


uniform vec3 Ka; // The ambient color of the model's Material
uniform vec3 Kd; // the diffuse color of the model's Material
uniform vec3 Ks; // The specular color of the model's Material
uniform float Ns; //The specular power of the model's Material

//uniform int NumberOfLights;

uniform vec3 AmbientColor[4]; // Ambient color of the light
uniform vec3 LightColor[4]; //Color of the Light
uniform vec3 LightDirection[4];

uniform vec3 CameraPosition; // Position of the viewport camera for specular calculations

out vec4 FragColor;



void main() {
    //Make sure the normal and the light directions have been normalised
    vec3 N = normalize(vNormal);

    vec3 T = normalize(vTangent);
    vec3 B = normalize(vBiTangent);

    mat3 TBN = mat3(T,B,N);

    vec3 texDiffuse = texture(diffuseTexture, vTexCoord).rgb;
    vec3 texSpecular = texture(specularTexture, vTexCoord).rgb;
    vec3 texNormal = texture(normalTexture, vTexCoord).rgb;

    N = TBN * (texNormal * 2 - 1);

    // Now we can calculate the lambert term, negative the light direction
    

    for(int i = 0; i < 4; i++)
    {

        vec3 L = normalize(LightDirection[i]);
        float lambertTerm = max(0, min(1, dot(N,-L)));


        //Calculate the view vector and the reflection vector
        vec3 V = normalize(CameraPosition - vPosition.xyz);
        vec3 R = reflect(L,N);


        // Determining the value of the specular term
        float specularTerm = pow(max(0,dot(R, V)), 32);


        //Determine the value of the ambient
        vec3 ambient = AmbientColor[i] * Ka * texDiffuse;



        //Deteremine the valuse of the diffuse
        vec3 diffuse = LightColor[i] * Kd * texDiffuse * lambertTerm;

        //Determine the value of the specular
        vec3 specular = LightColor[i] * Ks * texSpecular * specularTerm;

            FragColor = vec4(ambient + diffuse + specular, 1);

    }

}