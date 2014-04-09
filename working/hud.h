// -*- c++ -*-
#ifndef HUD_H
#define HUD_H

#include <osg/Camera>
#include <osgText/Text>
#include <osg/Geode>
#include <iostream>

class Hud{

private:
    osg::ref_ptr<osg::Camera> camera;
    osg::ref_ptr<osg::Geode> hudGeode;

    osgText::Text * text;

public:
    Hud();
    //void run1();
    //void run2();
    void setText(const std::string& hudTest);

    void setPosition(osg::Vec3d position);

	void setDisplayPos(const std::string& logInfo);
	void setDisplaySpeed(const std::string& logInfo);
	void setDisplayAcce(const std::string& logInfo);
	void setDisplayThrust(const std::string& logInfo);
	void setDisplayOrientation(const std::string& logInfo);

	  
    osg::Camera * getHudCamera();
    osg::Geode * getHudGeode();
    void initializeHudText();

};

#endif
