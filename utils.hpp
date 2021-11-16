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
#include <cmath>
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

static std::stringstream createTable(std::stringstream & stream, uint columns, std::string del = ","){
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

constexpr long double TORAD = M_PI/ 180;
constexpr long double EARCHRADIUS = 6378.14;
long double coordinatesToKm(long double lat1, long double lon1, long double lat2, long double lon2){
	double dlong = (lon2 - lon1) * TORAD ;
    	double dlat = (lat2 - lat1) * TORAD;
    	double a = pow(sin(dlat/2.0), 2) + cos(lat1*TORAD) * cos(lat2*TORAD) * pow(sin(dlong/2.0), 2);
    	double c = 2 * atan2(sqrt(a), sqrt(1-a));
    	double d = EARCHRADIUS * c;
    	return d;
}