#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

std::vector<std::string> split_string(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::string> split_string(const std::string &str){
    std::vector<std::string> result;
    std::istringstream iss(str);
    std::string word;
    while(iss >> word){
        result.push_back(word);
    }
    return result;
}

std::string join_no_sep(const std::vector<std::string>& v) {
    std::string out;
    for (const auto &s : v) out += s;
    return out;
}



void read_file(const std::string &file_name,std::vector<std::string> &lines){
    std::ifstream file(file_name);
    std::string line = "";
    if(file.is_open()){
        while(std::getline(file,line)){
            lines.push_back(line);
        }    
    }else{
        std::cerr << "Failed to open file " << file_name << "\n";
    }
}

template <typename T>
void print_vector(const std::vector<T> &vec){
    for(auto &item: vec){
        std::cout << item << " ";
    }
    std::cout << "\n";
}

template <typename T>
void print_2D_vector(const std::vector<std::vector<T>> &vec){
    for(const std::vector<T> &row: vec){
        print_vector(row);
    }
}