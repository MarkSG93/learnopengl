#version 410 core
in vec3 vertexColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec4 ourColor;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
//  FragColor = vec4(vertexColor, 1.0);
//  FragColor = vec4(ourColor);
//  FragColor = texture(ourTexture, TexCoord);
  FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}
