
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
    text = new osgText::Text;
    text->setFont(osgText::readFontFile("fonts/vera.ttf"));
    text->setColor(osg::Vec4(255,255,255,1.0f));
    text->setCharacterSize(20.0f);
    text->setLayout( osgText::Text::LEFT_TO_RIGHT );
    text->setText("");
    text->setPosition(osg::Vec3(0,50,0));

    hudGeode->addDrawable(text);

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


void Hud::setText(const std::string& hudText)
{
    text->setText(hudText);
}

void Hud::setPosition(osg::Vec3d position)
{
    text->setPosition(position);
}


void Hud::setDisplayPos(const std::string& logInfo)
{
	text->setText(logInfo);
	text->setPosition(osg::Vec3(0,150,0));
}

void Hud::setDisplaySpeed(const std::string& logInfo)
{
	text->setText(logInfo);
	text->setPosition(osg::Vec3(0,130,0));
}

void Hud::setDisplayAcce(const std::string& logInfo)
	{
	text->setText(logInfo);
	text->setPosition(osg::Vec3(0,110,0));
}

void Hud::setDisplayThrust(const std::string& logInfo)
	{
	text->setText(logInfo);
	text->setPosition(osg::Vec3(0,90,0));
}

void Hud::setDisplayOrientation(const std::string& logInfo)
	{
	text->setText(logInfo);
	text->setPosition(osg::Vec3(0,70,0));
}



/*
void Hud::run1()
{
	



}

void Hud::run2()
{
	

}
*/
