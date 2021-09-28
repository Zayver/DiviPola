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

