/**
 * @file structures.hpp
 * @brief
 * Cabecera para las definiciones de las estructuras del programa
 * Así como la sobrecarga de sus operadores y funciones
 */
#pragma once
#include <map>
#include <string>
#ifdef _WIN32
	#include <windows.h>
	#define clearscreen() system("cls")
#else
	#define clearscreen() system("clear");
#endif

class Command_exp : public std::exception {
     std::string info;

   public:
     Command_exp(const char *i) : info{i} {}
     const char *what() const noexcept { return info.c_str(); }
};


struct CP {
     std::string name;
     double latitude;
     double longitude;
     CP(const std::string &n, const double &l1, const double &l2) : name(n) {
          latitude = l1, longitude = l2;
     }
};

struct ANM {
     std::string name;
     std::map<unsigned int, CP> anm_cp;
	unsigned int population;
     ANM(const std::string &n) : name(n) {}
};
struct CM {
     std::string name;
     std::map<unsigned int, CP> cp;
     double latitude;
     double longitude;
     unsigned int population;
     int sc; //0 no tiene info, 1 no esta en sc y 2 si esta
	//entrega 2 cambia 0 no tiene info, 1 no esta en sc 
	//>1 si esta con:
	// 2 centro de aglomeracion, 3 uninodal, 4 capital menor
	// 5 normal o desconocida
	std::string SC_name;
	CM(){}
     CM(const std::string &n, const double &l1 = 0, const double &l2 = 0)
         : name(n), cp(), SC_name() {
          latitude = l1, longitude = l2;
     }
};
struct Department {
     std::string name;
     std::map<unsigned int, CM> cm;
     std::map<unsigned int, ANM> anm;
     Department(const std::string n) : name(n), cm(), anm() {}
};

//parte 2

struct urbanAgglomeration{
	std::map<std::string, CM> ordinary;
	std::map<std::string, CM> minor_capital;
	CM center;

	urbanAgglomeration(): ordinary(), minor_capital(), center(){
	}
};


struct SC{
	std::map<std::string, urbanAgglomeration> agglomerations;
	std::map<std::string, CM> uninodal;
	SC(): agglomerations(){}
};