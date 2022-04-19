#include "GameOver.h"

#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <windows.h>

#include "gl/glew.h"
#include "GLFW/glfw3.h"



extern game::EntHandle e_GameHandle;

namespace game
{

	GameOver::GameOver()
	{
		glEnable(GL_BLEND); //setup texture blend or sum
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		e_GameHandle.RegisterTexture("res/textures/gameover.png", 1);
		gameOverbg = std::make_unique<Plane>(1, glm::vec3(0, 0, 0), glm::vec2(960.0f, 540.0f));

	}

	GameOver::~GameOver()
	{

	}

	void GameOver::OnUpdate(SceneManager& sm, float deltaTime /*= 0*/)
	{
		if (GetAsyncKeyState(VK_ESCAPE) & 1)
		{
			sm.SetScene("MainMenu");
			return;
		}

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



			if (relposX > 0.873f && relposX < 0.946f && relposY > 0.035f && relposY < 0.149f)
			{
				//clicked back button
				sm.SetScene("MainMenu");
				return;
			}
			if (relposX > 0.341f && relposX < 0.56f && relposY > 0.756f && relposY < 0.886f)
			{
				//clicked restart button
				sm.SetScene("MainGame");
				return;
			}
		}
	}

	void GameOver::OnRender()
	{
		glEnable(GL_BLEND); //setup texture blend or sum
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		gameOverbg->Render();
	}

	void GameOver::OnDebugRender()
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