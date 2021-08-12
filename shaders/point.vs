#version 330 core
layout (location = 0) in vec2 vertex; //where [0]&[1] is position and [2][3] is texture coords

uniform vec2 gPos;
uniform vec2 gScale;
uniform vec2 vPos;
uniform vec2 vScale;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    vec2 p = vertex;
    p.x -= gPos.x;
	p.y -= gPos.y;

	p.x /= gScale.x;
	p.y /= gScale.y;

	p.x *= vScale.x;
	p.y *= vScale.y;

	p.y = vScale.y - p.y;

	p.x += vPos.x;
	p.y += vPos.y;
    
    gl_Position = projection * view * vec4(p, 0.0, 1.0);
}