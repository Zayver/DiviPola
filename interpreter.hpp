/**
 * @file interpreter.hpp
 * @brief
 * Cabecera encargada del intérprete de ordenes de la consola
 *
 */
#pragma once
#include "commands.hpp"
#include "commands2.hpp"
#include "commands3.hpp"
#include "help.hpp"
#include "structures.hpp"
#include "utils.hpp"
#include <iostream>
#include <map>
#include <string>
#include <vector>
class Interpreter_exception : public std::exception {
     std::string info;

   public:
     Interpreter_exception(const char *d) : info(d) {}
     const char *what() const noexcept { return this->info.c_str(); }
};
class Exit_signal {};

static const std::map<std::string, unsigned int> commands{
	{"test",99},
	{"quick",100},
    	{"carga_divipola", 0},
    	{"listar_departamentos", 1},
    	{"listar_municipios", 2},
    	{"listar_poblaciones", 3},
    	{"info_sumaria", 4},
    	{"carga_SC", 5},
    	{"esta_en_sistema", 6},
    	{"salir", 7},
    	{"clear", 8},
    	{"help", 9},
    	{"aglomeracion", 10},
    	{"uninodal", 11},
    	{"capital_menor", 12},
    	{"reporte", 13},
    	{"codificar", 14},
    	{"decodificar", 15},
	{"distancia",16},
	{"ruta_mas_corta",17},
	{"ciudad_remota",18}};




// este comando tendría que recibir TODO lo que todas las funciones harían D:
static void executeCommand(const std::vector<std::string> &tokens, mapper &dpto, SC & sc,
			std::map<std::string, Graph> & gsc) {
     if (tokens[0].empty())
          return;
     switch (commands.at(tokens[0])) {
	case 99:
		test(gsc, tokens[1]);
		break;
	case 100:
		carga_divipola("Divipola.csv", dpto);
		carga_SC("SistemaCiudades.csv", dpto);
		aglomeracion(sc, dpto);
		uninodal(sc, dpto);
		capital_menor(sc);
		break;
     case 0:
          if (tokens.size() != 2)
               throw Interpreter_exception(
                   "Invalid arguments for [carga_divipola]");
          carga_divipola(tokens[1], dpto);
          break;
     case 1:
          listar_departamentos(dpto);
          break;
     case 2:
          if (tokens.size() != 2)
               throw Interpreter_exception(
                   "Invalid arguments for [listar municipios]");
          listar_municipios(stoi(tokens[1]), dpto);
          break;
     case 3:
          if (tokens.size() != 2)
               throw Interpreter_exception(
                   "Invalid arguments for [listar municipios]");
          listar_poblaciones(stoi(tokens[1]), dpto);
          break;
     case 4:
          if (tokens.size() != 2)
               throw Interpreter_exception(
                   "Invalid arguments for [info_sumaria]");
          info_sumaria(stoi(tokens[1]), dpto);
          break;
     case 5:
          if (tokens.size() != 2)
               throw Interpreter_exception("Invalid arguments for [carga_SC]");
          carga_SC((tokens[1]), dpto);
          break;
     case 6:
          if (tokens.size() != 2)
               throw Interpreter_exception(
                   "Invalid arguments for [esta_en_sistema]");
          esta_en_sistema(stoi(tokens[1]), dpto);
          break;
     case 7:
          throw Exit_signal();
          break;
     case 8:
          clearscreen();
          break;
     case 9:
          if (tokens.size() == 2) {
               help(tokens[1]);
          } else {
               help();
          }
          break;
	//parte 2 incluidas en commands2.hpp
	case 10:
		aglomeracion(sc,dpto);
		break;
	case 11:
		uninodal(sc, dpto);
		break;
	case 12:
		capital_menor(sc);
		break;
	case 13:
		reporte(sc, dpto);
		break;
	case 14:
          if (tokens.size() != 3)
               throw Interpreter_exception(
                   "Invalid arguments for [codificar]");
          codificar((tokens[1]),(tokens[2]));
		break;

	case 15:
     	if (tokens.size() != 3)
               throw Interpreter_exception(
                   "Invalid arguments for [decodificar]");
          decodificar((tokens[1]),tokens[2]);
		break;
	//comandos entrega 3 incluidos en commands3.hpp
	case 16:
		if(tokens.size()!=2)
			throw Interpreter_exception("Invalid arguments for [distancia]");
		distancia(sc, gsc, tokens[1]);
		break;
	case 17:
		if(tokens.size()!=2)
			throw Interpreter_exception("Invalid arguments for [ruta_mas_corta]");
		ruta_mas_corta(gsc, sc,tokens[1]);
		break;
	case 18:
		if(tokens.size()!=2)
			throw Interpreter_exception("Invalid arguments for [ciudad_remota]");
		ciudad_remota(gsc,sc, tokens[1]);
		break;
		
     default:
          help();
          break;
     }
}
inline void interpreter() {
     std::string command, prev_command="";
     bool __exit = false;
     std::vector<std::string> tokens;
     mapper dpto; //departamentos 
	SC sc; //sistema de ciudades
	std::map<std::string, Graph> gsc;// mapa de grafos de las aglomeraciones con key en su nombre
     cout << "Interprete de comandos DIVIPOLA\n";
     do {
          cout << "divipola $ ";
          std::getline(std::cin, command, '\n');
          command = trim(command);
          tokens = tokenize(command);
		if(tokens[0]=="!"){
			cout<<"[!]: "<<prev_command<<'\n';
			tokens[0]=prev_command;	
			
		}
			
          try {
               executeCommand(tokens, dpto, sc, gsc);
          } catch (Interpreter_exception e) {
               cout << "ERROR: " << e.what() << '\n';
          } catch (std::out_of_range e) {
               cout << "Command not found, use [help] for avaliable commands\n";
          } catch (Exit_signal e) {
               __exit = true;
          } catch (Command_exp e) {
               cout << "Command error: " << e.what() << '\n';
          }
		if(!__exit)
			prev_command=tokens[0];
          cout << '\n';
     } while (!__exit);
}
