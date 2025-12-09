#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


// pair<string,string> split(const string& line) {
//     char delimiter = '-';
//     size_t start = 0;
//     size_t end = line.find(delimiter);
//     string first = line.substr(start,end - start);
//     string second = line.substr(end + 1);
//     return {first,second};
// }



// int main(){
//   // ifstream file("example.txt");
//   ifstream file("input.txt");
//   string line = "";
//   vector<pair<string,string>> ranges;
//   if(file.is_open()){
//     long long valid_ids = 0;
//     while(getline(file,line)){
//       if(line == "") break;
//       pair<string,string> spl = split(line);
//       valid_ids += stoll(spl.second) - stoll(spl.first);
//       ranges.push_back(spl);
//     }
//     cout << valid_ids << "\n";


//     int count = 0;
//     while(getline(file,line)){
//       long long n = stoll(line);
//       for(auto &p: ranges){
//         if(n >= stoll(p.first) && n <= stoll(p.second)){
//           count++;
//           break;
//         }
//       }
//     }
//     cout << "Count: " << count;
//   }
// }






pair<long long,long long> split(const string& line) {
    char delimiter = '-';
    size_t start = 0;
    size_t end = line.find(delimiter);
    long long first = stoll(line.substr(start,end - start));
    long long second = stoll(line.substr(end + 1));
    return {first,second};
}



int main(){
  // ifstream file("example.txt");
  ifstream file("input.txt");
  string line = "";
  vector<pair<long long, long long>> ranges;
  if(file.is_open()){
    while(getline(file,line)){
      if(line == "") break;
      pair<long long,long long> spl = split(line);
      ranges.push_back(spl);
    }

    sort(ranges.begin(), ranges.end());

    vector<pair<long long,long long>> merged_ranges;
    merged_ranges.push_back(ranges[0]);


    for(int i = 1; i < ranges.size(); i++){
      if(ranges[i].first <= merged_ranges.back().second){
        merged_ranges.back().second = max(merged_ranges.back().second,ranges[i].second);
      }else{
        merged_ranges.push_back(ranges[i]);
      }
    }
    long long count = 0;
    for(auto &p: merged_ranges){
      count += p.second - p.first + 1;
    }
    cout << count;
  }
}
