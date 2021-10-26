/**
 * @file commands2.hpp
 * @brief Comandos de la segunda entrega
 *
 */
#pragma once
#include "printer.hpp"
#include "structures.hpp"
#include "utils.hpp"
#include <algorithm>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
static void aglomeracion(SC &sc, const std::map<uint, Department> &dptos) {

     if (dptos.empty())
          throw Command_exp("[Aglomeracion]: Sin datos en memoria, imposible "
                            "crear aglomeraciones");

     uint agglo = 0, cant_cm = 0;
     for (auto &actual_dpto : dptos) {
          for (auto &actual_cm : actual_dpto.second.cm) {
			if(actual_cm.second.SC_name == "" || actual_cm.second.SC_name.find("A-") != 0)
                    continue; //es una uninodal o no pertence el sc

               auto status = sc.agglomerations.find(actual_cm.second.SC_name);
               if (status == sc.agglomerations.end()) {
                    // esto significa que la aglomeración no existe aun
                    auto temp = sc.agglomerations.emplace(
                        std::piecewise_construct,
                        std::make_tuple(actual_cm.second.SC_name),
                        std::make_tuple());

                    agglo++;

                    temp.first->second.ordinary.emplace(
                        std::piecewise_construct,
                        std::make_tuple(actual_cm.second.name),
                        std::make_tuple(actual_cm.second));
                    cant_cm++;
               } else {
                    // si existe añadir
                    status->second.ordinary.emplace(
                        std::piecewise_construct,
                        std::make_tuple(actual_cm.second.name),
                        std::make_tuple(actual_cm.second));
                    cant_cm++;
               }
          }
     }
     std::stringstream out;
     out << "Se crearon " << agglo << " aglomeraciones urbanas, compuestas por "
         << cant_cm << " municipios \n";
     printer::print(out);
}
static void uninodal(SC &sc, const std::map<uint, Department> &dptos) {
     if (dptos.empty())
          throw Command_exp(
              "[Uninodal]: Imposible cargar datos, estructura vacia");
     uint cant_uninodal = 0;
     for (auto &actual_dpto : dptos) {
          for (auto &actual_cm : actual_dpto.second.cm) {
               if (actual_cm.second.sc == 3) {
                    sc.uninodal.emplace(std::piecewise_construct,
                                        std::make_tuple(actual_cm.second.name),
                                        std::make_tuple(actual_cm.second));
                    cant_uninodal++;
               }
          }
     }
     std::stringstream out;
     out << "Se crearon " << cant_uninodal << " ciudades uninodales\n";
     printer::print(out);
}
static void capital_menor(SC &sc) {
     if (sc.agglomerations.empty())
          throw Command_exp("[capita_menor]: Imposible crear capitales "
                            "menores, estructuras vacías");

     uint cap = 0;
     for (auto &actual_agglo : sc.agglomerations) {
          for (auto it = actual_agglo.second.ordinary.cbegin();
               it != actual_agglo.second.ordinary.cend();) {
               // imposible usar for en range ya que al eliminar los iteradores
               // quedan invalidos

               // Se podría usar std::map.extract() pero es un añadido en c++17.
               // ya que preferimos para evitarnos incovenientes usar c++11
               // toca de esta manera:
               if (it->second.sc == 4) {
                    actual_agglo.second.minor_capital.insert(
                        actual_agglo.second.minor_capital.begin(),
                        std::make_pair(it->first, it->second));
                    it = actual_agglo.second.ordinary.erase(it);
                    cap++;
               } else
                    ++it;
          }
     }

     std::stringstream out;
     out << "Se crearon " << cap << " ciudades menores del SC\n";
     printer::print(out);
}
static void reporte(const SC &sc, const std::map<uint, Department> &dptos) {

     if (sc.agglomerations.empty() || sc.uninodal.empty())
          throw Command_exp("[reporte]: no hay datos en memoria");
     std::stringstream out;

	//calcular informe
	uint mun_aglo=0, pob_aglo= 0, 
		pob_uni=0, 
		may_100=0, pob_may_100=0,
		men_100=0, pob_men_100=0, 
		//PORCENTAJES SE CALCULAN
		tot_col=0, pob_tot_col=0;


	for(auto & actual_aglo:sc.agglomerations){
		mun_aglo+= actual_aglo.second.minor_capital.size()+ actual_aglo.second.ordinary.size();
		for(auto & actual_cm: actual_aglo.second.ordinary){
			pob_aglo+= actual_cm.second.population;
		}
		for(auto & actual_cm: actual_aglo.second.minor_capital){
			pob_aglo+= actual_cm.second.population;
		}
	}

	for(auto & temp: sc.uninodal ){
		pob_uni+=temp.second.population;
	}

	for(auto & temp: dptos){
		for(auto & aux:temp.second.cm){
			if(aux.second.sc!=1)
				continue;
			if(aux.second.population>100000){
				may_100++;
				pob_may_100+=aux.second.population;
			}
			else{
				men_100++;
				pob_men_100+=aux.second.population;
			}
		}
	}

	//poblacion ANM
	uint anm_cant=0, pob_anm=0;
	for(auto & actual_dpto: dptos){
		anm_cant+=actual_dpto.second.anm.size();
		for(auto & actual_anm : actual_dpto.second.anm){
			pob_anm+=actual_anm.second.population;
		}
	}
	tot_col= mun_aglo+sc.uninodal.size()+may_100+men_100  +anm_cant;
	pob_tot_col= pob_aglo+pob_uni+pob_may_100+pob_men_100 +pob_anm;


     out << "Sistema de ciudades,Municipios,Población total \n"
         << "Ciudades que forman SC,*,*\n"
         << " Aglomeraciones urbanas,"<<mun_aglo<<","<<pob_aglo<<"\n"
         << " Ciudades uninodales,"<<sc.uninodal.size()<<","<<pob_uni<<"\n"
         << "Ciudades fuera del Sistema,*,*\n"
         << "  Ciudades > 100.000 h,"<<may_100<<","<<pob_may_100<<"\n"
         << "  Ciudades < 100.000 h,"<<men_100<<","<<pob_men_100<<"\n"
         << "Total Sistema de ciudades,"<<mun_aglo+sc.uninodal.size()<<","<<pob_aglo+pob_uni<<"\n"
         << "\% con respecto a Colombia,"<<((mun_aglo+sc.uninodal.size())*100)/tot_col<<","<<((pob_aglo+pob_uni)*100)/pob_tot_col<<"\n"
         << "Total Colombia,"<<tot_col<<","<<pob_tot_col;

     out = createTable(out, 3);
     printer::print(out, 30, "", "");//30 num aleatorio pero mayor a los \n del stream
	//para imprimir toda la tabla considero que igual por grande que sea no se debe
	//paginar
}
