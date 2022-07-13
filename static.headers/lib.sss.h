#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>
#include <direct.h>
#include <chrono>
#include <thread>
#include <future>
#include <cmath>

const int unsigned short PARAM_STR = 1;
const int unsigned short PARAM_INT = 2;
const int unsigned short PARAM_FLOAT = 3;
const int unsigned short PARAM_DOUBLE = 3;

const int unsigned short NORMAL_ENCRYPT = 1;


inline void endl(int times = 1) {
    for (int i = 0; i < times; i++) {
        std::cout << std::endl;
    }
}

template <typename all_type>
inline void cout(all_type stdcout_value, int times_endl = 0) {
    std::cout << stdcout_value;
    endl(times_endl);
}

inline void coutvector(std::vector<std::string> vector_array) {
	for (int i = 0; i < vector_array.size(); i++)
		cout("[" + std::to_string(i) + "] => " + vector_array[i], true);
}
template <typename typeval>
inline void swap(typeval& a, typeval& b) { typeval aux = a; a = b; b = aux; }
inline void swap(bool& typebool) { if (typebool) typebool = false; else typebool = true; }
inline bool between(int value, int num1, int num2, int equal = 0) {
	if (num1 > num2) swap(num1, num2);
	switch (equal) {
	case 1:
		num1--;
		break;
	case 2:
		num2++;
		break;
	case 3:
		num1--;
		num2++;
		break;
	default: break;
	}
	return (num1 < value&& num2 > value);
}
inline std::string around(std::string show_value, std::string around_value) {
	return around_value + show_value + around_value;
}
inline bool chrisnum(char typechar) {
	return between(int(typechar), 47, 58);
}
inline void end(bool pause = true) {
	std::cout << "\n";
	if(pause) system("PAUSE");
}

inline bool stronlynum(std::string typestring) {
	for (int unsigned i = 0; i < typestring.length(); i++)
		if (!chrisnum(typestring[i])) return false;
	return true;
}
inline bool stronlyopnum(std::string typestring) {
	bool confi = false;
	for (int unsigned i = 0; i < typestring.length(); i++) {
		if (typestring[i] == '.' && confi == true) return false;
		if (typestring[i] == '.') confi = true;
		if (!chrisnum(typestring[i])) return false;
	}
	return true;
}

inline bool file_exist(std::string file_name) { 
	std::ifstream in(file_name); return in.good();
}
inline void create_file(std::string file_name) {
	if (!file_exist(file_name)) {
		std::ofstream out; out.open(file_name); out << ""; out.close();
	}
}
inline void create_folder(std::string folder_name) { if (_mkdir(folder_name.c_str())) {}; }

inline std::string strtoupper(std::string typestring) {
	for (int i = 0; i < typestring.length(); i++) typestring[i] = toupper(typestring[i]);
	return typestring;
}

inline std::string cutstring(std::string typestring, int begin, int end) {
	std::string aux = "";
	for (int i = begin; (i < typestring.length() && i < end); i++) aux += typestring[i];
	return aux;
}
inline std::string cutstring(std::string typestring, int end) {
	std::string aux = "";
	for (int i = 0; (i < typestring.length() && i < end); i++) aux += typestring[i];
		return aux;
}

inline std::string cleanstring(std::string typestring, const int method = PARAM_STR) {
	std::string aux = "";
	bool pos = false;

	switch (method) {
		case 1:
			for (int i = 0; i < typestring.length(); i++)
				if (typestring[i] != ' ') aux += typestring[i];
		break;
		case 2:
			for (int i = 0; i < typestring.length(); i++) {
				if (chrisnum(typestring[i])) aux += typestring[i];
			}
			if (aux == "") aux = "0";
			break;
		case 3:
			for (int i = 0; i < typestring.length(); i++) {
				if (typestring[i] == '.') {
					if (pos == false) swap(pos);
					else continue;
				}
				if (chrisnum(typestring[i]) || typestring[i] == '.') aux += typestring[i];
			}
			if (aux == "") aux = "0";
			if(aux[0] == '.') aux = "0" + aux;
			if (aux[aux.length() - 1] == '.') aux = aux + "0";
			break;
		default: break;
	}
	return aux;
}

inline std::vector<std::string> split(std::string typestring, char index) {
	std::vector<std::string> ret;
	std::string aux = "";
	for (int unsigned i = 0; i < typestring.length(); i++) {
		if (typestring[i] == index) {
			ret.push_back(aux);
			aux = "";
		}
		else aux += typestring[i];
	}
	if (aux != "") ret.push_back(aux);
	return ret;
}

inline int random_letter() {
	int x = rand() % 93 + 33;
	if (x != 92) return x;
	else return random_letter();
}
inline int random_num(int range, int extra_range = 0) {
	return (rand() % range + extra_range);
}
int election(std::string context, int num1, int num2, int equal = 0) {
	std::string line = "";
	cout(context); std::getline(std::cin, line, '\n');
	line = cleanstring(line, PARAM_INT);
	if (between(stoi(line), num1, num2, equal)) {
		return stoi(line);
	}
	return -1;
}
int** get_matrix(int row, int column, int base_number = 0) {
	int** arr = new int* [row];
	for (int i = 0; i < column; i++) arr[i] = new int[column];
	for (int i = 0; i < row; i++) for (int j = 0; j < column; j++) arr[i][j] = base_number;
	return arr;
}

std::string encrypt(std::string text, int method = NORMAL_ENCRYPT) {
	std::string line = "";
	if(method == 1) {
		for (int i = 0; i < text.length(); i++) {
			int num1 = random_num(9, 1), num2 = random_num(9, 1), num3 = random_num(9, 1);
			int chr = int(text[i]);
			chr = (((chr + num1) - num2) * num3);
			line += std::to_string(num1) +
				std::to_string(num2) + 
				std::to_string(num3) + "/" + 
				std::to_string(chr) + "?";
		}
		return cutstring(line, int(line.length() - 1));
	}
	return "";
}
std::string decrypt(std::string text, int method = NORMAL_ENCRYPT) {
	std::string line = "";
	if (method == 1) {
		std::vector<std::string> split_char = split(text, '?');
		for (int i = 0; i < split_char.size(); i++) {
			std::vector<std::string> split_res = split(split_char[i], '/');
			int num1 = split_res[0][0] - '0', num2  = split_res[0][1] - '0', num3 = split_res[0][2] - '0';
			line += char((((stoi(split_res[1])) / num3) + num2) - num1);
		}
		return line;
	}
	return "";
}




/*
class TextManager {
private:
    std::string file_name;
    std::ofstream out;
    std::ifstream in;

    bool break_nextread = false;

public:
    TextManager(std::string file_name) {
        change_filename(file_name);
    }

    void write(std::string text) {
        out.open(file_name, std::ios::app);
        out << text;
        out.close();
    }

    void write_line(std::string text) {
        this->write(text + "\n");
    }

    std::vector<std::string> read_lines() {
        in.open(file_name);
        std::string line;
        std::vector<std::string> lines;
        while (std::getline(in, line)) {
            lines.push_back(line);
        }
        in.close();
        return lines;
    }

    bool read_line(std::string& line) {
        if(break_nextread) {
            break_nextread = false;
            return false;
        }
        if(!in.is_open()) {
            in.open(file_name);
        }
        if(std::getline(in, line)) {
            return true;
        }
        else {
            this->readclose();
            return false;
        }
    }

    void readclose(bool false_nextread = false) {
        in.close();
        this->break_nextread = false_nextread;
    }

    void change_filename(std::string new_file_name) {
        this->file_name = new_file_name;
        create_file(this->file_name);
    }
};

class TextVariable: public TextManager {
private:
	char prefix;

public:
	TextVariable(std::string file_name, char prefix = '='): TextManager(file_name) {
		this->prefix = prefix;
	}

	void get_value(std::string variable_name) {
		
	}
};

/* Delimiter lines for 10000 */
class readtxt {
private:
	std::string file_name = "readtxt.txt";
	std::ofstream out; std::ifstream in;

	void error(std::string context) {
		if (show_errors) cout(context, 1);
	}
public:
	char prefix = '=';
	bool show_errors = false;	

	readtxt(std::string file_name, bool createfile = true, char prefix = '=') {
		if(createfile) create_file(file_name);
		this->file_name = file_name;
		this->prefix = prefix;
	}

	int prefix_pos(std::string line) {
		for (int i = 0; i < line.length(); i++)
			if(line[i] == this->prefix) return i;
		return -1;
	}
	int file_length() {
		int length = 0;
		std::string line = "";
		
		in.open(file_name);
		while (std::getline(in, line, '\n')) {
			length++;
		}
		in.close();
		return length;
	}
	
	int var_pos(std::string var_name) {
		std::string line = "";
		int actual_pos = 0;
		in.open(file_name);
		while (getline(in, line, '\n')) {
			if (cleanstring(cutstring(line, prefix_pos(line))) == var_name) {
				in.close();
				return actual_pos;
			}
			actual_pos++;
		}
		in.close();
		error("var not found => " + var_name);
		return -1;
	}
	std::string var_value(std::string var_name) {
		std::string line = "";
		in.open(file_name);
		while (getline(in, line, '\n')) {
			if (cleanstring(cutstring(line, prefix_pos(line))) == var_name) {
				in.close();
				return cutstring(line, prefix_pos(line) + 1, int(line.length()));
			}
		}
		in.close();
		return "";
	}
	void set_var_value(std::string var_name, std::string var_value) {
		std::string aux = std::to_string(random_num(10000)) + ".txt";
		create_file(aux);
		std::string line = "";

		in.open(file_name);
		out.open(aux);
		while (getline(in, line, '\n')) {
			if (cleanstring(cutstring(line, prefix_pos(line))) == var_name) {
				out << var_name + prefix + var_value + "\n";
				continue;
			}
			out << line + "\n";
		}
		out.close();
		in.close();
		remove(file_name.c_str());
		if (rename(aux.c_str(), file_name.c_str())) {};
	}
	std::vector<std::string> var_value_array(std::string var_name) {
		std::vector<std::string> ret;
		std::string line = "";
		in.open(file_name);
		while (getline(in, line, '\n')) {
			if (cleanstring(cutstring(line, prefix_pos(line))) == var_name) {
				ret.push_back(cutstring(line, prefix_pos(line) + 1, int(line.length())));
			}
		}
		in.close();
		return ret;
	}
	
	void newline(std::string line, std::string file_name = "file_name") {
		if (file_name == "file_name") file_name = this->file_name;
		out.open(file_name, std::ios::app);
		out << line + "\n";
		out.close();
	}
	void newvar(std::string var_name, std::string var_value, std::string file_name = "file_name") {
		newline(var_name + prefix + var_value, file_name);
	}
	
	void remove_pos(int position) {
		if (position >= 0) {
			int actual_pos = 0;
			std::string aux = std::to_string(random_num(10000)) + ".txt";
			create_file(aux);
			std::string line = "";
			
			in.open(file_name);
			out.open(aux);
			while (getline(in, line, '\n')) {
				if (actual_pos != position) {
					out << line + "\n";
				}
				actual_pos++;
			}
			out.close();
			in.close();
			remove(file_name.c_str());
			if (rename(aux.c_str(), file_name.c_str())) {};
		}
	}
	void remove_variable(std::string var_name) {
		std::string aux = std::to_string(random_num(10000)) + ".txt";
		create_file(aux);
		std::string line = "";

		in.open(file_name);
		out.open(aux);
		while (getline(in, line, '\n')) {
			if (cleanstring(cutstring(line, prefix_pos(line))) != var_name) {
				out << line + "\n";
			}
		}
		out.close();
		in.close();
		remove(file_name.c_str());
		if (rename(aux.c_str(), file_name.c_str())) {};
	}

	std::string get_filename() { return this->file_name; }
	void set_filename(std::string file_name) {
		this->file_name = file_name;
	}
};