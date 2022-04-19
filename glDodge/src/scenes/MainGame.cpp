#include "MainGame.h"


#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <filesystem>
#include <windows.h>

#include "gl/glew.h"

extern game::EntHandle e_GameHandle;

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<double> random(0, 1);

namespace game
{
	
	MainGame::MainGame()
		: m_drawCount(0.0f), m_SceneTranslate(0.0f), m_Score(0.0f), m_MaxHozizontalSpeed(20.0f), m_Acceleration(200.0f), m_SceneSpeed(0.0f), m_CubeColor(0.0f)
	{
		//setup

		glEnable(GL_BLEND); //setup texture blend or sum
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		e_GameHandle.RegisterTexture("res/textures/bg1.png", 1);
		e_GameHandle.RegisterTexture("res/textures/cube1.png", 2);
		e_GameHandle.RegisterTexture("res/textures/vapor1.png", 3); //credit https://opengameart.org/content/vaporwave-grid
		e_GameHandle.RegisterTexture("res/textures/bg2.png", 4);
		e_GameHandle.RegisterTexture("res/textures/cube2.png", 5);
		e_GameHandle.RegisterTexture("res/textures/vapor2.png", 6);
		e_GameHandle.RegisterTexture("res/textures/bg3.png", 7);
		e_GameHandle.RegisterTexture("res/textures/cube3.png", 8);
		e_GameHandle.RegisterTexture("res/textures/vapor3.png", 9);

		m_FloorTexID = 3;
		m_CubeTexID = 2;
	
		
		m_background = std::make_unique<Plane>(1, glm::vec3(0.0f, -100.0f, 0.0f), glm::vec2(960.0f, 740.0f));


		for (float i = 0; i < 4.0f; i += 1.0f) //create floor
		{
			for (float j = 0; j < 4.0f; j += 1.0f)
			{                                                                                                                         
				m_floor.push_back(std::make_unique<Cube>(3, glm::vec3((-c_FloorSize * 2) + (i * c_FloorSize), -3.0f, -((j * c_FloorSize) + c_FloorSize)), glm::vec3(c_FloorSize, 0.5f, c_FloorSize)));
			}
		}

		for (int i = 0; i < c_CubeCount; i++) //create cubes
		{
			m_cubes.push_back(std::make_unique<Cube>(2, glm::vec3((random(mt) * c_FloorSize * 4) - c_FloorSize * 2, -2.5f, -(random(mt) * c_FloorSize * 4 + 50)), glm::vec3(3.5f, 3.5f, 3.5f)));
		}

	}

	MainGame::~MainGame()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void MainGame::OnUpdate(SceneManager& sm, float deltaTime /*= 0*/)
	{

		//input
		if (GetAsyncKeyState(VK_LEFT) && m_SceneTranslate < m_MaxHozizontalSpeed)
		{
			m_SceneTranslate += m_Acceleration * deltaTime;

		} 
		else if (GetAsyncKeyState(VK_RIGHT) && m_SceneTranslate > -m_MaxHozizontalSpeed)
		{
			
			m_SceneTranslate -= m_Acceleration * deltaTime;
		}
		if (!GetAsyncKeyState(VK_RIGHT) && !GetAsyncKeyState(VK_LEFT))
		{
			if (m_SceneTranslate > 0.0f)
			{
				m_SceneTranslate -= m_Acceleration * deltaTime;
			}
			if (m_SceneTranslate < 0.0f)
			{
				m_SceneTranslate += m_Acceleration * deltaTime;
			}
			if (m_SceneTranslate <= 0.1f) //remove drift
			{
				m_SceneTranslate = 0.0f;
			}
		}

		if (GetAsyncKeyState(VK_ESCAPE) & 1)
		{
			sm.SetScene("MainMenu");
			return;
		}

		//scene updating
		

		for (int i = 0; i < m_floor.size(); i++) //move floor
		{
			m_floor[i]->SetTex(m_FloorTexID);
			m_floor[i]->TranslateBy(glm::vec3(m_SceneTranslate * deltaTime, 0.0f, m_SceneSpeed * deltaTime));
			if (m_floor[i]->m_Translate.z > c_FloorSize) //rests floor once it's behind the camera
			{
				m_floor[i]->m_Translate.z = -(c_FloorSize * 3); 
			}

			if (m_floor[i]->m_Translate.x < -(c_FloorSize * 2)) //makes floor never end
			{
				m_floor[i]->m_Translate.x = (c_FloorSize * 2);
			}

			if (m_floor[i]->m_Translate.x > (c_FloorSize * 2))
			{
				m_floor[i]->m_Translate.x = -(c_FloorSize * 2);
			}
		}

		//upate score
		m_Score += m_ScoreRate * deltaTime;

		//update scene speed
		if (m_Score <= 50.0) //easy
		{
			
			if (m_SceneSpeed < 30.0f)
				m_SceneSpeed += c_LevelTransportSpeed * deltaTime;

		}
		else if (m_Score >= 50.0f && m_Score <= 100.0f) //medium
		{
			m_FloorTexID = 6;
			m_CubeTexID = 5;
			
			m_background->SetTex(4);
			m_background->m_Translate.y = -30.0f;
			//m_background->SetColor(glm::vec4(0.0f, 200.0f, 0.0f, 0.0f));

			if (m_SceneSpeed < 50.0f)
				m_SceneSpeed += c_LevelTransportSpeed * deltaTime;
			//m_CubeColor = { 0.0f, 139.0f, 10.0f, 0.0f };


		}
		else if (m_Score >= 100.0f) //hard
		{
			m_FloorTexID = 9;
			m_CubeTexID = 8;
			m_background->m_Translate.y = -50.0f;

			m_background->SetTex(7);
			//m_CubeColor = { 251.0f, 0.0f, 0.0f, 0.0f };
			if (m_SceneSpeed < 100.0f)
				m_SceneSpeed += c_LevelTransportSpeed * deltaTime;
		}

		for (int i = 0; i < m_cubes.size(); i++) //move cubes
		{
			m_cubes[i]->SetTex(m_CubeTexID);
			m_cubes[i]->TranslateBy(glm::vec3(m_SceneTranslate * deltaTime, 0.0f, m_SceneSpeed * deltaTime));

			if (m_cubes[i]->m_Translate.z > 5.0f)
			{
				m_cubes[i]->m_Translate.z = -(c_FloorSize * 4);
				m_cubes[i]->m_Translate.x = (random(mt) * c_FloorSize * 4) - c_FloorSize * 2;
			}

			
			if (m_cubes[i]->m_Translate.z > -3.5f && m_cubes[i]->m_Translate.z < 0.0f && m_cubes[i]->m_Translate.x > -3.5f && m_cubes[i]->m_Translate.x < 0.0f)
			{
				//if collison detected
				sm.SetScene("GameOver");
				return;
			}

			if (m_Score >= 150.0f)
			{
				sm.SetScene("GameWin");
				return;
			}
			
		}

	}

	void MainGame::OnRender()
	{
		glClearColor(0.3f, 0.0f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST); //for background
		m_background->Render();
		glEnable(GL_DEPTH_TEST);

		m_drawCount = 0;
		for (auto ent : e_GameHandle.m_EntArry)
		{
			m_drawCount++;
			ent->Render();
		}

	}

	void MainGame::OnDebugRender()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowBorderSize = 0.0f;
	
		
		ImGui::SetNextWindowBgAlpha(0.0f); // Transparent background
 		ImGui::Begin("Score", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
		ImVec2 work_size = viewport->WorkSize;
		ImVec2 window_pos, window_pos_pivot;
		window_pos.x = (work_pos.x + 20);
		window_pos.y = (work_pos.y + 10);
		ImGui::SetWindowFontScale(work_size.x / 200);
		ImGui::SetWindowPos(window_pos);

 		ImGui::Text("SCORE:%.f", m_Score);
 		ImGui::End();
		
		#ifdef _DEBUG
		ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::ColorEdit4("Color", &m_CubeColor.r);
		//ImGui::SliderFloat3("Translate1", &translate1.x, -10.0f, 10.0f);
		ImGui::Text("DrawCount %i", m_drawCount);
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(GetActiveWindow(), &p);
		ImGui::Text("Cursor Pos: %i, %i", p.x, p.y);
		ImGui::Text("Score: %.f", m_Score);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
#endif
	}

}