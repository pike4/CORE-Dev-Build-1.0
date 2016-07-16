#pragma once
#include "SDL.h"
#include "Globals.h"
#include "Commands.h"
#include "VideoManager.h"
#include "AudioManager.h"
#include "AssetsManifest.h"
#include "Subject.h"

#include <map>

const int BUTTON_UP = 0;
const int BUTTON_DOWN = 1;

class EventManager : public Manager
{
public:

	static void update();
	static void start();
	static int state;

	static void handleEvent(int eventCode, int posOrNeg = 0, int x = 0, int y = 0);

private:

#pragma region Joystick Events

#pragma endregion


	static std::map<int, std::vector<int>> keyMap;

	static void notifyStateManager(int eventCode, int posOrNeg = 0, int x = 0, int y = 0);

/*enum events
	{
		a_KeyPress,
		b_KeyPress,
		c_KeyPress,
		d_KeyPress,
		e_KeyPress,
		f_KeyPress,
		g_KeyPress,
		h_KeyPress,
		i_KeyPress,
		j_KeyPress,
		k_KeyPress,
		l_KeyPress,
		m_KeyPress,
		n_KeyPress,
		o_KeyPress,
		p_KeyPress,
		q_KeyPress,
		r_KeyPress,
		t_KeyPress,
		u_KeyPress,
		v_KeyPress,
		w_KeyPress,
		x_KeyPress,
		y_KeyPress,
		z_KeyPress,
		space_KeyPress,
		lShift_KeyPress,
		lCtrl_KeyPress
	};*/
};

enum UserDefinedEvents
{
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
	mouse4Up
};

