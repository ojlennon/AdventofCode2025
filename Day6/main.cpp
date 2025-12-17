#include <OwenUtils.hpp>
#include <vector>
#include <string>


using namespace std;

using ll = long long;

vector<vector<int>> extract_vertical_columns(const vector<string> &lines) {
    vector<vector<int>> columns;
    if (lines.empty()) return columns;

    int width = 0;
    for (const auto &line : lines)
        width = max(width, (int)line.size());

    for (int col = 0; col < width; col++) {
        bool has_digit = false;

        // Check if this column has any digits
        for (const auto &line : lines) {
            if (col < line.size() && isdigit(line[col])) {
                has_digit = true;
                break;
            }
        }

        if (!has_digit)
            continue;

        // We found a column containing digits → extract the number vertically
        vector<int> vertical_digits;
        for (const auto &line : lines) {
            if (col < line.size() && isdigit(line[col])) {
                vertical_digits.push_back(line[col] - '0');
            }
        }

        columns.push_back(vertical_digits);
    }

    return columns;
}


ll evaluate(vector<string> &line){
    string op = line.back();
    ll result = stoi(line.front());
    for(int i = 1; i < line.size() - 1; i++){
        if(op == "+"){
            result += stoll(line.at(i));
        }else if(op == "*"){
            result *= stoll(line.at(i));
        }else{
            cerr << "Not a recognized operator " << op << endl;
            exit(1);
        }
    }
    return result;
}

vector<vector<string>> get_equations_p1(const vector<vector<string>> &lines){
   
    int height = lines.size();
    int width = lines[0].size();

     vector<vector<string>> vec(width);
    for(int i = 0; i < width; i++){
        vec[i].reserve(height);
        for (int j = 0; j < height; j++){
         vec[i].push_back(lines[j][i]);
        }
    }
    return vec;
}

vector<vector<string>> get_equations_p2(const vector<vector<string>> &lines){ 
    int height = lines.size();
    int width = lines[0].size();
    

    //get operator
    //vector of vertical digits
    //get actual numbers

    vector<string> column_numbers;

    

    return vec;
}


int main() {
    string file_name = "example.txt";
    // string file_name = "input.txt";
    vector<string> raw_lines;

    // Read the file
    read_file(file_name, raw_lines);

    // Split each line into words
    vector<vector<string>> lines;
    lines.reserve(raw_lines.size());
    for (const auto &line : raw_lines) {
        lines.emplace_back(split_string(line));
    }

    // Transpose lines into equations
    vector<vector<string>> eqs_p1 = get_equations_p1(lines);

    //part 1
    ll result = 0;
    for(auto &eq: eqs_p1){
        result += evaluate(eq);
    }
    // cout << result;
    print_2D_vector(extract_vertical_columns(raw_lines));

    //part 2
    return 0;
}