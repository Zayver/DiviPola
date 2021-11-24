/**
 * @file structures.hpp
 * @brief
 * Cabecera para las definiciones de las estructuras del programa
 * Así como la sobrecarga de sus operadores y funciones
 */
#pragma once
#include <algorithm>
#include <functional>
#include <ios>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#include <tr1/unordered_map>
#include <limits>
#include <list>
#include <iostream> //TODO: Delete
using std::cout;
#ifdef _WIN32
	#include <windows.h>
	#define clearscreen() system("cls")
#else
	#define clearscreen() system("clear");
#endif

class Command_exp : public std::exception {
     std::string info;

   public:
     Command_exp(const char *i) : info{i} {}
     const char *what() const noexcept { return info.c_str(); }
};


struct CP {
     std::string name;
     double latitude;
     double longitude;
     CP(const std::string &n, const double &l1, const double &l2) : name(n) {
          latitude = l1, longitude = l2;
     }
};

struct ANM {
     std::string name;
     std::map<unsigned int, CP> anm_cp;
	unsigned int population;
     ANM(const std::string &n) : name(n) {}
};
struct CM {
     std::string name;
     std::map<unsigned int, CP> cp;
     double latitude;
     double longitude;
     unsigned int population;
     int sc; //0 no tiene info, 1 no esta en sc y 2 si esta
	//entrega 2 cambia 0 no tiene info, 1 no esta en sc 
	//>1 si esta con:
	// 2 centro de aglomeracion, 3 uninodal, 4 capital menor
	// 5 normal o desconocida
	std::string SC_name;
	CM(){}
     CM(const std::string &n, const double &l1 = 0, const double &l2 = 0)
         : name(n), cp(), SC_name() {
          latitude = l1, longitude = l2;
     }
};
struct Department {
     std::string name;
     std::map<unsigned int, CM> cm;
     std::map<unsigned int, ANM> anm;
     Department(const std::string n) : name(n), cm(), anm() {}
};

//parte 2

struct urbanAgglomeration{
	std::map<std::string, CM> ordinary;
	std::map<std::string, CM> minor_capital;
	CM center;

	urbanAgglomeration(): ordinary(), minor_capital(), center(){
	}
};


struct SC{
	std::map<std::string, urbanAgglomeration> agglomerations;
	std::map<std::string, CM> uninodal;
	SC(): agglomerations(){}
};

//nodo
struct Node{
    
    char s;
    int f;
    Node *i,*d;
};
//HuffmanT
struct HuffmanBIN{
    std::tr1::unordered_map<char,std::string>CHuff;
    std::string bin;
};
//objeto de comparacion que sera usado para ordenar la pila
struct comp{
    bool operator()(Node*i,Node*d)
    {
        return i->f > d->f;
    }
};


//estructuras entrega 3 
struct Edge{
	CM connect;
	long double lengh;
     Edge(const CM &data) {
          connect = data;
          lengh = std::numeric_limits<double>::infinity();
     }
     Edge(const CM &data, const long double &size) {
          connect = data;
          lengh = size;
     }
};
struct Vertex{
	CM data;
	std::map<std::string,Edge> edges;
	Vertex(const CM & data): edges(){
		this->data= data;
	}
	
};
struct Graph{
	uint size;
	std::map<std::string, Vertex> vertexes;
	Graph(){}
	
	void insertVertex(const CM & data){
		Vertex d{data};
		vertexes.emplace(data.name,d);
	}
	void insertEdge(const CM & one, const CM& two, long double len){
		auto t1 = vertexes.find(one.name);
		auto t2 = vertexes.find(two.name);
		if(t1== vertexes.end() or t2== vertexes.end())
			throw std::bad_function_call(); //una excepcion rara

		Edge e{t2->second.data, len};
		t1->second.edges.emplace(t2->first, e );
		Edge e2{t1->second.data, len};
		t2->second.edges.emplace(t1->first, e2 );

	}
	void show(){
		for(auto & vertex: vertexes){
			cout<<vertex.first<<'\n';
			for(auto & edge: vertex.second.edges){
				cout<<"\t"<<edge.second.lengh<<"--"<<edge.first<<'\n'; 
			}
		}
	}
};