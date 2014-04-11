/*
	Render
		Holds the functions used for setting up the world and doing the physics and math calculations required to make the helicopter move
			Notable Functions:
			Game_Play() is the intro function required to set everything up
			updateGamePlay() does the physics calulations for the movement of the helicopter including calculating the forces of gravity, throttle, and friction
			setThrottle(int) takes a throttle value between 0-23 and updates the helicopter's throttle accordingly
			setJoystick(float, float) takes a value for theta and phi and updates the helicopter's direcion accordingly
			detectCollision(osg::BoundingSphere&, osg::BoundingSphere&) takes two bounding spheres (one for the helicopter and another for the obstacle) and
				determined if they intersect

			There are other functions that do the math and other functions
			
		Credits: Brian Schweitzer, Karlee Stein, Tylor Froese, Trevor Douglas (used lab code)

*/


#ifndef RENDER_H
#define RENDER_H

#include <osg/AnimationPath>
#include <osg/PositionAttitudeTransform>
#include <osgViewer/Viewer>
#include <iostream>
#include "Constants.h"
#include <osg/ShapeDrawable>
#include <osgText/Text>
#include <osg/Geode>
#include "hud.h"
#include "util.h"

class Render{
  private:
	  osg::ref_ptr<osg::PositionAttitudeTransform> helicopterTransform;
	  osg::ref_ptr<osg::PositionAttitudeTransform> groundTransform;
	  osg::ref_ptr<osg::PositionAttitudeTransform> cowTransform;///////////////////////////
	  osg::ref_ptr<osg::PositionAttitudeTransform> tor1Tr;
	  osg::ref_ptr<osg::PositionAttitudeTransform> tor2Tr;
	  osg::ref_ptr<osg::PositionAttitudeTransform> tor3Tr;
	  osg::ref_ptr<osg::ShapeDrawable> ball1;
	  osg::ref_ptr<osg::ShapeDrawable> ball2;
	  osg::ref_ptr<osg::ShapeDrawable> ball3;
	  osg::Vec3d modelPosition;
	  osg::Vec3f modelVelocity;
	  osgViewer::Viewer viewer;
	  float last;
	  float aGrav;
	  float rotorForce;
	  osg::Vec3f helicopterThrust;
	  bool crash;

	  bool friction;

	  osg::Vec3d cowPosition;
	  osg::Vec3f cowVelocity;
	  bool fire;
	  int fireTimer;


  public:
	  Render() : last(0) {
		  aGrav = (Constants::getInstance()->gravity)*(-1);
		rotorForce = 0;
	  }
	  void Game_Play();
	  void setThrottle(int position);
	  void increaseRotor();
	  void decreaseRotor();

	  void clearCrash(){crash=false;}

	  void setneutral();
	  void setzero();
	  void centerjoystick();

	  void setFire(){fire=true;}

	  void roll(float angle);
	  void pitch(float angle);
	  void yaw(float angle);

	  void toggleFriction();
	  	// hud initialize
	  Hud hud;

	  void setJoystick(float theta, float phi);
	  void updateDirection(float x, float y);
	  void setGravity(float gravity);
  	  void updateGamePlay();
	  void startMoving();
	  osg::Vec3f calculateForceDirections(float force, osg::Vec2f direction);
	  bool detectCollision(osg::BoundingSphere& bs1, osg::BoundingSphere& bs2);
	  void changeBallColour(osg::ref_ptr<osg::PositionAttitudeTransform>& ball);
	  std::string f2s(float num);

	  struct Orientation helicopterOrientation;
};

#endif