
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
    pos->setPosition(osg::Vec3(0,150,0));
	hudGeode->addDrawable(pos);

	speed = new osgText::Text;
    speed->setFont(osgText::readFontFile("fonts/vera.ttf"));
    speed->setColor(osg::Vec4(255,255,255,1.0f));
    speed->setCharacterSize(20.0f);
    speed->setLayout( osgText::Text::LEFT_TO_RIGHT );
    speed->setText("0, 0, 0");
    speed->setPosition(osg::Vec3(0,130,0));
	hudGeode->addDrawable(speed);

	acce = new osgText::Text;
    acce->setFont(osgText::readFontFile("fonts/vera.ttf"));
    acce->setColor(osg::Vec4(255,255,255,1.0f));
    acce->setCharacterSize(20.0f);
    acce->setLayout( osgText::Text::LEFT_TO_RIGHT );
    acce->setText("0, 0, 0");
    acce->setPosition(osg::Vec3(0,110,0));
	hudGeode->addDrawable(acce);

	thrust = new osgText::Text;
    thrust->setFont(osgText::readFontFile("fonts/vera.ttf"));
    thrust->setColor(osg::Vec4(255,255,255,1.0f));
    thrust->setCharacterSize(20.0f);
    thrust->setLayout( osgText::Text::LEFT_TO_RIGHT );
    thrust->setText("0, 0, 0");
    thrust->setPosition(osg::Vec3(0,90,0));
	hudGeode->addDrawable(thrust);

	orientation = new osgText::Text;
    orientation->setFont(osgText::readFontFile("fonts/vera.ttf"));
    orientation->setColor(osg::Vec4(255,255,255,1.0f));
    orientation->setCharacterSize(20.0f);
    orientation->setLayout( osgText::Text::LEFT_TO_RIGHT );
    orientation->setText("0, 0, 0");
    orientation->setPosition(osg::Vec3(0,70,0));
	hudGeode->addDrawable(orientation);
	
	text = new osgText::Text;
    text->setFont(osgText::readFontFile("fonts/vera.ttf"));
    text->setColor(osg::Vec4(255,255,255,1.0f));
    text->setCharacterSize(20.0f);
    text->setLayout( osgText::Text::LEFT_TO_RIGHT );
    text->setText("helicopter controls: '1' to decrease rotor speed, '2' to increase rotor speed, '0' to set rotor speed to 0, '3' to set throttle to neutral, 'c' center joystick,  ");
    text->setPosition(osg::Vec3(0,1000,0));
	hudGeode->addDrawable(text);

	text2 = new osgText::Text;
    text2->setFont(osgText::readFontFile("fonts/vera.ttf"));
    text2->setColor(osg::Vec4(255,255,255,1.0f));
    text2->setCharacterSize(20.0f);
    text2->setLayout( osgText::Text::LEFT_TO_RIGHT );
    text2->setText("helicopter controls: '1' to decrease rotor speed, '2' to increase rotor speed, '0' to set rotor speed to 0, 'c' center joystick,  ");
    text2->setPosition(osg::Vec3(0,980,0));
	hudGeode->addDrawable(text2);

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

/*
void Hud::setText(const std::string& hudText)
{
    text->setText(hudText);
}*/

void Hud::setPosition(osg::Vec3d position)
{
    text->setPosition(position);
}

std::string Hud::getPos(float x, float y, float z)
{
	std::stringstream ss (std::stringstream::in | std::stringstream::out);
	ss << "Position (x, y, z): " <<std::setprecision(7) << x << " " << y << " " <<z;
	std::string str = ss.str();
	return str;
}

std::string Hud::getSpeed(float x, float y, float z)
{
	std::stringstream ss (std::stringstream::in | std::stringstream::out);
	ss << "Velocity (x, y, z): " <<std::setprecision(7) << x << " " << y << " " <<z;
	std::string str = ss.str();
	return str;
}

std::string Hud::getAcce(float x, float y, float z)
{
	std::stringstream ss (std::stringstream::in | std::stringstream::out);
	ss << "Acceleration (x, y, z): " <<std::setprecision(7) << x << " " << y << " " <<z;
	std::string str = ss.str();
	return str;
}

std::string Hud::getOrientation(float x, float y, float z)
{
	std::stringstream ss (std::stringstream::in | std::stringstream::out);
	ss << "Orientation (x, y, z): " <<std::setprecision(7) << x << " " << y << " " <<z;
	std::string str = ss.str();
	return str;
}
std::string Hud::getThrust(float x, float y, float z)
{
	std::stringstream ss (std::stringstream::in | std::stringstream::out);
	ss << "Thrust (x, y, z): " <<std::setprecision(7) << x << " " << y << " " <<z;
	std::string str = ss.str();
	return str;
}


void Hud::updateText(float xp, float yp, float zp,float xv, float yv, float zv,float xa, float ya, float za, float xo, float yo, float zo,float xt, float yt, float zt)
{
	hudGeode->removeDrawable(pos);
	pos = new osgText::Text;
    pos->setFont(osgText::readFontFile("fonts/vera.ttf"));
    pos->setColor(osg::Vec4(255,255,255,1.0f));
    pos->setCharacterSize(20.0f);
    pos->setLayout( osgText::Text::LEFT_TO_RIGHT );
	pos->setText(getPos(xp, yp ,zp));
	pos->setPosition(osg::Vec3(0,150,0));
	hudGeode->addDrawable(pos);

	hudGeode->removeDrawable(speed);
	speed = new osgText::Text;
    speed->setFont(osgText::readFontFile("fonts/vera.ttf"));
    speed->setColor(osg::Vec4(255,255,255,1.0f));
    speed->setCharacterSize(20.0f);
    speed->setLayout( osgText::Text::LEFT_TO_RIGHT );
	speed->setText(getSpeed(xv, yv ,zv));
	speed->setPosition(osg::Vec3(0,130,0));
	hudGeode->addDrawable(speed);

	hudGeode->removeDrawable(acce);
	acce = new osgText::Text;
    acce->setFont(osgText::readFontFile("fonts/vera.ttf"));
    acce->setColor(osg::Vec4(255,255,255,1.0f));
    acce->setCharacterSize(20.0f);
    acce->setLayout( osgText::Text::LEFT_TO_RIGHT );
    acce->setText(getAcce(xa, ya ,za));
    acce->setPosition(osg::Vec3(0,110,0));
	hudGeode->addDrawable(acce);

	hudGeode->removeDrawable(thrust);
	thrust = new osgText::Text;
    thrust->setFont(osgText::readFontFile("fonts/vera.ttf"));
    thrust->setColor(osg::Vec4(255,255,255,1.0f));
    thrust->setCharacterSize(20.0f);
    thrust->setLayout( osgText::Text::LEFT_TO_RIGHT );
    thrust->setText(getThrust(xt, yt ,zt));
    thrust->setPosition(osg::Vec3(0,90,0));
	hudGeode->addDrawable(thrust);

	hudGeode->removeDrawable(orientation);
	orientation = new osgText::Text;
    orientation->setFont(osgText::readFontFile("fonts/vera.ttf"));
    orientation->setColor(osg::Vec4(255,255,255,1.0f));
    orientation->setCharacterSize(20.0f);
    orientation->setLayout( osgText::Text::LEFT_TO_RIGHT );
    orientation->setText(getOrientation(xo, yo ,zo));
    orientation->setPosition(osg::Vec3(0,70,0));
	hudGeode->addDrawable(orientation);
	
	/*
	hudGeode->removeDrawable(text);
	text = new osgText::Text;
    text->setFont(osgText::readFontFile("fonts/vera.ttf"));
    text->setColor(osg::Vec4(255,255,255,1.0f));
    text->setCharacterSize(20.0f);
    text->setLayout( osgText::Text::LEFT_TO_RIGHT );
    text->setText("0, 0, 0");
    text->setPosition(osg::Vec3(0,200,0));
	hudGeode->addDrawable(text);
	*/
}

/*
void Hud::run1()
{
	



}

void Hud::run2()
{
	

}
*/
