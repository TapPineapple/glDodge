#include "HelpMenu.h"

#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <windows.h>

#include "gl/glew.h"

extern game::EntHandle e_GameHandle;

namespace game
{

	HelpMenu::HelpMenu()

	{
		glEnable(GL_BLEND); //setup texture blend or sum
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		e_GameHandle.RegisterTexture("res/textures/info.png", 1);
		hm = std::make_unique<Plane>(1, glm::vec3(0, 0, 0), glm::vec2(960.0f, 540.0f));


	}

	HelpMenu::~HelpMenu()
	{

	}

	void HelpMenu::OnUpdate(SceneManager& sm, float deltaTime /*= 0*/)
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

			if (relposX > 0.028f && relposX < 0.118f && relposY > 0.801f && relposY < 0.941f)
			{
				//clicked back button
				sm.SetScene("MainMenu");
			}
		}
	}

	void HelpMenu::OnRender()
	{
		glEnable(GL_BLEND); //setup texture blend or sum
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		hm->Render();
	}

	void HelpMenu::OnDebugRender()
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