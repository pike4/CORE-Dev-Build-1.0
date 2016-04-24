#include "EventManager.h"
#include "Subject.h"
#include "StateManager.h"
#include "SystemManager.h"

void EventManager::start()
{
	w_KeyPress = new walkForwardButtonPressed();
	s_KeyPress = new walkBackwardButtonPressed();
	a_KeyPress = new walkLeftButtonPressed();
	d_KeyPress = new walkRightButtonPressed();
	up_KeyPress = w_KeyPress;
	down_KeyPress = s_KeyPress;
	left_KeyPress = a_KeyPress;
	right_KeyPress = d_KeyPress;

	mouseMotion = new mouseMoved();
	mouse1Press = new mouseDown();
	mouse1Release = new mouseUp();
}

void EventManager::update()
{
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
			case SDL_QUIT:
			{
				quit = true;
				break;
			}

			case SDL_KEYDOWN:
			{
				if (e.key.repeat)
				{
					break;
				}
				
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit = true;
					break;
				case SDLK_1:
					break;
				case SDLK_w:
					w_KeyPress->execute(1);
					printf("AAAAAAA");
					break;
				case SDLK_s:
					s_KeyPress->execute(1);
					break;
				case SDLK_a:
					a_KeyPress->execute(1);
					break;
				case SDLK_d:
					d_KeyPress->execute(1);
					break;
				case SDLK_UP:
					up_KeyPress->execute(1);
					break;
				case SDLK_LEFT:
					left_KeyPress->execute(1);
					StateManager::enqueue(new ChangeStateCommand(StateManager::CORE_PAUSED));
					break;
				case SDLK_RIGHT:
					StateManager::enqueue(new ChangeStateCommand(StateManager::CORE_RUNNING));
					break;
				case SDLK_DOWN:
					down_KeyPress->execute(1);
					break;
				case SDLK_SPACE:
					AudioManager::enqueue(new PauseMusicCommand());
					break;
				case SDLK_LSHIFT:
					AudioManager::enqueue(new ResumeMusicCommand());
					break;
				}
				break;
			}

			case SDL_KEYUP:
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit = true;
					break;
				case SDLK_w:
					w_KeyPress->execute(-1);
					break;
				case SDLK_s:
					s_KeyPress->execute(-1);
					break;
				case SDLK_a:
					a_KeyPress->execute(-1);
					break;
				case SDLK_d:
					d_KeyPress->execute(-1);
					break;
				case SDLK_UP:
					up_KeyPress->execute(-1);
					break;
				case SDLK_LEFT:
					left_KeyPress->execute(-1);
					break;
				case SDLK_RIGHT:
					right_KeyPress->execute(-1);
					break;
				case SDLK_DOWN:
					down_KeyPress->execute(-1);
					break;
				}
				break;
			}

			case SDL_MOUSEMOTION:
			{
				mouseMotion->execute(0);
				break;
			}

			case SDL_MOUSEBUTTONDOWN:
			{
				mouse1Press->execute(0);
				break;
			}

			case SDL_MOUSEBUTTONUP:
			{
				mouse1Release->execute(0);
				break;
			}
			}
	}

}

int EventManager::state;

#pragma region KeyEvent declarations
Subject* EventManager::a_KeyPress;
Subject* EventManager::b_KeyPress;
Subject* EventManager::c_KeyPress;
Subject* EventManager::d_KeyPress;
Subject* EventManager::e_KeyPress;
Subject* EventManager::f_KeyPress;
Subject* EventManager::g_KeyPress;
Subject* EventManager::h_KeyPress;
Subject* EventManager::i_KeyPress;
Subject* EventManager::j_KeyPress;
Subject* EventManager::k_KeyPress;
Subject* EventManager::l_KeyPress;
Subject* EventManager::m_KeyPress;
Subject* EventManager::n_KeyPress;
Subject* EventManager::o_KeyPress;
Subject* EventManager::p_KeyPress;
Subject* EventManager::q_KeyPress;
Subject* EventManager::r_KeyPress;
Subject* EventManager::s_KeyPress;
Subject* EventManager::t_KeyPress;
Subject* EventManager::u_KeyPress;
Subject* EventManager::v_KeyPress;
Subject* EventManager::w_KeyPress;
Subject* EventManager::x_KeyPress;
Subject* EventManager::y_KeyPress;
Subject* EventManager::z_KeyPress;
Subject* EventManager::space_KeyPress;
Subject* EventManager::lShift_KeyPress;
Subject* EventManager::lCtrl_KeyPress;
Subject* EventManager::left_KeyPress;
Subject* EventManager::right_KeyPress;
Subject* EventManager::up_KeyPress;
Subject* EventManager::down_KeyPress;
#pragma endregion

#pragma region Mouse Event Definitions
Subject* EventManager::mouse1Press;
Subject* EventManager::mouse1Release;
Subject* EventManager::mouse2Press;
Subject* EventManager::mouse2Release;
Subject* EventManager::mouse3Press;
Subject* EventManager::mouse3Release;
Subject* EventManager::mouse4Press;
Subject* EventManager::mouse4Release;
Subject* EventManager::mouse5Press;
Subject* EventManager::mouse5Release;
Subject* EventManager::scrollUp;
Subject* EventManager::scrollDown;
Subject* EventManager::mouseMotion;
#pragma endregion