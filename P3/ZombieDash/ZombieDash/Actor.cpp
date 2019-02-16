#include "Actor.h"
#include "StudentWorld.h"

Actor::Actor(int imageID, double startX, double startY) : GraphObject(imageID,startX,startY), keyPressed {}

virtual void Actor::doSomething()
{
	if (keyPressed != )
		Try to get user input(if any is available)




		If the user pressed the UP key then
		Increase my y location by one
		If the user pressed the DOWN key then
		Decrease my y location by one
		...
		If the user pressed the space bar to fire and I have flamethrower charges left, then
		Introduce three new flame objects into the game in front  of me
		...
}
...
 };