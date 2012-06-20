//
//  Keyboard.cpp
//  flatland
//
//  Created by Ryan Evans on 5/30/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "KeyboardBindings.h"
#include <SDL.h>

v8::Handle<v8::Value> fl_kb_IsKeyDown(const v8::Arguments& args) {
    v8::Locker locker;
    v8::HandleScope handle_scope;
    uint32_t key = args[0]->ToUint32()->Uint32Value();
    Uint8* keys = SDL_GetKeyboardState(NULL);
    bool results = (bool)keys[key];
	return handle_scope.Close(v8::Boolean::New(results));
}

void fl_kb_SetScancodeConstants(v8::Handle<v8::ObjectTemplate>& codes) {
    v8::HandleScope handle_scope;
    codes->Set(v8::String::New("unknown"), v8::Integer::New(SDL_SCANCODE_UNKNOWN));
    codes->Set(v8::String::New("a"), v8::Integer::New(SDL_SCANCODE_A));
    codes->Set(v8::String::New("b"), v8::Integer::New(SDL_SCANCODE_B));
    codes->Set(v8::String::New("c"), v8::Integer::New(SDL_SCANCODE_C));
    codes->Set(v8::String::New("d"), v8::Integer::New(SDL_SCANCODE_D));
    codes->Set(v8::String::New("e"), v8::Integer::New(SDL_SCANCODE_E));
    codes->Set(v8::String::New("f"), v8::Integer::New(SDL_SCANCODE_F));
    codes->Set(v8::String::New("g"), v8::Integer::New(SDL_SCANCODE_G));
    codes->Set(v8::String::New("h"), v8::Integer::New(SDL_SCANCODE_H));
    codes->Set(v8::String::New("i"), v8::Integer::New(SDL_SCANCODE_I));
    codes->Set(v8::String::New("j"), v8::Integer::New(SDL_SCANCODE_J));
    codes->Set(v8::String::New("k"), v8::Integer::New(SDL_SCANCODE_K));
    codes->Set(v8::String::New("l"), v8::Integer::New(SDL_SCANCODE_L));
    codes->Set(v8::String::New("m"), v8::Integer::New(SDL_SCANCODE_M));
    codes->Set(v8::String::New("n"), v8::Integer::New(SDL_SCANCODE_N));
    codes->Set(v8::String::New("o"), v8::Integer::New(SDL_SCANCODE_O));
    codes->Set(v8::String::New("p"), v8::Integer::New(SDL_SCANCODE_P));
    codes->Set(v8::String::New("q"), v8::Integer::New(SDL_SCANCODE_Q));
    codes->Set(v8::String::New("r"), v8::Integer::New(SDL_SCANCODE_R));
    codes->Set(v8::String::New("s"), v8::Integer::New(SDL_SCANCODE_S));
    codes->Set(v8::String::New("t"), v8::Integer::New(SDL_SCANCODE_T));
    codes->Set(v8::String::New("u"), v8::Integer::New(SDL_SCANCODE_U));
    codes->Set(v8::String::New("v"), v8::Integer::New(SDL_SCANCODE_V));
    codes->Set(v8::String::New("w"), v8::Integer::New(SDL_SCANCODE_W));
    codes->Set(v8::String::New("x"), v8::Integer::New(SDL_SCANCODE_X));
    codes->Set(v8::String::New("y"), v8::Integer::New(SDL_SCANCODE_Y));
    codes->Set(v8::String::New("z"), v8::Integer::New(SDL_SCANCODE_Z));
    codes->Set(v8::String::New("0"), v8::Integer::New(SDL_SCANCODE_1));
    codes->Set(v8::String::New("1"), v8::Integer::New(SDL_SCANCODE_2));
    codes->Set(v8::String::New("2"), v8::Integer::New(SDL_SCANCODE_3));
    codes->Set(v8::String::New("3"), v8::Integer::New(SDL_SCANCODE_4));
    codes->Set(v8::String::New("4"), v8::Integer::New(SDL_SCANCODE_5));
    codes->Set(v8::String::New("5"), v8::Integer::New(SDL_SCANCODE_6));
    codes->Set(v8::String::New("6"), v8::Integer::New(SDL_SCANCODE_7));
    codes->Set(v8::String::New("7"), v8::Integer::New(SDL_SCANCODE_8));
    codes->Set(v8::String::New("8"), v8::Integer::New(SDL_SCANCODE_9));
    codes->Set(v8::String::New("9"), v8::Integer::New(SDL_SCANCODE_0));
    
    codes->Set(v8::String::New("return"), v8::Integer::New(SDL_SCANCODE_RETURN));
    codes->Set(v8::String::New("escape"), v8::Integer::New(SDL_SCANCODE_ESCAPE));
    codes->Set(v8::String::New("backspace"), v8::Integer::New(SDL_SCANCODE_BACKSPACE));
    codes->Set(v8::String::New("tab"), v8::Integer::New(SDL_SCANCODE_TAB));
    codes->Set(v8::String::New("space"), v8::Integer::New(SDL_SCANCODE_SPACE));
    
    codes->Set(v8::String::New("minus"), v8::Integer::New(SDL_SCANCODE_MINUS));
    codes->Set(v8::String::New("equals"), v8::Integer::New(SDL_SCANCODE_EQUALS));
    codes->Set(v8::String::New("left_bracket"), v8::Integer::New(SDL_SCANCODE_LEFTBRACKET));
    codes->Set(v8::String::New("right_bracket"), v8::Integer::New(SDL_SCANCODE_RIGHTBRACKET));
    codes->Set(v8::String::New("backslash"), v8::Integer::New(SDL_SCANCODE_BACKSLASH));
                                  
    codes->Set(v8::String::New("non_us_hash"), v8::Integer::New(SDL_SCANCODE_NONUSHASH));
    codes->Set(v8::String::New("semicolon"), v8::Integer::New(SDL_SCANCODE_SEMICOLON));
    codes->Set(v8::String::New("apostrophe"), v8::Integer::New(SDL_SCANCODE_APOSTROPHE));
    codes->Set(v8::String::New("grave"), v8::Integer::New(SDL_SCANCODE_GRAVE));
    codes->Set(v8::String::New("comma"), v8::Integer::New(SDL_SCANCODE_COMMA));
    codes->Set(v8::String::New("period"), v8::Integer::New(SDL_SCANCODE_PERIOD));
    codes->Set(v8::String::New("slash"), v8::Integer::New(SDL_SCANCODE_SLASH));
    
    codes->Set(v8::String::New("capslock"), v8::Integer::New(SDL_SCANCODE_CAPSLOCK));
    
    codes->Set(v8::String::New("f1"), v8::Integer::New(SDL_SCANCODE_F1));
    codes->Set(v8::String::New("f2"), v8::Integer::New(SDL_SCANCODE_F2));
    codes->Set(v8::String::New("f3"), v8::Integer::New(SDL_SCANCODE_F3));
    codes->Set(v8::String::New("f4"), v8::Integer::New(SDL_SCANCODE_F4));
    codes->Set(v8::String::New("f5"), v8::Integer::New(SDL_SCANCODE_F5));
    codes->Set(v8::String::New("f6"), v8::Integer::New(SDL_SCANCODE_F6));
    codes->Set(v8::String::New("f7"), v8::Integer::New(SDL_SCANCODE_F7));
    codes->Set(v8::String::New("f8"), v8::Integer::New(SDL_SCANCODE_F8));
    codes->Set(v8::String::New("f9"), v8::Integer::New(SDL_SCANCODE_F9));
    codes->Set(v8::String::New("f10"), v8::Integer::New(SDL_SCANCODE_F10));
    codes->Set(v8::String::New("f11"), v8::Integer::New(SDL_SCANCODE_F11));
    codes->Set(v8::String::New("f12"), v8::Integer::New(SDL_SCANCODE_F12));
    
    codes->Set(v8::String::New("printscreen"), v8::Integer::New(SDL_SCANCODE_PRINTSCREEN));
    codes->Set(v8::String::New("scrolllock"), v8::Integer::New(SDL_SCANCODE_SCROLLLOCK));
    codes->Set(v8::String::New("pause"), v8::Integer::New(SDL_SCANCODE_PAUSE));
    codes->Set(v8::String::New("insert"), v8::Integer::New(SDL_SCANCODE_INSERT));
    codes->Set(v8::String::New("home"), v8::Integer::New(SDL_SCANCODE_HOME));
    codes->Set(v8::String::New("pageup"), v8::Integer::New(SDL_SCANCODE_PAGEUP));
    codes->Set(v8::String::New("delete"), v8::Integer::New(SDL_SCANCODE_DELETE));
    codes->Set(v8::String::New("end"), v8::Integer::New(SDL_SCANCODE_END));
    codes->Set(v8::String::New("pagedown"), v8::Integer::New(SDL_SCANCODE_PAGEDOWN));
    codes->Set(v8::String::New("right"), v8::Integer::New(SDL_SCANCODE_RIGHT));
    codes->Set(v8::String::New("left"), v8::Integer::New(SDL_SCANCODE_LEFT));
    codes->Set(v8::String::New("down"), v8::Integer::New(SDL_SCANCODE_DOWN));
    codes->Set(v8::String::New("up"), v8::Integer::New(SDL_SCANCODE_UP));
    
    codes->Set(v8::String::New("numlock_clear"), v8::Integer::New(SDL_SCANCODE_NUMLOCKCLEAR));
    codes->Set(v8::String::New("divide"), v8::Integer::New(SDL_SCANCODE_KP_DIVIDE));
    codes->Set(v8::String::New("multiply"), v8::Integer::New(SDL_SCANCODE_KP_MULTIPLY));
    codes->Set(v8::String::New("minus"), v8::Integer::New(SDL_SCANCODE_KP_MINUS));
    codes->Set(v8::String::New("plus"), v8::Integer::New(SDL_SCANCODE_KP_PLUS));
    codes->Set(v8::String::New("enter"), v8::Integer::New(SDL_SCANCODE_KP_ENTER));
    codes->Set(v8::String::New("numpad_1"), v8::Integer::New(SDL_SCANCODE_KP_1));
    codes->Set(v8::String::New("numpad_2"), v8::Integer::New(SDL_SCANCODE_KP_2));
    codes->Set(v8::String::New("numpad_3"), v8::Integer::New(SDL_SCANCODE_KP_3));
    codes->Set(v8::String::New("numpad_4"), v8::Integer::New(SDL_SCANCODE_KP_4));
    codes->Set(v8::String::New("numpad_5"), v8::Integer::New(SDL_SCANCODE_KP_5));
    codes->Set(v8::String::New("numpad_6"), v8::Integer::New(SDL_SCANCODE_KP_6));
    codes->Set(v8::String::New("numpad_7"), v8::Integer::New(SDL_SCANCODE_KP_7));
    codes->Set(v8::String::New("numpad_8"), v8::Integer::New(SDL_SCANCODE_KP_8));
    codes->Set(v8::String::New("numpad_9"), v8::Integer::New(SDL_SCANCODE_KP_9));
    codes->Set(v8::String::New("numpad_0"), v8::Integer::New(SDL_SCANCODE_KP_0));
    codes->Set(v8::String::New("numpad_period"), v8::Integer::New(SDL_SCANCODE_KP_PERIOD));
    
    codes->Set(v8::String::New("non_us_backslash"), v8::Integer::New(SDL_SCANCODE_NONUSBACKSLASH));
    codes->Set(v8::String::New("application"), v8::Integer::New(SDL_SCANCODE_APPLICATION));
    codes->Set(v8::String::New("power"), v8::Integer::New(SDL_SCANCODE_POWER));
    codes->Set(v8::String::New("numpad_equals"), v8::Integer::New(SDL_SCANCODE_KP_EQUALS));
    codes->Set(v8::String::New("f13"), v8::Integer::New(SDL_SCANCODE_F13));
    codes->Set(v8::String::New("f14"), v8::Integer::New(SDL_SCANCODE_F14));
    codes->Set(v8::String::New("f15"), v8::Integer::New(SDL_SCANCODE_F15));
    codes->Set(v8::String::New("f16"), v8::Integer::New(SDL_SCANCODE_F16));
    codes->Set(v8::String::New("f17"), v8::Integer::New(SDL_SCANCODE_F17));
    codes->Set(v8::String::New("f18"), v8::Integer::New(SDL_SCANCODE_F18));
    codes->Set(v8::String::New("f19"), v8::Integer::New(SDL_SCANCODE_F19));
    codes->Set(v8::String::New("f20"), v8::Integer::New(SDL_SCANCODE_F20));
    codes->Set(v8::String::New("f21"), v8::Integer::New(SDL_SCANCODE_F21));
    codes->Set(v8::String::New("f22"), v8::Integer::New(SDL_SCANCODE_F22));
    codes->Set(v8::String::New("f23"), v8::Integer::New(SDL_SCANCODE_F23));
    codes->Set(v8::String::New("f24"), v8::Integer::New(SDL_SCANCODE_F24));
    codes->Set(v8::String::New("execute"), v8::Integer::New(SDL_SCANCODE_EXECUTE));
    codes->Set(v8::String::New("help"), v8::Integer::New(SDL_SCANCODE_HELP));
    codes->Set(v8::String::New("menu"), v8::Integer::New(SDL_SCANCODE_MENU));
    codes->Set(v8::String::New("select"), v8::Integer::New(SDL_SCANCODE_SELECT));
    codes->Set(v8::String::New("stop"), v8::Integer::New(SDL_SCANCODE_STOP));
    codes->Set(v8::String::New("again"), v8::Integer::New(SDL_SCANCODE_AGAIN));
    codes->Set(v8::String::New("undo"), v8::Integer::New(SDL_SCANCODE_UNDO));
    codes->Set(v8::String::New("cut"), v8::Integer::New(SDL_SCANCODE_CUT));
    codes->Set(v8::String::New("copy"), v8::Integer::New(SDL_SCANCODE_COPY));
    codes->Set(v8::String::New("paste"), v8::Integer::New(SDL_SCANCODE_PASTE));
    codes->Set(v8::String::New("find"), v8::Integer::New(SDL_SCANCODE_FIND));
    codes->Set(v8::String::New("mute"), v8::Integer::New(SDL_SCANCODE_MUTE));
    codes->Set(v8::String::New("volume_up"), v8::Integer::New(SDL_SCANCODE_VOLUMEUP));
    codes->Set(v8::String::New("volume_down"), v8::Integer::New(SDL_SCANCODE_VOLUMEDOWN));
    codes->Set(v8::String::New("numpad_comma"), v8::Integer::New(SDL_SCANCODE_KP_COMMA));
    codes->Set(v8::String::New("numpad_equals_as400"), v8::Integer::New(SDL_SCANCODE_KP_EQUALSAS400));
    
    codes->Set(v8::String::New("intl_1"), v8::Integer::New(SDL_SCANCODE_INTERNATIONAL1));
    codes->Set(v8::String::New("intl_2"), v8::Integer::New(SDL_SCANCODE_INTERNATIONAL2));
    codes->Set(v8::String::New("intl_3"), v8::Integer::New(SDL_SCANCODE_INTERNATIONAL3));
    codes->Set(v8::String::New("intl_4"), v8::Integer::New(SDL_SCANCODE_INTERNATIONAL4));
    codes->Set(v8::String::New("intl_5"), v8::Integer::New(SDL_SCANCODE_INTERNATIONAL5));
    codes->Set(v8::String::New("intl_6"), v8::Integer::New(SDL_SCANCODE_INTERNATIONAL6));
    codes->Set(v8::String::New("intl_7"), v8::Integer::New(SDL_SCANCODE_INTERNATIONAL7));
    codes->Set(v8::String::New("intl_8"), v8::Integer::New(SDL_SCANCODE_INTERNATIONAL8));
    codes->Set(v8::String::New("intl_9"), v8::Integer::New(SDL_SCANCODE_INTERNATIONAL9));
    codes->Set(v8::String::New("lang_1"), v8::Integer::New(SDL_SCANCODE_LANG1));
    codes->Set(v8::String::New("lang_2"), v8::Integer::New(SDL_SCANCODE_LANG2));
    codes->Set(v8::String::New("lang_3"), v8::Integer::New(SDL_SCANCODE_LANG3));
    codes->Set(v8::String::New("lang_4"), v8::Integer::New(SDL_SCANCODE_LANG4));
    codes->Set(v8::String::New("lang_5"), v8::Integer::New(SDL_SCANCODE_LANG5));
    codes->Set(v8::String::New("lang_6"), v8::Integer::New(SDL_SCANCODE_LANG6));
    codes->Set(v8::String::New("lang_7"), v8::Integer::New(SDL_SCANCODE_LANG7));
    codes->Set(v8::String::New("lang_8"), v8::Integer::New(SDL_SCANCODE_LANG8));
    codes->Set(v8::String::New("lang_9"), v8::Integer::New(SDL_SCANCODE_LANG9));
    
    codes->Set(v8::String::New("alt_erase"), v8::Integer::New(SDL_SCANCODE_ALTERASE));
    codes->Set(v8::String::New("sysreq"), v8::Integer::New(SDL_SCANCODE_SYSREQ));
    codes->Set(v8::String::New("cancel"), v8::Integer::New(SDL_SCANCODE_CANCEL));
    codes->Set(v8::String::New("clear"), v8::Integer::New(SDL_SCANCODE_CLEAR));
    codes->Set(v8::String::New("prior"), v8::Integer::New(SDL_SCANCODE_PRIOR));
    codes->Set(v8::String::New("return_2"), v8::Integer::New(SDL_SCANCODE_RETURN2));
    codes->Set(v8::String::New("separator"), v8::Integer::New(SDL_SCANCODE_SEPARATOR));
    codes->Set(v8::String::New("out"), v8::Integer::New(SDL_SCANCODE_OUT));
    codes->Set(v8::String::New("oper"), v8::Integer::New(SDL_SCANCODE_OPER));
    codes->Set(v8::String::New("clear_again"), v8::Integer::New(SDL_SCANCODE_CLEARAGAIN));
    codes->Set(v8::String::New("crsel"), v8::Integer::New(SDL_SCANCODE_CRSEL));
    codes->Set(v8::String::New("exsel"), v8::Integer::New(SDL_SCANCODE_EXSEL));
    
    codes->Set(v8::String::New("numpad_00"), v8::Integer::New(SDL_SCANCODE_KP_00));
    codes->Set(v8::String::New("numpad_000"), v8::Integer::New(SDL_SCANCODE_KP_000));
    codes->Set(v8::String::New("numpad_thousands_separator"), v8::Integer::New(SDL_SCANCODE_THOUSANDSSEPARATOR));
    codes->Set(v8::String::New("numpad_decimal_seperator"), v8::Integer::New(SDL_SCANCODE_DECIMALSEPARATOR));
    codes->Set(v8::String::New("numpad_currency_unit"), v8::Integer::New(SDL_SCANCODE_CURRENCYUNIT));
    codes->Set(v8::String::New("numpad_currency_subunit"), v8::Integer::New(SDL_SCANCODE_CURRENCYSUBUNIT));
    codes->Set(v8::String::New("numpad_left_paren"), v8::Integer::New(SDL_SCANCODE_KP_LEFTPAREN));
    codes->Set(v8::String::New("numpad_right_paren"), v8::Integer::New(SDL_SCANCODE_KP_RIGHTPAREN));
    codes->Set(v8::String::New("numpad_left_brace"), v8::Integer::New(SDL_SCANCODE_KP_LEFTBRACE));
    codes->Set(v8::String::New("numpad_right_brace"), v8::Integer::New(SDL_SCANCODE_KP_RIGHTBRACE));
    codes->Set(v8::String::New("numpad_tab"), v8::Integer::New(SDL_SCANCODE_KP_TAB));
    codes->Set(v8::String::New("numpad_backspace"), v8::Integer::New(SDL_SCANCODE_KP_BACKSPACE));
    codes->Set(v8::String::New("numpad_a"), v8::Integer::New(SDL_SCANCODE_KP_A));
    codes->Set(v8::String::New("numpad_b"), v8::Integer::New(SDL_SCANCODE_KP_B));
    codes->Set(v8::String::New("numpad_c"), v8::Integer::New(SDL_SCANCODE_KP_C));
    codes->Set(v8::String::New("numpad_d"), v8::Integer::New(SDL_SCANCODE_KP_D));
    codes->Set(v8::String::New("numpad_e"), v8::Integer::New(SDL_SCANCODE_KP_E));
    codes->Set(v8::String::New("numpad_f"), v8::Integer::New(SDL_SCANCODE_KP_F));
    codes->Set(v8::String::New("numpad_xor"), v8::Integer::New(SDL_SCANCODE_KP_XOR));
    codes->Set(v8::String::New("numpad_power"), v8::Integer::New(SDL_SCANCODE_KP_POWER));
    codes->Set(v8::String::New("numpad_percent"), v8::Integer::New(SDL_SCANCODE_KP_PERCENT));
    codes->Set(v8::String::New("numpad_less"), v8::Integer::New(SDL_SCANCODE_KP_LESS));
    codes->Set(v8::String::New("numpad_greater"), v8::Integer::New(SDL_SCANCODE_KP_GREATER));
    codes->Set(v8::String::New("numpad_ampersand"), v8::Integer::New(SDL_SCANCODE_KP_AMPERSAND));
    codes->Set(v8::String::New("numpad_double_ampersand"), v8::Integer::New(SDL_SCANCODE_KP_DBLAMPERSAND));
    codes->Set(v8::String::New("numpad_vertical_bar"), v8::Integer::New(SDL_SCANCODE_KP_VERTICALBAR));
    codes->Set(v8::String::New("numpad_double_vertical_bar"), v8::Integer::New(SDL_SCANCODE_KP_DBLVERTICALBAR));
    codes->Set(v8::String::New("numpad_colon"), v8::Integer::New(SDL_SCANCODE_KP_COLON));
    codes->Set(v8::String::New("numpad_hash"), v8::Integer::New(SDL_SCANCODE_KP_HASH));
    codes->Set(v8::String::New("numpad_space"), v8::Integer::New(SDL_SCANCODE_KP_SPACE));
    codes->Set(v8::String::New("numpad_at"), v8::Integer::New(SDL_SCANCODE_KP_AT));
    codes->Set(v8::String::New("numpad_exclamation"), v8::Integer::New(SDL_SCANCODE_KP_EXCLAM));
    codes->Set(v8::String::New("numpad_mem_store"), v8::Integer::New(SDL_SCANCODE_KP_MEMSTORE));
    codes->Set(v8::String::New("numpad_mem_recall"), v8::Integer::New(SDL_SCANCODE_KP_MEMRECALL));
    codes->Set(v8::String::New("numpad_mem_clear"), v8::Integer::New(SDL_SCANCODE_KP_MEMCLEAR));
    codes->Set(v8::String::New("numpad_mem_add"), v8::Integer::New(SDL_SCANCODE_KP_MEMADD));
    codes->Set(v8::String::New("numpad_mem_subtract"), v8::Integer::New(SDL_SCANCODE_KP_MEMSUBTRACT));
    codes->Set(v8::String::New("numpad_mem_multiply"), v8::Integer::New(SDL_SCANCODE_KP_MEMMULTIPLY));
    codes->Set(v8::String::New("numpad_mem_divide"), v8::Integer::New(SDL_SCANCODE_KP_MEMDIVIDE));
    codes->Set(v8::String::New("numpad_plus_minus"), v8::Integer::New(SDL_SCANCODE_KP_PLUSMINUS));
    codes->Set(v8::String::New("numpad_clear"), v8::Integer::New(SDL_SCANCODE_KP_CLEAR));
    codes->Set(v8::String::New("numpad_clear_entry"), v8::Integer::New(SDL_SCANCODE_KP_CLEARENTRY));
    codes->Set(v8::String::New("numpad_binary"), v8::Integer::New(SDL_SCANCODE_KP_BINARY));
    codes->Set(v8::String::New("numpad_octal"), v8::Integer::New(SDL_SCANCODE_KP_OCTAL));
    codes->Set(v8::String::New("numpad_decimal"), v8::Integer::New(SDL_SCANCODE_KP_DECIMAL));
    codes->Set(v8::String::New("numpad_hexadecimal"), v8::Integer::New(SDL_SCANCODE_KP_HEXADECIMAL));
    
    codes->Set(v8::String::New("lctrl"), v8::Integer::New(SDL_SCANCODE_LCTRL));
    codes->Set(v8::String::New("lshift"), v8::Integer::New(SDL_SCANCODE_LSHIFT));
    codes->Set(v8::String::New("lalt"), v8::Integer::New(SDL_SCANCODE_LALT));
    codes->Set(v8::String::New("lgui"), v8::Integer::New(SDL_SCANCODE_LGUI));
    codes->Set(v8::String::New("rctrl"), v8::Integer::New(SDL_SCANCODE_RCTRL));
    codes->Set(v8::String::New("rshift"), v8::Integer::New(SDL_SCANCODE_RSHIFT));
    codes->Set(v8::String::New("ralt"), v8::Integer::New(SDL_SCANCODE_RALT));
    codes->Set(v8::String::New("rgui"), v8::Integer::New(SDL_SCANCODE_RGUI));
    
    codes->Set(v8::String::New("mode"), v8::Integer::New(SDL_SCANCODE_MODE));
    
    codes->Set(v8::String::New("audio_next"), v8::Integer::New(SDL_SCANCODE_AUDIONEXT));
    codes->Set(v8::String::New("audio_prev"), v8::Integer::New(SDL_SCANCODE_AUDIOPREV));
    codes->Set(v8::String::New("audio_stop"), v8::Integer::New(SDL_SCANCODE_AUDIOSTOP));
    codes->Set(v8::String::New("audio_play"), v8::Integer::New(SDL_SCANCODE_AUDIOPLAY));
    codes->Set(v8::String::New("audio_mute"), v8::Integer::New(SDL_SCANCODE_AUDIOMUTE));
    codes->Set(v8::String::New("media_select"), v8::Integer::New(SDL_SCANCODE_MEDIASELECT));
    codes->Set(v8::String::New("www"), v8::Integer::New(SDL_SCANCODE_WWW));
    codes->Set(v8::String::New("mail"), v8::Integer::New(SDL_SCANCODE_MAIL));
    codes->Set(v8::String::New("calculator"), v8::Integer::New(SDL_SCANCODE_CALCULATOR));
    codes->Set(v8::String::New("computer"), v8::Integer::New(SDL_SCANCODE_COMPUTER));
    codes->Set(v8::String::New("search"), v8::Integer::New(SDL_SCANCODE_AC_SEARCH));
    codes->Set(v8::String::New("home"), v8::Integer::New(SDL_SCANCODE_AC_HOME));
    codes->Set(v8::String::New("back"), v8::Integer::New(SDL_SCANCODE_AC_BACK));
    codes->Set(v8::String::New("forward"), v8::Integer::New(SDL_SCANCODE_AC_FORWARD));
    codes->Set(v8::String::New("stop"), v8::Integer::New(SDL_SCANCODE_AC_STOP));
    codes->Set(v8::String::New("refresh"), v8::Integer::New(SDL_SCANCODE_AC_REFRESH));
    codes->Set(v8::String::New("bookmarks"), v8::Integer::New(SDL_SCANCODE_AC_BOOKMARKS));
    
    codes->Set(v8::String::New("brightness_down"), v8::Integer::New(SDL_SCANCODE_BRIGHTNESSDOWN));
    codes->Set(v8::String::New("brightness_up"), v8::Integer::New(SDL_SCANCODE_BRIGHTNESSUP));
    codes->Set(v8::String::New("display_switch"), v8::Integer::New(SDL_SCANCODE_DISPLAYSWITCH));
                                                 
    codes->Set(v8::String::New("dillum_toggle"), v8::Integer::New(SDL_SCANCODE_KBDILLUMTOGGLE));
    codes->Set(v8::String::New("dillum_down"), v8::Integer::New(SDL_SCANCODE_KBDILLUMDOWN));
    codes->Set(v8::String::New("dillum_up"), v8::Integer::New(SDL_SCANCODE_KBDILLUMUP));
    codes->Set(v8::String::New("eject"), v8::Integer::New(SDL_SCANCODE_EJECT));
    codes->Set(v8::String::New("sleep"), v8::Integer::New(SDL_SCANCODE_SLEEP));
}

void KeyboardBindings_BindToGlobal(v8::Persistent<v8::ObjectTemplate>& global) {
    v8::HandleScope handle_scope;
    v8::Handle<v8::ObjectTemplate> toBind = v8::ObjectTemplate::New();
    toBind->Set(v8::String::New("isKeyDown"), v8::FunctionTemplate::New(fl_kb_IsKeyDown));
    v8::Handle<v8::ObjectTemplate> codes = v8::ObjectTemplate::New();
    fl_kb_SetScancodeConstants(codes);
    toBind->Set(v8::String::New("codes"), codes);
    global->Set("keyboard", toBind);
}
