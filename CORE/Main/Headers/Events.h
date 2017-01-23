#pragma once
enum UserDefinedEvents
{
	////////////////////////////////
	//Engine events
	////////////////////////////////
	updateStep,
	drawStep,

	////////////////////////////////
	//Global Events
	////////////////////////////////
	menuChange,

	////////////////////////////////
	//Control Events
	////////////////////////////////
	mouseEnter,
	mouseLeave,
	mouseDrag,
	mousePress,
	mouseRelease,
	doubleClick,

	////////////////////////////////
	//
	////////////////////////////////
	walkForwardButtonDown,
	walkForwardButtonUp,
	walkBackwardButtonDown,
	walkBackwardButtonUp,
	walkLeftButtonDown,
	walkLeftButtonUp,
	walkRightButtonDown,
	walkRightButtonUp,
	walkDownButtonDown,
	walkDownButtonUp,
	interactButtonDown,
	interactButtonUp,
	mouseMoved,
	mouse1Down,
	mouse1Up,
	mouse2Down,
	mouse2Up,
	mouse3Down,
	mouse3Up,
	mouse4Down,
	mouse4Up,

	updatePos
};