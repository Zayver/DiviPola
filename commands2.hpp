/**
 * @file commands2.hpp
 * @brief Comandos de la segunda entrega
 *
 */
#pragma once
#include "printer.hpp"
#include "structures.hpp"
#include "utils.hpp"
#include <algorithm>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <tuple>
#include <iostream>
#include <utility>
#include <queue>
#include <fstream>
#include <vector>
#include <tr1/unordered_map>

static void aglomeracion(SC &sc, const std::map<uint, Department> &dptos) {

     if (dptos.empty())
          throw Command_exp("[Aglomeracion]: Sin datos en memoria, imposible "
                            "crear aglomeraciones");

     uint agglo = 0, cant_cm = 0;
     for (auto &actual_dpto : dptos) {
          for (auto &actual_cm : actual_dpto.second.cm) {
			if(actual_cm.second.SC_name == "" || actual_cm.second.SC_name.find("A-") != 0)
                    continue; //es una uninodal o no pertence el sc

               auto status = sc.agglomerations.find(actual_cm.second.SC_name);
               if (status == sc.agglomerations.end()) {
                    // esto significa que la aglomeración no existe aun
                    auto temp = sc.agglomerations.emplace(
                        std::piecewise_construct,
                        std::make_tuple(actual_cm.second.SC_name),
                        std::make_tuple());

                    agglo++;

                    temp.first->second.ordinary.emplace(
                        std::piecewise_construct,
                        std::make_tuple(actual_cm.second.name),
                        std::make_tuple(actual_cm.second));
                    cant_cm++;
               } else {
                    // si existe añadir
                    status->second.ordinary.emplace(
                        std::piecewise_construct,
                        std::make_tuple(actual_cm.second.name),
                        std::make_tuple(actual_cm.second));
                    cant_cm++;
               }
          }
     }
     std::stringstream out;
     out << "Se crearon " << agglo << " aglomeraciones urbanas, compuestas por "
         << cant_cm << " municipios \n";
     printer::print(out);
}
static void uninodal(SC &sc, const std::map<uint, Department> &dptos) {
     if (dptos.empty())
          throw Command_exp(
              "[Uninodal]: Imposible cargar datos, estructura vacia");
     uint cant_uninodal = 0;
     for (auto &actual_dpto : dptos) {
          for (auto &actual_cm : actual_dpto.second.cm) {
               if (actual_cm.second.sc == 3) {
                    sc.uninodal.emplace(std::piecewise_construct,
                                        std::make_tuple(actual_cm.second.name),
                                        std::make_tuple(actual_cm.second));
                    cant_uninodal++;
               }
          }
     }
     std::stringstream out;
     out << "Se crearon " << cant_uninodal << " ciudades uninodales\n";
     printer::print(out);
}
static void capital_menor(SC &sc) {
     if (sc.agglomerations.empty())
          throw Command_exp("[capita_menor]: Imposible crear capitales "
                            "menores, estructuras vacías");

     uint cap = 0;
     for (auto &actual_agglo : sc.agglomerations) {
          for (auto it = actual_agglo.second.ordinary.cbegin();
               it != actual_agglo.second.ordinary.cend();) {
               // imposible usar for en range ya que al eliminar los iteradores
               // quedan invalidos

               // Se podría usar std::map.extract() pero es un añadido en c++17.
               // ya que preferimos para evitarnos incovenientes usar c++11
               // toca de esta manera:
               if (it->second.sc == 4) {
                    actual_agglo.second.minor_capital.insert(
                        actual_agglo.second.minor_capital.begin(),
                        std::make_pair(it->first, it->second));
                    it = actual_agglo.second.ordinary.erase(it);
                    cap++;
               } else
                    ++it;
          }
     }

     std::stringstream out;
     out << "Se crearon " << cap << " ciudades menores del SC\n";
     printer::print(out);
}
static void reporte(const SC &sc, const std::map<uint, Department> &dptos) {

     if (sc.agglomerations.empty() || sc.uninodal.empty())
          throw Command_exp("[reporte]: no hay datos en memoria");
     std::stringstream out;

	//calcular informe
	uint mun_aglo=0, pob_aglo= 0, 
		pob_uni=0, 
		may_100=0, pob_may_100=0,
		men_100=0, pob_men_100=0, 
		//PORCENTAJES SE CALCULAN
		tot_col=0, pob_tot_col=0;


	for(auto & actual_aglo:sc.agglomerations){
		mun_aglo+= actual_aglo.second.minor_capital.size()+ actual_aglo.second.ordinary.size();
		for(auto & actual_cm: actual_aglo.second.ordinary){
			pob_aglo+= actual_cm.second.population;
		}
		for(auto & actual_cm: actual_aglo.second.minor_capital){
			pob_aglo+= actual_cm.second.population;
		}
	}

	for(auto & temp: sc.uninodal ){
		pob_uni+=temp.second.population;
	}

	for(auto & temp: dptos){
		for(auto & aux:temp.second.cm){
			if(aux.second.sc!=1)
				continue;
			if(aux.second.population>100000){
				may_100++;
				pob_may_100+=aux.second.population;
			}
			else{
				men_100++;
				pob_men_100+=aux.second.population;
			}
		}
	}

	

	tot_col= mun_aglo+sc.uninodal.size()+may_100+men_100;
	pob_tot_col= pob_aglo+pob_uni+pob_may_100+pob_men_100;


     out << "Sistema de ciudades,Municipios,Población total \n"
         << "Ciudades que forman SC,*,*\n"
         << " Aglomeraciones urbanas,"<<mun_aglo<<","<<pob_aglo<<"\n"
         << " Ciudades uninodales,"<<sc.uninodal.size()<<","<<pob_uni<<"\n"
         << "Ciudades fuera del Sistema,*,*\n"
         << "  Ciudades > 100.000 h,"<<may_100<<","<<pob_may_100<<"\n"
         << "  Ciudades < 100.000 h,"<<men_100<<","<<pob_men_100<<"\n"
         << "Total Sistema de ciudades,"<<mun_aglo+sc.uninodal.size()<<","<<pob_aglo+pob_uni<<"\n"
         << "\% con respecto a Colombia,"<<((mun_aglo+sc.uninodal.size())*100)/tot_col<<","<<((pob_aglo+pob_uni)*100)/pob_tot_col<<"\n"
         << "Total Colombia,"<<tot_col<<","<<pob_tot_col;
     std::string huff = out.str();
     std::cout<<huff;
     out = createTable(out, 3);
     printer::print(out, 30, "", "");//30 num aleatorio pero mayor a los \n del stream
	//para imprimir toda la tabla considero que igual por grande que sea no se debe
	//paginar
}

//huffman

//Asignar nodo en el arbol
Node* getNode(char simbolo, int freq,Node*izq,Node*der)
{
    Node* node = new Node();
    node->s=simbolo;
    node->f=freq;
    node->i=izq;
    node->d=der;
    return node;
}

//revisa el arbol de Huffman y guarda los codigos en un mapa
void codificar(Node* root, std::string str,std::tr1::unordered_map<char,std::string>&CHuff)
{
    if(root==nullptr)
    {
        return;
    }
    if( (root->i==nullptr ) && (root->d==nullptr) )
    {
        CHuff[root->s]=str;
    }
    codificar(root->i,str+"0",CHuff);
    codificar(root->d,str+"1",CHuff);
}
//revisa y decodifica
void decodificar(std::tr1::unordered_map<char,std::string>CHuff, std::string text)
{
    std::string space_delimiter = " ";
    std::vector<std::string> words{};
    size_t pos = 0;
    while ((pos = text.find(space_delimiter)) != std::string::npos) {
        words.push_back(text.substr(0, pos));
        text.erase(0, pos + space_delimiter.length());
    }
    for (const auto &str : words) {
        for(auto bub:CHuff)
        {
            if(bub.second==str)
                //cout <<bub.first;
                bub.first;
        }
    }
}
std::string decodificar(std::tr1::unordered_map<char,std::string>CHuff, std::string text,std::string arc)
{
    std::string space_delimiter = " ";
    std::vector<std::string> words{};
    size_t pos = 0;
    std::string buffer="";
    while ((pos = text.find(space_delimiter)) != std::string::npos) {
        words.push_back(text.substr(0, pos));
        text.erase(0, pos + space_delimiter.length());
    }
    for (const auto &str : words) {
        for(auto bub:CHuff)
        {
            if(bub.second==str)
                buffer+=bub.first;
        }
    }
    return buffer;
}
//arbolito de mango
HuffmanBIN* tree(std::string t)
{
    //contador de simbolos en mapa
    std::tr1::unordered_map<char,int>fr;
    for(char s:t)
    {
        fr[s]++;
    }
    //cola de prioridad
    std::priority_queue <Node*,std::vector<Node*>,comp>pq;
    //agg nodos de simbolo
    for(auto pair:fr){
        pq.push(getNode(pair.first,pair.second,nullptr,nullptr));
    }
    //Rep hasta que haya mas de 1 nodo en la cola
    while (pq.size()!=1)
    {
        Node*izq=pq.top();pq.pop();
        Node*der=pq.top();pq.pop();
        int sum=izq->f+der->f;
        pq.push(getNode(pq.top()->s,sum,izq,der));
    }
    Node* root = pq.top();
    //impprime los codigos por simbolo
    std::tr1::unordered_map<char,std::string>CHuff;
    codificar(root,"",CHuff);
    cout<<"\nLos codigos de Huffman son:\n"<<"\n";
    for(auto p:CHuff)
    {
        cout<<p.first<<" "<<p.second<<"\n";
    }
    //imprime el mensaje original
    //cout<<"\nPreCodificar:\n"<<t<<'\n';
    std::string str="";
    for(char simbolo: t){
        str+=CHuff[simbolo]+" ";
    }
    /*cout<<"\nEl texto codificado es:\n"<<str<<'\n';
    cout<<"\nEl texto decodificado es: \n";
    int index=-1;
        decodificar(CHuff,str);
    cout <<"\n---------------\n";
    */HuffmanBIN* huffs = new HuffmanBIN();
    huffs->bin=str;
    huffs->CHuff=CHuff;
    return huffs;
}
static void codificar(const std::string &c,const std::string &filename)
{   
    std::ifstream file(c);
    if (!file.good())
          throw Command_exp("[Codificar]: No se pudo cargar el archivo correctamente, errores en la carga");
     if (file.peek() == std::ifstream::traits_type::eof())
          throw Command_exp("[Codificar]: Archivo vacío, imposible cargar elementos en memoria");
    std::fstream load(filename,/*std::ios::in|*/std::ios::out|std::ios::binary);
     if(!load.good())
		throw Command_exp("[codificar]: Imposible crear archivo");
    std::string buffer;
    std::string gigante="";
    while (!file.eof()) {
        std::getline(file, buffer,'\n');
        gigante+=buffer;
        gigante+="\n";
        }
    HuffmanBIN* huffs = tree(gigante);
    load.write((char*)&huffs,sizeof(HuffmanBIN)); 
    file.close();
    load.close();
}  
static void decodificar(const std::string &filename, const std::string & output)
{   
    std::ofstream file(output);
    std::ifstream load(filename,std::ios::binary);
     if (!file.good()||!load.good())
          throw Command_exp("[Decdificar]: No se pudo cargar el archivo correctamente, errores en la carga");
     if (load.peek() == std::ifstream::traits_type::eof())
          throw Command_exp("[Decodificar]: Archivo vacío, imposible cargar elementos en memoria");
    std::string buffer;
    std::string gigante="";
    HuffmanBIN* hufs = new HuffmanBIN();
    load.read((char*)&hufs,sizeof(hufs));
    std::string save = decodificar(hufs->CHuff,hufs->bin,"arc");
    cout<<save;
    file<<save;
    file.close();
    load.close();
} 