#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Uniforms for light properties
uniform vec3 light_position;
uniform vec3 eye_position;
uniform vec3 material_kd;
uniform vec3 material_ks;
uniform int material_shininess;

uniform vec3 object_color;

// Output value to fragment shader
out vec3 color;

void main()
{
	vec3 world_pos = (Model * vec4(v_position,1)).xyz;
	vec3 world_normal = normalize( mat3(Model) * v_normal );
	vec3 L = normalize( light_position - world_pos );
	vec3 V = normalize( eye_position - world_pos );
	vec3 H = normalize( L + V );
	
	vec3 ambient_light =material_kd * object_color;
	vec3 diffuse_light = material_kd *  max(dot(world_normal,L), 0);

	vec3 specular_light = vec3(1);
	if(dot(v_normal,L)>0)
		specular_light = material_ks * pow(max(dot(world_normal, H), 0), material_shininess);
	
	float atenuation = 1/pow(distance(light_position,world_pos),2);	
	
	color = ambient_light + atenuation * (diffuse_light+specular_light) * object_color;
	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
