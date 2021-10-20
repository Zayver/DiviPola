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
#include <iomanip>
#include "printer.hpp"

static void aglomeracion(SC &sc, const std::map<uint, Department> &dptos) {

	if(dptos.empty())
		throw Command_exp("[Aglomeracion]: Sin datos en memoria imposible crear aglomeraciones");
	
	uint agglo=0,cant_cm=0; 
	for(auto & actual_dpto: dptos ){
		for(auto & actual_cm: actual_dpto.second.cm){
			if(actual_cm.second.SC_name=="" || actual_cm.second.SC_name.find("A-")!=0)
				continue; // no pertenece al sistema de ciudades o es una uninodal 

			auto status = sc.agglomerations.find(actual_cm.second.SC_name);
			if(status==sc.agglomerations.end()){
				//esto significa que la aglomeración no existe aun
				auto temp = sc.agglomerations.emplace(std::piecewise_construct,
					std::make_tuple(actual_cm.second.SC_name),
					std::make_tuple());	
				
				agglo++;

					temp.first->second.ordinary.emplace(
						std::piecewise_construct,
						std::make_tuple(actual_cm.second.name),
						std::make_tuple(actual_cm.second));
					cant_cm++;
			}
			else{
				// si existe añadir 
				status->second.ordinary.emplace(
					std::piecewise_construct,
					std::make_tuple(actual_cm.second.name),
					std::make_tuple(actual_cm.second)
				);
				cant_cm++;
			}
		}
	}
	std::stringstream out; out <<"Se crearon "<<agglo<< " aglomeraciones urbanas, compuestas por "<<cant_cm<<" municipios \n";
	printer::print(out);
}
static void uninodal(SC & sc, const std::map<uint, Department> &dptos ) {
	uint cant_uninodal=0;
	for(auto & actual_dpto: dptos){
		for(auto & actual_cm : actual_dpto.second.cm){
			if(actual_cm.second.sc==3){
				sc.uninodal.emplace(
					std::piecewise_construct,
					std::make_tuple(actual_cm.second.name),
					std::make_tuple(actual_cm.second)
				);
				cant_uninodal++;
			}
		}

	}
	std::stringstream out; out <<"Se crearon "<<cant_uninodal<< " ciudades uninodales\n";
	printer::print(out);
}
static void capital_menor() {}
static void reportr(const SC & sc) {
	std::stringstream out;

	out<<std::setfill('#')<<std::setw(30)<<'\n'
	<<std::setw(5)<<"Sistema de ciudades"<<"|"<<std::setw(5)<<"Municipios"<<std::setw(5)<<"|"<<"Población total|\n"
	<<"Ciudades que hacen parte del Sistema"<<std::setw(5)<<"|"<<std::setw(5)<<"|\n"
	<<"\tAglomeraciones urbanas" // no terminado
	;
	printer::print(out);
}


