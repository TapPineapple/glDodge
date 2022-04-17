#include "MainGame.h"

#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <windows.h>

#include "gl/glew.h"

extern game::EntHandle e_GameHandle;

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<double> random(0, 1);

namespace game
{
	
	MainGame::MainGame()
		: m_drawCount(0.0f), m_SceneTranslate(0.0f)
	{
		//setup

		glEnable(GL_BLEND); //setup texture blend or sum
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		e_GameHandle.RegisterTexture("res/textures/test.png", 1);
		e_GameHandle.RegisterTexture("res/textures/vapor.jpg", 2);
	
		
		for (float i = 0; i < 4.0f; i += 1.0f) //create floor
		{
			for (float j = 0; j < 4.0f; j += 1.0f)
			{                                                                                                                         
				m_floor.push_back(std::make_unique<Cube>(2, glm::vec3((-c_FloorSize * 2) + (i * c_FloorSize), -3.0f, -((j * c_FloorSize) + c_FloorSize)), glm::vec3(c_FloorSize, 0.5f, c_FloorSize)));
			}
		}

		for (int i = 0; i < c_CubeCount; i++) //create cubes
		{
			m_cubes.push_back(std::make_unique<Cube>(2, glm::vec3((random(mt) * c_FloorSize * 4) - c_FloorSize * 2, -2.5f, -(random(mt) * c_FloorSize * 4 + 50)), glm::vec3(3.5f, 3.5f, 3.5f)));
		}
		
	}

	MainGame::~MainGame()
	{

	}

	void MainGame::OnUpdate(SceneManager& sm, float deltaTime /*= 0*/)
	{
		m_SceneTranslate = 0; //improve this
		if (GetAsyncKeyState(VK_LEFT))
			m_SceneTranslate = 20.0f * deltaTime;
		if (GetAsyncKeyState(VK_RIGHT))
			m_SceneTranslate = -20.0f * deltaTime;

		for (int i = 0; i < m_floor.size(); i++) //move floor
		{
			m_floor[i]->TranslateBy(glm::vec3(m_SceneTranslate, 0.0f, m_SceneSpeed * deltaTime));
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

		for (int i = 0; i < m_cubes.size(); i++) //move cubes
		{
			m_cubes[i]->TranslateBy(glm::vec3(m_SceneTranslate, 0.0f, m_SceneSpeed * deltaTime));
			m_cubes[i]->SetColor(m_CubeColor);

			if (m_cubes[i]->m_Translate.z > 5.0f)
			{
				m_cubes[i]->m_Translate.z = -(c_FloorSize * 4);
				m_cubes[i]->m_Translate.x = (random(mt) * c_FloorSize * 4) - c_FloorSize * 2;
			}


			if (m_cubes[i]->m_Translate.z > -3.5f && m_cubes[i]->m_Translate.z < 0.0f && m_cubes[i]->m_Translate.x > -3.5f && m_cubes[i]->m_Translate.x < 0.0f)
				sm.SetScene("MainGame");
		}

	}

	void MainGame::OnRender()
	{
		glClearColor(0.3f, 0.0f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
		ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::ColorEdit4("Color", &m_CubeColor.r);
		//ImGui::SliderFloat3("Translate1", &translate1.x, -10.0f, 10.0f);
		ImGui::Text("DrawCount %i", m_drawCount);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

}