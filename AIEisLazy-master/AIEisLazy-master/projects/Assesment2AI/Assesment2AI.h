#pragma once

#include "Application.h"
#include "MainChar.h"
#include <glm/glm.hpp>

// derived application class that wraps up all globals neatly
class Assesment2AI : public Application
{
public:

	Assesment2AI();
	virtual ~Assesment2AI();

	Char1* Bot1;
	Char2* Bot2;
	
protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;
};