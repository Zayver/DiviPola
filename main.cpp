/**
 * @file main.cpp
 * @authors
 * -Nicolás Sanchéz
 * -Santiago Leal
 * -Santiago Zuñiga
 * @brief 
 * Archivo con la función main que invoca al interprete principal
 */
#include "interpreter.hpp" 
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