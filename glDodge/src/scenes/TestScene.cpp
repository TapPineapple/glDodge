#include "TestScene.h"
#include <imgui/imgui.h>

#include "gl/glew.h"

namespace game
{

	TestScene::TestScene()
	{

	}

	TestScene::~TestScene()
	{

	}

	void TestScene::OnUpdate(SceneManager& sm, float deltaTime /*= 0*/)
	{
		glClearColor(0.3f, 0.5f, 0.0f, 1.0f);
	}

	void TestScene::OnRender()
	{

	}

	void TestScene::OnDebugRender()
	{
		ImGui::Begin("Collapse V2 - tap#0061");
		ImGui::BeginTabBar("test");
		if (ImGui::BeginTabItem("Aimbot"))
		{
			bool test = 0;
			ImGui::Checkbox("Aimbot", &test);
			float fov = 180.0f;
			ImGui::SliderFloat("FOV", &fov, 360, 0);
		}

		ImGui::BeginTabItem("Visuals");
		ImGui::BeginTabItem("Visuals");
		ImGui::EndTabItem();
	
		ImGui::EndTabBar();

		ImGui::End();
	}
}