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
	{
		//setup
		glEnable(GL_BLEND); //setup texture blend or sum
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	MainGame::~MainGame()
	{

	}

	void MainGame::OnUpdate(SceneManager& sm, float deltaTime /*= 0*/)
	{
		if (GetAsyncKeyState(VK_END))
			sm.SetScene("TestScene");
	}

	void MainGame::OnRender()
	{
		glClearColor(0.5f, 0.0f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		for (auto ent : e_GameHandle.m_EntArry)
		{
			ent->Render();
		}
	}

	void MainGame::OnDebugRender()
	{

	}

}