#pragma once
#include <functional>
#include <iostream>
#include <vector>

#include "Scene.h"

namespace game
{
	class SceneManager 
	{
	public:
		SceneManager(Scene*& currentScene)
			: m_CurrentScene(currentScene)
		{}

		template<typename T>
		void RegisterScene(const std::string& name)
		{
			std::cout << "[*] Registering Scene: " << name << "\n";
			m_Tests.push_back(std::make_pair(name, []() {return new T; }));
		}
	private:
		Scene*& m_CurrentScene;
		std::vector <std::pair<std::string, std::function<Scene*()>>> m_Tests;

	};

}