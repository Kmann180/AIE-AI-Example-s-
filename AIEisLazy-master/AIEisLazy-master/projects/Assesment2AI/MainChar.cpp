#include "MainChar.h"
#include "Assesment2AI.h"
#include <Gizmos.h>
#include <Utilities.h>
#include <math.h>
#include <iostream>


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////Bot1////Bot1////Bot1////Bot1////Bot1////Bot1////Bot1////Bot1////Bot1////Bot1////Bot1////Bot1////Bot1////Bot1///////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Char1::update()
{
	Gizmos::addAABBFilled(vm_Position, glm::vec3(0.1f), glm::vec4(1, 1, 0, 1));
}

void Char1::ChooseNextWaypoint(Char2 *Bot2, Char1 *Bot1)
{
	float X, Y, Z;
	X = (((Bot2->vm_Position.x) - (Bot1->vm_Position.x)) + (((Bot2->vm_Position.x) + (Bot1->vm_Position.x)) / 2));

	Y = (((Bot2->vm_Position.y) - (Bot1->vm_Position.y)) + (((Bot2->vm_Position.y) + (Bot1->vm_Position.y)) / 2));

	Z = (((Bot2->vm_Position.z) - (Bot1->vm_Position.z)) + (((Bot2->vm_Position.z) + (Bot1->vm_Position.z)) / 2));
	
	Bot1->NextWaypoint = glm::vec3 (X, Y, Z);
}


void Char1::Move(float a_deltaTime, Char1 *Bot1, Char2 *Bot2)
{
	Dir = glm::normalize( Bot1->NextWaypoint - Bot1->vm_Position);

	if (!AtPoint(Bot1))
	{
		Bot1->vm_Position = Bot1->vm_Position + Dir * (Bot1->fSpeed * .5f) * a_deltaTime;
	}

	else if (AtPoint(Bot1))
	{ 
		if (Bot2->AtPoint(Bot2))
		{
			ChooseNextWaypoint(Bot2, Bot1);
		}
	};
}

bool Char1::AtPoint(Char1 *Bot1)
{
	if (glm::distance2(Bot1->vm_Position, NextWaypoint) < .25f)
	{
		return true;
	}
	else return false;
}

//If Far
/*
void Char1::CheckIfFar(Char2 *Bot2, Char1 *Bot1)
{
	float range = (8.0f * 8.0f);
	float distance = glm::distance2(Bot1->vm_Position, Bot2->vm_Position);
	if (distance >= range)
	{
		Bot1->isFar = true;
	}
	else
	{
		Bot1->isFar = false;
	}
}
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////Bot2////Bot2////Bot2////Bot2////Bot2////Bot2////Bot2////Bot2////Bot2////Bot2////Bot2////Bot2////Bot2////Bot2///////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Char2::update()
{
	Gizmos::addAABBFilled(vm_Position, glm::vec3(0.1f), glm::vec4(1, 1, 0, 1));
}

void Char2::ChooseNextWaypoint2(Char2 *Bot2, Agent *Bot1)
{

	if (glm::distance2(Bot2->vm_Position, glm::vec3(4, 0, 4)) < .5f)
	{
		Bot2->NextWaypoint2 = glm::vec3(-4, 0, 4); //
	}
	if (glm::distance2(Bot2->vm_Position, glm::vec3(0, 0, 5)) < .5f)
	{
		Bot2->NextWaypoint2 = glm::vec3(4, 0, 4);//
	}
	if (glm::distance2(Bot2->vm_Position, glm::vec3(-4, 0, 4)) < .5f)
	{
		Bot2->NextWaypoint2 = glm::vec3(0, 0, -5); //
	}
	if (glm::distance2(Bot2->vm_Position, glm::vec3(-5, 0, 0)) < .5f)
	{
		Bot2->NextWaypoint2 = glm::vec3(-4, 0, -4); //
	}
	if (glm::distance2(Bot2->vm_Position, glm::vec3(-4, 0, -4)) < .5f)
	{
		Bot2->NextWaypoint2 = glm::vec3(5, 0, 0); //
	}
	if (glm::distance2(Bot2->vm_Position, glm::vec3(0, 0, -5)) < .5f)
	{
		Bot2->NextWaypoint2 = glm::vec3(-5, 0, 0); //
	}
	if (glm::distance2(Bot2->vm_Position, glm::vec3(4, 0, -4)) < .5f)
	{
		Bot2->NextWaypoint2 = glm::vec3(0, 0, 5); //
	}
	if (glm::distance2(Bot2->vm_Position, glm::vec3(5, 0, 0)) < .5f)
	{
		Bot2->NextWaypoint2 = glm::vec3(4, 0, -4); //
	}
}
/*
glm::vec3 Char2::Wander(glm::vec3 a_positon)
{
	float temp = fspeed * Utility::getDeltaTime();
	glm::vec3 SpeedMove = glm::normalize(a_positon - vm_Position);
	SpeedMove = glm::cross(SpeedMove, glm::vec3(temp));
	return glm::vec3 (vm_Position - SpeedMove);
}
*/

void Char2::Move(float a_deltaTime, Char2 *Bot2, Agent *Bot1)
{
	 Dir = glm::normalize(Bot2->NextWaypoint2 - Bot2->vm_Position);
	if (!AtPoint(Bot2))
	{
			Bot2->vm_Position = Bot2->vm_Position + Dir * Bot2->fSpeed * a_deltaTime;

		if (isFleeing)
		{
			Dodge(Bot2, Bot1);
			glm::vec3 Dir2 = Dir * ChangeDir;
			Bot2->vm_Position = Bot2->vm_Position - Dir2 * (Bot2->fSpeed * 2) * a_deltaTime;
			ChooseNextWaypoint2(Bot2, Bot1);
		}
	}

	else if (AtPoint(Bot2))
	{
		if (isFleeing)
		{
			Dodge(Bot2, Bot1);
			glm::vec3 Dir2 = Dir * ChangeDir;
			Bot2->vm_Position = Bot2->vm_Position - Dir2 * (Bot2->fSpeed * 2) * a_deltaTime;
			ChooseNextWaypoint2(Bot2, Bot1);
		}
		
	};
}

bool Char2::AtPoint(Char2 *Bot2)
{
	if (glm::distance2(Bot2->vm_Position, NextWaypoint2) < .25f)
	{
		return true;
	}
	else return false;
}

void Char2::CheckIfClose(Char2 *Bot2, Agent *Bot1)
{
	float range = (2.0f * 2.0f);
	float distance = glm::distance2(Bot2->vm_Position, Bot1->vm_Position);
	if (distance <= range)
	{
		Bot2->isFleeing = true;
	}
	else
	{
		Bot2->isFleeing = false;
	}
}

void Char2::Dodge(Char2 *Bot2, Agent *Bot1)
{
	if (Bot2->vm_Position.x >= Bot1->vm_Position.x && Bot2->vm_Position.z >= Bot1->vm_Position.z)
	{
		ChangeDir = glm::vec3(0,0,-1);
	}

	if (Bot2->vm_Position.x >= Bot1->vm_Position.x && Bot2->vm_Position.z <= Bot1->vm_Position.z)
	{
		ChangeDir = glm::vec3(-1, 0, 0);
	}

	if (Bot2->vm_Position.x <= Bot1->vm_Position.x && Bot2->vm_Position.z <= Bot1->vm_Position.z)
	{
		ChangeDir = glm::vec3(0, 0, -1);
	}

	if (Bot2->vm_Position.x <= Bot1->vm_Position.x && Bot2->vm_Position.z >= Bot1->vm_Position.z)
	{
		ChangeDir = glm::vec3(-1, 0, 0);
	}
}

