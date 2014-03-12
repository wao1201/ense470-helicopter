/*
	TimerHandler
		Handles the actions that need to be done on each frame
		Gets mouse coords and sends them to the force redirection function
		Calls updateGamePlay to calculate the physics and move the helicopter


			
		Credits: Karlee Stein, Trevor Douglas (using lab code)

*/

#include "TimerHandler.h"

bool TimerHandler::handle( const osgGA::GUIEventAdapter& ea,
		                       osgGA::GUIActionAdapter& aa )
{
	
	switch ( ea.getEventType())
	{
	case osgGA::GUIEventAdapter::FRAME:

		float x = ea.getX();
		float y = ea.getY();
		std::cout << "X:  " << x << std::endl;
		std::cout << "Y:  " << y << std::endl;
		gameRender->updateDirection(x, y);
		gameRender->updateGamePlay();
		_count++;
		break;
	}

	return false;



}
