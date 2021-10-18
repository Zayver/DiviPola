/**
 * @file commands2.hpp
 * @brief Comandos de la segunda entrega 
 * 
 */
#pragma once
#include "structures.hpp"
#include <map>
#include <sstream>
#include <string>
#include <tuple>
#include "printer.hpp"

static void componente1(SC &sc, const std::map<uint, Department> &dptos) {
     uint mun = 0, aglo=0;
	for(auto & actual_dpto : dptos){
		for(auto & actual_cm: actual_dpto.second.cm){
			if(actual_cm.second.SC_name=="")
				continue; // el cm no tiene aglomeracion entonces no se puede crear
			else{
				
				//se podría dejar al constrcutor de set que decida si estan repetidas o no
				//pero como toca contarlas pues:
				auto actual_aglo = sc.city_system.find(actual_cm.second.SC_name);
				if(actual_aglo==sc.city_system.end()){
					//significa que la aglomeracion aun no existe entonces aumentarla
					aglo++;

					urbanAgglomeration add;
					add.cm.emplace(actual_cm.second);
					sc.city_system.emplace(actual_cm.second.SC_name,add);
				}
				else{
					//la aglomeracion ya exoste entonces agregar el cm a esta
					actual_aglo->second.cm.emplace(actual_cm.second);

				}

				mun++;				


			}
			
		}
	}
	std::stringstream out; out<<"Se crearon "<<aglo<<" compuestas de: "<<mun<<" centros municipales\n";
	printer::print(out);
}
static void componente2() {}
static void componente3() {}
static void componente4() {}


