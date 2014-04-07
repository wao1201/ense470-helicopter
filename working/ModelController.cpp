/*
	ModelController
		Sets up key events for the helicopter to increase and decrease rotation.
		Uses modified lab code to call our functions

		Credits: Tylor Froese, Brian Schwietzer, Trevor Douglas (using lab code)

*/

#include "ModelController.h"
#include "ScriptRunner.h"
#include "Logger.h"
#include <fstream>

//Override
bool ModelController::handle( const osgGA::GUIEventAdapter& ea,
		                       osgGA::GUIActionAdapter& aa )
{
	ScriptRunner * sr = ScriptRunner::getInstance();	if ( !_model )
	{
			return false;  //Make sure model is initialized
	}
	switch ( ea.getEventType())
	{

		case osgGA::GUIEventAdapter::KEYDOWN:
			switch( ea.getKey() )
			{
			case '2':
				gameRender->increaseRotor();
				break;
    		case '1':
				gameRender->decreaseRotor();
				break;
			case '3':
				gameRender->setneutral();
				break;
			case '0':
				gameRender->setzero();
				break;
			case 'C': case 'c':
				gameRender->centerjoystick();
				break;
			case 'p': case 'P':
				if(!sr->getStatus())
				{
					ifstream test;
					test.open("testScript.txt");
					sr->parseScript(test);

					sr->runScripts();
					Constants::getInstance()->disableMouse = true; // disable mouse when run script
				}
				break;
			case 'l': case 'L':
				Logger::getInstance()->toggleLogging();
				break;
			}
			break;
	}
	return false;

}