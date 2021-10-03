#pragma once
#include "structures.hpp"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <ios>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
using std::cout;
namespace printer {
template <typename first, typename second>
static void printMap(const std::map<first, second> &data,
                     const std::string &header = "",
                     const std::string &tail = "", const uint &perPage = 10,
                     const std::string &separator = "---") {
     auto start = data.begin();
     uint size = data.size();
     if (size > perPage) {
          // clearscreen;
          uint pages = ceil((float)size / perPage);
          for (uint i = 0; i < pages; i++) {
               std::cout << header;
               for (uint j = 0; start != data.end() && j < perPage;
                    start++, j++) {
                    std::cout << start->first << "---" << start->second.name
                              << '\n';
               }
               std::cout << "\nPágina: " << i + 1 << " de: " << pages << '\n';
               std::cout << tail;
               getchar();
               clearscreen();
          }
     } else {
          std::cout << header;
          for (auto &temp : data) {
               std::cout << temp.first << separator << temp.second.name << '\n';
          }
          std::cout << tail;
     }
}
static void print(const std::string &str, const uint perPage = 8) {
     uint new_lines = std::count(str.begin(), str.end(), '\n');
     if (new_lines > perPage) {
          uint pages = ceil((float)new_lines / perPage);
          auto pointer = str.begin();
          for (uint i = 0; i < pages; i++) {
               for (uint j = 0; j < perPage && pointer != str.end();
                    j++, pointer++) {
                    cout << pointer.base() << '\n';
               }
               std::cout << "\nPágina: " << i + 1 << " de: " << pages << '\n';
               getchar();
               clearscreen();
          }
     } else {
          std::cout << str << '\n';
     }
}

static void print(std::stringstream &stream, const uint &perPage = 8,
                  const std::string &head = std::string(25, '-'),
                  const std::string &tail = std::string(25, '-')) {
     uint new_lines = std::count(std::istreambuf_iterator<char>(stream),
                                 std::istreambuf_iterator<char>(), '\n');
     stream.seekg(std::ios::beg);
     if (new_lines > perPage) {
          uint pages = ceil((float)new_lines / perPage);
          char buffer[255];
          cout << head << '\n';
          for (uint i = 0, j = 0; !stream.eof(); i++) {
               stream.getline(buffer, 255, '\n');
               cout << buffer << '\n';
               if (i == perPage) {
                    cout << tail << '\n';
                    std::cout << "\nPágina: " << j + 1 << " de " << pages
                              << '\n';
                    getchar();
                    clearscreen();
                    cout << head << '\n';
				i=0;
                    j++;
               }
               if (stream.eof()) {
                    cout << tail << '\n';
               }
          }
     } else {
          cout << stream.str() << '\n';
     }
}
} // namespace printer