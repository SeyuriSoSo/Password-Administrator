/*
    std::ifstream  src("test.txt", std::ios::binary);
    std::ofstream  dst("test2.txt",   std::ios::binary);

    dst << src.rdbuf();
    */

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <direct.h>
#include <cmath>

#include "ProcessTimer.h"
#include "pro_timer.h"

namespace aes {

const int unsigned short NORMAL_ENCRYPT = 1;

inline int random_number(int range, int offset = 0) {
    return rand() % range + offset;
}

inline char random_letter(bool letter_upper = true, bool letter_lower = true, bool number = true, bool symbol = true) {
    std::string letters_lower = "abcdefghijklmnopqrstuvwxyz";
    std::string letters_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string numbers = "0123456789";
    std::string symbols = "\"!@#$%^&*()_+-=[]{}|;':,./<>?";
    std::string data = "";
    if (letter_upper) data += letters_upper;
    if (letter_lower) data += letters_lower;
    if (number) data += numbers;
    if (symbol) data += symbols;
    return data[rand() % data.size()];
}

inline std::string random_string(int length = 8, bool letter_upper = true, bool letter_lower = true, bool number = true, bool symbol = true) {
    std::string data = "";
    for (int i = 0; i < length; i++)
        data += random_letter(letter_upper, letter_lower, number, symbol);
    return data;
}

inline void break_line(int times = 1) {
    for(int i = 0; i < times; i++)
        std::cout << std::endl;
}

std::string get_text(std::string text = "") {
    std::string data;
    std::cout << text;
    std::getline(std::cin, data);
    return data;
}

template <typename text_type>
inline void print_text(text_type text, int breakline_times = 1) {
    std::cout << text;
    break_line(breakline_times);
}

template <typename vec_type>
inline void print_vector(std::vector<vec_type> vec) {
    for(int i = 0; i < vec.size(); i++)
        std::cout << "[" << i << "] => " << vec[i] << "\n";
}

template <typename all_type>
inline void swap(all_type &a, all_type &b) {
    all_type temp = a; a = b; b = temp;
}

inline void swap(bool &boo) {
    boo = !boo;
}

inline bool between(int value, int min, int max, int equal = 0) {
	switch (equal) {
	case 1:
		min--;
		break;
	case 2:
		max++;
		break;
	case 3:
		min--;
		max++;
		break;
	default: break;
	}
	return (min < value && max > value);
}

inline bool validate_string_numberint(std::string str) {
    for(int i = 0; i < str.size(); i++)
        if((str[i] < '0' || str[i] > '9') && str[i] != '-')
            return false;
    return true;
}

inline bool validate_string_numberfloat(std::string str) {
    for(int i = 0; i < str.length(); i++)
        if((str[i] < '0' || str[i] > '9') && (str[i] != '.' && str[i] != '-'))
            return false;
    return true;
}

inline std::string sanitize_stringint(std::string str) {
    std::string new_str = "";
    for(int i = 0; i < str.length(); i++)
        if((str[i] >= '0' && str[i] <= '9') || str[i] == '-')
            new_str += str[i];
    return new_str;
}

inline std::string sanitize_stringfloat(std::string str) {
    std::string new_str = "";
    for(int i = 0; i < str.length(); i++)
        if((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || str[i] == '-')
            new_str += str[i];
    return new_str;
}

inline bool file_exist(std::string file_name) {
    std::ifstream file(file_name); return file.good();
}

inline bool create_file(std::string file_name) {
    if (!file_exist(file_name)) {
	    std::ofstream out; out.open(file_name); out << ""; out.close();
        return true;
    }
    return false;
}

inline bool create_directory(std::string dir_name) {
    if(_mkdir(dir_name.c_str()) == 0)
        return true;
    return false;
}

inline bool delete_file(std::string file_name) {
    if(remove(file_name.c_str()) == 0)
        return true;
    return false;
}

inline bool delete_directory(std::string dir_name) {
    if(rmdir(dir_name.c_str()) == 0)
        return true;
    return false;
}

inline std::string no_whitespace(std::string str) {
    std::string new_str = "";
    for(int i = 0; i < str.length(); i++)
        if(str[i] != ' ') new_str += str[i];
    return new_str;
}

inline std::string string_toupper(std::string text) {
    for(int i = 0; i < text.length(); i++)
        text[i] = toupper(text[i]);
    return text;
}

inline std::string string_tolower(std::string text) {
    for(int i = 0; i < text.length(); i++)
        text[i] = tolower(text[i]);
    return text;
}

inline std::vector<std::string> split(std::string typestring, char separator) {
    std::vector<std::string> vec;
    std::string line = "";
    for(int i = 0; i < typestring.length(); i++) {
        if(typestring[i] == separator) {
            vec.push_back(line);
            line = "";
        }
        else line += typestring[i];
    }
    if(line != "") vec.push_back(line);
    return vec;
}

std::string encrypt(std::string text, int method = NORMAL_ENCRYPT) {
	std::string line = "";
    if(method == 1) {
    	for (int i = 0; i < text.length(); i++) {
            int num1 = random_number(9, 1), num2 = random_number(9, 1), num3 = random_number(9, 1);
    		int chr = int(text[i]);
	    	chr = (((chr + num1) - num2) * num3);
		    line += std::to_string(num1) +
    			std::to_string(num2) + 
	    		std::to_string(num3) + "/" + 
	    		std::to_string(chr) + "?";
	    }
        return line.erase(line.length() - 1);
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

class TextManager {
private:
    std::string file_name;
    std::ofstream file_out;
    std::ifstream file_in;

    std::vector<std::string> aux_files;

public:
    bool auto_reset_read = true;
    
    TextManager(std::string file_name) {
        this->file_name = file_name;
        aes::create_file(file_name);
        this->open();
    }

    ~TextManager() {
        this->close();
        for(int i = 0; i < aux_files.size(); i++)
            aes::delete_file(aux_files[i]);
    }

    void write(std::string text) {
        file_out << text;
    }

    void write_line(std::string text) {
        file_out << text + "\n";
    }

    std::vector<std::string> read_lines() {
        std::vector<std::string> vec;
        std::string line = "";
        while(this->read_line(line)) {
            vec.push_back(line);
        }
        return vec;
    }
    bool read_line(std::string &line) {
        if(std::getline(file_in, line)) return true;
        else {
            if(this->auto_reset_read) {
                this->reset_in();
            }
            return false;
        }
    }

    void open_out() {
        file_out.open(file_name, std::ios::app);
    }
    void open_in() {
        file_in.open(file_name);
    }
    void open() {
        this->open_out();
        this->open_in();
    }

    void reset_in() {
        this->close_in();
        this->open_in();
    }
    void reset_in_break(bool &boo) {
        boo = false;
        this->reset_in();
    }
    void reset() {
        this->close();
        this->open();
    }

    void close_in() {
        file_in.close();
    }
    void close_out() {
        file_out.close();
    }
    void close() {
        this->close_in();
        this->close_out();
    }

    std::string get_variable(std::string variable_name) {
        this->reset();
        std::string line = "";
        while(this->read_line(line)) {
            auto pos = line.find('=');
            if(pos == std::string::npos) continue;
            if(variable_name == no_whitespace(line.substr(0, pos))) {
                this->reset_in();
                return line.substr(pos + 1, line.size());
            }
        }
        this->reset_in();
        return "";
    }

    std::string get_variablename(std::string variable_value) {
        this->reset();
        std::string line = "";
        while(this->read_line(line)) {
            auto pos = line.find('=');
            if(pos == std::string::npos) continue;
            if(variable_value == line.substr(pos + 1, line.size())) {
                this->reset();
                return line.substr(0, pos);
            }
        }
        this->reset();
        return "";
    }

    bool remove_variable(std::string variable_name) {
        this->reset();
        std::string aux = aes::random_string(5, true, true, false, false) + ".txt";
        std::string line = "";
        bool complete = false;
        std::ofstream file_in_aux;
        file_in_aux.open(aux, std::ios::app);
        while(this->read_line(line)) {
            if(!complete) {
                auto pos = line.find('=');
                if(pos != std::string::npos && variable_name == no_whitespace(line.substr(0, pos))) {
                    complete = true;
                    continue;
                }
            }
            file_in_aux << line << "\n";
        }
        file_in_aux.close();
        this->close();
        aes::delete_file(file_name);
        rename(aux.c_str(), file_name.c_str());
        this->open();
        if(complete) return true;
        else return false;
    }

    bool set_variable(std::string variable_name, std::string variable_value) {
        this->reset();
        std::string aux = aes::random_string(5, true, true, false, false) + ".txt";
        std::string line = "";
        bool complete = false;
        std::ofstream file_in_aux;
        file_in_aux.open(aux, std::ios::app);
        while(this->read_line(line)) {
            if(!complete) {
                auto pos = line.find('=');
                if(pos != std::string::npos && variable_name == no_whitespace(line.substr(0, pos))) {
                    line = variable_name + "=" + variable_value;
                    complete = true;
                }
            }
            file_in_aux << line << "\n";
        }
        file_in_aux.close();
        this->close();
        aes::delete_file(file_name);
        rename(aux.c_str(), file_name.c_str());
        this->open();
        if(complete) return true;
        else return false;
    }
};


}