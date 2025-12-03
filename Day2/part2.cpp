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

int64_t check_range( int64_t start,  int64_t end){
  int64_t count = 0;
  for(int64_t i = start; i <= end; i++){
    if(check_number(i)) count+= i; 
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
    //   cout << "range: " << range << "\n";
      vector<string> nums = split(range, '-');
    //   cout << nums.size() << nums.at(0) << " " << nums.at(1)<<"\n";
       int64_t first = stoll(nums[0]);
       int64_t second = stoll(nums[1]);
      count += check_range(first,second);
    }
    cout << count;
  }
}
