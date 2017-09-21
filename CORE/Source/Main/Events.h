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


   //Alpha Keys
   key_q,
   key_w,
   key_e,
   key_r,
   key_t,
   key_y,
   key_u,
   key_i,
   key_o,
   key_p,
   key_a,
   key_s,
   key_d,
   key_f,
   key_g,
   key_h,
   key_j,
   key_k,
   key_l,
   key_z,
   key_x,
   key_c,
   key_v,
   key_b,
   key_n,
   key_m,

   //Numeric
   key_1,
   key_2,
   key_3,
   key_4,
   key_5,
   key_6,
   key_7,
   key_8,
   key_9,
   key_10,

   //Symbols
   key_excalmation,
   key_at,
   key_pound,
   key_dollar,
   key_percent,
   key_carat,
   key_ampersand,
   key_asterisk,
   key_left_parenth,
   key_right_parenth,

   //Room
   entity_added,
   


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