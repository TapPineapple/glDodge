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
		template<typename T>
		void RegisterScene(const std::string& name)
		{
			std::cout << "[*] Registering Scene: " << name << "\n";
			m_Scenes.push_back(std::make_pair(name, []() { return new T; }));
		}
		
		std::vector <std::pair<std::string, std::function<Scene* ()>>> m_Scenes;
	};

}