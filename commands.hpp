/**
 * @file commands.hpp
 * @brief
 * Cabecera de comandos para el interprete de linea
 */
#pragma once
#include "structures.hpp"
#include "utils.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::cout;
using mapper = std::map<unsigned int, Department>;

class Command_exp : public std::exception {
     std::string info;

   public:
     Command_exp(const char *i) : info{i} {}
     const char *what() const noexcept { return info.c_str(); }
};

void carga_divipola(const std::string &filename, mapper &dpto) {
     std::ifstream file(filename);

     // apertura incorrecta
     if (!file.good())
          throw Command_exp("[carga_divipola]: No se pudo cargar el archivo "
                            "correctamente, errores en la carga");
     // mirar si el archivo esta vacio
     if (file.peek() == std::ifstream::traits_type::eof())
          throw Command_exp("[carga_divipola]: Archivo vacio, imposible cargar "
                            "elementos en memoria");

     std::string buffer;
     std::vector<std::string> tokens(9); // alocar 9 elementos ya que esta es la
                                         // cantidad de cosas que tiene el csv
     std::getline(file, buffer,
                  '\n'); // ignorar la primera linea, la de los encabezados
     unsigned int totalm = 0, totalp = 0, totalanm = 0; // para contar
     int line_pos;
     while (!file.eof()) {
          // sacar dpto:
          std::getline(file, buffer, '\n');
          tokens = tokenize(buffer, ",");
          int n_dp = stoi(tokens[0]), n_cm;
          auto actual_dpto = dpto.emplace(n_dp, tokens[1]);
          std::pair<std::_Rb_tree_iterator<std::pair<const unsigned int, CM>>,
                    bool>
              actual_cm; // HORRIBLE PERO NO HAY DE OTRA :(
          while (n_dp == stoi(tokens[0])) {
               if (tokens[6] == "CM") {
                    n_cm = std::stoi(tokens[2]);
                    actual_cm = actual_dpto.first->second.cm.emplace(
                        std::piecewise_construct, std::make_tuple(n_cm),
                        std::make_tuple(tokens[3], stod(tokens[7]),
                                        stod(tokens[8])));

                    actual_cm.first->second.sc =
                        0; // 0 indica que no tiene SC info
                    totalm++;
                    line_pos = file.tellg();
                    std::getline(file, buffer, '\n');
                    tokens = tokenize(buffer, ",");
               } else if (stoi(tokens[4]) % 1000 == 0 && tokens[6] == "CP") {
                    int n_anm = std::stoi(tokens[2]);
                    auto actual_anm = actual_dpto.first->second.anm.emplace(
                        std::piecewise_construct, std::make_tuple(n_anm),
                        std::make_tuple(tokens[3]));
                    totalanm++;
                    while (stoi(tokens[2]) == n_anm) {
                         if (tokens.size() < 9) {
                              actual_anm.first->second.anm_cp.emplace(
                                  std::piecewise_construct,
                                  std::make_tuple(std::stoi(tokens[4])),
                                  std::make_tuple(tokens[5], 0, 0));

                         } else {
                              actual_anm.first->second.anm_cp.emplace(
                                  std::piecewise_construct,
                                  std::make_tuple(std::stoi(tokens[4])),
                                  std::make_tuple(tokens[5], stod(tokens[7]),
                                                  stod(tokens[8])));
                         }

                         totalp++;

                         line_pos = file.tellg();
                         std::getline(file, buffer, '\n');
                         tokens = tokenize(buffer, ",");
                         if (tokens.size() < 6)
                              break;
                    }
               } else {
                    while (stoi(tokens[2]) == n_cm) {
                         if (tokens.size() < 9) {
                              actual_cm.first->second.cp.emplace(
                                  std::piecewise_construct,
                                  std::make_tuple(std::stoi(tokens[4])),
                                  std::make_tuple(tokens[5], 0, 0));

                         } else {
                              actual_cm.first->second.cp.emplace(
                                  std::piecewise_construct,
                                  std::make_tuple(std::stoi(tokens[4])),
                                  std::make_tuple(tokens[5], stod(tokens[7]),
                                                  stod(tokens[8])));
                         }

                              
                         totalp++;

                         line_pos = file.tellg();
                         std::getline(file, buffer, '\n');
                         tokens = tokenize(buffer, ",");
                         if (tokens.size() < 6)
                              break;
                    }
               }
               if (tokens.size() < 6)
                    break;
          }
          if (tokens.size() >= 6)
               file.seekg(line_pos);
     }
     file.close();

     // contar cosas
     cout << "Correcto,se cargaron: \n";
     cout << "\t" << dpto.size() - 1 << "   Departamentos\n";
     cout << "\t" << totalm << "   Municipios\n";
     cout << "\t" << totalanm << "   Areas no municipalizadas\n";
     cout << "\t" << totalp << "   Centros poblados\n";
}

void listar_departamentos(const mapper &dpto) {
     if (dpto.empty())
          throw Command_exp("[listar_departamentos]: No hay dptos en memoria");
     cout << "Departamentos de la republica de Colombia:\n";
     cout << "Cantidad cargada: " << dpto.size() << "\n\n";
     for (auto &temp : dpto) {
          cout << temp.first << "---" << temp.second.name << '\n';
     }
}
void listar_municipios(const unsigned int &code, const mapper &dpto) {
     auto d = dpto.find(code);
     // retorna end incluso si no encuentra entonces chequear:
     if (d == dpto.end())
          throw Command_exp("[listar_municipios]: Dpto no encontrado");
     if (d->second.cm.empty())
          throw Command_exp(
              "[listar_municipios]: Dpto sin municipios cargados");

     cout << "Municipios del departamento: " << d->second.name << '\n';
     cout << "Cantidad: " << d->second.cm.size() << "\n\n";
     for (auto &temp : d->second.cm) {
          cout << temp.first << "---" << temp.second.name <<'\n';
     }
     if (!d->second.anm.empty()) {
          cout << "El departamento posee " << d->second.anm.size()
               << " areas no municipalizadas\n";
          for (auto &temp : d->second.anm) {
               cout << temp.first << "---" << temp.second.name <<'\n';
          }
     }
}
void listar_poblaciones(const unsigned int &code, const mapper &dpto) {
     /*   para reducir la complejidad de busqueda
             dado que los id son:
             depto---CM---CP
             XX-----XXX---XXX
     */
     // buscar dpto
     auto search = dpto.find(code / 1000);
     if (search == dpto.end())
          throw Command_exp("[listar_poblaciones]: Departamento inexistente");

     // buscar municipio
     auto search2 = search->second.cm.find(code);
     if (search2 == search->second.cm.end()) {
          // si no existe como municipio buscar ANM
          auto search3 = search->second.anm.find(code);
          if (search3 == search->second.anm.end()) {
               throw Command_exp("[listar_poblaciones]: Municipio inexistente");
          }

          // aca encuentra anm entonces
          cout << "Poblaciones area no municipalizada de: "
               << search3->second.name << '\n';
          cout << "Cantidad: " << search3->second.anm_cp.size() << "\n\n";
          for (auto &aux : search3->second.anm_cp) {
               cout << aux.first << "---" << aux.second.name <<'\n';
          }
          return;
     }

     cout << "Poblaciones municipio de: " << search2->second.name << '\n';
     cout << "Cantidad: " << search2->second.cp.size() << "\n\n";
     for (auto &aux : search2->second.cp) {
          cout << aux.first << "---" << aux.second.name << '\n';
     }
}
void info_sumaria(const unsigned int &code, const mapper &dpto) {
     if (dpto.empty())
          throw Command_exp("[info_sumaria]: No hay dptos en memoria");
     auto search = dpto.find(code);
     if (search == dpto.end())
          throw Command_exp("[info_sumaria]: Departamento inexistente");
     unsigned int m = search->second.cm.size();
     unsigned int c = 0;
     for (auto &temp : search->second.cm) {
          c += temp.second.cp.size();
     }
     cout << "El departamento " << search->second.name
          << " esta conformado por " << m << " municipios, " << c
          << " centros poblados y \n"
          << search->second.anm.size() << " areas no municipalizadas";
}
void carga_SC(const std::string &file_name, mapper &dpto) {
     std::ifstream file(file_name);
     if (!file.good())
          throw Command_exp("[carga_SC]: No se pudo cargar el archivo "
                            "correctamente, errores en la carga");
     if (file.peek() == std::ifstream::traits_type::eof())
          throw Command_exp("[carga_SC]: Archivo vacio, imposible cargar "
                            "elementos en memoria");
     std::string buffer;
     std::vector<std::string> tokens(7); // alocar 7 elementos ya que esta es la
                                         // cantidad de cosas que tiene el csv
     std::getline(file, buffer,
                  '\n'); // ignorar la primera linea, la de los encabezados

     unsigned int totald = 0, totalSC = 0, totalnSC = 0, n_dp = 0;
     while (!file.eof()) {
          std::getline(file, buffer, '\n');
          tokens = tokenize(buffer, ",");
		if(tokens.size()<5)
			break;
          int n_actualdpto = stoi(tokens[4]);
          auto actual_dpto = dpto.find(
              n_actualdpto / 1000); // aumiendo que no haya errores en el archivo
          if (n_actualdpto != n_dp) {
               totald++;
               n_dp = n_actualdpto;
          }
          auto actual_cm = actual_dpto->second.cm.find(stoi(tokens[4]));
          if (actual_cm == actual_dpto->second.cm.end() && (tokens[3].find("(ANM)")==std::string::npos)) {
               cout << "No hay datos de SC para " << tokens[3] << '\n';
               continue;
          }
          if (tokens[0] == "Fuera SC") {
               actual_cm->second.sc = 1;
               totalnSC++;
          } else {
               actual_cm->second.sc = 2;
               totalSC++;
          }
     }
     cout << "Se cargaron correctamente " << totald << '\n'
          << "En sistema de ciudades: " << totalSC << '\n'
          << "Fuera del Sistema de ciudades: " << totalnSC << '\n'
          << "Total: " << totalSC + totalnSC << '\n';
     file.close();
}
void esta_en_sistema(const unsigned int &code, const mapper &dpto) {
     auto search2 = dpto.find(code / 1000);
     if (search2 == dpto.end()) {
          throw Command_exp("[esta_en_sistema]: Departamento Inexistente");
     }
     auto search = search2->second.cm.find(code);
     if (search == search2->second.cm.end()) {
		auto search3= search2->second.anm.find(code);
		if(search3 != search2->second.anm.end()){
			cout<<"Area no municipalizada no pertenece al SC\n";
			return;
		}
          throw Command_exp(
              "[esta_en_sistema]: Municipio inexistente en divipola\n");
     } else {
          cout << "[esta_en_sistema]: El Municipio "
               << search->second.name;
          if (search->second.sc == 0)
               cout<<" no contiene info del SC cargado en memoria\n";
          if (search->second.sc == 1)
               cout << " no hace parte del sistema de ciudades\n";
          if (search->second.sc == 2)
               cout << " hace parte del sistema de ciudades\n";
     }
}
