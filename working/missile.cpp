#include "missile.h"

MissileConfig::MissileConfig(void)
{
	this->mass = 100;
	this->Airspeed = 40;
}

MissileConfig::MissileConfig(float Airspeed, float mass)
{
	this->mass = mass;
	this->Airspeed = Airspeed;
}


MissileConfig::~MissileConfig(void)
{
}
