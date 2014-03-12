/*
	ModelController
		Sets up key events for the helicopter to increase and decrease rotation.
		Uses modified lab code to call our functions

		Credits: Tylor Froese, Brian Schwietzer, Trevor Douglas (using lab code)

*/


#include "ModelController.h"

//Override
bool ModelController::handle( const osgGA::GUIEventAdapter& ea,
		                       osgGA::GUIActionAdapter& aa )
{

	if ( !_model )
	{
			return false;  //Make sure model is initialized
	}
	switch ( ea.getEventType())
	{

		case osgGA::GUIEventAdapter::KEYDOWN:
			switch( ea.getKey() )
			{
			case '1':
				gameRender->increaseRotor();
				break;

    		case '2':
				gameRender->decreaseRotor();
				break;
			case '3':
				gameRender->neutralRotor();
				break;

			}
			break;
	}
	return false;

}