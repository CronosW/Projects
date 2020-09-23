#version 330
 
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform float useAlpha;
uniform float time;
in vec2 texcoord;

layout(location = 0) out vec4 out_color;

void main()
{
	vec4 color;
	// TODO : calculate the out_color using the texture2D() function
	if (useAlpha == 3) {
		color = texture2D(texture_1, texcoord - vec2(1,0) * time / 2);
	}
	else if (useAlpha == 4) {
		color = texture2D(texture_1, texcoord);
	}
	else {
		color = texture2D(texture_1, texcoord);
	}

	if (texture2D(texture_2, texcoord).x > 0.5 && useAlpha == 1) {
		discard;
	}
	if (useAlpha == 2) {
		out_color = mix(color, vec4(0.2f, 0.4f, 0.6f, 1), 0.5f);
	}
	else {
		out_color = color;
	}
}