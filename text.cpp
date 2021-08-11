#include "text.h"

Font::Font(const char* file)
{
	FT_Library ftlib;
	if (FT_Init_FreeType(&ftlib))
	{
		std::cout << "failed to load freetype2 library" << std::endl;
		return;
	}

	FT_Face face;
	if (FT_New_Face(ftlib, file, 0, &face))
	{
		std::cout << "error loading " << file << std::endl;
		return;
	}

	FT_Set_Pixel_Sizes(face, 0, SIZE);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (unsigned char c = 0; c < 128; c++)
	{
		loadCharacter(face, c);
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ftlib);
}

bool Font::loadCharacter(FT_Face face, char c)
{
	if (FT_Load_Char(face, c, FT_LOAD_RENDER))
	{
		std::cout << "error loading " << c << std::endl;
		return false;
	}
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RED,
		face->glyph->bitmap.width,
		face->glyph->bitmap.rows,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		face->glyph->bitmap.buffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	_chars.insert(std::pair<char, Character*>(c, new Character(
	texture,
	glm::vec2(face->glyph->bitmap.width / (double)SIZE, face->glyph->bitmap.rows / (double)SIZE),
	glm::vec2(face->glyph->bitmap_left / (double)SIZE, face->glyph->bitmap_top / (double)SIZE),
	(face->glyph->advance.x >> 6) / (double)SIZE
	)));

	return true;
}

Character* Font::getChar(char c)
{
	return _chars[c];
}