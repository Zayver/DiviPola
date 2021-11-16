/**
 * @file structures.hpp
 * @brief
 * Cabecera para las definiciones de las estructuras del programa
 * Así como la sobrecarga de sus operadores y funciones
 */
#pragma once
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#include <tr1/unordered_map>
#include <limits>
#include <list>

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
bool operator==(const CM &first, const CM &second) {
     return first.name == second.name;
}

struct Edge {
     CM cm;
     long double lengh;
     Edge(const CM &data) {
          cm = data;
          lengh = std::numeric_limits<double>::infinity();
     }
     Edge(const CM &data, const long double size) {
          cm = data;
          lengh = size;
     }
};
bool operator==(const Edge &first, const Edge &second) {
     return first.cm.name == second.cm.name;
}
bool operator<(const Edge &first, const Edge &second) {
     return first.lengh < second.lengh;
}

struct Vertex {
     CM cm;
     std::list<Edge> members;
	double distance = std::numeric_limits<double>::infinity();
     bool visited = false;
	Vertex *predecessor = nullptr;
     Vertex(const CM &data) : members() { cm = data; }
	Vertex(){}
};

class Compare {
   public:
     bool operator()(Vertex *v1, Vertex *v2) {
          return v1->distance < v2->distance;
     }
};

struct Graph {
     std::map<std::string, Vertex> vertex;

	Graph(): vertex{}{}
     Graph(const std::initializer_list<CM> &params): vertex{}{
          for (auto &temp : params) {
               insertVertex(temp);
          }
     }
     void insertVertex(const CM &temp) {
          vertex.emplace(std::piecewise_construct, std::make_tuple(temp.name),
                         std::make_tuple(temp));
     }
     void deleteVertex(const CM &del) {
          auto c = vertex.find(del.name);
          c->second.members.remove_if(
              [del](const Edge &cm) { return cm.cm.name == del.name; });
          vertex.erase(del.name);
     }
     void insertEdge(const CM &first, const CM &second) {
          vertex.at(first.name).members.emplace_back(second);
          vertex.at(second.name).members.emplace_back(first);
     }
     void insertEdge(const CM &first, const CM &second,
                     const long double size) {
          vertex.at(first.name).members.emplace_back(second, size);
          vertex.at(second.name).members.emplace_back(first, size);
     }
     void deleteEdge(const CM &first, const CM &second) {
          vertex.at(first.name).members.remove(second);
          vertex.at(second.name).members.remove(first);
     }
	Vertex* search(const CM & cm){
		auto d = vertex.find(cm.name);
		if(d!=vertex.end())
			return &d->second;
		else
		 	return nullptr;
	}
     void dijkstraAlgorithm(Vertex* &start) {

		//reinicializar cosas en los vertices
		for(auto & temp: vertex){
			temp.second.distance= std::numeric_limits<double>::infinity();
			temp.second.predecessor=nullptr;
			temp.second.visited=false;
		}

		std::priority_queue<Vertex *, std::vector<Vertex *>, Compare> left;
		start->distance=0;
		left.emplace(start);

		while(!left.empty()){
			
			Vertex * current = left.top();
			for(auto & temp: current->members){
				auto f = vertex.find(temp.cm.name);
				if(!f->second.visited){
					if(current->distance+temp.lengh< f->second.distance){
						f->second.distance= current->distance+temp.lengh;
						f->second.predecessor=current;
						left.push(&f->second);
					}
				}

			}
			left.pop();
			
			current->visited=true;
			
		}
			

	}
	std::list<Vertex*> shortestPath(Vertex* start, Vertex * end){
		dijkstraAlgorithm(start);
		std::list<Vertex*>sp;
		sp.push_front(end);
		while(end->predecessor!=nullptr){
			sp.push_front(end->predecessor);
			end=end->predecessor;
		}
		return sp;
	}
	
};
