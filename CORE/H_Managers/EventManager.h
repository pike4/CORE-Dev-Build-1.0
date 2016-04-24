#pragma once
#include "SDL.h"
#include "Globals.h"
#include "Commands.h"
#include "VideoManager.h"
#include "AudioManager.h"
#include "AssetsManifest.h"
#include "CoreEvent.h"
#include "Subject.h"

#include <map>

class EventManager : public Manager
{
public:

	static void update();

	static void start();

	static int state;

	

private:

//CoreEvent objects to be explicitly and permanently hard-coded to their respective SDL_Events
#pragma region KeyEvent declarations
	static Subject* a_KeyPress;
	static Subject* b_KeyPress;
	static Subject* c_KeyPress;
	static Subject* d_KeyPress;
	static Subject* e_KeyPress;
	static Subject* f_KeyPress;
	static Subject* g_KeyPress;
	static Subject* h_KeyPress;
	static Subject* i_KeyPress;
	static Subject* j_KeyPress;
	static Subject* k_KeyPress;
	static Subject* l_KeyPress;
	static Subject* m_KeyPress;
	static Subject* n_KeyPress;
	static Subject* o_KeyPress;
	static Subject* p_KeyPress;
	static Subject* q_KeyPress;
	static Subject* r_KeyPress;
	static Subject* s_KeyPress;
	static Subject* t_KeyPress;
	static Subject* u_KeyPress;
	static Subject* v_KeyPress;
	static Subject* w_KeyPress;
	static Subject* x_KeyPress;
	static Subject* y_KeyPress;
	static Subject* z_KeyPress;
	static Subject* space_KeyPress;
	static Subject* lShift_KeyPress;
	static Subject* lCtrl_KeyPress;
	static Subject* left_KeyPress;
	static Subject* right_KeyPress;
	static Subject* up_KeyPress;
	static Subject* down_KeyPress;
#pragma endregion
#pragma region Mouse Events
	static Subject* mouse1Press;
	static Subject* mouse1Release;
	static Subject* mouse2Press;
	static Subject* mouse2Release;
	static Subject* mouse3Press;
	static Subject* mouse3Release;
	static Subject* mouse4Press;
	static Subject* mouse4Release;
	static Subject* mouse5Press;
	static Subject* mouse5Release;
	static Subject* scrollUp;
	static Subject* scrollDown;
	static Subject* mouseMotion;
#pragma endregion

#pragma region Joystick Events

#pragma endregion


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

map<int, CoreEvent> eventMap;
};