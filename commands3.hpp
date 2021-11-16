/**
 * @file commands3.hpp
 * @brief Comandos para la 3ra entrega
 *
 */
#pragma once
#include "printer.hpp"
#include "structures.hpp"
#include "utils.hpp"
#include <map>
#include <sstream>
#include <string>

static void distancia(const SC &sc, std::map<std::string, Graph> &gsc,
                      const std::string &aglo = "") {
     if (sc.agglomerations.empty())
          throw Command_exp("[distancia]: Sistema de ciudades vacio");
     // dejar el parametro por defecto hace que se creen los grafos
     // para todas las aglomeraciones
     if (aglo == "") {
          for (auto &a_aglo : sc.agglomerations) {
               Graph ng;
               // loopear por cada cm del aglo para vertex
               for (auto &a_cm : a_aglo.second.ordinary) {
                    ng.insertVertex(a_cm.second);
               }
               for (auto &a_cm : a_aglo.second.minor_capital) {
                    ng.insertVertex(a_cm.second);
               }

               // añadir las aristas con sus distancias
               for (auto &temp : ng.vertex) {
                    if (temp.first == a_aglo.second.center.name)
                         continue; // no puede añadirse una arista consigo mismo

                    ng.insertEdge(
                        a_aglo.second.center, temp.second.cm,
                        coordinatesToKm(a_aglo.second.center.latitude,
                                        a_aglo.second.center.longitude,
                                        temp.second.cm.latitude,
                                        temp.second.cm.longitude));
               }

               gsc.emplace(
                   std::piecewise_construct, std::make_tuple(a_aglo.first),
                   std::make_tuple(ng)); // construir el grafo para cada aglo
          }
     } else {
          auto search = sc.agglomerations.find(aglo);
          if (search == sc.agglomerations.end())
               throw Command_exp("[distancia]: No existe la aglomeración");
          Graph ng;
          // loopear por cada cm del aglo para vertex
          for (auto &a_cm : search->second.ordinary) {
               ng.insertVertex(a_cm.second);
          }
          for (auto &a_cm : search->second.minor_capital) {
               ng.insertVertex(a_cm.second);
          }
          // añadir las aristas con sus distancias
          for (auto &temp : ng.vertex) {
               if (temp.first == search->second.center.name)
                    continue; // no puede añadirse una arista consigo mismo

               cout << search->second.center.name << "--" << temp.second.cm.name
                    << '\n';
               ng.insertEdge(search->second.center, temp.second.cm,
                             coordinatesToKm(search->second.center.latitude,
                                             search->second.center.longitude,
                                             temp.second.cm.latitude,
                                             temp.second.cm.longitude));
          }
          gsc.emplace(std::piecewise_construct, std::make_tuple(search->first),
                      std::make_tuple(ng));
     }
     printer::print("Correcto se calcularon y se guardaron las distancias\n");
}
static void ruta_mas_corta(std::map<std::string, Graph> &gsc,
                           const std::string &aglo) {
     if (gsc.empty())
          throw Command_exp("Grafos vacíos");
     auto search = gsc.find(aglo);
     if (search == gsc.end())
          throw Command_exp("Agromeracion inexistente");

     auto center = search->second.vertex.begin()++->second;
	std::stringstream out; 
     for (auto &temp : search->second.vertex) {
          if (center.cm == temp.second.cm)
               continue;
          auto path = search->second.shortestPath(&center, &temp.second);

          printer::print("Path de "+center.cm.name+ " a "+ temp.second.cm.name+"\n");
          for (auto &temp2: path) {
               out << temp2->cm.name << "---" << temp2->distance << '\n';
          }
          out << "Distancia: " << path.back()->distance << '\n';
		printer::print(out);
     }
}
static void ciudad_remota(std::map<std::string, Graph> &gsc,
                          const std::string &aglo) {}