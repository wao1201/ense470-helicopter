#pragma once
class MissileConfig
{
public:
	float Airspeed;
	float mass;
	MissileConfig(void);
	MissileConfig(float Airspeed, float mass);
	~MissileConfig(void);
};