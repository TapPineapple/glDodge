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
		~SceneManager()
		{
			delete m_CurrentScene;
		}

		template<typename T>
		void RegisterScene(const std::string& name)
		{
			std::cout << "[*] Registering Scene: " << name << "\n";
			m_Scenes.push_back(std::make_pair(name, []() { return new T; }));
		}
		
		void SetScene(const std::string& name)
		{
			for (auto index : m_Scenes)
			{
				if (index.first.compare(name) == 0)
				{
					delete m_CurrentScene;
					m_CurrentScene = index.second();
				}
			}
		}

		Scene* m_CurrentScene = nullptr;
	private:
		std::vector <std::pair<std::string, std::function<Scene*()>>> m_Scenes;

	};

}