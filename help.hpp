/**
 * @file help.hpp
 * @brief
 * Relacionado con toda la ayuda de comandos y demás
 */
#pragma once
#include "printer.hpp"
#include "structures.hpp"
#include <cstdio>
#include <iostream>
#include <sstream>
using std::cout;

static void help(const std::string &command) {
     if (command == "carga_divipola") {
          cout << "Carga en una o más estructuras de datos en memoria el \n \
		contenido del archivo identificado por nombre_archivo\n";
          cout << "Sintaxis [carga_divipola] [nombre de archivo]\n";

     } else if (command == "listar_departamentos") {
          cout << "Imprime la lista de departamentos cargados\n";
          cout << "Sintaxis [listar_departamentos]\n";

     } else if (command == "listar_municipios") {
          cout << "Imprime la información del dpto cargado en memoria indicado "
                  "por el id\n";
          cout << "Sintaxis [listar_municipios] [codigo dpto]\n";

     } else if (command == "listar_poblaciones") {
          cout << "Lista las poblaciones la información del municipio cargado "
                  "en memoria\n";
          cout << "Sintaxis [listar_poblaciones] [codigo municipio]\n";

     } else if (command == "info_sumaria") {
          cout << "Imprime la información básica (nombre, municipios, centros "
                  "poblados) \n";
          cout << "Sintaxis [info_sumaria] [codigo dpto]\n";

     } else if (command == "carga_SC") {
          cout << "Carga en memoria el contenido del archivo proporcionado\n \
		con la info básica para el sistema de ciudades\n";
          cout << "Sintaxis [carga_divipola] [nombre de archivo]\n";

     } else if (command == "esta_en_sistema") {
          cout << "Determina si un municipio, con código dado por el usuario,\n\
		existe dentro de las municipios definidos en el Sistema de Ciudades ";
          cout << "Sintaxis [carga_divipola] [codigo municipio]\n";

     } else if (command == "salir") {
          cout << "Terminar el programa limpiando registros y liberando "
                  "memoria\n";
          cout << "Sintaxis [salir]\n";

     } else if (command == "clear") {
          cout << "Limpia pantalla\n";
          cout << "Sintaxis [clear]\n";

     } else if (command == "componente1") {
          cout << "Crear componente C1 aglomeraciones urbanas\n";
     } else if (command == "componente2") {
          cout << "Crear componente C2 ciudades uninodales\n";
     } else if (command == "componente3") {
          cout << "Crear componente C3 ciudades con menos de 100.000 "
                  "habitantes\n";
     } else if (command == "componente4") {
          cout << "Crear componente C4 ciudades excentas de las "
                  "clasificaciones\n";
     } else if (command == "reporte") {
          cout << "Generar reporte y mostrarlo en pantalla\n";
     } else if (command == "codificar") {
          cout << "Generar la codificación de huffman con los datos del SC\n";
     } else if (command == "descodificar") {
          cout << "Cargar en memoria los datos de la codificación de huffman y "
                  "mostrarlos\n";
     } else {
          cout << "Comando desconocido, use [help] para ver comandos\n";
     }
}
static void help() {
     std::stringstream output;
     output << "Lista de comandos disponibles:\n\n"
            << "! comando previo\n"
            << "carga_divipola\n"
            << "listar_departamentos\n"
            << "listar_municipios\n"
            << "listar_poblaciones\n"
            << "info_sumaria\n"
            << "carga_SC\n"
            << "esta_en_sistema\n"
            << "salir\n"
            << "clear\n"
            << "componente1\n"
            << "componente2\n"
            << "componente3\n"
            << "componente4\n"
            << "reporte\n"
            << "codificar\n"
            << "decodificar\n"
            << "Sintaxis: [help] [comando] para info detallada\n";

	printer::print(output);
}