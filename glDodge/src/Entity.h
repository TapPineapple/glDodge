#pragma once

#include <vector>
#include <memory>
#include <map>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "VertexBufferLayout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace game
{

	class EntHandle;

	class Entity
	{
	public:
		Entity() {}
		virtual ~Entity() {}
		virtual void Render() {}
	private:
	};

	//example cube creation 
	// std::vector<Entity>entArray; 
	//Cube CubeClass = new CubeClass(entArray, inital position data, texID) //constructor will push_back every ent created

	class Cube : public Entity //i want this to be pushed into an array of
	{
	public:

		//************************************
		// Method:    Cube
		// FullName:  game::Cube::Cube
		// Access:    public 
		// Returns:   
		// Qualifier:
		// Parameter: EntHandle & handle
		// Parameter: int texID
		// Parameter: glm::vec3 pos
		// Parameter: glm::vec3 size
		// Parameter: glm::vec3 rot
		//************************************
		Cube(EntHandle& handle, int texID, glm::vec3 pos, glm::vec3 size, glm::vec3 rot);
		~Cube();

		void Render() override;
		void Translate(glm::vec3 pos);
		void Translate(glm::vec3 pos, glm::vec3 rot);

	private:
		EntHandle& m_Handle;
		int m_TexID;

		glm::mat4 m_Model;
		glm::mat4 m_View;

		glm::vec3 m_Translate;

		std::unique_ptr<VertexArray> m_VertexArr; //abstracted vertex array class
		std::unique_ptr<VertexBuffer> m_VertexBuf; //abstracted vertext buffer class
		
	};


	class EntHandle
	{
	public:
		std::vector<Entity*> m_EntArry; //array of all ents
		
		std::unique_ptr<Shader> m_CubeShader; //m_CubeShader = std::make_unique<Shader>("res/shaders/cube.shader"); do this in the other area
		glm::mat4 m_DefaultProjection = glm::perspective(glm::radians(80.0f), 960.0f / 540.0f, 0.1f, 100.0f);


		std::map<int, std::unique_ptr<Texture>> m_TexMap; //map of all textures
		void RegisterTexture(std::string path, int texID)
		{
			m_TexMap[texID] = std::make_unique<Texture>(path);
		}
	};
}
