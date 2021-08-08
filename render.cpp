#include "render.h"

Renderer::Renderer(Shader &shader)
{
	this->shader = shader;
	initRenderData();
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

void Renderer::DrawTex(Texture& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 colour)
{
	shader.Use();
	glm::mat4 model = glm::mat4(1.0f);  

	model = glm::translate(model, glm::vec3(position, 0.0f)); //translate object by position

																				//rotate obejct
	model = glm::translate(model, glm::vec3(0.5 * size.x, 0.5 * size.y, 0.0)); // move object by half its size, so rotates around centre
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0, 0.0, 1.0));//then do rotation
	model = glm::translate(model, glm::vec3(-0.5 * size.x, -0.5 * size.y, 0.0)); //then translate back to original position

	model = glm::scale(model, glm::vec3(size, 1.0f)); //then scale

	glUniformMatrix4fv(shader.Location("model"), 1, GL_FALSE, &model[0][0]);
	glUniform3fv(shader.Location("spriteColour"), 1, &colour[0]);
	glUniform1i(shader.Location("enableTexture"), GL_TRUE);
	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void Renderer::DrawSquare(glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 colour)
{
	shader.Use();
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(position, 0.0f)); //translate object by position

																				//rotate obejct
	model = glm::translate(model, glm::vec3(0.5 * size.x, 0.5 * size.y, 0.0)); // move object by half its size, so rotates around centre
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0, 0.0, 1.0));//then do rotation
	model = glm::translate(model, glm::vec3(-0.5 * size.x, -0.5 * size.y, 0.0)); //then translate back to original position

	model = glm::scale(model, glm::vec3(size, 1.0f)); //then scale

	glUniformMatrix4fv(shader.Location("model"), 1, GL_FALSE, &model[0][0]);
	glUniform3fv(shader.Location("spriteColour"), 1, &colour[0]);
	glUniform1i(shader.Location("enableTexture"), GL_FALSE);

	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void Renderer::DrawLine(glm::vec2 point1, glm::vec2 point2, glm::vec3 colour, float width)
{
	shader.Use();
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

	glUniformMatrix4fv(shader.Location("model"), 1, GL_FALSE, &model[0][0]);
	glUniform3fv(shader.Location("spriteColour"), 1, &colour[0]);
	glUniform1i(shader.Location("enableTexture"), GL_FALSE);
	glBindVertexArray(lineVAO);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
}

void Renderer::Resize(int width, int height)
{
	glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(shader.Location("projection"), 1, GL_FALSE, &proj[0][0]);
}