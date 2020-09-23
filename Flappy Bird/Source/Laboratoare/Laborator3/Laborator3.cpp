#include "Laborator3.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

float position_bird_component1_x = 100, position_bird_component1_y = 400;
float position_bird_component2_x = 110, position_bird_component2_y = 420;
float position_bird_component3_x = 150, position_bird_component3_y = 410;
float position_bird_component4_x = 160, position_bird_component4_y = 397;
float position_tube1_component1_x = 500, position_tube1_component1_y = 0;
float position_tube1_component2_x = 500, position_tube1_component2_y = 600;
float position_tube2_component1_x = 900, position_tube2_component1_y = 0;
float position_tube2_component2_x = 900, position_tube2_component2_y = 500;
float position_tube3_component1_x = 1300, position_tube3_component1_y = 0;
float position_tube3_component2_x = 1300, position_tube3_component2_y = 400;
float position_tube4_component1_x = 1700, position_tube4_component1_y = 0;
float position_tube4_component2_x = 1700, position_tube4_component2_y = 600;
float rotate_bird_component1 = 0;
float rotate_bird_component2 = 0;
float rotate_bird_component3 = 0;
float rotate_bird_component4 = M_PI / 8;
float scale_tube1_component1 = 3, scale_tube1_component2 = 7;
float scale_tube2_component1 = 2, scale_tube2_component2 = 7;
float scale_tube3_component1 = 1, scale_tube3_component2 = 7;
float scale_tube4_component1 = 3, scale_tube4_component2 = 7;
int how_much_bird = 3;
int how_much_tube = 3;
int how_much_jump = 90;
int score_player = 0;
int k = 0;
int score_player_current = 0;
int best_score;
bool finish = false;
bool space = false;
bool start = false;
bool ok1 = false, ok2 = false, ok3 = false, ok4 = false;
bool ok_score = false;
bool bird_position;
FILE *best;

Laborator3::Laborator3()
{
}

Laborator3::~Laborator3()
{
}

void Laborator3::Init()
{
	best = fopen("best_score.txt", "r+");

	if(best != NULL)
		fscanf(best, "%d", best_score);

	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;

	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;

	Mesh* dreptunghi1 = Object2D::CreateSquare("dreptunghi1", corner, squareSide, glm::vec3(1, 0, 2.4f), true);
	AddMeshToList(dreptunghi1);

	Mesh* dreptunghi2 = Object2D::CreateSquare("dreptunghi2", corner, squareSide, glm::vec3(1, 0, 2.4f), true);
	AddMeshToList(dreptunghi2);

	Mesh* dreptunghi3 = Object2D::CreateSquare("dreptunghi3", corner, squareSide, glm::vec3(1, 0, 2.4f), true);
	AddMeshToList(dreptunghi3);

	Mesh* dreptunghi4 = Object2D::CreateSquare("dreptunghi4", corner, squareSide, glm::vec3(1, 0, 2.4f), true);
	AddMeshToList(dreptunghi4);

	Mesh* dreptunghi5 = Object2D::CreateSquare("dreptunghi5", corner, squareSide, glm::vec3(1, 0, 2.4f), true);
	AddMeshToList(dreptunghi5);

	Mesh* dreptunghi6 = Object2D::CreateSquare("dreptunghi6", corner, squareSide, glm::vec3(1, 0, 2.4f), true);
	AddMeshToList(dreptunghi6);

	Mesh* dreptunghi7 = Object2D::CreateSquare("dreptunghi7", corner, squareSide, glm::vec3(1, 0, 2.4f), true);
	AddMeshToList(dreptunghi7);

	Mesh* dreptunghi8 = Object2D::CreateSquare("dreptunghi8", corner, squareSide, glm::vec3(1, 0, 2.4f), true);
	AddMeshToList(dreptunghi8);

	Mesh* dreptunghi9 = Object2D::CreateSquare("dreptunghi9", corner, squareSide, glm::vec3(1, 0, 2.4f), true);
	AddMeshToList(dreptunghi9);

	Mesh* circle = Object2D::CreateCircle("circle", corner, squareSide, glm::vec3(0.4f, 2.8f, 0.5f), true);
	AddMeshToList(circle);

	Mesh* triangle = Object2D::CreateTriangle("triangle", corner, squareSide, glm::vec3(1, 0, 2.4f), true);
	AddMeshToList(triangle);

	Mesh* triangle2 = Object2D::CreateTriangle("triangle2", corner, squareSide, glm::vec3(1, 0, 2.4f), true);
	AddMeshToList(triangle2);

}

void Laborator3::FrameStart()
{

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();

	glViewport(0, 0, resolution.x, resolution.y);
}

float x = 0, y = 0;
void Laborator3::Update(float deltaTimeSeconds)
{
	if (!finish)
	{

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(position_bird_component1_x, position_bird_component1_y);
		modelMatrix *= Transform2D::Rotate(rotate_bird_component1);
		modelMatrix *= Transform2D::Scale(0.4f, 0.2f);
		RenderMesh2D(meshes["dreptunghi1"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(position_bird_component2_x, position_bird_component2_y);
		modelMatrix *= Transform2D::Rotate(rotate_bird_component2);
		modelMatrix *= Transform2D::Scale(4, 4);
		RenderMesh2D(meshes["triangle"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(position_bird_component3_x, position_bird_component3_y);
		modelMatrix *= Transform2D::Rotate(rotate_bird_component3);
		modelMatrix *= Transform2D::Scale(3, 3);
		RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(position_bird_component4_x, position_bird_component4_y);
		modelMatrix *= Transform2D::Rotate(rotate_bird_component4);
		modelMatrix *= Transform2D::Scale(4, 4);
		RenderMesh2D(meshes["triangle"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(position_tube1_component1_x, position_tube1_component1_y);
		modelMatrix *= Transform2D::Scale(0.6f, scale_tube1_component1);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(position_tube1_component2_x, position_tube1_component2_y);
		modelMatrix *= Transform2D::Scale(0.6f, scale_tube1_component2);
		RenderMesh2D(meshes["dreptunghi3"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(position_tube2_component1_x, position_tube2_component1_y);
		modelMatrix *= Transform2D::Scale(0.6f, scale_tube2_component1);
		RenderMesh2D(meshes["dreptunghi4"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(position_tube2_component2_x, position_tube2_component2_y);
		modelMatrix *= Transform2D::Scale(0.6f, scale_tube2_component2);
		RenderMesh2D(meshes["dreptunghi5"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(position_tube3_component1_x, position_tube3_component1_y);
		modelMatrix *= Transform2D::Scale(0.6f, scale_tube3_component1);
		RenderMesh2D(meshes["dreptunghi6"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(position_tube3_component2_x, position_tube3_component2_y);
		modelMatrix *= Transform2D::Scale(0.6f, scale_tube3_component2);
		RenderMesh2D(meshes["dreptunghi7"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(position_tube4_component1_x, position_tube4_component1_y);
		modelMatrix *= Transform2D::Scale(0.6f, scale_tube4_component1);
		RenderMesh2D(meshes["dreptunghi8"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(position_tube4_component2_x, position_tube4_component2_y);
		modelMatrix *= Transform2D::Scale(0.6f, scale_tube4_component2);
		RenderMesh2D(meshes["dreptunghi9"], shaders["VertexColor"], modelMatrix);

		if (start == true)
		{	
			if (bird_position == false && space != true)
			{
				rotate_bird_component1 = -M_PI / 4;
				rotate_bird_component2 = -M_PI / 4;
				position_bird_component2_x += 8; position_bird_component2_y -= 11;
				position_bird_component3_x -= 7; position_bird_component3_y -= 42;
				rotate_bird_component4 = 2 * M_PI - rotate_bird_component4;
				position_bird_component4_x -= 18; position_bird_component4_y -= 48;

				bird_position = true;
			}

			if (space != true)
			{
				position_bird_component1_y -= how_much_bird;
				position_bird_component2_y -= how_much_bird;
				position_bird_component3_y -= how_much_bird;
				position_bird_component4_y -= how_much_bird;
			}


			if (space == true)
			{
				k += 5;
				position_bird_component1_y += 5;
				position_bird_component2_y += 5;
				position_bird_component3_y += 5;
				position_bird_component4_y += 5;
			}

			position_tube1_component1_x -= how_much_tube;
			position_tube1_component2_x -= how_much_tube;

			position_tube2_component1_x -= how_much_tube;
			position_tube2_component2_x -= how_much_tube;

			position_tube3_component1_x -= how_much_tube;
			position_tube3_component2_x -= how_much_tube;

			position_tube4_component1_x -= how_much_tube;
			position_tube4_component2_x -= how_much_tube;

			if (score_player_current > best_score)
			{		
					//fprintf(best, "%d", score_player_current);
					best_score = score_player_current;
			}

			if (position_tube1_component1_x < position_bird_component1_x && ok1 == false)
			{
				score_player_current++;
				ok1 = true;
			}

			if (position_tube2_component1_x < position_bird_component1_x && ok2 == false)
			{
				score_player_current++;
				ok2 = true;
			}

			if (position_tube3_component1_x < position_bird_component1_x && ok3 == false)
			{
				score_player_current++;
				ok3 = true;
			}

			if (position_tube4_component1_x < position_bird_component1_x && ok4 == false)
			{
				score_player_current++;
				ok4 = true;
			}

			if (position_tube1_component1_x < 0) {
				position_tube1_component1_x = 1900;
				position_tube1_component1_y = 0;
				scale_tube1_component1 = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 3));
				position_tube1_component2_x = 1900;
				position_tube1_component2_y = scale_tube1_component1 * 100 + 300;
				ok1 = false;
			}

			if (position_tube2_component1_x < 0) {
				position_tube2_component1_x = 1900;
				position_tube2_component1_y = 0;
				scale_tube2_component1 = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 3));
				position_tube2_component2_x = 1900;
				position_tube2_component2_y = scale_tube2_component1 * 100 + 300;
				ok2 = false;
			}

			if (position_tube3_component1_x < 0) {
				position_tube3_component1_x = 1900;
				position_tube3_component1_y = 0;
				scale_tube3_component1 = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 3));
				position_tube3_component2_x = 1900;
				position_tube3_component2_y = scale_tube3_component1 * 100 + 300;
				ok3 = false;
			}

			if (position_tube4_component1_x < 0) {
				position_tube4_component1_x = 1900;
				position_tube4_component1_y = 0;
				scale_tube4_component1 = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 3));
				position_tube4_component2_x = 1900;
				position_tube4_component2_y = scale_tube4_component1 * 100 + 300;
				ok4 = false;
			}

			if (score_player_current != score_player)
			{
				printf("%d\n", score_player_current);
				score_player = score_player_current;

				if (score_player_current < 12)
					ok_score = false;
			}

			if (score_player_current % 4 == 0 && score_player_current && ok_score == false)
			{
				how_much_bird++;
				how_much_tube += 3;
				how_much_jump += 10;
				ok_score = true;
			}
		}
 
		if ((position_bird_component1_x >= position_tube1_component1_x + -50 &&
			position_bird_component1_x <= position_tube1_component1_x + 50) &&
			position_bird_component1_y <= position_tube1_component1_y + scale_tube1_component1 * 100)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);			
			finish = 1;
		}
		
		if ((position_bird_component2_x >= position_tube1_component1_x + -50 &&
			position_bird_component2_x <= position_tube1_component1_x + 50) &&
			position_bird_component2_y <= position_tube1_component1_y + scale_tube1_component1 * 100)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component3_x >= position_tube1_component1_x + -30 &&
			position_bird_component3_x <= position_tube1_component1_x + 30) &&
			position_bird_component3_y <= position_tube1_component1_y + scale_tube1_component1 * 100)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component4_x >= position_tube1_component1_x + -20 &&
			position_bird_component4_x <= position_tube1_component1_x + 20) &&
			position_bird_component4_y <= position_tube1_component1_y + scale_tube1_component1 * 100)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score); 
			finish = 1;
		}

		if ((position_bird_component1_x >= position_tube2_component1_x + -50 &&
			position_bird_component1_x <= position_tube2_component1_x + 50) &&
			position_bird_component1_y <= position_tube2_component1_y + scale_tube2_component1 * 100)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component2_x >= position_tube2_component1_x + -50 &&
			position_bird_component2_x <= position_tube2_component1_x + 50) &&
			position_bird_component2_y <= position_tube2_component1_y + scale_tube2_component1 * 100)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component3_x >= position_tube2_component1_x + -30 &&
			position_bird_component3_x <= position_tube2_component1_x + 30) &&
			position_bird_component3_y <= position_tube2_component1_y + scale_tube2_component1 * 100)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component4_x >= position_tube2_component1_x + -20 &&
			position_bird_component4_x <= position_tube2_component1_x + 20) &&
			position_bird_component4_y <= position_tube2_component1_y + scale_tube2_component1 * 100)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component1_x >= position_tube3_component1_x + -50 &&
			position_bird_component1_x <= position_tube3_component1_x + 50) &&
			position_bird_component1_y <= position_tube3_component1_y + scale_tube3_component1 * 100)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component2_x >= position_tube3_component1_x + -50 &&
			position_bird_component2_x <= position_tube3_component1_x + 50) &&
			position_bird_component2_y <= position_tube3_component1_y + scale_tube3_component1 * 100)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component3_x >= position_tube3_component1_x + -30 &&
			position_bird_component3_x <= position_tube3_component1_x + 30) &&
			position_bird_component3_y <= position_tube3_component1_y + scale_tube3_component1 * 100)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component4_x >= position_tube3_component1_x + -20 &&
			position_bird_component4_x <= position_tube3_component1_x + 20) &&
			position_bird_component4_y <= position_tube3_component1_y + scale_tube3_component1 * 100)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component1_x >= position_tube4_component1_x + -50 &&
			position_bird_component1_x <= position_tube4_component1_x + 50) &&
			position_bird_component1_y <= position_tube4_component1_y + scale_tube4_component1 * 100)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component2_x >= position_tube4_component1_x + -50 &&
			position_bird_component2_x <= position_tube4_component1_x + 50) &&
			position_bird_component2_y <= position_tube4_component1_y + scale_tube4_component1 * 100)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component3_x >= position_tube4_component1_x + -30 &&
			position_bird_component3_x <= position_tube4_component1_x + 30) &&
			position_bird_component3_y <= position_tube4_component1_y + scale_tube4_component1 * 100)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component4_x >= position_tube4_component1_x + -20 &&
			position_bird_component4_x <= position_tube4_component1_x + 20) &&
			position_bird_component4_y <= position_tube4_component1_y + scale_tube4_component1 * 100)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component1_x >= position_tube1_component1_x + -50 &&
			position_bird_component1_x <= position_tube1_component1_x + 50) &&
			position_bird_component1_y >= position_tube1_component1_y + scale_tube1_component1 * 100 + 300)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component2_x >= position_tube1_component1_x + -50 &&
			position_bird_component2_x <= position_tube1_component1_x + 50) &&
			position_bird_component2_y >= position_tube1_component1_y + scale_tube1_component1 * 100 + 300)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component3_x >= position_tube1_component1_x + -30 &&
			position_bird_component3_x <= position_tube1_component1_x + 30) &&
			position_bird_component3_y >= position_tube1_component1_y + scale_tube1_component1 * 100 + 300)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component4_x >= position_tube1_component1_x + -20 &&
			position_bird_component4_x <= position_tube1_component1_x + 20) &&
			position_bird_component4_y >= position_tube1_component1_y + scale_tube1_component1 * 100 +300)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component1_x >= position_tube2_component1_x + -50 &&
			position_bird_component1_x <= position_tube2_component1_x + 50) &&
			position_bird_component1_y >= position_tube2_component1_y + scale_tube2_component1 * 100 + 300)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component2_x >= position_tube2_component1_x + -50 &&
			position_bird_component2_x <= position_tube2_component1_x + 50) &&
			position_bird_component2_y >= position_tube2_component1_y + scale_tube2_component1 * 100 + 300)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component3_x >= position_tube2_component1_x + -30 &&
			position_bird_component3_x <= position_tube2_component1_x + 30) &&
			position_bird_component3_y >= position_tube2_component1_y + scale_tube2_component1 * 100 + 300)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component4_x >= position_tube2_component1_x + -20 &&
			position_bird_component4_x <= position_tube2_component1_x + 20) &&
			position_bird_component4_y >= position_tube2_component1_y + scale_tube2_component1 * 100 + 300)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component1_x >= position_tube3_component1_x + -50 &&
			position_bird_component1_x <= position_tube3_component1_x + 50) &&
			position_bird_component1_y >= position_tube3_component1_y + scale_tube3_component1 * 100 + 300)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component2_x >= position_tube3_component1_x + -50 &&
			position_bird_component2_x <= position_tube3_component1_x + 50) &&
			position_bird_component2_y >= position_tube3_component1_y + scale_tube3_component1 * 100 + 300)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component3_x >= position_tube3_component1_x + -30 &&
			position_bird_component3_x <= position_tube3_component1_x + 30) &&
			position_bird_component3_y >= position_tube3_component1_y + scale_tube3_component1 * 100 + 300)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component4_x >= position_tube3_component1_x + -20 &&
			position_bird_component4_x <= position_tube3_component1_x + 20) &&
			position_bird_component4_y >= position_tube3_component1_y + scale_tube3_component1 * 100 + 300)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component1_x >= position_tube4_component1_x + -50 &&
			position_bird_component1_x <= position_tube4_component1_x + 50) &&
			position_bird_component1_y >= position_tube4_component1_y + scale_tube4_component1 * 100 + 300)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component2_x >= position_tube4_component1_x + -50 &&
			position_bird_component2_x <= position_tube4_component1_x + 50) &&
			position_bird_component2_y >= position_tube4_component1_y + scale_tube4_component1 * 100 + 300)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component3_x >= position_tube4_component1_x + -30 &&
			position_bird_component3_x <= position_tube4_component1_x + 30) &&
			position_bird_component3_y >= position_tube4_component1_y + scale_tube4_component1 * 100 + 300)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}

		if ((position_bird_component4_x >= position_tube4_component1_x + -20 &&
			position_bird_component4_x <= position_tube4_component1_x + 20) &&
			position_bird_component4_y >= position_tube4_component1_y + scale_tube4_component1 * 100 + 300)
		{
			printf("GAME OVER\n SCORE: %d\n", score_player_current); printf("BEST SCORE: %d", best_score);
			finish = 1;
		}
	}
	else
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(400, 500);
		modelMatrix *= Transform2D::Rotate(M_PI);
		modelMatrix *= Transform2D::Scale(1.0f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(400, 400);
		modelMatrix *= Transform2D::Rotate(M_PI);
		modelMatrix *= Transform2D::Scale(1.0f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(400, 450);
		modelMatrix *= Transform2D::Rotate(M_PI);
		modelMatrix *= Transform2D::Scale(0.6f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(400, 400);
		modelMatrix *= Transform2D::Rotate(M_PI/2);
		modelMatrix *= Transform2D::Scale(0.4f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(300, 380);
		modelMatrix *= Transform2D::Rotate(M_PI / 2);
		modelMatrix *= Transform2D::Scale(1.2f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);
		
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(600, 500);
		modelMatrix *= Transform2D::Rotate(M_PI);
		modelMatrix *= Transform2D::Scale(1.0f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(600, 450);
		modelMatrix *= Transform2D::Rotate(M_PI);
		modelMatrix *= Transform2D::Scale(1.0f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(500, 380);
		modelMatrix *= Transform2D::Rotate(M_PI / 2);
		modelMatrix *= Transform2D::Scale(1.2f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(600, 380);
		modelMatrix *= Transform2D::Rotate(M_PI / 2);
		modelMatrix *= Transform2D::Scale(1.2f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(700, 380);
		modelMatrix *= Transform2D::Rotate(M_PI / 2);
		modelMatrix *= Transform2D::Scale(1.2f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(680, 490);
		modelMatrix *= Transform2D::Rotate(-M_PI / 3);
		modelMatrix *= Transform2D::Scale(1.2f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(750, 390);
		modelMatrix *= Transform2D::Rotate(M_PI / 3);
		modelMatrix *= Transform2D::Scale(1.2f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(805, 380);
		modelMatrix *= Transform2D::Rotate(M_PI / 2);
		modelMatrix *= Transform2D::Scale(1.2f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(900, 380);
		modelMatrix *= Transform2D::Rotate(M_PI / 2);
		modelMatrix *= Transform2D::Scale(1.2f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(1000, 500);
		modelMatrix *= Transform2D::Rotate(M_PI);
		modelMatrix *= Transform2D::Scale(1.0f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(1000, 450);
		modelMatrix *= Transform2D::Rotate(M_PI);
		modelMatrix *= Transform2D::Scale(1.0f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(1000, 400);
		modelMatrix *= Transform2D::Rotate(M_PI);
		modelMatrix *= Transform2D::Scale(1.0f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(400, 300);
		modelMatrix *= Transform2D::Rotate(M_PI);
		modelMatrix *= Transform2D::Scale(1.0f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(400, 200);
		modelMatrix *= Transform2D::Rotate(M_PI);
		modelMatrix *= Transform2D::Scale(1.0f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(300, 180);
		modelMatrix *= Transform2D::Rotate(M_PI / 2);
		modelMatrix *= Transform2D::Scale(1.2f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(400, 180);
		modelMatrix *= Transform2D::Rotate(M_PI / 2);
		modelMatrix *= Transform2D::Scale(1.2f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(480, 290);
		modelMatrix *= Transform2D::Rotate(-M_PI / 3);
		modelMatrix *= Transform2D::Scale(1.2f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(550, 190);
		modelMatrix *= Transform2D::Rotate(M_PI / 3);
		modelMatrix *= Transform2D::Scale(1.2f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);


		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(700, 180);
		modelMatrix *= Transform2D::Rotate(M_PI / 2);
		modelMatrix *= Transform2D::Scale(1.2f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(800, 300);
		modelMatrix *= Transform2D::Rotate(M_PI);
		modelMatrix *= Transform2D::Scale(1.2f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(800, 250);
		modelMatrix *= Transform2D::Rotate(M_PI);
		modelMatrix *= Transform2D::Scale(1.2f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(800, 200);
		modelMatrix *= Transform2D::Rotate(M_PI);
		modelMatrix *= Transform2D::Scale(1.2f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(900, 160);
		modelMatrix *= Transform2D::Rotate(M_PI / 2);
		modelMatrix *= Transform2D::Scale(1.3f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(1000, 300);
		modelMatrix *= Transform2D::Rotate(M_PI);
		modelMatrix *= Transform2D::Scale(1.2f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(1000, 250);
		modelMatrix *= Transform2D::Rotate(M_PI);
		modelMatrix *= Transform2D::Scale(1.2f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(1000, 230);
		modelMatrix *= Transform2D::Rotate(M_PI / 2);
		modelMatrix *= Transform2D::Scale(0.6f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(880, 230);
		modelMatrix *= Transform2D::Rotate( - M_PI/6);
		modelMatrix *= Transform2D::Scale(1.4f, 0.2f);
		RenderMesh2D(meshes["dreptunghi2"], shaders["VertexColor"], modelMatrix);

	
	}
}

void Laborator3::FrameEnd()
{

}

void Laborator3::OnInputUpdate(float deltaTime, int mods)
{
	if (space == true)
	{
		start = true;

		if(k >= how_much_jump)
		{
			k = 0;
			space = false;
		}
	}

}

void Laborator3::OnKeyPress(int key, int mods)
{
	if (key == 32)
	{
		space = true;

		if (bird_position == true)
		{
			rotate_bird_component1 = 0;
			rotate_bird_component2 = 0;
			position_bird_component2_x -= 8; position_bird_component2_y += 11;
			position_bird_component3_x += 7; position_bird_component3_y += 42;
			rotate_bird_component4 = M_PI / 8;
			position_bird_component4_x += 18; position_bird_component4_y += 48;
			bird_position = false;
		}
	}

}

void Laborator3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{

}

void Laborator3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{

}

void Laborator3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event

}

void Laborator3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator3::OnWindowResize(int width, int height)
{
}
