#pragma once
#include <memory>
#include <vector>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "VertexBufferLayout.h"


namespace game
{
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
		Cube(std::vector<Entity> entArray, glm::vec3 pos, glm::vec3 size, glm::vec3 rot, int texID);
		~Cube();

		void Render() const override;
		void Translate(glm::vec3 pos);
		void Translate(glm::vec3 pos, glm::vec3 rot);

	private:
		int m_TexID; //the ID of the texture in custom sprite sheet

		std::unique_ptr<VertexArray> m_VertexArr; //abstracted vertex array class
		std::unique_ptr<VertexBuffer> m_VertexBuf; //abstracted vertext buffer class
		std::unique_ptr<Shader> m_Shader; //abstracted shader class
		std::unique_ptr<Texture> m_Texture; //abstracted texture class
	};
}