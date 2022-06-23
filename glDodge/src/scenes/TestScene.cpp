#include "TestScene.h"

#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <windows.h>

#include "gl/glew.h"

extern game::EntHandle e_GameHandle;

namespace game
{


	TestScene::TestScene()
	
	{
		glEnable(GL_BLEND); //setup texture blend or sum
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		e_GameHandle.RegisterTexture("res/textures/test.png", 1);
		Cube1 = std::make_unique<Cube>(1, glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f));
		
		Cube1->TranslateTo(glm::vec3(0.0f, 0.0f, -3.0f));

		Cube2 = std::make_unique<Cube>(1, glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f));
		Cube2->TranslateTo(glm::vec3(1.0f, 0.0f, -3.0f));

	}

	TestScene::~TestScene()
	{

	}

	void TestScene::OnUpdate(SceneManager& sm, float deltaTime /*= 0*/)
	{
		Cube1->TranslateTo(glm::vec3(cos(glfwGetTime()), 1.0f, -3.0f));
		Cube2->TranslateTo(glm::vec3(sin(glfwGetTime()), -1.0f, -3.0f));
		//Cube2->Translate(translate2);
		if (GetAsyncKeyState(VK_END) & 1)
			sm.SetScene("MainGame");
	}

	void TestScene::OnRender()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		for (auto ent : e_GameHandle.m_EntArry)
		{
			ent->Render();
		}
	}

	void TestScene::OnDebugRender()
	{
		
		ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
}