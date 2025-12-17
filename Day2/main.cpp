#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <sstream>

using namespace std;

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

bool check_number_part_one(int64_t num){
  if (num == 0) return false;
  int64_t digits = (int64_t)log10(num) + 1;
  if(digits % 2 == 1) return false;
  int64_t divisor = (int64_t)pow(10, digits / 2);
  int64_t left_half = num / divisor;
  int64_t right_half = num % divisor;
    
    return left_half == right_half;
}

bool check_number_part_two(int64_t num){
  if (num == 0) return false;
  string str_num = to_string(num);
  int64_t len = str_num.length();
  for(int pattern_len = 1; pattern_len <= len / 2; pattern_len++){
    if(len % pattern_len != 0) continue; // pattern length must divide total length
    string pattern = str_num.substr(0, pattern_len);
    bool is_repeating = true;
        for(int i = pattern_len; i < len; i += pattern_len){
            if(str_num.substr(i, pattern_len) != pattern){
                is_repeating = false;
                break;
            }
        }        
        if(is_repeating){
            return true;
        }
    }
    
    return false;
}


int64_t check_range( int64_t start,  int64_t end){
  int64_t count = 0;
  for(int64_t i = start; i <= end; i++){
    // if(check_number_part_one(i)) count+= i; 
    if(check_number_part_two(i)) count+= i; 
  }
  return count;
}


int main(){
  std::ifstream inputFile("input.txt");
  if(inputFile.is_open()){
    std::string line;
    std::getline(inputFile,line);
    std::vector<string> ranges = split(line,',');
    int64_t count = 0;
    for(const auto& range : ranges){
      // cout << "range: " << range << "\n";
      vector<string> nums = split(range, '-');
      // cout << nums.size() << nums.at(0) << " " << nums.at(1)<<"\n";
       int64_t first = stoll(nums[0]);
       int64_t second = stoll(nums[1]);
      count += check_range(first,second);
    }
    cout << count;
  }
}
