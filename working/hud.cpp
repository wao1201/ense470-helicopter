
#include "hud.h"
#include <osg/Camera>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

Hud::Hud()
{
    camera = new osg::Camera;
    hudGeode = new osg::Geode;
    camera->setClearMask( GL_DEPTH_BUFFER_BIT);
    camera->setProjectionMatrixAsOrtho2D(0,1280,0,1024);
    camera->setViewMatrix(osg::Matrix::identity());
    camera->setRenderOrder( osg::Camera::POST_RENDER );
    camera->setReferenceFrame( osg::Camera::ABSOLUTE_RF );
}

void Hud::initializeHudText()
{
    //initialize our text pointer;	
    pos = new osgText::Text;
    pos->setFont(osgText::readFontFile("fonts/vera.ttf"));
    pos->setColor(osg::Vec4(255,255,255,1.0f));
    pos->setCharacterSize(20.0f);
    pos->setLayout( osgText::Text::LEFT_TO_RIGHT );
    pos->setText("0, 0, 0");
    pos->setPosition(osg::Vec3(0,140,0));
	hudGeode->addDrawable(pos);

	speed = new osgText::Text;
    speed->setFont(osgText::readFontFile("fonts/vera.ttf"));
    speed->setColor(osg::Vec4(255,255,255,1.0f));
    speed->setCharacterSize(20.0f);
    speed->setLayout( osgText::Text::LEFT_TO_RIGHT );
    speed->setText("0, 0, 0");
    speed->setPosition(osg::Vec3(0,120,0));
	hudGeode->addDrawable(speed);

	acce = new osgText::Text;
    acce->setFont(osgText::readFontFile("fonts/vera.ttf"));
    acce->setColor(osg::Vec4(255,255,255,1.0f));
    acce->setCharacterSize(20.0f);
    acce->setLayout( osgText::Text::LEFT_TO_RIGHT );
    acce->setText("0, 0, 0");
    acce->setPosition(osg::Vec3(0,100,0));
	hudGeode->addDrawable(acce);

	thrust = new osgText::Text;
    thrust->setFont(osgText::readFontFile("fonts/vera.ttf"));
    thrust->setColor(osg::Vec4(255,255,255,1.0f));
    thrust->setCharacterSize(20.0f);
    thrust->setLayout( osgText::Text::LEFT_TO_RIGHT );
    thrust->setText("0, 0, 0");
    thrust->setPosition(osg::Vec3(0,80,0));
	hudGeode->addDrawable(thrust);

	orientation = new osgText::Text;
    orientation->setFont(osgText::readFontFile("fonts/vera.ttf"));
    orientation->setColor(osg::Vec4(255,255,255,1.0f));
    orientation->setCharacterSize(20.0f);
    orientation->setLayout( osgText::Text::LEFT_TO_RIGHT );
    orientation->setText("0, 0, 0");
    orientation->setPosition(osg::Vec3(0,60,0));
	hudGeode->addDrawable(orientation);

	missile = new osgText::Text;
    missile->setFont(osgText::readFontFile("fonts/vera.ttf"));
    missile->setColor(osg::Vec4(255,255,255,1.0f));
    missile->setCharacterSize(20.0f);
    missile->setLayout( osgText::Text::LEFT_TO_RIGHT );
    missile->setText("0, 0, 0");
    missile->setPosition(osg::Vec3(0,40,0));
	hudGeode->addDrawable(missile);

	indication = new osgText::Text;
    indication->setFont(osgText::readFontFile("fonts/vera.ttf"));
    indication->setColor(osg::Vec4(255,255,255,1.0f));
    indication->setCharacterSize(20.0f);
    indication->setLayout( osgText::Text::LEFT_TO_RIGHT );
    indication->setText("0, 0, 0");
    indication->setPosition(osg::Vec3(0,20,0));
	hudGeode->addDrawable(indication);
	
	helpinfo1 = new osgText::Text;
    helpinfo1->setFont(osgText::readFontFile("fonts/vera.ttf"));
    helpinfo1->setColor(osg::Vec4(255,255,255,1.0f));
    helpinfo1->setCharacterSize(15.0f);
    helpinfo1->setLayout( osgText::Text::LEFT_TO_RIGHT );
    helpinfo1->setText("Helicopter controls: '1' to decrease rotor speed, '2' to increase rotor speed, '0' to set rotor speed to 0, '3' to set throttle to neutral, 'c' center joystick,  ");
    helpinfo1->setPosition(osg::Vec3(0,1000,0));
	hudGeode->addDrawable(helpinfo1);

	helpinfo2 = new osgText::Text;
    helpinfo2->setFont(osgText::readFontFile("fonts/vera.ttf"));
    helpinfo2->setColor(osg::Vec4(255,255,255,1.0f));
    helpinfo2->setCharacterSize(15.0f);
    helpinfo2->setLayout( osgText::Text::LEFT_TO_RIGHT );
    helpinfo2->setText("Orientation controls: 'w' increase pitch, 'x' decrease pitch, 'a' roll left, 'd' roll right, '<-' yaw left, '->' yaw right , 'f' toggle friction, 'r' reset after crash");
    helpinfo2->setPosition(osg::Vec3(0,980,0));
	hudGeode->addDrawable(helpinfo2);

    camera->addChild(hudGeode);

}

osg::Camera * Hud::getHudCamera()
{
    return camera;
}

osg::Geode * Hud::getHudGeode()
{
    return hudGeode;
}


std::string Hud::getPos(float x, float y, float z)
{
	std::stringstream ss (std::stringstream::in | std::stringstream::out);
	ss << "Position (x, y, z): " <<std::setw(8)<<std::fixed<<std::setprecision(5) << x << " " <<std::setw(8)<< y << " " <<std::setw(8)<<z;
	std::string str = ss.str();
	return str;
}

std::string Hud::getSpeed(float x, float y, float z)
{
	std::stringstream ss (std::stringstream::in | std::stringstream::out);
	ss << "Helicopter Velocity (x, y, z): " <<std::setw(8)<<std::fixed<<std::setprecision(5) << x << " " <<std::setw(8)<< y << " " <<std::setw(8)<<z;
	std::string str = ss.str();
	return str;
}

std::string Hud::getAcce(float x, float y, float z)
{
	std::stringstream ss (std::stringstream::in | std::stringstream::out);
	ss << "Acceleration (x, y, z): " <<std::setw(8)<<std::fixed<<std::setprecision(5) << x << " " <<std::setw(8)<< y << " " <<std::setw(8)<<z;
	std::string str = ss.str();
	return str;
}

std::string Hud::getOrientation(float x, float y, float z)
{
	std::stringstream ss (std::stringstream::in | std::stringstream::out);
	ss << "Orientation (x, y, z): "<<std::setw(8)<<std::fixed<<std::setprecision(5)<< x << " " <<std::setw(8)<< y << " " <<std::setw(8)<<z;
	std::string str = ss.str();
	return str;
}
std::string Hud::getThrust(float x, float y, float z)
{
	std::stringstream ss (std::stringstream::in | std::stringstream::out);
	ss << "Thrust (x, y, z): "  <<std::setw(8)<<std::fixed<<std::setprecision(5) << x << " " <<std::setw(8)<< y << " " <<std::setw(8)<<z;
	std::string str = ss.str();
	return str;
}

std::string Hud::getSpeedM(float x, float y, float z)
{
	std::stringstream ss (std::stringstream::in | std::stringstream::out);
	ss << "Missile Velocity (x, y, z): " <<std::setw(8)<<std::fixed<<std::setprecision(5) << x << " " <<std::setw(8)<< y << " " <<std::setw(8)<<z;
	std::string str = ss.str();
	return str;
}

std::string Hud::getIndicationM(float z)
{
	std::stringstream ss (std::stringstream::in | std::stringstream::out);
	ss << "Missile Inclination (z): " <<std::setw(8)<<std::fixed<<std::setprecision(5) <<z;
	std::string str = ss.str();
	return str;
}


void Hud::updateText(float xp, float yp, float zp,float xv, float yv, float zv,float xa, float ya, float za, float xo, float yo, float zo, float xt, float yt, float zt, float xm, float ym, float zm, float zi)
{
	hudGeode->removeDrawable(pos);
	pos = new osgText::Text;
    pos->setFont(osgText::readFontFile("fonts/vera.ttf"));
    pos->setColor(osg::Vec4(255,255,255,1.0f));
    pos->setCharacterSize(20.0f);
    pos->setLayout( osgText::Text::LEFT_TO_RIGHT );
	pos->setText(getPos(xp, yp ,zp));
	pos->setPosition(osg::Vec3(0,140,0));
	hudGeode->addDrawable(pos);

	hudGeode->removeDrawable(speed);
	speed = new osgText::Text;
    speed->setFont(osgText::readFontFile("fonts/vera.ttf"));
    speed->setColor(osg::Vec4(255,255,255,1.0f));
    speed->setCharacterSize(20.0f);
    speed->setLayout( osgText::Text::LEFT_TO_RIGHT );
	speed->setText(getSpeed(xv, yv ,zv));
	speed->setPosition(osg::Vec3(0,120,0));
	hudGeode->addDrawable(speed);

	hudGeode->removeDrawable(acce);
	acce = new osgText::Text;
    acce->setFont(osgText::readFontFile("fonts/vera.ttf"));
    acce->setColor(osg::Vec4(255,255,255,1.0f));
    acce->setCharacterSize(20.0f);
    acce->setLayout( osgText::Text::LEFT_TO_RIGHT );
    acce->setText(getAcce(xa, ya ,za));
    acce->setPosition(osg::Vec3(0,100,0));
	hudGeode->addDrawable(acce);

	hudGeode->removeDrawable(thrust);
	thrust = new osgText::Text;
    thrust->setFont(osgText::readFontFile("fonts/vera.ttf"));
    thrust->setColor(osg::Vec4(255,255,255,1.0f));
    thrust->setCharacterSize(20.0f);
    thrust->setLayout( osgText::Text::LEFT_TO_RIGHT );
    thrust->setText(getThrust(xt, yt ,zt));
    thrust->setPosition(osg::Vec3(0,80,0));
	hudGeode->addDrawable(thrust);

	hudGeode->removeDrawable(orientation);
	orientation = new osgText::Text;
    orientation->setFont(osgText::readFontFile("fonts/vera.ttf"));
    orientation->setColor(osg::Vec4(255,255,255,1.0f));
    orientation->setCharacterSize(20.0f);
    orientation->setLayout( osgText::Text::LEFT_TO_RIGHT );
    orientation->setText(getOrientation(xo, yo ,zo));
    orientation->setPosition(osg::Vec3(0,60,0));
	hudGeode->addDrawable(orientation);

	hudGeode->removeDrawable(missile);
	missile = new osgText::Text;
    missile->setFont(osgText::readFontFile("fonts/vera.ttf"));
    missile->setColor(osg::Vec4(255,255,255,1.0f));
    missile->setCharacterSize(20.0f);
    missile->setLayout( osgText::Text::LEFT_TO_RIGHT );
    missile->setText(getSpeedM(xm, ym, zm));
    missile->setPosition(osg::Vec3(0,40,0));
	hudGeode->addDrawable(missile);

	hudGeode->removeDrawable(indication);
	indication = new osgText::Text;
    indication->setFont(osgText::readFontFile("fonts/vera.ttf"));
    indication->setColor(osg::Vec4(255,255,255,1.0f));
    indication->setCharacterSize(20.0f);
    indication->setLayout( osgText::Text::LEFT_TO_RIGHT );
    indication->setText(getIndicationM(zi));
    indication->setPosition(osg::Vec3(0,20,0));
	hudGeode->addDrawable(indication);
	
}

void Hud::crashed(bool isCrash)
{
	if (isCrash)
	{
	hudGeode->removeDrawable(crash);
	crash = new osgText::Text;
    crash->setFont(osgText::readFontFile("fonts/vera.ttf"));
    crash->setColor(osg::Vec4(255,0,0,1.0f));
    crash->setCharacterSize(80.0f);
    crash->setLayout( osgText::Text::LEFT_TO_RIGHT );
    crash->setText("Crashed !!!");
    crash->setPosition(osg::Vec3(410,510,0));
	hudGeode->addDrawable(crash);
	crashFlag = true;
	}
	else
	{
		hudGeode->removeDrawable(crash);
		crashFlag = false;
	}

}

