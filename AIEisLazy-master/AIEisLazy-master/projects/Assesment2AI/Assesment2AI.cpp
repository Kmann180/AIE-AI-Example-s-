#include "Assesment2AI.h"
#include "Gizmos.h"
#include "Utilities.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

Assesment2AI::Assesment2AI()
{

}

Assesment2AI::~Assesment2AI()
{

}

bool Assesment2AI::onCreate(int a_argc, char* a_argv[]) 
{
	// initialise the Gizmos helper class
	Gizmos::create();

	// create a world-space matrix for a camera
	m_cameraMatrix = glm::inverse( glm::lookAt(glm::vec3(10,10,10),glm::vec3(0,0,0), glm::vec3(0,1,0)) );

	// get window dimensions to calculate aspect ratio
	int width = 0, height = 0;
	glfwGetWindowSize(m_window, &width, &height);

	// create a perspective projection matrix with a 90 degree field-of-view and widescreen aspect ratio
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, width / (float)height, 0.1f, 1000.0f);

	// set the clear colour and enable depth testing and backface culling
	glClearColor(0.25f,0.25f,0.25f,1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	////////////////////////////////////////////////////////////////////
	Bot1 = new Char1();
	Bot1->vm_Position = glm::vec3(0,0,0);
//	Bot1->setSpeed(.6f);

	Bot2 = new Char2();
//	Bot2->setSpeed(.3f);
	Bot2->vm_Position = glm::vec3(4,0,4);
	Bot1->ChooseNextWaypoint(Bot2, Bot1);
	Bot2->ChooseNextWaypoint2(Bot2, Bot1);
	//////////////////////////////////////////////////////////////////////
	return true;
}

void Assesment2AI::onUpdate(float a_deltaTime) 
{
	// update our camera matrix using the keyboard/mouse
	Utility::freeMovement( m_cameraMatrix, a_deltaTime, 10 );

	// clear all gizmos from last frame
	Gizmos::clear();
	
	// add an identity matrix gizmo
	Gizmos::addTransform( glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1) );

	// add a 20x20 grid on the XZ-plane
	for ( int i = 0 ; i < 21 ; ++i )
	{
		Gizmos::addLine( glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), 
						 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
		
		Gizmos::addLine( glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), 
						 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
	}
	
	/////////////////////////////////////////////////////////////
//	Bot2->vm_Position = Bot2->seekPosition(Bot2->vm_SeekPos);

	Bot2->update();
	Bot1->update();

	Bot1->Move(a_deltaTime, Bot1, Bot2);
	Bot2->Move(a_deltaTime, Bot2, Bot1);

	Bot2->CheckIfClose(Bot2, Bot1);
//	Bot1->CheckIfFar(Bot2, Bot1);

	///////////////////////////////////////////////////////////////
	// quit our application when escape is pressed
	if (glfwGetKey(m_window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		quit();
}

void Assesment2AI::onDraw() 
{
	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// get the view matrix from the world-space camera matrix
	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );
	
	// draw the gizmos from this frame
	Gizmos::draw(m_projectionMatrix, viewMatrix);

	// get window dimensions for 2D orthographic projection
	int width = 0, height = 0;
	glfwGetWindowSize(m_window, &width, &height);
	Gizmos::draw2D(glm::ortho<float>(0, width, 0, height, -1.0f, 1.0f));

	
}

void Assesment2AI::onDestroy()
{
	// clean up anything we created
	Gizmos::destroy();

	/////////////////////////////////
	delete Bot1;
	delete  Bot2;
	/////////////////////////////////
}

// main that controls the creation/destruction of an application
int main(int argc, char* argv[])
{
	// explicitly control the creation of our application
	Application* app = new Assesment2AI();
	
	if (app->create("AIE - Assesment2AI",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
		app->run();
		
	// explicitly control the destruction of our application
	delete app;

	return 0;
}