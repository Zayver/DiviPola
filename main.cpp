/**
 * @file main.cpp
 * @authors
 * -Nicolás Sanchéz
 * -Santiago Leal
 * -Santiago Zuñiga
 * @brief 
 * Archivo con la función main que invoca al interprete principal
 */
//se usan smart pointers para la tercera entrega soportados solo desde c++11
//entonces:
#if __cplusplus < 201103L
	#error Min std supported: C++11
	#include <null>
	//para que no siga compilando luego del #error
#endif

#include "interpreter.hpp" 
#ifdef _WIN32
#endif
int main(){ 
	//*Para salida de windows
	#ifdef _WIN32
		SetConsoleOutputCP( 65001 ); //65001 significa utf-8 en regedit de windows 
	#endif
	
	clearscreen();
	interpreter();
	clearscreen();
	return 0;
}