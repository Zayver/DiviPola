/**
 * @file interpreter.hpp
 * @brief 
 * Cabecera encargada del intérprete de ordenes de la consola
 * 
 */
#pragma once
#include <map>
#include <vector>
#include <string>
#include "help.hpp"
#include "utils.hpp"
#include "commands.hpp"
class Interpreter_exception : public std::exception{
	std::string info;
  public:
	Interpreter_exception(const char* d): info(d){}
	const char* what() const noexcept{return this->info.c_str();}
};
class Exit_signal{

};

static const std::map<std::string, unsigned int> commands{
			{"carga_divipola", 0},
			{"listar_departamentos", 1 },
			{"listar_municipios",2  },
			{"listar_poblaciones", 3 },
			{"info_sumaria", 4  },
			{"carga_SC",5  },
			{"esta_en_sistema", 6 },
			{"salir",  7},
			{"clear", 8 },
			{"help", 9}
		};

//este comando tendría que recibir TODO lo que todas las funciones harían D:
void executeCommand(const std::vector<std::string> & tokens,std::list<Department>&dpto){
	if(tokens[0].empty())
		return;
	switch (commands.at(tokens[0])) {
		case 0:
			if(tokens.size()!=2)
				throw Interpreter_exception("Invalid arguments for [carga_divipola]");
			carga_divipola(tokens[1], dpto);
			if(dpto.empty())
				throw std::bad_alloc();
			break;
		case 1:
			listar_departamentos(dpto);
			break;
		case 2:
			if(tokens.size()!=2)
				throw Interpreter_exception("Invalid arguments for [listar municipios]");
			listar_municipios(stoi(tokens[1]),dpto);
			break;
		case 3:
			if(tokens.size()!=2)
				throw Interpreter_exception("Invalid arguments for [listar municipios]");
			listar_poblaciones(stoi(tokens[1]),dpto);
			break;
		case 4:
			info_sumaria();
			break;
		case 5:
			carga_SC();
			break;
		case 6:
			esta_en_sistema();
			break;
		case 7:
			throw Exit_signal();
			break;
		case 8:
			clearscreen();
			break;
		case 9:
			if(tokens.size()==2){
				help(tokens[1]);
			}
			else{
				help();
			}
			break;
		default:
			help();
			break;
	}
}
inline void interpreter(){
	std::string command; bool __exit=false; std::vector<std::string> tokens;
	std::list<Department> dpto;
	cout<<"Interprete de comandos DIVIPOLA\n";
	do{
		cout<<"divipola $ ";
		std::getline(std::cin, command, '\n');
		command = trim(command);
		tokens = tokenize(command);
		try{
			executeCommand(tokens, dpto);
		}
		catch(Interpreter_exception e){
			cout<<"ERROR: "<<e.what()<<'\n';
		}
		catch(std::out_of_range e){
			cout<<"Command not found, use [help] for avaliable commands\n";
		}
		catch(Exit_signal e){
			__exit=true;
		}
		catch(Command_exp e){
			cout<<"Command error: "<<e.what()<<'\n';
		}
		
		cout<<'\n';
	}while(!__exit);
}
