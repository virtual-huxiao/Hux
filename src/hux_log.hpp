#pragma once
#include <iostream>
#include <cassert>

#if defined(WINDOWS)
#include "Windows.h"
#elif defined(LINUX)
#include <sstream>
#endif



namespace hux {
enum Color {
#if defined(WINDOWS)
	f_black = 0,
	f_blue = FOREGROUND_BLUE,
	f_green = FOREGROUND_GREEN,
	f_red = FOREGROUND_RED,
	f_yellow = f_red + f_green,
	f_purple = f_red + f_blue,
	f_cyan = f_blue + f_green,
	f_white = f_blue + f_green + f_red,

	b_black = 0,
	b_blue = BACKGROUND_BLUE,
	b_green = BACKGROUND_GREEN,
	b_red = BACKGROUND_RED,
	b_yellow = b_red + b_green,
	b_purple = b_red + b_blue,
	b_cyan = b_blue + b_green,
	b_white = b_blue + b_green + b_red,
#elif defined(LINUX)
	f_black = 30,
	f_red,
	f_green,
	f_yellow,
	f_blue,
	f_purple,
	f_cyan,
	f_white,

	b_black = 40,
	b_red,
	b_green,
	b_yellow,
	b_blue,
	b_purple,
	b_cyan,
	b_white,
#endif
};

enum FontStyle {
#if defined(WINDOWS)
	normal = 0,
	underscore = COMMON_LVB_UNDERSCORE,
#elif defined(LINUX)
	normal = 14,
	underscore = 4,
#endif
};


template <class _Elem, class _Traits>
std::basic_ostream<_Elem, _Traits>& outmode(
	std::basic_ostream<_Elem, _Traits>& _Ostr,
	Color front = Color::f_white,
	Color back = Color::b_black,
	FontStyle font = FontStyle::normal) {
	assert((Color::f_black <= front && front <=Color::f_white));
	assert((Color::f_black <= front && front <= Color::f_white));
	assert((FontStyle::normal == font || font == FontStyle::underscore));
#if defined(WINDOWS)
	static HANDLE _COUT_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(_COUT_HANDLE,
		static_cast<int>(front)+
		static_cast<int>(back)+
		static_cast<int>(font));
	(void)_Ostr;
	return _Ostr;
#elif defined(LINUX)
	thread_local std::stringstream sstream;	//c++20 has std::format, but now is c++14!
	sstream.str("");
	sstream<<"\033["<<front<<';'<<back<< ';' <<font<<'m';
	return _Ostr<<sstream.str();
#endif
}

template <class _Elem, class _Traits>
std::basic_ostream<_Elem, _Traits>& reset(
	std::basic_ostream<_Elem, _Traits>& _Ostr) {
#if defined(WINDOWS)
	return outmode(_Ostr);
#elif defined(LINUX)
	return _Ostr << "\033[0m";
#endif
}

//call std::endl and reset all Style
template <class _Elem, class _Traits>
std::basic_ostream<_Elem, _Traits>& br(
	std::basic_ostream<_Elem, _Traits>& _Ostr) {
	return (reset(_Ostr)<<std::endl);
}

struct custom {
	
	constexpr custom(Color front = Color::f_white,
		Color back = Color::b_black,
		FontStyle font = FontStyle::normal) noexcept:
		front_{front},back_{back}, font_{font}
	{}

	Color front_;
	Color back_;
	FontStyle font_;

	template <class _Elem, class _Traits>
	friend std::basic_ostream<_Elem, _Traits>& operator<<(std::basic_ostream<_Elem, _Traits>& _Ostr, const hux::custom& rvalue) {
		return hux::outmode(_Ostr,rvalue.front_,rvalue.back_,rvalue.font_);
	}
};

//Which implementation is better? You can choose one or the other which are you think better.
#define HUX_CONSTEXPR_STATIC_OBJ_MODE
//#define HUX_FUNCTIONAL_MODE
#if defined(HUX_CONSTEXPR_STATIC_OBJ_MODE)

#define OUTOBJ(objname,...) constexpr static hux::custom objname{__VA_ARGS__};
OUTOBJ(err, f_white, b_red)
OUTOBJ(nor, f_white, b_black)
OUTOBJ(run, f_green, b_black)
OUTOBJ(war, f_yellow, b_purple)
#undef OUTOBJ

#elif defined(HUX_FUNCTIONAL_MODE)

#define OUTFUN(funname,...) template <class _Elem, class _Traits> std::basic_ostream<_Elem, _Traits>&\
 funname(std::basic_ostream<_Elem, _Traits>& _Ostr){return outmode(_Ostr,##__VA_ARGS__);}
OUTFUN(err, f_white, b_red)
OUTFUN(nor, f_white, b_black)
OUTFUN(run, f_green, b_black)
OUTFUN(war, f_yellow, b_purple)
#undef OUTOBJ

#endif

}

