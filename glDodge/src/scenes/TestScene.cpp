#include "TestScene.h"

#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "gl/glew.h"



namespace game
{

	TestScene::TestScene()
	{
		glEnable(GL_BLEND); //setup texture blend or sum
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		handle.m_CubeShader = std::make_unique<Shader>("res/shaders/cube.shader");
		handle.m_DefaultProjection = glm::perspective(glm::radians(70.0f), 960.0f / 540.0f, 0.1f, 100.0f);
		
		Cube1 = std::make_unique<Cube>(handle, 1, glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0, 0, 0));
		handle.RegisterTexture("res/textures/test.png" , 1);
		Cube1->Translate(glm::vec3(0.0f, 0.0f, -3.0f));

		Cube2 = std::make_unique<Cube>(handle, 1, glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0, 0, 0));
		handle.RegisterTexture("res/textures/test.png", 1);
		Cube2->Translate(glm::vec3(0.0f, 0.0f, -3.0f));

	}

	TestScene::~TestScene()
	{

	}

	void TestScene::OnUpdate(SceneManager& sm, float deltaTime /*= 0*/)
	{
		Cube1->Translate(translate1);
		Cube2->Translate(translate2);
	}

	void TestScene::OnRender()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		for (auto ent : handle.m_EntArry)
		{
			ent->Render();
		}
	}

	void TestScene::OnDebugRender()
	{
		ImGui::SliderFloat3("TranslateA", &translate1.x, -5.0f, 5.0f);
		ImGui::SliderFloat3("TranslateB", &translate2.x, -5.0f, 5.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}