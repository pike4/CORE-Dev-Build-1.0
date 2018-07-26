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
	key_0,
	key_1,
	key_2,
	key_3,
	key_4,
	key_5,
	key_6,
	key_7,
	key_8,
	key_9,

	//Symbols
	key_apos,
	key_exclam,
	key_at,
	key_pound,
	key_dollar,
	key_percent,
	key_carat,
	key_ampersand,
	key_asterisk,
	key_lparen,
	key_rparen,
	key_minus,
	key_eq,
	key_lbracket,
	key_rbracket,
	key_bslash,
	key_semicolon,
	key_quote,
	key_lt,
	key_gt,
	key_fslash,

	// Control Keys
	key_ltab,
	key_caps,
	key_lshift,
	key_lctrl,
	key_lalt,
	key_bspace,
	key_enter,
	key_rshift,
	key_ralt,
	key_rctl,
	key_ins,
	key_home,
	key_pageup,
	key_del,
	key_end,
	key_pagedown,

	// Function keys
	key_f1,
	key_f2,
	key_f3,
	key_f4,
	key_f5,
	key_f6,
	key_f7,
	key_f8,
	key_f9,
	key_f10,
	key_f11,
	key_f12,



	// Room
	entity_added,

	// Mouse
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