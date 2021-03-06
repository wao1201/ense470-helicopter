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

#include "ScriptRunner.h"
#include "Logger.h"
#include "ModelController.h"
#include "Render.h"
#include "TimerHandler.h"
#include "Vector2.h"
#include "Constants.h"
#include <osg/ShapeDrawable>
#include <iostream>
#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/NodeTrackerManipulator>
#include <osg/FrameStamp>

void Render::Game_Play(){
	crash = false;
	friction = true;
	missileCollison = false;
	fireTimer=Constants::getInstance()->fireRate;

	//hud
	hud.initializeHudText();
	osg::Camera * hudCamera;

	ScriptRunner * sr = ScriptRunner::getInstance();
	sr->setRender(this);
	osg::ref_ptr<osg::Node> helicopter = osgDB::readNodeFile("Sikorsky2.osg");
	osg::ref_ptr<osg::Node> ground = osgDB::readNodeFile("lz.osg");
	osg::ref_ptr<osg::Node> flycow = osgDB::readNodeFile("cow.osg");

	ball1  = new osg::ShapeDrawable;
	ball1->setShape( new osg::Sphere(osg::Vec3(0.0f, 0.0f,0.0f), 25.0f));
	ball1->setColor(osg::Vec4(0.0f,0.0f,1.0f,1.0f));
	osg::ref_ptr<osg::Geode> ball1Node = new osg::Geode;
	ball1Node->addDrawable(ball1.get());

	ball2  = new osg::ShapeDrawable;
	ball2->setShape( new osg::Sphere(osg::Vec3(0.0f, 0.0f,0.0f), 25.0f));
	ball2->setColor(osg::Vec4(0.0f,0.0f,1.0f,1.0f));
	osg::ref_ptr<osg::Geode> ball2Node = new osg::Geode;
	ball2Node->addDrawable(ball2.get());

	ball3  = new osg::ShapeDrawable;
	ball3->setShape( new osg::Sphere(osg::Vec3(0.0f, 0.0f,0.0f), 25.0f));
	ball3->setColor(osg::Vec4(0.0f,0.0f,1.0f,1.0f));
	osg::ref_ptr<osg::Geode> ball3Node = new osg::Geode;
	ball3Node->addDrawable(ball3.get());

	tor1Tr = new osg::PositionAttitudeTransform;
	tor2Tr = new osg::PositionAttitudeTransform;
	tor3Tr = new osg::PositionAttitudeTransform;

	tor1Tr->addChild(ball1Node.get());
	tor2Tr->addChild(ball2Node.get());
	tor3Tr->addChild(ball3Node.get());

	tor1Tr->setPosition(osg::Vec3(0.0f, -200.0f, 80.0f));
	tor2Tr->setPosition(osg::Vec3(10.0f, -300.0f, 70.0f));
	tor3Tr->setPosition(osg::Vec3(20.0f, -400.0f, 60.0f));

	osg::ref_ptr<osg::Group> torusGroup = new osg::Group();
	torusGroup->addChild(tor1Tr);
	torusGroup->addChild(tor2Tr);
	torusGroup->addChild(tor3Tr);

	helicopterTransform = new osg::PositionAttitudeTransform;
	helicopterTransform->addChild(helicopter.get());
	helicopterTransform->setPosition(osg::Vec3(0.0f, 0.0f, 0.0f));
	helicopterTransform->setAttitude(osg::Quat((0), osg::Vec3d(1.0, 0.0, 0.0)));

	
	// rotate model
	helicopterTransform->setAttitude( 	 	
		osg::Quat( 	 	
			osg::DegreesToRadians(90.0f),osg::Vec3f(1,0,0), 	 	
	        osg::DegreesToRadians(0.0f),osg::Vec3f(0,0,1), 	 	
	        osg::DegreesToRadians(0.0f),osg::Vec3f(0,1,0) 	 	
	        ) 	 	
	);

	osg::ref_ptr<ModelController> ctrler = new ModelController(helicopterTransform.get(),this);

	groundTransform = new osg::PositionAttitudeTransform;
	groundTransform->addChild(ground.get());
	groundTransform->setPosition(osg::Vec3(0.0f, 0.0f, -100.0f));
	groundTransform->setScale(osg::Vec3(30.0f, 30.0f, 1.0f));

	modelPosition.set(helicopterTransform->getPosition());
	modelVelocity.set(osg::Vec3f(0,0,0));

	helicopterThrust = osg::Vec3f(0.0, 0.0, 0.0);

	
	// missile
	cowTransform = new osg::PositionAttitudeTransform;
	cowTransform->addChild(flycow.get());
	cowTransform->setPosition(modelPosition);
	cowTransform->setScale(osg::Vec3(0.3f, 0.3f, 0.3f));
	cowPosition.set(helicopterTransform->getPosition());
	cowVelocity.set(osg::Vec3f(0,0,0));
	fire = false; // default missile setting
	

	//hud
	hudCamera = hud.getHudCamera();
	
	osg::ref_ptr<osg::Group> rootNode = new osg::Group;  //Create a group node
	rootNode->addChild( groundTransform.get());
	rootNode->addChild( helicopterTransform.get());
	rootNode->addChild( cowTransform.get());
	rootNode->addChild(torusGroup.get());


	//hud
	rootNode->addChild(hudCamera);
	
	viewer.addEventHandler( ctrler.get());

	viewer.addEventHandler(new TimerHandler(this));	

	viewer.setUpViewInWindow(50,50,1024,768);

	viewer.setSceneData( rootNode.get());

	//This bit of code will have the camera follow the model
    osg::ref_ptr<osgGA::NodeTrackerManipulator> nodeTracker = new osgGA::NodeTrackerManipulator;
    nodeTracker->setHomePosition( osg::Vec3(0.0, 100.0, 0),
                                    osg::Vec3(), osg::Z_AXIS );
    //This will track the center of the helicopter and rotate as well.
    nodeTracker->setTrackerMode( osgGA::NodeTrackerManipulator::NODE_CENTER_AND_ROTATION );
    nodeTracker->setRotationMode( osgGA::NodeTrackerManipulator::TRACKBALL );
    nodeTracker->setTrackNode( helicopter );
    viewer.setCameraManipulator( nodeTracker );


	last = 0;
	viewer.run();
}

void Render::setThrottle(int position)
{
	float baseThrottle = Constants::getInstance()->baseThrottle;
	float maxThrottle = Constants::getInstance()->maxThrottle;

	if (position > 0)
	{
		if (position < maxThrottle)
			rotorForce = baseThrottle*position;
		else
			rotorForce = baseThrottle*maxThrottle;
	}
	else
		rotorForce = 0;
}

void Render::increaseRotor()
{
	float baseThrottle = Constants::getInstance()->baseThrottle;
	float maxThrottle = Constants::getInstance()->maxThrottle;

	if (rotorForce < baseThrottle*maxThrottle)
		rotorForce += baseThrottle; // 0.2;
	else
		rotorForce = baseThrottle*maxThrottle;
}

void Render::decreaseRotor()
{
	if(rotorForce > 0)
	{
		rotorForce -= Constants::getInstance()->baseThrottle; //0.2;
	}
	else
	{
		rotorForce = 0;
	}
}

// set rotor force to neutral
void Render::setneutral()
{
	rotorForce = Constants::getInstance()->helicopter->mass*Constants::getInstance()->gravity;
}
// set rotor force to zero
void Render::setzero()
{
	rotorForce = 0;
}
// set joystick to center
void Render::centerjoystick()
{
	helicopterOrientation.x_theta = helicopterOrientation.y_theta = 0;
}

// toggle friction
void Render::toggleFriction()
{
	 if(friction){
		std::cout<<"Toggle friction off"<<std::endl;
		
		friction = false;
	}
	else
	{
		friction = true;
		std::cout<<"Toggle friction on"<<std::endl;
	}
}

void Render::setJoystick(float theta, float phi)
{
	helicopterOrientation.x_theta = cos(osg::DegreesToRadians(phi))*(theta);
		
	helicopterOrientation.y_theta = sin(osg::DegreesToRadians(phi))*(theta);

}

//the following 2 functions are no longer being used to and real extent, but were left in to avoid errors in the functions that use them
osg::Vec3f Render::calculateForceDirections(float force, osg::Vec2f direction){
	Vector2 vector = Vector2::Vector2(direction.x(), direction.y());
	float viewHeight = viewer.getCamera()->getViewport()->height();
	float viewWidth = viewer.getCamera()->getViewport()->width();
	
	float relationship = (viewHeight<viewWidth)?15/(viewHeight/4):15/(viewWidth/4);
	
	float theta = osg::DegreesToRadians(vector.Length()*relationship);
	float phi = atan2(direction.y(), direction.x());

	Logger::getInstance()->log("Theta: " + f2s(theta) + " Phi: " + f2s(phi));
	return osg::Vec3f(-(force*sin(theta)*cos(phi)), -(force*sin(theta)*sin(phi)),(force*cos(theta)));
}

void Render::updateDirection(float x, float y){
	float viewHeight = viewer.getCamera()->getViewport()->height();
	float viewWidth = viewer.getCamera()->getViewport()->width();
 
	y = y - (viewHeight/2);
	x = x - (viewWidth/2);
	if(viewHeight < viewWidth)
	{
		y = (y>viewHeight/4)?(viewHeight/4):y;
		y = (y<(-viewHeight/4))?-(viewHeight/4):y;
		x = (x>viewHeight/4)?(viewHeight/4):x;
		x = (x<(-viewHeight/4))?-(viewHeight/4):x;
	} else {
		y = (y>viewWidth/4)?(viewWidth/4):y;
		y = (y<(-viewWidth/4))?-(viewWidth/4):y;
		x = (x>viewWidth/4)?(viewWidth/4):x;
		x = (x<(-viewWidth/4))?-(viewWidth/4):x;
	}
	
  osg::Vec2f xy(x, y);

 helicopterThrust = calculateForceDirections(rotorForce, xy);
}

void Render::setGravity(float gravity)
{
	aGrav = gravity;
}

bool Render::detectCollision(osg::BoundingSphere& bs1, osg::BoundingSphere& bs2)
{
	if (bs1.intersects(bs2))
		return true;
	else
		return false;
}

// milestone 3
void Render::roll(float angle)
{
	helicopterOrientation.y_theta += angle;
	if(helicopterOrientation.y_theta > 30)
		helicopterOrientation.y_theta=30;
	else if(helicopterOrientation.y_theta < -30)
		helicopterOrientation.y_theta =-30;

}

void Render::pitch(float angle)
{
	helicopterOrientation.x_theta += angle;
	if(helicopterOrientation.x_theta > 30)
		helicopterOrientation.x_theta=30;
	else if(helicopterOrientation.x_theta < -30)
		helicopterOrientation.x_theta =-30;
}

void Render::yaw(float angle)
{
	//eliminate negatinve orientation problem:
	helicopterOrientation.z_theta += angle;
	if(helicopterOrientation.z_theta<0)
		helicopterOrientation.z_theta = 360 + helicopterOrientation.z_theta;

	helicopterOrientation.z_theta = fmod(helicopterOrientation.z_theta,360);
}

void Render::updateGamePlay()
{
	//Cow collision detection:
	if (Render::detectCollision(osg::BoundingSphere(cowTransform->getBound()), osg::BoundingSphere(tor1Tr->getBound())) && missileCollison==false)
	{
		missileCollison = true;
		ball1->setColor(osg::Vec4(0.0f,1.0f,0.0f,0.0f));
		Logger::getInstance()->log("Cow collision with ball #1");
		std::cout<<"Cow impacts ball #1\n";
	}
	if (Render::detectCollision(osg::BoundingSphere(cowTransform->getBound()), osg::BoundingSphere(tor2Tr->getBound())) && missileCollison==false)
	{
		missileCollison = true;
		ball2->setColor(osg::Vec4(0.0f,1.0f,0.0f,0.0f));
		Logger::getInstance()->log("Cow collision with ball #2");
		std::cout<<"Cow impacts ball #2\n";
	}
	if (Render::detectCollision(osg::BoundingSphere(cowTransform->getBound()), osg::BoundingSphere(tor3Tr->getBound())) && missileCollison==false)
	{
		missileCollison = true;
		ball3->setColor(osg::Vec4(0.0f,1.0f,0.0f,0.0f));
		Logger::getInstance()->log("Cow collision with ball #3");
		std::cout<<"Cow impacts ball #3\n";
	}

	if((cowPosition.z() < 0) && missileCollison==false)
	{  //these ones should be radius of ball
		missileCollison = true;
		std::cout<<"Cow impacts ground\n";
		Logger::getInstance()->log("Cow impacts ground\n");

	}


	if (Render::detectCollision(osg::BoundingSphere(helicopterTransform->getBound()), osg::BoundingSphere(tor1Tr->getBound())))
	{
		ball1->setColor(osg::Vec4(1.0f,0.0f,0.0f,0.0f));
		Logger::getInstance()->log("Collision with ball #1");
	}
	if (Render::detectCollision(osg::BoundingSphere(helicopterTransform->getBound()), osg::BoundingSphere(tor2Tr->getBound())))
	{
		ball2->setColor(osg::Vec4(1.0f,0.0f,0.0f,0.0f));
		Logger::getInstance()->log("Collision with ball #2");
	}
	if (Render::detectCollision(osg::BoundingSphere(helicopterTransform->getBound()), osg::BoundingSphere(tor3Tr->getBound())))
	{
		ball3->setColor(osg::Vec4(1.0f,0.0f,0.0f,0.0f));
		Logger::getInstance()->log("Collision with ball #3");
	}

	float frictionScalar;
	if(friction==true)
		frictionScalar = Constants::getInstance()->frictionConstant;//*sqrt(pow(modelVelocity.x(),2)+pow(modelVelocity.y(),2)+pow(modelVelocity.z(),2));
	else
		frictionScalar = 0;

	float mass = Constants::getInstance()->helicopter->mass;

	float axForce = (sin(osg::DegreesToRadians(helicopterOrientation.y_theta))*rotorForce)//magnitude of rotor initially this direction
					*cos(osg::DegreesToRadians(helicopterOrientation.z_theta))//transform for when heli turns
					+(sin(osg::DegreesToRadians(helicopterOrientation.x_theta))*rotorForce)//magnitude of rotor initially in other direction
					*sin(osg::DegreesToRadians(helicopterOrientation.z_theta))//transform for when heli turns
					- frictionScalar*modelVelocity.x();//friction portion
	float ayForce = -(((sin(osg::DegreesToRadians(helicopterOrientation.x_theta))*rotorForce)//same as for axForce
					*cos(osg::DegreesToRadians(helicopterOrientation.z_theta))
					+(sin(osg::DegreesToRadians(helicopterOrientation.y_theta))*rotorForce)
					*sin(osg::DegreesToRadians(helicopterOrientation.z_theta)))
					- frictionScalar*modelVelocity.y());
	float azForce = cos(osg::DegreesToRadians(helicopterOrientation.x_theta))*cos(osg::DegreesToRadians(helicopterOrientation.y_theta))*rotorForce + aGrav*mass - frictionScalar*modelVelocity.z();

	float xAcc = axForce/mass;
	float yAcc = ayForce/mass;
	float zAcc = azForce/mass;


	float delta = 0.0235; //viewer.getFrameStamp()->getReferenceTime() - last;

	last = viewer.getFrameStamp()->getReferenceTime();

	float xPos = modelPosition.x() + (modelVelocity.x()*delta) + (0.5)*xAcc*(pow(delta,2));
	float xVel = (modelVelocity.x() + xAcc*delta)*0.99999999999;

	float yPos = modelPosition.y() + (modelVelocity.y()*delta) + (0.5)*yAcc*(pow(delta,2));
	float yVel = (modelVelocity.y() + yAcc*delta)*0.99999999999;

	float zPos = modelPosition.z() + (modelVelocity.z()*delta) + (0.5)*zAcc*(pow(delta,2));
	float zVel = (modelVelocity.z() + zAcc*delta)*0.99999999999;

	if(zPos < 1){  //these ones should be radius of ball
		if(zVel < -3)//THIS VALUE IS SUBJECT TO CHANGE
		{
			crash=true;
			Logger::getInstance()->log("Collison with ground");
		}
		else
		{
			Logger::getInstance()->log("Successful landing");
		}

		zPos = 1;
		zVel *= 0;

	}

	hud.crashed(crash);


	Logger* logger = Logger::getInstance();
	string something = f2s(xPos);
	logger->log("X Pos: " + f2s(xPos) + " Y Pos: " + f2s(yPos) + " Z Pos: " + f2s(zPos)); 
	logger->log("X Vel: " + f2s(xVel) + " Y Vel: " + f2s(yVel) +" Z Vel: " + f2s(zVel));
	logger->log("X Acc: " + f2s(xAcc) + " Y Acc: " + f2s(yAcc) +" Z Acc: " + f2s(zAcc));
	logger->log("Throttle Position: " + f2s(rotorForce/Constants::getInstance()->baseThrottle));

	modelPosition.set(osg::Vec3d(xPos, yPos, zPos));
	modelVelocity.set(osg::Vec3f(xVel, yVel, zVel));
	helicopterTransform->setPosition(modelPosition);




	//m3: missile
	if(fire == true)
	{
		if(fireTimer==Constants::getInstance()->fireRate)
		{
			cowVelocity.set(osg::Vec3f((sin(osg::DegreesToRadians(helicopterOrientation.z_theta)))*Constants::getInstance()->missile->Airspeed + (modelVelocity.x()*delta),
										-((cos(osg::DegreesToRadians(helicopterOrientation.z_theta)))*Constants::getInstance()->missile->Airspeed + (modelVelocity.y()*delta)),
										(sin(-(osg::DegreesToRadians(helicopterOrientation.x_theta+5))))*Constants::getInstance()->missile->Airspeed + (-modelVelocity.z()*delta)));

			cowPosition.set(osg::Vec3d(cowPosition.x() + cowVelocity.x()*delta,cowPosition.y() + cowVelocity.y()*delta,cowPosition.z() + cowVelocity.z()*delta));

			cowTransform->setPosition(cowPosition);
		}
		if(fireTimer<=Constants::getInstance()->fireRate && fireTimer>0)
		{
			cowPosition.set(osg::Vec3d(cowPosition.x() + cowVelocity.x()*delta,cowPosition.y() + cowVelocity.y()*delta,cowPosition.z() + cowVelocity.z()*delta));

			cowTransform->setPosition(cowPosition);
		}

		fireTimer--;
		if(fireTimer<=0)
		{
			missileCollison = false;
			fireTimer=Constants::getInstance()->fireRate;
			fire=false;
		}
	}
	else
	{
		cowTransform->setPosition(modelPosition);
		cowPosition = modelPosition;
	}

	// orientation
	helicopterTransform->setAttitude( 	 	
		osg::Quat( 	 	
			osg::DegreesToRadians(90 + helicopterOrientation.x_theta),osg::Vec3f(1,0,0), 	 	
	        osg::DegreesToRadians(helicopterOrientation.y_theta),osg::Vec3f(0,1,0), 	 	
	        osg::DegreesToRadians(helicopterOrientation.z_theta),osg::Vec3f(0,0,1) 	 	
	        ) 	 	
	);
	
	// hud
	hud.updateText(xPos, yPos, zPos, xVel, yVel, zVel, xAcc, yAcc, zAcc, helicopterOrientation.x_theta , helicopterOrientation.y_theta, helicopterOrientation.z_theta, axForce, ayForce, azForce, cowVelocity.x(), cowVelocity.y(), cowVelocity.z(),helicopterOrientation.x_theta+5);
	
	if(ScriptRunner::getInstance()->getStatus()){ ScriptRunner::getInstance()->doCommand(); }
	
}

void Render::startMoving()
{
    viewer.addEventHandler(new TimerHandler(this));
}

std::string Render::f2s(float num){

	stringstream ss (stringstream::in | stringstream::out);

	ss << num;

  string str = ss.str();
  return str;
}

