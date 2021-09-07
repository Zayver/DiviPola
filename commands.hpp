/**
 * @file commands.hpp
 * @brief 
 * Cabecera de comandos para el interprete de linea
 */
#pragma once
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include "structures.hpp"
#include "utils.hpp"
#include <iostream>

using std::cout;
using mapper =std::map<unsigned int ,Department>;

class Command_exp: public std::exception{
	std::string info;
  public:
	Command_exp(const char* i): info{i}{}
	const char * what()const noexcept{return info.c_str();}
};

void carga_divipola(const std::string & filename, mapper& dpto){
	std::ifstream file(filename);
	
	//apertura incorrecta
	if(!file.good())
		throw Command_exp("[carga_divipola]: No se pudo cargar el archivo correctamente, errores en la carga");
	//mirar si el archivo esta vacio
	if(file.peek()== std::ifstream::traits_type::eof())
		throw Command_exp("[carga_divipola]: Archivo vacio, imposible cargar elementos en memoria");
	
	std::string buffer;
	std::vector<std::string> tokens(9); //alocar 9 elementos ya que esta es la cantidad de cosas que tiene el csv
	std::getline(file, buffer, '\n'); //ignorar la primera linea, la de los encabezados
	unsigned int totalm=0, totalp=0; //para contar
	int line_pos;
	while(!file.eof()){
		//sacar dpto:
		std::getline(file, buffer, '\n');
		tokens = tokenize(buffer, ",");
		int n_dp= stoi(tokens[0]);
		auto actual_dpto = dpto.emplace(n_dp, tokens[1]);
		std::pair<std::_Rb_tree_iterator<std::pair<const unsigned int, CM>>, bool> actual_cm; // HORRIBLE PERO NO HAY DE OTRA :(
		while(n_dp == stoi(tokens[0])){
			if(tokens[6]=="CM"){
				actual_cm = actual_dpto.first->second.cm.emplace(
					std::piecewise_construct, 
					std::make_tuple(std::stoi(tokens[2])), 
					std::make_tuple(tokens[3], stod(tokens[7]), stod(tokens[8]))
				);
				totalm++;
				line_pos= file.tellg();
				std::getline(file, buffer, '\n');
				tokens = tokenize(buffer, ",");
			}
			else{
				while(tokens[6]!="CM"){
					if(actual_dpto.first->second.cm.empty())
						throw std::bad_cast();
					if(tokens.size()<9){
						actual_cm.first->second.cp.emplace(
							std::piecewise_construct, 
							std::make_tuple(std::stoi(tokens[4])), 
							std::make_tuple(tokens[5],0,0)
						);
					
					}
					else{
						actual_cm.first->second.cp.emplace(
							std::piecewise_construct, 
							std::make_tuple(std::stoi(tokens[4])), 
							std::make_tuple(tokens[5], stod(tokens[7]), stod(tokens[8]))
						);
					}
					
					totalp++;
					
					line_pos= file.tellg();
					std::getline(file, buffer, '\n');
					tokens = tokenize(buffer, ",");
					if(tokens.size()<6)
						break;
					

				}

			}
			if(tokens.size()<6)
				break;
		}
		if(tokens.size()>=6)
			file.seekg(line_pos);
	}
	file.close();
	//contar cosas
	cout<<"Correcto,se cargaron: \n";
	cout<<"\t"<<dpto.size()-1<<"   Departamentos\n";
	cout<<"\t"<<totalm<<"   Municipios\n";
	cout<<"\t"<<totalp<<"   Centros poblados\n";
}

void listar_departamentos(const mapper&dpto){
	if(dpto.empty())
		throw Command_exp("[listar_departamentos]: No hay dptos en memoria");
	cout<<"Departamentos de la republica de Colombia:\n";
	cout<<"Cantidad cargada: "<<dpto.size()<<"\n\n";
	for(auto&temp: dpto){
		cout<<temp.first<<"---"<<temp.second.name<<'\n';
	}

}
void listar_municipios(const unsigned int& code, const mapper&dpto){
	auto d = dpto.find(code);
	//retorna end incluso si no encuentra entonces chequear:
	if(d == dpto.end())
		throw Command_exp("[listar_municipios]: Dpto no encontrado");
	if(d->second.cm.empty())
		throw Command_exp("[listar_municipios]: Dpto sin municipios cargados");
	
	cout<<"Municipios del departamento: "<<d->second.name<<'\n';
	cout<<"Cantidad: "<<d->second.cm.size()<<"\n\n"; 
	for(auto & temp: d->second.cm){
		cout<<temp.first<<"---"<<temp.second.name<<'\n';
	}
}
void listar_poblaciones(const unsigned int & code, const mapper& dpto){
	/*   para reducir la complejidad de busqueda
		dado que los id son:
		depto---CM---CP
		XX-----XXX---XXX
	*/
	auto search = dpto.find(code/1000);
	if(search == dpto.end())
		throw Command_exp("[listar_poblaciones]: Departamento inexistente");
	auto search2 = search->second.cm.find(code);
	if(search2 == search->second.cm.end())
		throw Command_exp("[listar_poblaciones]: Municipio inexistente");
	
	cout<<"Poblaciones municipio de: "<<search2->second.name<<'\n';
	cout<<"Cantidad: "<<search2->second.cp.size()<<"\n\n";	
	for(auto & aux: search2->second.cp ){
		cout<<aux.first<<"---"<<aux.second.name<<'\n';
	}
		
	
}
void info_sumaria(){

}
void carga_SC(){

}
void esta_en_sistema(){

}