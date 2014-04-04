/*
	Command
		Executes the command with the given parameters

		Credits: Tylor Froese, Brian Schwietzer

*/

#include "Command.h"
#include "Render.h"
#include <vector>
#include <iostream>
#include "SleepThread.h"

Command::Command(COMMAND_TYPE command, vector<float> parameters)
{
	commandName = command;
	params = parameters;
	//timeStamp = 0;
	sleepThread = NULL;
}

bool Command::executeCommand(Render * render)
{
	bool done = false;
	//cout<<commandName<<endl;
	switch(commandName)
	{
	case set_joystick:
		//cout<<commandName<<endl;
		cout << printf("setting joystick to %f degrees, %f degrees\n", params[0],params[1]);
		render->setJoystick(params[0],params[1]);
		return true;
		break;
	case centre_joystick:
		//cout<<commandName<<endl;
		cout << "centering the joystick\n";
		render->centerjoystick();
		return true;
		break;
	case throttle:
		//cout<<commandName<<endl;
		cout << "setting the throttle to " << params[0] << endl;
		render->setThrottle(params[0]);
		return true;
		break;
	case error:
		return true;
		break;
	case delay:
		//cout<<commandName<<endl;
		if(sleepThread == NULL) {
			sleepThread = new SleepThread(params[0]);
			sleepThread->start();
		}
		done = wait(sleepThread);
		return done;
		break;
	}
}

bool Command::wait(SleepThread * sleepThread)
{
	if(sleepThread->isRunning())
	{
		return false;
	}
	delete sleepThread;
	return true;
}
