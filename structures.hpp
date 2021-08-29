	#pragma once
	#include <cstdio>
	#include <string>
	#include <list>

	//borrar
	#include <iostream> 
	using std::cout;

	struct CP{
		unsigned int code;
		std::string name;
		CP(const unsigned int code, const std::string n):name(n){
			this->code=code;
		}
	};
	struct CM{
		//puede que lleve mas cosas pero no entiendo eso bien
		unsigned int code;
		std::string name;
		std::list<CP>cp;
		unsigned int population;
		CM(const unsigned int code, const std::string n): name(n), cp(){
			this->code=code;
		}
		void insertCP(const unsigned int code, const std::string name){
			cp.emplace_back(code, name);
		}
		std::string getName() const noexcept{ return name;}

	};
	struct Department{
		unsigned int code; // no se si dejarlo como string
		std::string name;
		std::list<CM> cm;
		Department(const unsigned int code, const std::string n)
		:name(n), cm(){
			this->code=code;
		}
		
		auto getLastCM(){
			return cm.back();
		}
		std::string getName() const noexcept{return name;}

		
	};

	bool operator ==(const Department &dpto, const unsigned int & code){
			return dpto.code==code;
	}

