#pragma once
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include "LabCamera1.h"

class Laborator6 : public SimpleScene
{
	public:
		Laborator6();
		~Laborator6();

		void Init() override;


		Mesh* CreateCircle(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
		{
			glm::vec3 corner = leftBottomCorner;
			const int s = 20;
			const double radius = 5;
			std::vector<VertexFormat> vertices;

			for (int a = 0; a < 360; a += 360 / s)
			{
				double heading = a * M_PI / 180;
				vertices.push_back(VertexFormat(corner + glm::vec3(cos(heading) * radius, sin(heading)* radius, 0), color));
			}

			int score;

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


	
					
		Mesh * CreateMesh(const char * name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices);

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		//void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix);
		void RenderSimpleMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix, glm::vec3 color1, glm::vec3 color2, glm::vec3 color3);
		//void RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix) override;


		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		Lab::Camera1 *camera1;
		glm::mat4 projectionMatrix;
		bool renderCameraTarget;
};
