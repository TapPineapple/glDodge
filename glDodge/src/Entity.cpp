#include "Entity.h"
#include <filesystem>

extern game::EntHandle e_GameHandle;


namespace game
{
	Cube::Cube(int texID, glm::vec3 _pos, glm::vec3 size)
		: m_TexID(texID), m_Model(glm::mat4(1.0f)), m_View(glm::mat4(1.0f)), m_Translate(_pos)
	{
		
		glm::vec3 pos(0.0f);
		float vertices[] = {

			//x             //y             //z              /texture pos
			pos.x,          pos.y,          pos.z,           0.0f, 0.0f,
			pos.x + size.x, pos.y,          pos.z,           1.0f, 0.0f,
			pos.x + size.x, pos.y + size.y, pos.z,           1.0f, 1.0f,
			pos.x + size.x, pos.y + size.y, pos.z,           1.0f, 1.0f,
			pos.x,          pos.y + size.y, pos.z,           0.0f, 1.0f,
			pos.x,          pos.y,          pos.z,           0.0f, 0.0f,
												
			pos.x,          pos.y,          pos.z + size.z,  0.0f, 0.0f,
			pos.x + size.x, pos.y,          pos.z + size.z,  1.0f, 0.0f,
			pos.x + size.x, pos.y + size.y, pos.z + size.z,  1.0f, 1.0f,
			pos.x + size.x, pos.y + size.y, pos.z + size.z,  1.0f, 1.0f,
			pos.x,          pos.y + size.y, pos.z + size.z,  0.0f, 1.0f,
			pos.x,          pos.y,          pos.z + size.z,  0.0f, 0.0f,
												
			pos.x,          pos.y + size.y, pos.z + size.z,  1.0f, 0.0f,
			pos.x,          pos.y + size.y, pos.z,           1.0f, 1.0f,
			pos.x,          pos.y,          pos.z,           0.0f, 1.0f,
			pos.x,          pos.y,          pos.z,           0.0f, 1.0f,
			pos.x,          pos.y,          pos.z + size.z,  0.0f, 0.0f,
			pos.x,          pos.y + size.y, pos.z + size.z,  1.0f, 0.0f,
												
			pos.x + size.x, pos.y + size.y, pos.z + size.z,  1.0f, 0.0f,
			pos.x + size.x, pos.y + size.y, pos.z,           1.0f, 1.0f,
			pos.x + size.x, pos.y,          pos.z,           0.0f, 1.0f,
			pos.x + size.x, pos.y,          pos.z,           0.0f, 1.0f,
			pos.x + size.x, pos.y,          pos.z + size.z,  0.0f, 0.0f,
			pos.x + size.x, pos.y + size.y, pos.z + size.z,  1.0f, 0.0f,
												
			pos.x,          pos.y,          pos.z,           0.0f, 1.0f,
			pos.x + size.x, pos.y,          pos.z,           1.0f, 1.0f,
			pos.x + size.x, pos.y,          pos.z + size.z,  1.0f, 0.0f,
			pos.x + size.x, pos.y,          pos.z + size.z,  1.0f, 0.0f,
			pos.x,          pos.y,          pos.z + size.z,  0.0f, 0.0f,
			pos.x,          pos.y,          pos.z,           0.0f, 1.0f,
												
			pos.x,          pos.y + size.y, pos.z,           0.0f, 1.0f,
			pos.x + size.x, pos.y + size.y, pos.z,           1.0f, 1.0f,
			pos.x + size.x, pos.y + size.y, pos.z + size.z,  1.0f, 0.0f,
			pos.x + size.x, pos.y + size.y, pos.z + size.z,  1.0f, 0.0f,
			pos.x,          pos.y + size.y, pos.z + size.z,  0.0f, 0.0f,
			pos.x,          pos.y + size.y, pos.z,           0.0f, 1.0f
		};
		
		m_VertexArr = std::make_unique<VertexArray>();
		m_VertexBuf = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));

		VertexBufferLayout layout{};
		m_VertexArr->Bind();
		layout.Push<float>(3); //vec3 position
		layout.Push<float>(2); //tex coords
		m_VertexArr->AddBuffer(*m_VertexBuf, layout);

		e_GameHandle.m_EntArry.push_back(this); //this might have to turn into a map later so that when the deconstructor is called it gets removed from the array
		
	}

	Cube::~Cube()
	{
		for (int i = 0; i < e_GameHandle.m_EntArry.size(); i++)
		{
			if (e_GameHandle.m_EntArry[i] == this)
				e_GameHandle.m_EntArry.erase(e_GameHandle.m_EntArry.begin() + i); //idk if this works
		}

	}

	void Cube::Render()
	{
		e_GameHandle.m_TexMap[m_TexID]->Bind(); //bind texture
		e_GameHandle.m_CubeShader->Bind(); //bind shader

		//m_Model = glm::rotate(m_Model, 0, glm::vec3(0.5f, 1.0f, 0.0f));
		m_View = glm::translate(glm::mat4(1.0f), m_Translate);

		e_GameHandle.m_CubeShader->SetUniformMat4f("model", m_Model);
		e_GameHandle.m_CubeShader->SetUniformMat4f("view", m_View);
		e_GameHandle.m_CubeShader->SetUniformMat4f("projection", e_GameHandle.m_DefaultProjection);

		e_GameHandle.m_CubeShader->SetUniform4f("u_Color", m_ColorShift);

		m_VertexArr->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);

	}

	void Cube::TranslateTo(glm::vec3 pos)
	{
		m_Translate = pos;
	}

	void Cube::TranslateBy(glm::vec3 pos)
	{
		m_Translate += pos;
	}

	void Cube::SetTex(int texID)
	{
		m_TexID = texID;
	}

	void Cube::SetColor(glm::vec4 color)
	{
		m_ColorShift = color;
	}

	/*---------------------------------------------------*/

	Plane::Plane(int texID, glm::vec3 _pos, glm::vec2 size)
		: m_TexID(texID), m_Translate(_pos)
	{
		glm::vec3 pos = glm::vec3(0.0f);
		float vertices[16] =
		{
			pos.x,          pos.y,          0.0f, 0.0f, //0
			pos.x + size.x, pos.y,          1.0f, 0.0f, //1
			pos.x + size.x, pos.y + size.y, 1.0f, 1.0f,//2
			pos.x,          pos.y + size.y, 0.0f, 1.0f //3

		};
		unsigned int indices[6] =
		{
			0, 1, 2,
			2, 3, 0
		};

		m_VertexArr = std::make_unique<VertexArray>();
		m_VertexBuf = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
		m_IndexBuf = std::make_unique<IndexBuffer>(indices, sizeof(indices));

		VertexBufferLayout layout{};
		m_VertexArr->Bind();
		layout.Push<float>(2); //vec2 position
		layout.Push<float>(2); //tex coords
		m_VertexArr->AddBuffer(*m_VertexBuf, layout);

		//e_GameHandle.m_EntArry.push_back(this); 
	}

	Plane::~Plane()
	{
		for (int i = 0; i < e_GameHandle.m_EntArry.size(); i++)
		{ 
			//removes entity from global entity list when it's destructor is called
			if (e_GameHandle.m_EntArry[i] == this)
				e_GameHandle.m_EntArry.erase(e_GameHandle.m_EntArry.begin() + i);
		}
	}

	void Plane::Render()
	{
		e_GameHandle.m_TexMap[m_TexID]->Bind(); //bind texture
		e_GameHandle.m_PlaneShader->Bind(); //bind shader

		m_Model = glm::translate(glm::mat4(1.0f), m_Translate);
		m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		e_GameHandle.m_PlaneShader->SetUniformMat4f("model", m_Model);
		e_GameHandle.m_PlaneShader->SetUniformMat4f("view", m_View);
		e_GameHandle.m_PlaneShader->SetUniformMat4f("projection", e_GameHandle.m_Default2DProjection);

		e_GameHandle.m_PlaneShader->SetUniform4f("u_Color", m_ColorShift);


		m_VertexArr->Bind();
		m_IndexBuf->Bind();

		glDrawElements(GL_TRIANGLES, m_IndexBuf->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Plane::SetTex(int texID)
	{
		m_TexID = texID;
	}

	void Plane::SetColor(glm::vec4 color)
	{
		m_ColorShift = color;
	}

	/*---------------------------------------------------*/
	//https://learnopengl.com/In-Practice/Text-Rendering

	Text::Text(int texID, std::string text, float _x, float _y, glm::vec3 color, float scale, const char* fontpath)
		: m_TexID(texID), m_Text(text), m_Translate(glm::vec3(_x, _y, 1.0f)), m_Color(color), m_Scale(scale)
	{
		m_Proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f);


		e_GameHandle.m_TextShader->Bind();
		e_GameHandle.m_TextShader->SetUniformMat4f("projection", m_Proj);

		FT_Library ft;
		// All functions return a value different than 0 whenever an error occurred
		if (FT_Init_FreeType(&ft))
		{
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;	
		}

		

		// load font as face
		FT_Face face;
		if (FT_New_Face(ft, fontpath, 0, &face)) {
			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		}
		else {
			// set size to load glyphs as
			FT_Set_Pixel_Sizes(face, 0, 48);

			// disable byte-alignment restriction
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			// load first 128 characters of ASCII set
			for (unsigned char c = 0; c < 128; c++)
			{
				// Load character glyph 
				if (FT_Load_Char(face, c, FT_LOAD_RENDER))
				{
					std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
					continue;
				}
				// generate texture
				unsigned int texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					face->glyph->bitmap.width,
					face->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					face->glyph->bitmap.buffer
				);
				// set texture options
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				// now store character for later use
				Character character = {
					texture,
					glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
					glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
					static_cast<unsigned int>(face->glyph->advance.x)
				};
				Characters.insert(std::pair<char, Character>(c, character));
			}
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		// destroy FreeType once we're finished
		FT_Done_Face(face);
		FT_Done_FreeType(ft);


		// configure VAO/VBO for texture quads
		// -----------------------------------
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//e_GameHandle.m_EntArry.push_back(this); 
	}

	Text::~Text()
	{
		for (int i = 0; i < e_GameHandle.m_EntArry.size(); i++)
		{
			//removes entity from global entity list when it's destructor is called (probably works)
			if (e_GameHandle.m_EntArry[i] == this)
				e_GameHandle.m_EntArry.erase(e_GameHandle.m_EntArry.begin() + i);
		}
	}

	void Text::Render()
	{
		e_GameHandle.m_TextShader->Bind();
		e_GameHandle.m_TextShader->SetUniform3f("textColor", m_Color.r, m_Color.g, m_Color.b);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(m_VAO);

		float x = m_Translate.x;
		float y = m_Translate.y;
		// iterate through all characters
		std::string::const_iterator c;
		for (c = m_Text.begin(); c != m_Text.end(); c++)
		{
			Character ch = Characters[*c];

			float xpos = x + ch.Bearing.x * m_Scale;
			float ypos = y - (ch.Size.y - ch.Bearing.y) * m_Scale;

			float w = ch.Size.x * m_Scale;
			float h = ch.Size.y * m_Scale;
			// update VBO for each character
			float vertices[6][4] = {
				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos,     ypos,       0.0f, 1.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },

				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },
				{ xpos + w, ypos + h,   1.0f, 0.0f }
			};
			// render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			// update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (ch.Advance >> 6) * m_Scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Text::SetText(std::string& text)
	{
		m_Text = std::move(text);
	}

	void Text::SetColor(glm::vec4 color)
	{
		//m_ColorShift = color;
	}

}



