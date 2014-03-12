/*
	Render
		Holds the functions used for setting up the world and doing the physics and math calculations required to make the helicopter move
			Notable Functions:
			Game_Play() is the intro function required to set everything up
			updateGamePlay() does the physics calulations for the movement of the helicopter

			There are other functions that do the math and other functions
			
		Credits: Brian Schweitzer, Karlee Stein, Tylor Froese, Trevor Douglas (used lab code)

*/


#ifndef RENDER_H
#define RENDER_H

#include <osg/AnimationPath>
#include <osg/PositionAttitudeTransform>
#include <osgViewer/Viewer>
#include <iostream>


class Render{
  private:
	  osg::ref_ptr<osg::PositionAttitudeTransform> helicopterTransform;
	  osg::ref_ptr<osg::PositionAttitudeTransform> groundTransform;
	  osg::Vec3d modelPosition;
	  osg::Vec3f modelVelocity;
	  osgViewer::Viewer viewer;
	  float last;
	  float aGrav;
	  float rotorForce;
	  osg::Vec3f helicopterThrust;
  public:
	  Render() : last(0) {
		aGrav = -9.81;
		rotorForce = 0;
	  }
	  void Game_Play();
	  void increaseRotor();
	  void decreaseRotor();
	  void neutralRotor();
	  void updateDirection(float x, float y);
  	  void updateGamePlay();
	  void startMoving();
	  osg::Vec3f calculateForceDirections(float force, osg::Vec2f direction);
};

#endif