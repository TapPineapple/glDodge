#include "GameOver.h"

#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <windows.h>
#include <map>

#include "gl/glew.h"
#include "GLFW/glfw3.h"



extern game::EntHandle e_GameHandle;
extern game::GlobalScores e_ScoreData;

namespace game
{
	GameOver::GameOver()
	{
		glEnable(GL_BLEND); //setup texture blend or sum
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//register textures
		e_GameHandle.RegisterTexture("res/textures/gameover.png", 1);

		gameOverbg = std::make_unique<Plane>(1, glm::vec3(0, 0, 0), glm::vec2(960.0f, 540.0f));


		//inst text
		leaderboardText = std::make_unique<Text>("LEADERBOARD", 600.0f, 360.0f, glm::vec3(1.0f, 1.0f, 1.0f), 0.9f, "res/fonts/8bitOperatorPlus8-Regular.ttf");

		scoreText = std::make_unique<Text>("Score", 70.0f, 205.0f, glm::vec3(1.0f, 1.0f, 1.0f), 2.9f, "res/fonts/8bitOperatorPlus8-Regular.ttf");
		
		for (int i = 0; i < 5; i++)
		{
			lbPlaces.push_back(std::make_unique<Text>("", 600.0f, 300.0f - (i * 35.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.9f, "res/fonts/8bitOperatorPlus8-Regular.ttf"));
		}

		//setup score text
		std::string scoreStr;
		scoreStr.append(std::to_string(e_ScoreData.lastScore));
		scoreText->SetText(scoreStr);

		//setup leaderboard text
		if (e_ScoreData.m_LeaderboardData.size() < 5)
		{
			e_ScoreData.m_LeaderboardData.insert({ e_ScoreData.lastScore, scoreStr });
		}
		else
		{
			int minKey = INT_MAX;
			for (auto const& [key, val] : e_ScoreData.m_LeaderboardData) //ooo so modern :O
			{
				if (key < minKey)
				{
					minKey = key;
				}
			}
			if (e_ScoreData.lastScore > minKey)
			{
				e_ScoreData.m_LeaderboardData.erase(minKey); //removes smallest score
				e_ScoreData.m_LeaderboardData.insert({ e_ScoreData.lastScore, scoreStr }); //adds new score to map
			}

		}
		//time to update leaderboard text
		int _i = 0;
		std::map<int, std::string>::reverse_iterator it;
		for (it = e_ScoreData.m_LeaderboardData.rbegin(); it != e_ScoreData.m_LeaderboardData.rend(); it++)
		{
			if (it->first > 0)
			{
				std::string lbStr;
				lbStr.append(std::to_string(_i + 1));
				lbStr.append(". ");
				lbStr.append(std::to_string(it->first));
				lbPlaces[_i]->SetText(lbStr);
				_i++;
			}
		}
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
		scoreText->Render();
		leaderboardText->Render();

		for (auto& text : lbPlaces)
		{
			text->Render();
		}
	}

	void GameOver::OnDebugRender()
	{

		#ifdef _DEBUG
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
#endif
	}
}