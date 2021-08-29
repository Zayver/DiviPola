#pragma once
#include <cstdio>
#include <list>
#include <fstream>
#include <string>
#include <typeinfo>
#include <vector>
#include "structures.hpp"
#include "utils.hpp"

//borrar
//debug TODO: BORRAR
#include <iostream>
using std::cout;

class Command_exp: public std::exception{
	std::string info;
  public:
	Command_exp(const char* i): info{i}{}
	const char * what()const noexcept{return info.c_str();}
};

void carga_divipola(const std::string & filename, std::list<Department>& dpto){
	std::ifstream file(filename);
	
	//apertura correcta
	if(!file.good())
		throw Command_exp("[carga_divipola]: No se pudo cargar el archivo correctamente, errores en la carga");
	//mirar si el archivo esta vacio
	if(file.peek()== std::ifstream::traits_type::eof())
		throw Command_exp("[carga_divipola]: Archivo vacio, imposible cargar elementos en memoria");
	
	std::string buffer;
	std::vector<std::string> tokens(9); //alocar 9 elementos ya que esta es la cantidad de cosas que tiene el csv
	std::getline(file, buffer, '\n'); //ignorar la primera linea, la de los encabezados
	
	while(!file.eof()){
		//sacar dpto:
		std::getline(file, buffer, '\n');
		tokens = tokenize(buffer, ",");
		int n_dp= stoi(tokens[0]);
		dpto.emplace_back(n_dp, tokens[1]);
		
		//el primero es un CM entonces:
		dpto.back().cm.emplace_back(stoi(tokens[2]), tokens[3]);

		while(n_dp == stoi(tokens[0])){
			
			//leer linea:
			std::getline(file, buffer, '\n');
			tokens = tokenize(buffer, ",");
			//mirar que es
			if(tokens[6]=="CM"  && stoi(tokens[0])==n_dp )
				dpto.back().cm.emplace_back(stoi(tokens[2]), tokens[3]);
			else{
				while(tokens[6]=="CP"){
					if(dpto.back().cm.empty())
						throw std::bad_cast();
					dpto.back().cm.back().cp.emplace_back(stoi(tokens[4]), tokens[5]);
					std::getline(file, buffer, '\n');
					tokens = tokenize(buffer, ",");

					if(tokens.size()<6)
                    		break;
					//mirar si hay un CM:
					if(tokens[6]=="CM" && stoi(tokens[0])==n_dp)
						dpto.back().cm.emplace_back(stoi(tokens[2]), tokens[3]);
					
					
				}
				if(tokens.size()<6)
               		break;
			}
			
		}
	}
	file.close();
}

void listar_departamentos(const std::list<Department> &dpto){
	if(dpto.empty())
		throw Command_exp("[listar_departamentos]: No hay dptos en memoria");
	cout<<"Departamentos de la republica de Colombia:\n";
	cout<<"Cantidad cargada: "<<dpto.size()<<"\n\n";
	for(auto&temp: dpto){
		cout<<temp.code<<"---"<<temp.name<<'\n';
	}

}
void listar_municipios(const unsigned int& code,const std::list<Department> &dpto){
	auto d = std::find(dpto.begin(), dpto.end(), code); 
	//retorna end incluso si no encuentra entonces chequear:
	if(d->code!=code)
		throw Command_exp("[listar_municipios]: Dpto no encontrado");
	if(d->cm.empty())
		throw Command_exp("[listar_municipios]: Dpto sin municipios cargados");
	
	cout<<"Municipios del departamento: "<<d->name<<'\n';
	cout<<"Cantidad: "<<d->cm.size()<<"\n\n"; 
	for(auto & temp: d->cm){
		cout<<temp.code<<"---"<<temp.name<<'\n';
	}
}
void listar_poblaciones(){

}
void info_sumaria(){

}
void carga_SC(){

}
void esta_en_sistema(){

}
void salir(){

}


//debug borrar

void debug(const std::list<Department>d){
	for(auto&temp: d){
		cout<<temp.getName()<<'\n';
	}
}
