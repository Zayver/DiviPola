/**
 * @file help.hpp
 * @brief 
 * Relacionado con toda la ayuda de comandos y demás 
 */
#pragma once
#include <iostream>
#include <string>
using std::cout;

static void help(const std::string & command){
	if(command=="carga_divipola"){
		cout<<"Carga en una o más estructuras de datos en memoria el \n \
		contenido del archivo identificado por nombre_archivo\n";
		cout<<"Sintaxis [carga_divipola] [nombre de archivo]\n";

	}
	else if(command=="listar_departamentos"){
		cout<<"Imprime la lista de departamentos cargados\n";
		cout<<"Sintaxis [listar_departamentos]\n";

	}
	else if(command=="listar_municipios"){
		cout<<"Imprime la información del dpto cargado en memoria indicado por el id\n";
		cout<<"Sintaxis [listar_municipios] [codigo dpto]\n";

	}
	else if(command=="listar_poblaciones"){
		cout<<"Lista las poblaciones la información del municipio cargado en memoria\n";
		cout<<"Sintaxis [listar_poblaciones] [codigo municipio]\n";

	}
	else if(command=="info_sumaria"){
		cout<<"Imprime la información básica (nombre, municipios, centros poblados) \n";
		cout<<"Sintaxis [info_sumaria] [codigo dpto]\n";

	}
	else if(command=="carga_SC"){
		cout<<"Carga en memoria el contenido del archivo proporcionado\n \
		con la info básica para el sistema de ciudades\n";
		cout<<"Sintaxis [carga_divipola] [nombre de archivo]\n";

	}
	else if(command=="esta_en_sistema"){
		cout<<"Determina si un municipio, con código dado por el usuario,\n\
		existe dentro de las municipios definidos en el Sistema de Ciudades ";
		cout<<"Sintaxis [carga_divipola] [codigo municipio]\n";

	}
	else if(command=="salir"){
		cout<<"Terminar el programa limpiando registros y liberando memoria\n";
		cout<<"Sintaxis [salir]\n";

	}
	else if(command=="clear"){
		cout<<"Limpia pantalla\n";
		cout<<"Sintaxis [clear]\n";

	}
	else{
		cout<<"Comando desconocido, use [help] para ver comandos\n";
	}

}
static void help(){
	cout<<"Lista de comandos disponibles:\n\n";
		cout<<"! comando previo\n";
		cout<<"carga_divipola\n";
		cout<<"listar_departamentos\n";
		cout<<"listar_municipios\n";
		cout<<"listar_poblaciones\n";
		cout<<"info_sumaria\n";
		cout<<"carga_SC\n";
		cout<<"esta_en_sistema\n";
		cout<<"salir\n";
		cout<<"clear\n";
		cout<<"Sintaxis: [help] [comando] para info detallada\n";

	}