/**
 * @file utils.hpp
 * @brief
 * Utilerias y demás
 *
 */
#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
typedef unsigned int uint;

static std::string trim(const std::string &input) {

     std::string output;
     std::unique_copy(input.begin(), input.end(),
                      std::back_insert_iterator<std::string>(output),
                      [](char a, char b) { return isspace(a) && isspace(b); });
     output.erase(output.begin(),
                  find_if(output.begin(), output.end(),
                          not1(std::ptr_fun<int, int>(isspace))));
     output.erase(find_if(output.rbegin(), output.rend(),
                          not1(std::ptr_fun<int, int>(isspace)))
                      .base(),
                  output.end());

     return output;
}

static std::vector<std::string> tokenize(std::string s, const std::string del = " ",
                                  const char dlim = '\"') {
     std::vector<std::string> tokens;
     int start = 0, end = s.find(del);
     while (end != -1) {
          if (s.at(start) == dlim) {
               start++;
               end = s.find(dlim, start);
          }
          if (start != end)
               tokens.emplace_back(s.substr(start, end - start));
          start = end + del.size();
          end = s.find(del, start);
     }
     tokens.emplace_back(s.substr(start, end - start));
     return tokens;
}

std::stringstream createTable(std::stringstream & stream, uint columns, std::string del = ","){
	//!EL STREAM NO DEBE TERMINAR CON UN SALTO DE LINEA PORQUE SI NO 
	//!SE IMPRIME UNA FILA DE MAS
	std::stringstream table;
	std::string buffer_tok;
	uint cell_s= 30; //por defecto aceptaria 30 
	uint cell_space = cell_s*columns+5;
	table<<std::setfill('-')<<std::setw(cell_space)<<'\n';  //header
	
	
	char buffer[255];
	while (!stream.eof()) {
		stream.getline(buffer, 255,'\n');
		buffer_tok= std::string(buffer);
		auto tokens = tokenize(buffer_tok,del);
		table<<std::setfill(' ');
		table<<"|";
		for(auto & temp: tokens){
			table<<std::setw(cell_s)<<temp<<"|";
		}
		table<<'\n';
		table<<std::setfill('-')<<std::setw(cell_space)<<'\n'; // tail
	}

	
	return table;
};
