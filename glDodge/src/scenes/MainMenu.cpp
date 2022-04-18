#include "MainMenu.h"

#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <windows.h>
#include <WindowsX.h>

#include "gl/glew.h"

extern game::EntHandle e_GameHandle;

namespace game
{

	MainMenu::MainMenu()

	{
		glEnable(GL_BLEND); //setup texture blend or sum
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		e_GameHandle.RegisterTexture("res/textures/mainmenu.png", 1);
		mm = std::make_unique<Plane>(1, glm::vec3(0,0,0), glm::vec2(960.0f, 540.0f));
	}

	MainMenu::~MainMenu()
	{

	}

	void MainMenu::OnUpdate(SceneManager& sm, float deltaTime /*= 0*/)
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			RECT rect;
			int width = 0;
			int height = 0;;
			if (GetWindowRect(GetActiveWindow(), &rect))
			{
				width = rect.right - rect.left;
				height = rect.bottom - rect.top;
			}

			POINT p;
			GetCursorPos(&p);
			ScreenToClient(GetActiveWindow(), &p);

			float relposX = static_cast<float>(p.x) / width;
			float relposY = static_cast<float>(p.y) / height;

			if (relposX > 0.335f && relposX < 0.656f && relposY > 0.514f && relposY < 0.652f)
			{
				//clicked Play
				sm.SetScene("MainGame");
			}

			if (relposX > 0.886f && relposX < 0.976f && relposY > 0.802f && relposY < 0.942f)
			{
				//clicked Help button
				sm.SetScene("HelpMenu");
			}

		}

	}

	void MainMenu::OnRender()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		mm->Render();
	}

	void MainMenu::OnDebugRender()
	{

		ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		RECT rect;
		int width = 0;
		int height = 0;;
		if (GetWindowRect(GetActiveWindow(), &rect))
		{
			width = rect.right - rect.left;
			height = rect.bottom - rect.top;
		}

		POINT p;
		GetCursorPos(&p);
		ScreenToClient(GetActiveWindow(), &p);

		float relposX = static_cast<float>(p.x) / width;
		float relposY = static_cast<float>(p.y) / height;
		ImGui::Text("Cursor Pos: %f, %f", relposX, relposY);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
}