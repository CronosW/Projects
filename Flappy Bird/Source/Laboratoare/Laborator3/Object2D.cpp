#include "Object2D.h"
#include <math.h>
#include <Core/Engine.h>

int a;

Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D::CreateCircle(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;
	const int s = 20; 
	const double radius = 5;
	std::vector<VertexFormat> vertices;
	
	for (a = 0; a < 360; a += 360 / s)
	{
		double heading = a * M_PI / 180;
		vertices.push_back(VertexFormat(corner + glm::vec3(cos(heading) * radius, sin(heading)* radius, 0), color));
	}

	

	Mesh* circle = new Mesh(name);
	std::vector<unsigned short> indices = {
		19, 0, 1,
		19, 1, 2,
		19, 2, 3,
		19, 3, 4,
		19, 4, 5,
		19, 5, 6,
		19, 6, 7, 
		19, 7, 8,
		19, 8, 9,
		19, 9, 10,
		19, 10, 11,
		19, 11, 12,
		19, 12, 13,
		19, 13, 14,
		19, 14, 15,
		19, 15, 16,
		19, 16, 17,
		19, 17, 18,
		
	};

	if (!fill) {
		circle->SetDrawMode(GL_LINE_LOOP);
	}
	

	circle->InitFromData(vertices, indices);
	return circle;
}

Mesh* Object2D::CreateTriangle(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;
	std::vector<VertexFormat> vertices = {

		VertexFormat(corner + glm::vec3(0, 0, 0), glm::vec3(0, 1, 1)),
		VertexFormat(corner + glm::vec3(3, 5.19f, 0), glm::vec3(0, 1, 1)),
		VertexFormat(corner + glm::vec3(6, 0, 0), glm::vec3(0, 1, 1)),
		
	};

	Mesh* triangle = new Mesh("triangle");
	std::vector<unsigned short> indices = {
		0, 1, 2,
	};

	if (!fill) {
		triangle->SetDrawMode(GL_LINE_LOOP);
	}


	triangle->InitFromData(vertices, indices);
	return triangle;
	
}
