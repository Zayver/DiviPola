/**
 * @file commands3.hpp
 * @brief Comandos para la 3ra entrega
 *
 */
#pragma once
#include "printer.hpp"
#include "structures.hpp"
#include "utils.hpp"
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

static void test(std::map<std::string, Graph> &gsc, const std::string &aglo) {
     auto s = gsc.find(aglo);
     s->second.show();
}
static void distancia(const SC &sc, std::map<std::string, Graph> &gsc,
                      const std::string &aglo) {
     if (sc.agglomerations.empty())
          throw Command_exp("[distancia]: Sistema de ciudades vacio");
     auto search = sc.agglomerations.find(aglo);
     if (search == sc.agglomerations.end())
          throw Command_exp("[distancia]: Aglomeración inexistente");

     Graph ginsert;

	/*
		*TODOS LOS CICLOS SE PODRÍAN REDUCIR
		*PERO EL CODIGO QUEDARÍA MUY ILEGIBLE Y CONFUSO
	*/
     // insertar vertices
     CM center = search->second.center;
     ginsert.insertVertex(center); // centro de la aglo
     for (auto &temp : search->second.ordinary) {
          if (center.name == temp.second.name)
               continue;
          ginsert.insertVertex(temp.second);
          auto len =
              coordinatesToKm(center.latitude, center.longitude,
                              temp.second.latitude, temp.second.longitude);
          ginsert.insertEdge(center, temp.second, len);
     }
     for (auto &temp : search->second.minor_capital) {
          ginsert.insertVertex(temp.second);
          auto len =
              coordinatesToKm(center.latitude, center.longitude,
                              temp.second.latitude, temp.second.longitude);
          ginsert.insertEdge(center, temp.second, len);
     }
     // insertar aristas restantes, todos contra todos
	
     for (auto &temp : search->second.ordinary) {
          for (auto &temp1 : search->second.minor_capital) {
               auto len = coordinatesToKm(
                   temp.second.latitude, temp.second.longitude,
                   temp1.second.latitude, temp1.second.longitude);
               ginsert.insertEdge(temp.second, temp1.second, len);
          }
     }

	//ordinarias 
	for(auto & temp: search->second.ordinary){
		for(auto &temp1: search->second.ordinary){
			if(temp.first==temp1.first)
				continue; //son iguales
			auto len = coordinatesToKm(
                   temp.second.latitude, temp.second.longitude,
                   temp1.second.latitude, temp1.second.longitude);
               ginsert.insertEdge(temp.second, temp1.second, len);
		}
	}
	//capitales menores
	for(auto & temp: search->second.minor_capital){
		for(auto &temp1: search->second.minor_capital){
			if(temp.first==temp1.first)
				continue; //son iguales
			auto len = coordinatesToKm(
                   temp.second.latitude, temp.second.longitude,
                   temp1.second.latitude, temp1.second.longitude);
               ginsert.insertEdge(temp.second, temp1.second, len);
		}
	}

     gsc.emplace(aglo, ginsert);
     printer::print("Correcto se calcularon y se guardaron las distancias de "
                    "la aglomereración: " +
                    aglo + "\n");
}
static void ruta_mas_corta(std::map<std::string, Graph> &gsc, SC &sc,
                           const std::string &aglo) {

     if (gsc.empty())
          throw Command_exp("[ruta_mas_corta]: Grafo vacío");
     auto search = gsc.find(aglo);
     if (search == gsc.end())
          throw Command_exp("[ruta_mas_corta]: Aglomeración inexistente");

     auto center_search = sc.agglomerations.find(aglo);
     CM center = center_search->second.center;
     Vertex v{center};
	auto graf = gsc.find(aglo);
	graf->second.dijskstra(center);
	
	printer::print("\nCaminos más cortos a las ciudades aglo de "+aglo);
	for(auto & temp: graf->second.vertexes){
		if(temp.first==center.name)
			continue;
		graf->second.shortestPath(temp.second);
	}
	printer::print("Caminos más cortos a las ciudades aglo de "+aglo);
}
static void ciudad_remota(std::map<std::string, Graph> &gsc,SC &sc,
                          const std::string &aglo) {
	if (gsc.empty())
          throw Command_exp("[ruta_mas_corta]: Grafo vacío");
     auto search = gsc.find(aglo);
     if (search == gsc.end())
          throw Command_exp("[ruta_mas_corta]: Aglomeración inexistente");

	auto center_search = sc.agglomerations.find(aglo);
     CM center = center_search->second.center;
	Vertex * c = search->second.find(center);

	c = search->second.longestVertex(c);

	search->second.shortestPath(*c);	 

}