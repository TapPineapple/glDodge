#pragma once
#include <memory>
#include <vector>
#include <unordered_map>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "VertexBufferLayout.h"


namespace game
{
	struct EntHandle //entity handle struct
	{
		EntHandle()
		{
			m_CubeShader = std::make_unique<Shader>();
		}
		std::unique_ptr<Shader> m_CubeShader;
		std::vector<std::unique_ptr<Entity>> m_EntArray;
		std::unordered_map<std::string, std::unique_ptr<Texture>> m_TextureMap; //the cpp std library is ugly

		void RegisterTexture(std::string name, std::string& path)
		{
			m_TextureMap.insert(std::make_pair<std::string&, std::unique_ptr<Texture>>(name, std::make_unique<Texture>(path)));
		}
	};

	class Entity
	{
	public:
		Entity() {}
		virtual ~Entity() {}
		virtual void Render() const {}
	private:
	};

	//example cube creation 
	// std::vector<Entity>entArray; 
	//Cube CubeClass = new CubeClass(entArray, inital position data, texID) //constructor will push_back every ent created

	class Cube : public Entity //i want this to be pushed into an array of
	{
	public:
		Cube(EntHandle& cubeHandle, int texID, glm::vec3 pos, glm::vec3 size, glm::vec3 rot);
		~Cube();

		void Render() const override;
		void Translate(glm::vec3 pos);
		void Translate(glm::vec3 pos, glm::vec3 rot);

	private:
		int m_TexID; //the ID of the texture in custom sprite sheet

		glm::mat4 m_Model;
		glm::mat4 m_View;
		glm::mat4 m_Proj;

		std::unique_ptr<VertexArray> m_VertexArr; //abstracted vertex array class
		std::unique_ptr<VertexBuffer> m_VertexBuf; //abstracted vertext buffer class
		
	};
}