#ifndef _MAINCHAR_H_
#define _MAINCHAR_H_

#include <glm\glm.hpp>
#include <time.h>
#include <glm\ext.hpp>


class Agent
{
public:
	Agent(){}
	~Agent(){}

	virtual void update() = 0;
	glm::vec3 vm_Position;
	glm::vec3 vm_SeekPos;
	float dist;

};

/////////////////////////////////////////////////////

class Char2 : public Agent
{
public:
	Char2()
	{
		previousSpeedTime = time_t(0);
	}
	~Char2(){}


	void update();
	void ChooseNextWaypoint2(Char2 *Bot2, Agent *Bot1);
	glm::vec3 NextWaypoint2;
	void Move(float a_deltaTime, Char2 *Bot2, Agent *Bot1);
	float fSpeed = 1;
	bool AtPoint(Char2 *Bot1);
	bool isFleeing = false;
	void CheckIfClose(Char2 *Bot2, Agent *Bot1);
	glm::vec3 Dir;
	void Dodge(Char2 *Bot2, Agent *Bot1);
	glm::vec3 ChangeDir;
	glm::vec3 Wander(glm::vec3 a_position);

protected:
	float fspeed = 1;
	float previousSpeedTime;

};

/////////////////////////////////////////////////////

class Char1 : public Agent
{
public:
	Char1(){
		previousSpeedTime = time_t(0);
	}
	~Char1(){}
	
	glm::vec3 getOtherPosition(Char2 other)
	{
		return other.vm_Position;
	}

	void update();
	void ChooseNextWaypoint(Char2 *Bot2, Char1 *Bot1);
	glm::vec3 NextWaypoint;
	void Move(float a_deltaTime, Char1 *Bot1, Char2 *Bot2);
//	void CheckIfFar(Char2 *Bot2, Char1 *Bot1);
	float fSpeed = 10;
	bool AtPoint(Char1 *Bot1);
	glm::vec3 Dir;
	bool isFar = false;
	

protected:
	float previousSpeedTime;

};

#endif