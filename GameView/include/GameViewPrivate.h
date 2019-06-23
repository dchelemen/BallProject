#pragma once

#include "GameCommon/include/Object.h"

// GLEW
#include <GL/glew.h>

// SDL
#include <SDL.h>

// GLM
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
//

class CCamera;
class CDefaultShader;
class CGrassShader;
class CGameLogger;

class CGameViewPrivate : public CObject
{
private:
	enum class Direction
	{
		TRANSLATE_UP,
		TRANSLATE_DOWN,
		TRANSLATE_LEFT,
		TRANSLATE_RIGHT,
		TURN_UP,
		TURN_DOWN,
		TURN_LEFT,
		TURN_RIGHT,
		NONE
	};

	struct SVertex
	{
		glm::vec3 m_Position;
		glm::vec3 m_Color;
		glm::vec2 m_Texture;
	};

public:
	CGameViewPrivate( CObject* aParent );
	~CGameViewPrivate();

	bool Init();
	void Clean();

	void Render();

	void KeyboardDown(SDL_KeyboardEvent&);
	void KeyboardUp(SDL_KeyboardEvent&);
	void MouseMove(SDL_MouseMotionEvent&);
	void MouseDown(SDL_MouseButtonEvent&);
	void MouseUp(SDL_MouseButtonEvent&);
	void MouseWheel(SDL_MouseWheelEvent&);
	void Resize(int, int);

private:

	CDefaultShader*		m_DefaultShader;
	CGrassShader*		m_GrassShader;

	glm::mat4			m_Model_mtx;
	glm::mat4			m_Proj_mtx;

	CCamera*			m_Camera;
	GLuint				m_MVPLocation;

	// OpenGL ids
	GLuint				m_VAO_id; // vertex array object
	GLuint				m_VBO_id; // vertex buffer object
	GLuint				m_IndexBuffers_id; // vertex index buffer object
	GLuint				m_GrassTexture_id;

	CGameLogger*		m_Logger;
};

