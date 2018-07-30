#include "CORE.h"
#include "CORE_Devices.h"
#include "CORE_Resources.h"
#include "CORE_SystemIO.h"

#include "SDL.h"

namespace CORE_Devices
{
	// Instantiate mapping from proprietary keycodes to engine keycodes
	void mapHW()
	{
		// Arrow keys
		hwMap[SDLK_UP] = key_up;
		hwMap[SDLK_DOWN] = key_down;
		hwMap[SDLK_LEFT] = key_left;
		hwMap[SDLK_RIGHT] = key_right;

		// Alpha keys
		hwMap[SDLK_q] = key_q;
		hwMap[SDLK_w] = key_w;
		hwMap[SDLK_e] = key_e;
		hwMap[SDLK_r] = key_r;
		hwMap[SDLK_t] = key_t;
		hwMap[SDLK_y] = key_y;
		hwMap[SDLK_u] = key_u;
		hwMap[SDLK_i] = key_i;
		hwMap[SDLK_o] = key_o;
		hwMap[SDLK_p] = key_p;
		hwMap[SDLK_a] = key_a;
		hwMap[SDLK_s] = key_s;
		hwMap[SDLK_d] = key_d;
		hwMap[SDLK_f] = key_f;
		hwMap[SDLK_g] = key_g;
		hwMap[SDLK_h] = key_h;
		hwMap[SDLK_j] = key_j;
		hwMap[SDLK_k] = key_k;
		hwMap[SDLK_l] = key_l;
		hwMap[SDLK_z] = key_z;
		hwMap[SDLK_x] = key_x;
		hwMap[SDLK_c] = key_c;
		hwMap[SDLK_v] = key_v;
		hwMap[SDLK_b] = key_b;
		hwMap[SDLK_n] = key_n;
		hwMap[SDLK_m] = key_m;

		// Numeric
		hwMap[SDLK_0] = key_0;
		hwMap[SDLK_1] = key_1;
		hwMap[SDLK_2] = key_2;
		hwMap[SDLK_3] = key_3;
		hwMap[SDLK_4] = key_4;
		hwMap[SDLK_5] = key_5;
		hwMap[SDLK_6] = key_6;
		hwMap[SDLK_7] = key_7;
		hwMap[SDLK_8] = key_8;
		hwMap[SDLK_9] = key_9;

		// Symbols
		hwMap[SDLK_BACKQUOTE] = key_apos;
		hwMap[SDLK_MINUS] = key_minus;
		hwMap[SDLK_EQUALS] = key_eq;
		hwMap[SDLK_LEFTBRACKET] = key_lbracket;
		hwMap[SDLK_RIGHTBRACKET] = key_rbracket;
		hwMap[SDLK_BACKSLASH] = key_bslash;
		hwMap[SDLK_SEMICOLON] = key_semicolon;
		hwMap[SDLK_QUOTE] = key_quote;
		hwMap[SDLK_COMMA] = key_comma;
		hwMap[SDLK_PERIOD] = key_period;
		hwMap[SDLK_SLASH] = key_fslash;
		hwMap[SDLK_SPACE] = key_space;

		// Control Keys
		hwMap[SDLK_ESCAPE]	= key_esc;
		hwMap[SDLK_TAB]		= key_tab;
		hwMap[SDLK_CAPSLOCK]= key_caps;
		hwMap[SDLK_LSHIFT]	= key_lshift;
		hwMap[SDLK_LCTRL]	= key_lctrl;
		hwMap[SDLK_LALT]	= key_lalt;
		hwMap[SDLK_BACKSPACE] = key_bspace;
		hwMap[SDLK_RETURN]	= key_enter;
		hwMap[SDLK_RSHIFT]	= key_rshift;
		hwMap[SDLK_RALT]	= key_ralt;
		hwMap[SDLK_MENU]	= key_menu;
		hwMap[SDLK_RCTRL]	= key_rctl;
		hwMap[SDLK_INSERT]	= key_ins;
		hwMap[SDLK_HOME]	= key_home;
		hwMap[SDLK_PAGEUP]	= key_pageup;
		hwMap[SDLK_DELETE]	= key_del;
		hwMap[SDLK_END]		= key_end;
		hwMap[SDLK_PAGEDOWN] = key_pagedown;
		hwMap[SDLK_PRINTSCREEN] = key_prtscn;
		hwMap[SDLK_SCROLLLOCK] = key_scrolllock;
		hwMap[SDLK_PAUSE] = key_pausebreak;
		hwMap[SDLK_LGUI] = key_lwindows;
		hwMap[SDLK_RGUI] = key_rwindows;
		
		// Function keys
		hwMap[SDLK_F1]	= key_f1;
		hwMap[SDLK_F2]	= key_f2;
		hwMap[SDLK_F3]	= key_f3;
		hwMap[SDLK_F4]	= key_f4;
		hwMap[SDLK_F5]	= key_f5;
		hwMap[SDLK_F6]	= key_f6;
		hwMap[SDLK_F7]	= key_f7;
		hwMap[SDLK_F8]	= key_f8;
		hwMap[SDLK_F9]	= key_f9;
		hwMap[SDLK_F10]	= key_f10;
		hwMap[SDLK_F11]	= key_f11;
		// hwMap[SDLK_F12]	= key_f12;

		// Numpad numbers
		hwMap[SDLK_KP_0] = key_num_0;
		hwMap[SDLK_KP_1] = key_num_1;
		hwMap[SDLK_KP_2] = key_num_2;
		hwMap[SDLK_KP_3] = key_num_3;
		hwMap[SDLK_KP_4] = key_num_4;
		hwMap[SDLK_KP_5] = key_num_5;
		hwMap[SDLK_KP_6] = key_num_6;
		hwMap[SDLK_KP_7] = key_num_7;
		hwMap[SDLK_KP_8] = key_num_8;
		hwMap[SDLK_KP_9] = key_num_9;

		// Other numpad keys
		hwMap[SDLK_KP_DIVIDE] = key_num_fslash;
		hwMap[SDLK_KP_MULTIPLY] = key_num_ast;
		hwMap[SDLK_KP_MINUS] = key_num_minus;
		hwMap[SDLK_KP_PLUS] = key_num_plus;
		hwMap[SDLK_KP_ENTER] = key_num_enter;
		hwMap[SDLK_KP_PERIOD] = key_num_period;
		hwMap[SDLK_NUMLOCKCLEAR] = key_numlock;

		// Mouse events
		hwMap[SDL_MOUSEMOTION] = mouseMoved;
		hwMap[SDL_MOUSEBUTTONDOWN] = mouse1Down;
		hwMap[SDL_MOUSEBUTTONUP] = mouse1Up;
	}

	void start()
	{
		mapHW();

		keyMap[key_w].push_back(walkForwardButtonDown);
		keyMap[key_s].push_back(walkBackwardButtonDown);
		keyMap[key_a].push_back(walkLeftButtonDown);
		keyMap[key_d].push_back(walkRightButtonDown);
	}

	void update()
	{
		while (SDL_PollEvent(&e))
		{
			Event newEvent = (0);
			switch (e.type)
			{
			case SDL_QUIT:
				{
					CORE::quit = true;
					break;
				}
			
				case SDL_KEYDOWN:
				{
					if (e.key.repeat)
						break;
					newEvent.opcode = getKeyCode(e.key.keysym.sym);
					newEvent.push(BUTTON_DOWN);
					notifyStateManager(newEvent);
					break;
				}

				case SDL_KEYUP:
				{
					newEvent.opcode = getKeyCode(e.key.keysym.sym);
					newEvent.push(BUTTON_UP);

					notifyStateManager(newEvent);
					break;
				}

				case SDL_MOUSEMOTION:
				{
					int x, y;
					SDL_GetMouseState(&x, &y);

					newEvent.opcode = getKeyCode(SDL_MOUSEMOTION);
					newEvent.push(x);
					newEvent.push(y);

					notifyStateManager(newEvent);
					break;
				}

				case SDL_MOUSEBUTTONDOWN:
				{
					int x, y;
					SDL_GetMouseState(&x, &y);

					newEvent.opcode = mouse1Down;
					newEvent.push(0);
					newEvent.push(x);
					newEvent.push(y);

					notifyStateManager(newEvent);
					break;
				}

				case SDL_MOUSEBUTTONUP:
				{
					int x, y;
					SDL_GetMouseState(&x, &y);

					newEvent.opcode = mouse1Up;
					newEvent.push(0);
					newEvent.push(x);
					newEvent.push(y);

					notifyStateManager(newEvent);
					break;
				}
			}
		}

	}

	int getKeyCode(int keyCode)
	{
		if (hwMap.find(keyCode) != hwMap.end())
		{
			return hwMap[keyCode];
		}
		
		CORE_SystemIO::error("CORE_Devices error: keycode not found");
		return keyError;
	}

	void handleEvent(int eventCode, int posOrNeg, int x, int y)
	{

	}

	//Maps the current keycode to all of its matching CORE events and passes them to the State
	//Manager along with some other info as needed
	void notifyStateManager(Event e)
	{
		for (int i = 0; i < keyMap[e.opcode].size(); i++)
		{
			Event keyEvent = e;
			keyEvent.opcode = keyMap[e.opcode][i];

			CORE::handle(keyEvent);
		}
		
		CORE::handle(e);
	}
	
	SDL_Event e;
	int state;
	std::map<int, std::vector<int>> keyMap;

	//Maps proprietary hardware event codes to standard CORE event codes
	std::map<int, int> hwMap;
}