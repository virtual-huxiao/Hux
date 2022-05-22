#include <iostream>
#include "src/hux_log.hpp"

int main() {

	//The built-in content
	::std::cout << hux::err << "error output" << hux::br;
	::std::cout << hux::nor << "normal output" << hux::br;
	::std::cout << hux::war << "warning output" << hux::br;
	::std::cout << hux::run << "running output" << hux::br;
	::std::cout << ::std::endl;

	//The custom content
	hux::custom custom_color{ hux::f_cyan };
	::std::cout << custom_color << "custom output"<<hux::br;
	::std::cout << hux::custom{ hux::f_white } << "custom output" << hux::br;
	::std::cout << hux::custom{ hux::f_yellow, hux::b_purple } << "custom output" << hux::br;
	::std::cout << hux::custom{ hux::f_blue } << "custom output" << hux::br;
	::std::cout << hux::custom{ hux::f_green } << "custom output" << hux::br;
	::std::cout << hux::custom{ hux::f_purple } << "custom output" << hux::br;
	hux::outmode(std::cout, hux::f_black, hux::b_white) << "Equivalent custom output" << hux::br;

	//hux::br will reset style and out std::endl, this is for normal output later
	::std::cout<< hux::err<< "ERROR!" << ::std::endl;
	::std::cout<< "This place is polluted!" << ::std::endl;
	::std::cout << hux::br;
	/*equivalent:*/ //::std::cout << hux::reset << std::endl;
	::std::cout << "This this is normal." << ::std::endl;

	//It's best to call rest at the end, especially in Windows!
	hux::reset(::std::cout);	//or ::std::cout<<hux::reset;

	return 0;
}