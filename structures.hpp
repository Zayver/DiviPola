/**
 * @file structures.hpp
 * @brief
 * Cabecera para las definiciones de las estructuras del programa
 * Así como la sobrecarga de sus operadores y funciones
 */
#pragma once
#include <string>
#include <map>
struct CP{
	std::string name;
	double latitude;
	double longitude;
	CP(const std::string &n,const double & l1, const double &l2 ):name(n){
		latitude=l1, longitude=l2;
	}
};
struct CM{
	std::string name;
	std::map<unsigned int, CP>cp;
	double latitude;
	double longitude;
	unsigned int population;
	CM(const std::string &n, const double & l1=0, const double &l2=0): name(n), cp(){
		latitude=l1, longitude=l2;
	}
};
struct Department{
	std::string name;
	std::map<unsigned int, CM> cm;
	Department(const std::string n):name(n), cm(){
	}
	
};