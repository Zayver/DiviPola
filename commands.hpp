/**
 * @file commands.hpp
 * @brief 
 * Cabecera de comandos para el interprete de linea
 */
#pragma once
#include <list>
#include <fstream>
#include <string>
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
		dpto.emplace_back(n_dp, tokens[1]);

		while(n_dp == stoi(tokens[0])){
			if(tokens[6]=="CM"){
				dpto.back().cm.emplace_back(stoi(tokens[2]),tokens[3]);
				totalm++;
				line_pos= file.tellg();
				std::getline(file, buffer, '\n');
				tokens = tokenize(buffer, ",");
			}
			else{
				while(tokens[6]!="CM"){
					if(dpto.back().cm.empty())
						throw std::bad_cast();
					dpto.back().cm.back().cp.emplace_back(stoi(tokens[4]), tokens[5]);
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
void listar_poblaciones(const unsigned int & code, const std::list<Department> & dpto){
	for (auto & temp: dpto){
		for(auto & temporal : temp.cm){
			if(temporal.code==code){
				if(temporal.cp.empty())
					throw Command_exp("[listar_municipios]: Municipio sin poblaciones cargadas");
				
				cout<<"Poblaciones del municipio: "<<temporal.name<<'\n';
				cout<<"Cantidad: "<<temporal.cp.size()<<"\n\n";
				for(auto& taux: temporal.cp){
					cout<<taux.code<<"---"<<taux.name<<"\n";
				}
				return;
			}
		}
	}
	throw Command_exp("[listar_poblaciones]: Municipio no encontrado");
}
void info_sumaria(){

}
void carga_SC(){

}
void esta_en_sistema(){

}