#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 normala;
layout(location = 2) in vec2 textura;
layout(location = 3) in vec3 color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;
uniform vec3 color1;
uniform vec3 color2;
uniform vec3 color3;
uniform int flag;

// TODO: output values to fragment shader
out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_textura;
out vec3 frag_color;

void main()
{
	// TODO: send output to fragment shader
	frag_normal = normala;
	if(flag == 0)
		frag_color = color1 * abs(cos(2*Time)) + color2 * abs(sin(2*Time));
	else
		frag_color = color2 * abs(cos(Time)) + color3 * abs(sin(Time));
	frag_position = v_position;
	frag_textura = textura;

	// TODO: compute gl_Position
	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
