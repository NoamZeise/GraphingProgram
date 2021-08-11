#include "render.h"

Renderer::Renderer(int width, int height)
{
	Shader textureShader("shaders/sprite.vs", "shaders/sprite.fs");

	textureShader.Use();

	//configure sprite shader
	glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));

	glUniform1i(textureShader.Location("image"), 0);
	glUniformMatrix4fv(textureShader.Location("projection"), 1, GL_FALSE, &proj[0][0]);
	glUniformMatrix4fv(textureShader.Location("view"), 1, GL_FALSE, &view[0][0]);

	this->_textureShader = textureShader;

	initRenderData();
	initFontData();
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &lineVAO);
	glDeleteBuffers(1, &lineVBO);
	glDeleteVertexArrays(1, &quadVAO);
	glDeleteBuffers(1, &quadVBO);
}

void Renderer::initRenderData()
{

	//create quad
	float quadVerticies[] =
	{
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);

	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVerticies), quadVerticies, GL_STATIC_DRAW);

	glBindVertexArray(quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

	//create line
	float lineVerticies[] = {0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f, 0.0f};
	glGenVertexArrays(1, &lineVAO);
	glGenBuffers(1, &lineVBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineVerticies), lineVerticies, GL_STATIC_DRAW);
	
	glBindVertexArray(lineVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);


	//unbind VAO and VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Renderer::initFontData()
{
	CourierNew = new Font("c:/windows/fonts/arial.ttf");
}

void Renderer::DrawTex(Texture& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 colour)
{
	_textureShader.Use();
	glm::mat4 model = glm::mat4(1.0f);  

	model = glm::translate(model, glm::vec3(position, 0.0f)); //translate object by position

																				//rotate obejct
	model = glm::translate(model, glm::vec3(0.5 * size.x, 0.5 * size.y, 0.0)); // move object by half its size, so rotates around centre
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0, 0.0, 1.0));//then do rotation
	model = glm::translate(model, glm::vec3(-0.5 * size.x, -0.5 * size.y, 0.0)); //then translate back to original position

	model = glm::scale(model, glm::vec3(size, 1.0f)); //then scale

	glUniformMatrix4fv(_textureShader.Location("model"), 1, GL_FALSE, &model[0][0]);
	glUniform3fv(_textureShader.Location("spriteColour"), 1, &colour[0]);
	glUniform1i(_textureShader.Location("enableTexture"), GL_TRUE);
	glUniform1i(_textureShader.Location("enableFont"), GL_FALSE);
	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}


void Renderer::DrawSquare(glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 colour)
{
	_textureShader.Use();
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(position, 0.0f)); //translate object by position

																				//rotate obejct
	model = glm::translate(model, glm::vec3(0.5 * size.x, 0.5 * size.y, 0.0)); // move object by half its size, so rotates around centre
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0, 0.0, 1.0));//then do rotation
	model = glm::translate(model, glm::vec3(-0.5 * size.x, -0.5 * size.y, 0.0)); //then translate back to original position

	model = glm::scale(model, glm::vec3(size, 1.0f)); //then scale

	glUniformMatrix4fv(_textureShader.Location("model"), 1, GL_FALSE, &model[0][0]);
	glUniform3fv(_textureShader.Location("spriteColour"), 1, &colour[0]);
	glUniform1i(_textureShader.Location("enableTexture"), GL_FALSE);
	glUniform1i(_textureShader.Location("enableFont"), GL_FALSE);

	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void Renderer::DrawString(std::string text, glm::vec2 position, float size, float rotate, glm::vec3 colour)
{
	_textureShader.Use();
	glUniform3fv(_textureShader.Location("spriteColour"), 1, &colour[0]);
	glUniform1i(_textureShader.Location("enableTexture"), GL_FALSE);
	glUniform1i(_textureShader.Location("enableFont"), GL_TRUE);
	glActiveTexture(GL_TEXTURE0);
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character* cTex = CourierNew->getChar(*c);
		if (cTex == nullptr)
		{
			continue;
		}
		glm::vec2 thisPos = position;
		thisPos.x += cTex->Bearing.x * size;
		thisPos.y += (cTex->Size.y - cTex->Bearing.y) * size;
		thisPos.y -= cTex->Size.y * size;
		glm::vec2 dim = glm::vec2(cTex->Size.x * size, cTex->Size.y * size);
		dim.x /= 1;
		dim.y /= 1;
		glm::mat4 model = glm::mat4(1.0f);

		model = glm::translate(model, glm::vec3(thisPos, 0.0f)); //translate object by position

		//model = glm::translate(model, glm::vec3(0.5 * dim.x, 0.5 * dim.y, 0.0)); // move object by half its size, so rotates around centre
		//model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0, 0.0, 1.0));//then do rotation
		//model = glm::translate(model, glm::vec3(-0.5 * dim.x, -0.5 * dim.y, 0.0)); //then translate back to original position

		model = glm::scale(model, glm::vec3(dim, 1.0f)); //then scale


		glUniformMatrix4fv(_textureShader.Location("model"), 1, GL_FALSE, &model[0][0]);
		glBindTexture(GL_TEXTURE_2D, cTex->TextureID);

		glBindVertexArray(quadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		position.x += cTex->Advance * size;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::DrawLine(glm::vec2 point1, glm::vec2 point2, glm::vec3 colour, float width)
{
	_textureShader.Use();
	glLineWidth(width);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(point1, 0.0f));

	float scale = Geometry::distance(Vector2(point1.x, point1.y), Vector2(point2.x, point2.y));

	glm::vec2 dVec = glm::vec2(point2.x - point1.x, point2.y - point1.y);
	dVec = glm::vec2(dVec.x / scale, dVec.y / scale);
	glm::vec2 oVec = glm::vec2(1.0f, 0.0f);

	float angle = atan2(dVec.y, dVec.x) - atan2(oVec.y, oVec.x);


	model = glm::rotate(model, angle, glm::vec3(0.0, 0.0, 1.0));

	
	model = glm::scale(model, glm::vec3(glm::vec2(scale), 1.0f)); //then scale

	glUniformMatrix4fv(_textureShader.Location("model"), 1, GL_FALSE, &model[0][0]);
	glUniform3fv(_textureShader.Location("spriteColour"), 1, &colour[0]);
	glUniform1i(_textureShader.Location("enableTexture"), GL_FALSE);
	glUniform1i(_textureShader.Location("enableFont"), GL_FALSE);
	glBindVertexArray(lineVAO);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
}

void Renderer::DrawPoint(glm::vec2 point, glm::vec3 colour, float size)
{
	_textureShader.Use();
	glPointSize(size);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(point, 0.0f));

	glUniformMatrix4fv(_textureShader.Location("model"), 1, GL_FALSE, &model[0][0]);
	glUniform3fv(_textureShader.Location("spriteColour"), 1, &colour[0]);
	glUniform1i(_textureShader.Location("enableTexture"), GL_FALSE);
	glUniform1i(_textureShader.Location("enableFont"), GL_FALSE);
	glBindVertexArray(lineVAO);
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0);
}

void Renderer::Resize(int width, int height)
{
	glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(_textureShader.Location("projection"), 1, GL_FALSE, &proj[0][0]);
}