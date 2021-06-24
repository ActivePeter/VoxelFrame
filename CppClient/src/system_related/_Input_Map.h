#pragma once

/**
 * M_ represent the macros
*/

/*! @defgroup buttons Mouse buttons
 *  @brief Mouse button IDs.
 *
 *  See [mouse button input](@ref input_mouse_button) for how these are used.
 *
 *  @ingroup input
 *  @{ */
#define M_Input_MOUSE_BUTTON_1 0
#define M_Input_MOUSE_BUTTON_2 1
#define M_Input_MOUSE_BUTTON_3 2
#define M_Input_MOUSE_BUTTON_4 3
#define M_Input_MOUSE_BUTTON_5 4
#define M_Input_MOUSE_BUTTON_6 5
#define M_Input_MOUSE_BUTTON_7 6
#define M_Input_MOUSE_BUTTON_8 7
#define M_Input_MOUSE_BUTTON_LAST M_Input_MOUSE_BUTTON_8
#define M_Input_MOUSE_BUTTON_LEFT M_Input_MOUSE_BUTTON_1
#define M_Input_MOUSE_BUTTON_RIGHT M_Input_MOUSE_BUTTON_2
#define M_Input_MOUSE_BUTTON_MIDDLE M_Input_MOUSE_BUTTON_3
/*! @} */

/* The unknown key */
#define M_Input_KEY_UNKNOWN -1

/* Printable keys */
#define M_Input_KEY_SPACE 32
#define M_Input_KEY_APOSTROPHE 39 /* ' */
#define M_Input_KEY_COMMA 44      /* , */
#define M_Input_KEY_MINUS 45      /* - */
#define M_Input_KEY_PERIOD 46     /* . */
#define M_Input_KEY_SLASH 47      /* / */
#define M_Input_KEY_0 48
#define M_Input_KEY_1 49
#define M_Input_KEY_2 50
#define M_Input_KEY_3 51
#define M_Input_KEY_4 52
#define M_Input_KEY_5 53
#define M_Input_KEY_6 54
#define M_Input_KEY_7 55
#define M_Input_KEY_8 56
#define M_Input_KEY_9 57
#define M_Input_KEY_SEMICOLON 59 /* ; */
#define M_Input_KEY_EQUAL 61     /* = */
#define M_Input_KEY_A 65
#define M_Input_KEY_B 66
#define M_Input_KEY_C 67
#define M_Input_KEY_D 68
#define M_Input_KEY_E 69
#define M_Input_KEY_F 70
#define M_Input_KEY_G 71
#define M_Input_KEY_H 72
#define M_Input_KEY_I 73
#define M_Input_KEY_J 74
#define M_Input_KEY_K 75
#define M_Input_KEY_L 76
#define M_Input_KEY_M 77
#define M_Input_KEY_N 78
#define M_Input_KEY_O 79
#define M_Input_KEY_P 80
#define M_Input_KEY_Q 81
#define M_Input_KEY_R 82
#define M_Input_KEY_S 83
#define M_Input_KEY_T 84
#define M_Input_KEY_U 85
#define M_Input_KEY_V 86
#define M_Input_KEY_W 87
#define M_Input_KEY_X 88
#define M_Input_KEY_Y 89
#define M_Input_KEY_Z 90
#define M_Input_KEY_LEFT_BRACKET 91  /* [ */
#define M_Input_KEY_BACKSLASH 92     /* \ */
#define M_Input_KEY_RIGHT_BRACKET 93 /* ] */
#define M_Input_KEY_GRAVE_ACCENT 96  /* ` */
#define M_Input_KEY_WORLD_1 161      /* non-US #1 */
#define M_Input_KEY_WORLD_2 162      /* non-US #2 */

/* Function keys */
#define M_Input_KEY_ESCAPE 256
#define M_Input_KEY_ENTER 257
#define M_Input_KEY_TAB 258
#define M_Input_KEY_BACKSPACE 259
#define M_Input_KEY_INSERT 260
#define M_Input_KEY_DELETE 261
#define M_Input_KEY_RIGHT 262
#define M_Input_KEY_LEFT 263
#define M_Input_KEY_DOWN 264
#define M_Input_KEY_UP 265
#define M_Input_KEY_PAGE_UP 266
#define M_Input_KEY_PAGE_DOWN 267
#define M_Input_KEY_HOME 268
#define M_Input_KEY_END 269
#define M_Input_KEY_CAPS_LOCK 280
#define M_Input_KEY_SCROLL_LOCK 281
#define M_Input_KEY_NUM_LOCK 282
#define M_Input_KEY_PRINT_SCREEN 283
#define M_Input_KEY_PAUSE 284
#define M_Input_KEY_F1 290
#define M_Input_KEY_F2 291
#define M_Input_KEY_F3 292
#define M_Input_KEY_F4 293
#define M_Input_KEY_F5 294
#define M_Input_KEY_F6 295
#define M_Input_KEY_F7 296
#define M_Input_KEY_F8 297
#define M_Input_KEY_F9 298
#define M_Input_KEY_F10 299
#define M_Input_KEY_F11 300
#define M_Input_KEY_F12 301
#define M_Input_KEY_F13 302
#define M_Input_KEY_F14 303
#define M_Input_KEY_F15 304
#define M_Input_KEY_F16 305
#define M_Input_KEY_F17 306
#define M_Input_KEY_F18 307
#define M_Input_KEY_F19 308
#define M_Input_KEY_F20 309
#define M_Input_KEY_F21 310
#define M_Input_KEY_F22 311
#define M_Input_KEY_F23 312
#define M_Input_KEY_F24 313
#define M_Input_KEY_F25 314
#define M_Input_KEY_KP_0 320
#define M_Input_KEY_KP_1 321
#define M_Input_KEY_KP_2 322
#define M_Input_KEY_KP_3 323
#define M_Input_KEY_KP_4 324
#define M_Input_KEY_KP_5 325
#define M_Input_KEY_KP_6 326
#define M_Input_KEY_KP_7 327
#define M_Input_KEY_KP_8 328
#define M_Input_KEY_KP_9 329
#define M_Input_KEY_KP_DECIMAL 330
#define M_Input_KEY_KP_DIVIDE 331
#define M_Input_KEY_KP_MULTIPLY 332
#define M_Input_KEY_KP_SUBTRACT 333
#define M_Input_KEY_KP_ADD 334
#define M_Input_KEY_KP_ENTER 335
#define M_Input_KEY_KP_EQUAL 336
#define M_Input_KEY_LEFT_SHIFT 340
#define M_Input_KEY_LEFT_CONTROL 341
#define M_Input_KEY_LEFT_ALT 342
#define M_Input_KEY_LEFT_SUPER 343
#define M_Input_KEY_RIGHT_SHIFT 344
#define M_Input_KEY_RIGHT_CONTROL 345
#define M_Input_KEY_RIGHT_ALT 346
#define M_Input_KEY_RIGHT_SUPER 347
#define M_Input_KEY_MENU 348