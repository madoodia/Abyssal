#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 vCol;
// out vec3 ourColor;
uniform float hOffset;

void main()
{
    gl_Position = vec4(aPos.x+hOffset, aPos.y, aPos.z, 1.0);
	// ourColor = aColor;
    vCol = vec4(clamp(aPos, 0.0f, 1.0f), 1.0f);	
}