#include "Laborator6.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include "LabCamera1.h"


using namespace std;

Laborator6::Laborator6()
{
}

Laborator6::~Laborator6()
{
}

std::vector<VertexFormat> vertices_cylinder;
std::vector<unsigned short> indices_cylinder;



	void CreateCylinder(glm::vec3 color, float centerx, float centery, float centerz1, float centerz2) {


	int nr = 0;
	int s = 20;
	double radius = 5;
	double px[50], py[50];
	

	for (int i = 0; i < 360; i += 360 / s)
	{

		double heading = i * M_PI / 180;
		px[nr] = cos(heading) * radius;
		py[nr] = sin(heading)* radius + 10;
		nr++;

	}

	for (int i = 0; i < nr; i++)
		vertices_cylinder.push_back(VertexFormat(glm::vec3(px[i] + centerx, py[i] + centery, 50 * centerz1), color));
	for (int i = 0; i < nr; i++)
		vertices_cylinder.push_back(VertexFormat(glm::vec3(px[i] + centerx, py[i] + centery, 50 * centerz2), color));

	int nr2 = 0;

	for (int i = 0; i < nr - 1; i++)
	{
		indices_cylinder[nr2] = i;
		indices_cylinder[nr2 + 1] = i + 1;
		indices_cylinder[nr2 + 2] = i + nr;
		nr2 = nr2 + 3;
	}

	indices_cylinder[nr2] = nr - 1;
	indices_cylinder[nr2 + 1] = 0;
	indices_cylinder[nr2 + 2] = 2 * nr - 1;

	nr2 = nr2 + 3;


	for (int i = nr; i < 2 * nr - 1; i++)
	{
		indices_cylinder[nr2] = i;
		indices_cylinder[nr2 + 1] = i + 1;
		indices_cylinder[nr2 + 2] = i - nr + 1;
		nr2 = nr2 + 3;
	}

	indices_cylinder[nr2] = 2 * nr - 1;
	indices_cylinder[nr2 + 1] = nr;
	indices_cylinder[nr2 + 2] = 0;
	
	nr2 = nr2 + 3;

}

void Laborator6::Init()
{

	renderCameraTarget = false;


	camera1 = new Lab::Camera1();
	camera1->Set(glm::vec3(-22, 1, 1.3), glm::vec3(0,0,1.3), glm::vec3(0, 1, 0));

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Shader *shader = new Shader("ShaderLab6");
		shader->AddShader("Source/Laboratoare/Laborator6/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Laborator6/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
	
	int a = 50;
	float b = 0.1f;
	// Create a simple cube
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-a, -b,  a), glm::vec3(0, 1, 1), glm::vec3(0, 0.5f, 0)),
			VertexFormat(glm::vec3(a, -b,  a), glm::vec3(1, 0, 1), glm::vec3(0, 0.5f, 0)),
			VertexFormat(glm::vec3(-a,  b,  a), glm::vec3(1, 0, 0), glm::vec3(0, 0.5f, 0)),
			VertexFormat(glm::vec3(a,  b,  a), glm::vec3(0, 1, 0), glm::vec3(0, 0.5f, 0)),
			VertexFormat(glm::vec3(-a, -b, -a), glm::vec3(1, 1, 1), glm::vec3(0, 0.5f, 0)),
			VertexFormat(glm::vec3(a, -b, -a), glm::vec3(0, 1, 1), glm::vec3(0, 0.5f, 0)),
			VertexFormat(glm::vec3(-a,  b, -a), glm::vec3(1, 1, 0), glm::vec3(0, 0.5f, 0)),
			VertexFormat(glm::vec3(a,  b, -a), glm::vec3(0, 0, 1), glm::vec3(0, 0.5f, 0)),
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		CreateMesh("cube", vertices, indices);
	}

	int a_cer = 50;
	float b_cer = 1000;
	// Create a simple cube
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-a_cer, -b_cer,  a_cer), glm::vec3(0, 1, 1), glm::vec3(0, 0.5f, 0)),
			VertexFormat(glm::vec3(a_cer, -b_cer,  a_cer), glm::vec3(1, 0, 1), glm::vec3(0, 0.5f, 0)),
			VertexFormat(glm::vec3(-a_cer,  b_cer,  a_cer), glm::vec3(1, 0, 0), glm::vec3(0, 0.5f, 0)),
			VertexFormat(glm::vec3(a_cer,  b_cer,  a_cer), glm::vec3(0, 1, 0), glm::vec3(0, 0.5f, 0)),
			VertexFormat(glm::vec3(-a_cer, -b_cer, -a_cer), glm::vec3(1, 1, 1), glm::vec3(0, 0.5f, 0)),
			VertexFormat(glm::vec3(a_cer, -b_cer, -a_cer), glm::vec3(0, 1, 1), glm::vec3(0, 0.5f, 0)),
			VertexFormat(glm::vec3(-a_cer,  b_cer, -a_cer), glm::vec3(1, 1, 0), glm::vec3(0, 0.5f, 0)),
			VertexFormat(glm::vec3(a_cer,  b_cer, -a_cer), glm::vec3(0, 0, 1), glm::vec3(0, 0.5f, 0)),
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		CreateMesh("cube_cer", vertices, indices);
	}

	int a1 = 2;
	float b1 = 0.15f;
	int c1 = 5;
	// Create a simple cube

	{
		vector<VertexFormat> vertices1
		{
			VertexFormat(glm::vec3(-a1, -b1,  c1), glm::vec3(0, 1, 1), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(a1, -b1,  c1), glm::vec3(1, 0, 1), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(-a1,  b1,  c1), glm::vec3(1, 0, 0), glm::vec3(0.5, 0.5, 0.5)),
			VertexFormat(glm::vec3(a1,  b1,  c1), glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
			VertexFormat(glm::vec3(-a1, -b1, -c1), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(a1, -b1, -c1), glm::vec3(0, 1, 1), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(-a1,  b1, -c1), glm::vec3(1, 1, 0), glm::vec3(0.5, 0.5, 0.5)),
			VertexFormat(glm::vec3(a1,  b1, -c1), glm::vec3(0, 0, 1), glm::vec3(0.5, 0.5, 0.5)),
		};

		vector<unsigned short> indices1 =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		CreateMesh("cube1", vertices1, indices1);
	}

	
	// Create a simple cube



	float a2 = 0.1f;
	float b2 = 0.3f;
	int c2 = 5;


	{
		vector<VertexFormat> vertices2
		{
			VertexFormat(glm::vec3(-a2, -b2,  c2), glm::vec3(0, 1, 1), glm::vec3(0.7f, 0.7f, 0.7f)),
			VertexFormat(glm::vec3(a2, -b2,  c2), glm::vec3(1, 0, 1), glm::vec3(0.7f, 0.7f, 0.7f)),
			VertexFormat(glm::vec3(-a2,  b2,  c2), glm::vec3(1, 0, 0), glm::vec3(0.7f, 0.7f, 0.7f)),
			VertexFormat(glm::vec3(a2,  b2,  c2), glm::vec3(0, 1, 0), glm::vec3(0.7f, 0.7f, 0.7f)),
			VertexFormat(glm::vec3(-a2, -b2, -c2), glm::vec3(1, 1, 1), glm::vec3(0.7f, 0.7f, 0.7f)),
			VertexFormat(glm::vec3(a2, -b2, -c2), glm::vec3(0, 1, 1), glm::vec3(0.7f, 0.7f, 0.7f)),
			VertexFormat(glm::vec3(-a2,  b2, -c2), glm::vec3(1, 1, 0), glm::vec3(0.7f, 0.7f, 0.7f)),
			VertexFormat(glm::vec3(a2,  b2, -c2), glm::vec3(0, 0, 1), glm::vec3(0.7f, 0.7f, 0.7f)),
		};

		vector<unsigned short> indices2 =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		CreateMesh("cube2", vertices2, indices2);
	}



	float a3 = 0.6f;
	float b3 = 0.4f;
	int c3 = 1.5;


	{
		vector<VertexFormat> vertices3
		{
			VertexFormat(glm::vec3(-a3, -b3,  c3), glm::vec3(0, 1, 1), glm::vec3(0, 0, 1)),
			VertexFormat(glm::vec3(a3, -b3,  c3), glm::vec3(1, 0, 1), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(-a3,  b3,  c3), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(a3,  b3,  c3), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)),
			VertexFormat(glm::vec3(-a3, -b3, -c3), glm::vec3(1, 1, 1), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(a3, -b3, -c3), glm::vec3(0, 1, 1), glm::vec3(0, 0, 1)),
			VertexFormat(glm::vec3(-a3,  b3, -c3), glm::vec3(1, 1, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(a3,  b3, -c3), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1)),
		};

		vector<unsigned short> indices3 =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		CreateMesh("cube3", vertices3, indices3);
	}


	float a4 = 0.4f;
	float b4 = 0.2f;
	float c4 = 0.4f;


	{
		vector<VertexFormat> vertices4
		{
			VertexFormat(glm::vec3(-a4, -b4,  c4), glm::vec3(0, 1, 1), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(a4, -b4,  c4), glm::vec3(1, 0, 1), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(-a4,  b4,  c4), glm::vec3(1, 0, 0), glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(a4,  b4,  c4), glm::vec3(0, 1, 0), glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(-a4, -b4, -c4), glm::vec3(1, 1, 1), glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(a4, -b4, -c4), glm::vec3(0, 1, 1), glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(-a4,  b4, -c4), glm::vec3(1, 1, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(a4,  b4, -c4), glm::vec3(0, 0, 1), glm::vec3(1, 0, 0)),
		};

		vector<unsigned short> indices4 =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		CreateMesh("cube4", vertices4, indices4);
	}



	{
		vector<VertexFormat> vertices5
		{
			VertexFormat(glm::vec3(-a1, -b1,  c1), glm::vec3(0, 1, 1), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(a1, -b1,  c1), glm::vec3(1, 0, 1), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(-a1,  b1,  c1), glm::vec3(1, 0, 0), glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(a1,  b1,  c1), glm::vec3(0, 1, 0), glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(-a1, -b1, -c1), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(a1, -b1, -c1), glm::vec3(0, 1, 1), glm::vec3(0, 0, 0)),
			VertexFormat(glm::vec3(-a1,  b1, -c1), glm::vec3(1, 1, 0), glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(a1,  b1, -c1), glm::vec3(0, 0, 1), glm::vec3(1, 1, 1)),
		};

		vector<unsigned short> indices5 =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		CreateMesh("cube5", vertices5, indices5);
	}

	Mesh* circle1 = CreateCircle("circle1", glm::vec3(0, 10, 0), 100.0f, glm::vec3(0, 0, 0.3f), true);
	AddMeshToList(circle1);

	indices_cylinder.resize(200);
	CreateCylinder(glm::vec3(0, 0, 0), 0, 0, 2, 1.9f);
	CreateMesh("cylinder", vertices_cylinder, indices_cylinder);


	a1 = 1;
	b1 = 4.0f;
	c1 = 1;
	{
		vector<VertexFormat> vertices1
		{
			VertexFormat(glm::vec3(-a1, -b1,  c1), glm::vec3(0, 1, 1), glm::vec3(0.6, 0.6, 0.6)),
			VertexFormat(glm::vec3(a1, -b1,  c1), glm::vec3(1, 0, 1), glm::vec3(0.6, 0.6, 0.6)),
			VertexFormat(glm::vec3(-a1,  b1,  c1), glm::vec3(1, 0, 0), glm::vec3(0.6, 0.6, 0.6)),
			VertexFormat(glm::vec3(a1,  b1,  c1), glm::vec3(0, 1, 0), glm::vec3(0.6, 0.6, 0.6)),
			VertexFormat(glm::vec3(-a1, -b1, -c1), glm::vec3(1, 1, 1), glm::vec3(0.6, 0.6, 0.6)),
			VertexFormat(glm::vec3(a1, -b1, -c1), glm::vec3(0, 1, 1), glm::vec3(0.6, 0.6, 0.6)),
			VertexFormat(glm::vec3(-a1,  b1, -c1), glm::vec3(1, 1, 0), glm::vec3(0.6, 0.6, 0.6)),
			VertexFormat(glm::vec3(a1,  b1, -c1), glm::vec3(0, 0, 1), glm::vec3(0.6, 0.6, 0.6)),
		};

		vector<unsigned short> indices1 =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		CreateMesh("cube6", vertices1, indices1);
	}


	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
}

Mesh* Laborator6::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// TODO: Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO: Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// TODO: Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO: Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	meshes[name]->vertices = vertices;
	meshes[name]->indices = indices;
	return meshes[name];
}


void Laborator6::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);


}



int x1 = 1;
float viteza = 0.03f;
int ok = 0;
float x_masina = -19.2;
float y_masina = 0.3;
float z_masina = 1.3;
float unghi_rotatie_masina = 90.5f;
float unghi_rotatie_roti = 0.0f;
int score;

void Laborator6::Update(float deltaTimeSeconds)
{
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(100));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab6"], modelMatrix, glm::vec3(0.45, 0.55, 0.9), glm::vec3(0.4, 0.91, 0.9), glm::vec3(0.1, 0.2, 0));
	}


	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-10, -0.2, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f));
		RenderSimpleMesh(meshes["cube"], shaders["ShaderLab6"], modelMatrix,  glm::vec3(0.1, 0.5, 0), glm::vec3(0.1, 0.7, 0), glm::vec3(0.1, 0.3, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-15.2, 0, 0.9));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-90.5f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube1"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-18.2, 0, 0.875));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-90.5f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube1"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-11.7, 0, -0.55));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-45.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube1"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-9.7, 0, -2.55));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-45.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube1"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5));
	}
	
	
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-6.1, 0, -4.23));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-85.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube1"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.2, 0, -4.57));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-85.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube1"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.3, 0, -3.4));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(5), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube1"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5));
	}
	
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.72, 0, 1.4));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(5), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube1"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5, 0, 4.77));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-85.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube1"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-4.4, 0, 5.2));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-85.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube1"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-9.3, 0, 5.6));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-85.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube1"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-14.2, 0, 6.025));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-85.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube1"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-18.3, 0, 6.35));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-85.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube1"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-19.7, 0, 6.5));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-85.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube1"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-22, 0.01, 5.2));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(0), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube5"], shaders["VertexNormal"], modelMatrix, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
	}


	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-18.5, 0, 7.42));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-85.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-18.5, 0, 5.395));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-85.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}


	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-9.2, 0, 6.63));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-85.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-14.1, 0, 7.05));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-85.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}


	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-9.3, 0, 4.62));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-85.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-14.2, 0, 5.05));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-85.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.6, 0, 5.77));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-85.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.5, 0, 3.95));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-85.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-4.3, 0, 6.2));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-85.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}


	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-4.4, 0, 4.2));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-85.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.3, 0, -3.4));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(5), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}


	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.72, 0, 1.4));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(5), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.47, 0, -1.4));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(5), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.87, 0, 3.1));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(5), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.72, 0, 1.4));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(5), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.3, 0, -5.75));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-85.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}



	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-18.3, 0, -0.1));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-90.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}


	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-16, 0, -0.1));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-90.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}


	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-18.3, 0, 1.9));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-90.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}


	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-15.25, 0, 1.9));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-90.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}


	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-11.75, 0, -1.85));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-45.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-9.75, 0, -3.85));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-45.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-11.5, 0, 0.65));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-45.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-9.5, 0, -1.35));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-45.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-6.1, 0, -5.23));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-85.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.2, 0, -5.57));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-85.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-5.25, 0, -3.35));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-85.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.1, 0, -3.62));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-85.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7), glm::vec3(0.7, 0.7, 0.7));
	}


	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, camera1->GetTargetPosition());

		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -0.5, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(unghi_rotatie_masina), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube3"], shaders["VertexNormal"], modelMatrix, glm::vec3(1, 1, 0), glm::vec3(1, 1, 0), glm::vec3(1, 1, 0));
	}


	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, camera1->GetTargetPosition());
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -0.5, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(unghi_rotatie_masina), glm::vec3(0, 1, 0));
		modelMatrix = glm::translate(modelMatrix, glm::vec3 (0, 0.3, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
		RenderSimpleMesh(meshes["cube4"], shaders["VertexNormal"], modelMatrix, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
	}


	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, camera1->GetTargetPosition());
		modelMatrix = glm::rotate(modelMatrix, RADIANS(unghi_rotatie_roti), glm::vec3(0, 1, 0));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.38, -0.85, 0.39));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.02f));
		RenderSimpleMesh(meshes["circle1"], shaders["VertexColor"], modelMatrix, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, camera1->GetTargetPosition());
		modelMatrix = glm::rotate(modelMatrix, RADIANS(unghi_rotatie_roti), glm::vec3(0, 1, 0));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.38, -0.85, 0.31));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.02f));
		RenderSimpleMesh(meshes["circle1"], shaders["VertexColor"], modelMatrix, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
	}


	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, camera1->GetTargetPosition());
		modelMatrix = glm::rotate(modelMatrix, RADIANS(unghi_rotatie_roti), glm::vec3(0, 1, 0));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.38, -0.85, -1.6));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.02f));
		RenderSimpleMesh(meshes["cylinder"], shaders["VertexColor"], modelMatrix, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, camera1->GetTargetPosition());
		modelMatrix = glm::rotate(modelMatrix, RADIANS(unghi_rotatie_roti), glm::vec3(0, 1, 0));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.35, -0.85, 0.39));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.02f));
		RenderSimpleMesh(meshes["circle1"], shaders["VertexColor"], modelMatrix, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, camera1->GetTargetPosition());
		modelMatrix = glm::rotate(modelMatrix, RADIANS(unghi_rotatie_roti), glm::vec3(0, 1, 0));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.35, -0.85, 0.31));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.02f));
		RenderSimpleMesh(meshes["circle1"], shaders["VertexColor"], modelMatrix, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
	}


	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, camera1->GetTargetPosition());
		modelMatrix = glm::rotate(modelMatrix, RADIANS(unghi_rotatie_roti), glm::vec3(0, 1, 0));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.35, -0.85, -1.6));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.02f));
		RenderSimpleMesh(meshes["cylinder"], shaders["VertexColor"], modelMatrix, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, camera1->GetTargetPosition());
		modelMatrix = glm::rotate(modelMatrix, RADIANS(unghi_rotatie_roti), glm::vec3(0, 1, 0));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.35, -0.85, -0.31));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.02f));
		RenderSimpleMesh(meshes["circle1"], shaders["VertexColor"], modelMatrix, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, camera1->GetTargetPosition());
		modelMatrix = glm::rotate(modelMatrix, RADIANS(unghi_rotatie_roti), glm::vec3(0, 1, 0));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.35, -0.85, -0.39));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.02f));
		RenderSimpleMesh(meshes["circle1"], shaders["VertexColor"], modelMatrix, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
	}


	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, camera1->GetTargetPosition());
		modelMatrix = glm::rotate(modelMatrix, RADIANS(unghi_rotatie_roti), glm::vec3(0, 1, 0));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.35, -0.85, -2.3));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.02f));
		RenderSimpleMesh(meshes["cylinder"], shaders["VertexColor"], modelMatrix, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, camera1->GetTargetPosition());
		modelMatrix = glm::rotate(modelMatrix, RADIANS(unghi_rotatie_roti), glm::vec3(0, 1, 0));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.38, -0.85, -0.39));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.02f));
		RenderSimpleMesh(meshes["circle1"], shaders["VertexColor"], modelMatrix, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, camera1->GetTargetPosition());
		modelMatrix = glm::rotate(modelMatrix, RADIANS(unghi_rotatie_roti), glm::vec3(0, 1, 0));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.38, -0.85, -0.31));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.02f));
		RenderSimpleMesh(meshes["circle1"], shaders["VertexColor"], modelMatrix, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
	}


	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, camera1->GetTargetPosition());
		modelMatrix = glm::rotate(modelMatrix, RADIANS(unghi_rotatie_roti), glm::vec3(0, 1, 0));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.38, -0.85, -2.3));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.02f));
		RenderSimpleMesh(meshes["cylinder"], shaders["VertexColor"], modelMatrix, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 0, 2));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-25.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["cube6"], shaders["VertexNormal"], modelMatrix, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-6, 0, 4.6));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(0), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["cube6"], shaders["VertexNormal"], modelMatrix, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-15, 0, 0.4));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(-45.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["cube6"], shaders["VertexNormal"], modelMatrix, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	}







  
/*	
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5f, 1, -1.2f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));;
		RenderSimpleMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5f, 1, -1.2f));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(180.0f), glm::vec3(0, 1, 1));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.015f));
		RenderSimpleMesh(meshes["cylinder"], shaders["VertexColor"], modelMatrix);
	}
	*/

	if (renderCameraTarget)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, camera1->GetTargetPosition());
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		//RenderSimpleMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
	}


	printf("%d\n", score);


}

void Laborator6::FrameEnd()
{
	//DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

/*void Laborator6::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// TODO : get shader location for uniform mat4 "Model"
	int location = glGetUniformLocation(shader->program, "Model");
	// TODO : set shader uniform "Model" to modelMatrix

	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// TODO : get shader location for uniform mat4 "View"
	 location = glGetUniformLocation(shader->program, "View");
	// TODO : set shader uniform "View" to viewMatrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// TODO : get shader location for uniform mat4 "Projection"
	 location = glGetUniformLocation(shader->program, "Projection");
	// TODO : set shader uniform "Projection" to projectionMatrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
//	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	location = glGetUniformLocation(shader->program, "time");
	glUniform1f(location, Engine::GetElapsedTime());
		
	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);


	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera1->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();


}*/

void Laborator6::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, glm::vec3 color1, glm::vec3 color2, glm::vec3 color3)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// TODO : get shader location for uniform mat4 "Model"
	//void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)

	int location_1 = glGetUniformLocation(shader->GetProgramID(), "Model");

	// TODO : set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(location_1, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// TODO : get shader location for uniform mat4 "View"
	int location_2 = glGetUniformLocation(shader->program, "View");

	// TODO : set shader uniform "View" to viewMatrix
	glm::mat4 viewMatrix = camera1->GetViewMatrix();
	glUniformMatrix4fv(location_2, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// TODO : get shader location for uniform mat4 "Projection"
	int location_3 = glGetUniformLocation(shader->program, "Projection");

	// TODO : set shader uniform "Projection" to projectionMatrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	glUniformMatrix4fv(location_3, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// bonus trimitem timpul
	float time = Engine::GetElapsedTime();
	int flag = 0;
	int location_time = glGetUniformLocation(shader->program, "Time");
	if (abs(sin(time / 10)) > sin(M_PI / 4))
		flag = 1;
	if (abs(sin(time / 10)) < sin(M_PI / 4))
		flag = 0;
	glUniform1f(location_time, time / 10);
	int c1 = glGetUniformLocation(shader->program, "color1");
	int c2 = glGetUniformLocation(shader->program, "color2");
	int c3 = glGetUniformLocation(shader->program, "color3");
	glUniform3f(c1, color1[0], color1[1], color1[2]);
	glUniform3f(c2, color2[0], color2[1], color2[2]);
	glUniform3f(c3, color3[0], color3[1], color3[2]);
	int f1 = glGetUniformLocation(shader->program, "flag");
	glUniform1i(f1, flag);


	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}



/*void Laborator6::RenderSimpleMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera1->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}*/

void Laborator6::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event

	/*if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			renderCameraTarget = false;
			// TODO : rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera1->RotateFirstPerson_OX(-sensivityOX * deltaY);
			camera1->RotateFirstPerson_OY(-sensivityOY * deltaX);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			renderCameraTarget = true;
			// TODO : rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera1->RotateThirdPerson_OX(-sensivityOX * deltaY);
			camera1->RotateThirdPerson_OY(-sensivityOY * deltaX);
		}

	}*/
}

void Laborator6::OnInputUpdate(float deltaTime, int mods)
{

	// move the camera only if MOUSE_RIGHT button is pressed

	/*if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_W)) {
			// TODO : translate the camera forward
			camera1->TranslateForward(cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			// TODO : translate the camera to the left
			camera1->TranslateRight(-cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			// TODO : translate the camera backwards
			camera1->TranslateForward(-cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			// TODO : translate the camera to the right
			camera1->TranslateRight(cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// TODO : translate the camera down
			camera1->TranslateUpword(-cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			// TODO : translate the camera up
			camera1->TranslateUpword(cameraSpeed * deltaTime);
		}
	}
	*/

	if (window->KeyHold(GLFW_KEY_O)) {
		// TODO : translate the camera up
		glm::mat4 Projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);
		projectionMatrix = Projection;
	}

	if (window->KeyHold(GLFW_KEY_P)) {
		// TODO : translate the camera up
		glm::mat4 Projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 100.0f, 0.1f);
		projectionMatrix = Projection;
	}


	if (window->KeyHold(GLFW_KEY_UP)) {

		if(viteza < 3)
		viteza *= 1.05f;
		score++;

		//camera1->TranslateForward(viteza * deltaTime);
		camera1->MoveForward(deltaTime * viteza);
		if (viteza == 0)
			viteza = 0.2;
		ok = 1;

		if (window->KeyHold(GLFW_KEY_DOWN))
		{

			//camera1->TranslateForward(viteza * deltaTime);
			camera1->MoveForward(deltaTime * viteza);
			viteza /= 1.1f;
			if (viteza < 0.001)
				viteza = 0;
		}

		if (window->KeyHold(GLFW_KEY_RIGHT)) {
			unghi_rotatie_masina -= 35.0f * viteza * deltaTime;
			unghi_rotatie_roti -= 35.0f * viteza * deltaTime;
			camera1->RotateFirstPerson_OY(-0.6 * viteza * deltaTime);
		
		}


		if (window->KeyHold(GLFW_KEY_LEFT)) {
			unghi_rotatie_masina += 35.0f * viteza * deltaTime;
			unghi_rotatie_roti += 35.0f * viteza * deltaTime;
			camera1->RotateFirstPerson_OY(0.6 * viteza * deltaTime);
			

		}


	}
	
	else if (ok == 1) {
		viteza /= 1.05f;
		if (viteza < 0.001)
			viteza = 0;

	}
	camera1->MoveForward(deltaTime * viteza);
}
	

void Laborator6::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Laborator6::OnKeyRelease(int key, int mods)
{
	// add key release event
}


void Laborator6::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator6::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator6::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator6::OnWindowResize(int width, int height)
{
}
