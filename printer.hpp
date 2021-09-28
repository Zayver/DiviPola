#pragma once
#include "structures.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
using mapper = std::map<unsigned int, Department>;

namespace printer {
/*
//!Funcion para imprimir cualquier contenedor excepto map, por si acaso
template <typename Container, typename dataType>
void print(const Container &data, const uint &perPage = 10) {
     std::ostream_iterator<dataType> out_it(std::cout, "\n");
     auto start = data.begin();
     auto end = data.begin();
     uint size = data.size();
     if (size > perPage) {
          uint pages = ceil((float)size / perPage);
          for (uint i = 0, increment = 0; i < pages; i++) {
               if (increment + perPage > size)
                    increment = size - increment;
               else
                    increment = perPage;
               std::advance(end, increment);
               std::copy(start, end, out_it);
               std::advance(start, increment);
               std::cout << "\nPagina: " << i + 1 << " de: " << pages << '\n';
               //getchar();
               //clearscreen();
          }
     } else {
          std::copy(start, data.end(), out_it);
     }
}*/

template<typename first, typename second>
static void printMap(const std::map<first, second> &data,
			const std::string& header="", const std::string & tail="",
              	const uint &perPage = 10, const std::string & separator="---") {
     auto start = data.begin();
     uint size = data.size();
     if (size > perPage) {
          //clearscreen;
          uint pages = ceil((float)size / perPage);
          for (uint i = 0; i < pages; i++) {
			std::cout<<header;
               for (uint j = 0; start != data.end() && j < perPage;
                    start++, j++) {
                    std::cout << start->first<<"---"<<start->second.name<<'\n';
               }
               std::cout << "\nPágina: " << i + 1 << " de: " << pages << '\n';
			std::cout<<tail;
               getchar();
               clearscreen();
          }
     } else {
		std::cout<<header;
		for(auto & temp: data){
			std::cout << temp.first<<separator<<temp.second.name<<'\n';
		}
		std::cout<<tail;
     }
}
/*
static void printMap_set(const mapper &data) {
     std::set<std::string> printer;
     std::transform(
         data.begin(), data.end(), std::inserter(printer, printer.begin()),
         [](const std::pair<uint, Department> &aux) {
              return std::to_string(aux.first) + "---" + aux.second.name;
         });
	print<std::set<std::string>, std::string>(printer);
}*/
} // namespace printer