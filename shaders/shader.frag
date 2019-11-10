#version 330

in vec4 vCol;

out vec4 color; 

void main()
{
	color = vCol;// vec4(1.0f, 1.0f, 0.0f, 1.0f);
}