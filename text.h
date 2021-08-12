#ifndef TEXT_H
#define TEXT_H

#include <map>
#include <string>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

struct Character
{
	Character(unsigned int TextureID, glm::vec2 Size, glm::vec2 Bearing, double Advance)
	{
		this->TextureID = TextureID;
		this->Size = Size;
		this->Bearing = Bearing;
		this->Advance = Advance;
	}
	~Character()
	{
		glDeleteTextures(1, &TextureID);
	}
	unsigned int TextureID;
	glm::vec2 Size;
	glm::vec2 Bearing;
	double Advance;
};

class Font
{
public:
	Font(const char* file);
	~Font();
	Character* getChar(char c);
private:
	std::map<char, Character*> _chars;
	bool loadCharacter(FT_Face f ,char c);
	const int SIZE = 50;
};


#endif