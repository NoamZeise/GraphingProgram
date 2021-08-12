#include "render.h"

Renderer::Renderer(int width, int height)
{

	glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));

	_textureShader = new Shader("shaders/sprite.vs", "shaders/sprite.fs");
	_textureShader->Use();
	glUniform1i(_textureShader->Location("image"), 0);
	glUniformMatrix4fv(_textureShader->Location("projection"), 1, GL_FALSE, &proj[0][0]);
	glUniformMatrix4fv(_textureShader->Location("view"), 1, GL_FALSE, &view[0][0]);


	_pointShader = new Shader("shaders/point.vs", "shaders/point.fs");
	_pointShader->Use();
	glUniformMatrix4fv(_pointShader->Location("projection"), 1, GL_FALSE, &proj[0][0]);
	glUniformMatrix4fv(_pointShader->Location("view"), 1, GL_FALSE, &view[0][0]);

	initRenderData();
	initFontData();
}

Renderer::~Renderer()
{
	delete _textureShader;
	delete _pointShader;
	delete CourierNew;
	delete _line;
	delete _quad;
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
	_quad = new VertexData(&quadVerticies[0], sizeof(quadVerticies) / sizeof(float), 4);
	//create line
	float lineVerticies[] = {0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f, 0.0f};

	_line = new VertexData(&lineVerticies[0], sizeof(lineVerticies) / sizeof(float), 4);
}

void Renderer::initFontData()
{
	CourierNew = new Font("c:/windows/fonts/arial.ttf");
}

void Renderer::DrawTex(Texture& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 colour)
{
	_textureShader->Use();
	glm::mat4 model = glm::mat4(1.0f);  

	model = getModel(position, size, rotate);

	glUniformMatrix4fv(_textureShader->Location("model"), 1, GL_FALSE, &model[0][0]);
	glUniform3fv(_textureShader->Location("spriteColour"), 1, &colour[0]);
	glUniform1i(_textureShader->Location("enableTexture"), GL_TRUE);
	glUniform1i(_textureShader->Location("enableFont"), GL_FALSE);
	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	_quad->Draw(GL_TRIANGLES);
}


void Renderer::DrawSquare(glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 colour)
{
	_textureShader->Use();
	glm::mat4 model = getModel(position, size, rotate);

	glUniformMatrix4fv(_textureShader->Location("model"), 1, GL_FALSE, &model[0][0]);
	glUniform3fv(_textureShader->Location("spriteColour"), 1, &colour[0]);
	glUniform1i(_textureShader->Location("enableTexture"), GL_FALSE);
	glUniform1i(_textureShader->Location("enableFont"), GL_FALSE);

	_quad->Draw(GL_TRIANGLES);
}

void Renderer::DrawString(std::string text, glm::vec2 position, float size, float rotate, glm::vec3 colour)
{
	_textureShader->Use();
	glUniform3fv(_textureShader->Location("spriteColour"), 1, &colour[0]);
	glUniform1i(_textureShader->Location("enableTexture"), GL_FALSE);
	glUniform1i(_textureShader->Location("enableFont"), GL_TRUE);
	glActiveTexture(GL_TEXTURE0);
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character* cTex = CourierNew->getChar(*c);
		if (cTex == nullptr)
			continue;

		glm::vec2 thisPos = position;
		thisPos.x += cTex->Bearing.x * size;
		thisPos.y += (cTex->Size.y - cTex->Bearing.y) * size;
		thisPos.y -= cTex->Size.y * size;

		glm::vec2 dim = glm::vec2(cTex->Size.x * size, cTex->Size.y * size);
		dim.x /= 1;
		dim.y /= 1;

		glm::mat4 model = getModel(thisPos, dim, rotate);
		glUniformMatrix4fv(_textureShader->Location("model"), 1, GL_FALSE, &model[0][0]);
		glBindTexture(GL_TEXTURE_2D, cTex->TextureID);

		_quad->Draw(GL_TRIANGLES);

		position.x += cTex->Advance * size;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::DrawLine(glm::vec2 point1, glm::vec2 point2, glm::vec3 colour, float width)
{
	_textureShader->Use();
	glLineWidth(width);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(point1, 0.0f));

	float scale = Geometry::distance(Vector2(point1.x, point1.y), Vector2(point2.x, point2.y));

	glm::vec2 dVec = glm::vec2(point2.x - point1.x, point2.y - point1.y);
	dVec = glm::vec2(dVec.x / scale, dVec.y / scale);
	glm::vec2 oVec = glm::vec2(1.0f, 0.0f);

	float angle = atan2(dVec.y, dVec.x) - atan2(oVec.y, oVec.x);

	model = glm::rotate(model, angle, glm::vec3(0.0, 0.0, 1.0));

	model = glm::scale(model, glm::vec3(glm::vec2(scale), 1.0f));

	glUniformMatrix4fv(_textureShader->Location("model"), 1, GL_FALSE, &model[0][0]);
	glUniform3fv(_textureShader->Location("spriteColour"), 1, &colour[0]);
	glUniform1i(_textureShader->Location("enableTexture"), GL_FALSE);
	glUniform1i(_textureShader->Location("enableFont"), GL_FALSE);
	_line->Draw(GL_LINES);
}



void Renderer::DrawPoint(glm::vec2 point, glm::vec3 colour, float size)
{
	_textureShader->Use();
	glPointSize(size);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(point, 0.0f));

	glUniformMatrix4fv(_textureShader->Location("model"), 1, GL_FALSE, &model[0][0]);
	glUniform3fv(_textureShader->Location("spriteColour"), 1, &colour[0]);
	glUniform1i(_textureShader->Location("enableTexture"), GL_FALSE);
	glUniform1i(_textureShader->Location("enableFont"), GL_FALSE);
	
	_line->Draw(GL_POINTS, 1);
}

void Renderer::DrawVertexPoints(VertexData* vd, glm::vec2 gPosition, glm::vec2 gScale, glm::vec2 vPosition, glm::vec2 vScale, glm::vec3 colour, float size)
{
	_pointShader->Use();
	glPointSize(size);

	glUniform2fv(_pointShader->Location("gPos"), 1, &gPosition[0]);
	glUniform2fv(_pointShader->Location("gScale"), 1, &gScale[0]);
	glUniform2fv(_pointShader->Location("vPos"), 1, &vPosition[0]);
	glUniform2fv(_pointShader->Location("vScale"), 1, &vScale[0]);
	glUniform3fv(_pointShader->Location("spriteColour"), 1, &colour[0]);

	vd->Draw(GL_POINTS);
}

void Renderer::Resize(int width, int height)
{
	glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
	_textureShader->Use();
	glUniformMatrix4fv(_textureShader->Location("projection"), 1, GL_FALSE, &proj[0][0]);
	_pointShader->Use();
	glUniformMatrix4fv(_pointShader->Location("projection"), 1, GL_FALSE, &proj[0][0]);
}

glm::mat4 Renderer::getModel(glm::vec2 position, glm::vec2 size, float rotate)
{
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(position, 0.0f)); //translate object by position
	//rotate obejct
	model = glm::translate(model, glm::vec3(0.5 * size.x, 0.5 * size.y, 0.0)); // move object by half its size, so rotates around centre
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0, 0.0, 1.0));//then do rotation
	model = glm::translate(model, glm::vec3(-0.5 * size.x, -0.5 * size.y, 0.0)); //then translate back to original position

	model = glm::scale(model, glm::vec3(size, 1.0f)); //then scale

	return model;
}