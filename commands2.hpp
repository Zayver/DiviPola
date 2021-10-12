#pragma once
#include "structures.hpp"
#include <map>

static void componente1(SC &sc, const std::map<uint, Department> &dptos) {
     if (sc.city_system.size() == 0)
          throw Command_exp("[componente1]: Sistema de ciudades vacío, error");

     for (auto dpto : dptos) {
          for (auto &cm : dpto.second.cm) {
               if (cm.second.SC_name != "") {
				//si tiene un SC buscarlo si ya está en el arbol si no agregarlo
				if(sc.city_system.find(cm.second.SC_name)== sc.city_system.end()){
					sc.city_system.emplace(std::piecewise_construct,
                                        std::make_tuple(cm.second.SC_name),
                                        std::make_tuple(&cm.second));
				}
				
                    
               }
          }
     }
}
static void componente2() {}
static void componente3() {}
static void componente4() {}
