#ifndef HUD_H
#define HUD_H

#include <osg/Camera>
#include <osgText/Text>
#include <osg/Geode>
#include <iostream>
#include <iomanip>

class Hud{

private:
    osg::ref_ptr<osg::Camera> camera;
    osg::ref_ptr<osg::Geode> hudGeode;

    osgText::Text * pos;
	osgText::Text * speed;
	osgText::Text * acce;
	osgText::Text * thrust;
	osgText::Text * orientation;
	osgText::Text * missile;
	osgText::Text * indication;
	osgText::Text * helpinfo1;
	osgText::Text * helpinfo2;
	osgText::Text * crash;

	bool crashFlag;

public:
    Hud();

    osg::Camera * getHudCamera();
    osg::Geode * getHudGeode();
    void initializeHudText();

	void crashed(bool isCrash);

	std::string getPos(float x, float y, float z);
	std::string getSpeed(float x, float y, float z);
	std::string getAcce(float x, float y, float z);
	std::string getOrientation(float x, float y, float z);
	std::string getThrust(float x, float y, float z);
	std::string getSpeedM(float x, float y, float z);
	std::string getIndicationM(float z);

	void updateText(float xp, float yp, float zp,float xv,float yv,float zv,float xa,float ya,float za, float xo, float yo, float zo,float xt, float yt, float zt, float xm, float ym, float zm, float zi);

};

#endif