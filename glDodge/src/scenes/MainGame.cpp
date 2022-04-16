#include "MainGame.h"

#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <windows.h>

#include "gl/glew.h"

extern game::EntHandle e_GameHandle;

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


//  		for (float i = 0.0f; i < 10.0f; i += 1.0f)
//  		{
//  			for (float j = 0.0f; j < 10.0f; j += 1.0f)
//  			{
//  				float x = (100.0f * i) - 600.0f;
//  				float z = (100.0f * j) - 1100.0f;
//  				floor.push_back(std::make_unique<Cube>(1, glm::vec3(x, -5.0f, z), glm::vec3(100.0f, 0.5f, 100.0f)));
//  			}
//  		}
	
 		for (float i = 0; i < 5.0f; i += 1.0f)
 		{
			for (float j = 0; j < 3.0f; j += 1.0f)
			{
				floor.push_back(std::make_unique<Cube>(2, glm::vec3(-250.0f + (i * 100.0f), -3.0f, (j * -100.0f) - 100.0f), glm::vec3(100.0f, 0.5f, 100.0f)));
			}
 		}

		//floor1 = std::make_unique<Cube>(1, glm::vec3(-100.0f, -5.0f, -100.0f), glm::vec3(200.0f, 0.5f, 100.0f));
		//floor2 = std::make_unique<Cube>(1, glm::vec3(-100.0f, -5.0f, -100.0f), glm::vec3(100.0f, 0.5f, 100.0f));
		//floor3 = std::make_unique<Cube>(1, glm::vec3(0.0f, -5.0f, -100.0f), glm::vec3(100.0f, 0.5f, 100.0f));
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

		for (int i = 0; i < floor.size(); i++)
		{
			floor[i]->RelTranslate(glm::vec3(m_SceneTranslate, 0.0f, 0.0f));
		}
		//o_Floor->Translate(translate1);
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
		ImGui::SliderFloat3("Translate", &translate1.x, -10.0f, 10.0f);
		ImGui::Text("DrawCount %i", m_drawCount);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

}