/**
 * @file help.hpp
 * @brief
 * Relacionado con toda la ayuda de comandos y demás
 */
#pragma once
#include "printer.hpp"
#include "structures.hpp"
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

     } else if (command == "aglomeracion") {
          cout << "Crear componente C1 aglomeraciones urbanas\n";
     } else if (command == "uninodal") {
          cout << "Crear componente C2 ciudades uninodales\n";
     } else if (command == "capital_menor") {
          cout << "Crear componente C3 ciudades con menos de 100.000 "
                  "habitantes\n";
     } else if (command == "reporte") {
          cout << "Generar reporte y mostrarlo en pantalla\n";
     } else if (command == "codificar") {
          cout << "Generar la codificación de huffman con los datos del SC\n";
          cout << "Sintaxis: [codificar] [archivo entrada] [nombre salida] \n";
     } else if (command == "decodificar") {
          cout << "Cargar en memoria los datos de la codificación de huffman y "
                  "mostrarlos\n";
          cout
              << "Sintaxis: [decodificar] [archivo entrada] [nombre salida] \n";
     } else if (command == "distancia") {
          cout << "Calcular las distancias entre la aglo\n";
          cout << "Sintaxis: [distancia] [aglomeración]\n";
     } else if (command == "ruta_mas_corta") {
          cout << "Calcular las rutas más cortas entre el centro y las "
                  "ciudades\n";
          cout << "Sintaxis: [ruta_mas_corta] [aglomeración] \n";
     } else if (command == "ciudad_remota") {
          cout << "Calcular la ciudad más remota en la aglomeracion\n";
          cout << "Sintaxis: [ciudad_remota] [aglo]\n";
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
            << "distancia\n"
            << "ruta_mas_corta\n"
            << "ciudad_remota\n"
            << "Sintaxis: [help] [comando] para info detallada\n";

     printer::print(output);
}