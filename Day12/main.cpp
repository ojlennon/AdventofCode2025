#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <queue>
#include "OwenUtils.hpp"

using namespace std;

class Present
{
public:
    int width;
    int height;
    int size = 0;
    vector<vector<string>> shape;
    vector<pair<int, int>> coordinates; // coordinates of "#" in shape
    Present(int w, int h, vector<string> lines_in) : width(w), height(h)
    {
        shape = split_string_no_spaces(lines_in);
        // process shape to get coordinates
        for (int r = 0; r < height; r++)
        {
            for (int c = 0; c < width; c++)
            {
                if (shape[r][c] == "#")
                {
                    coordinates.push_back(make_pair(r, c));
                    size++;
                }
            }
        }
    }

    int get_size()
    {
        return size;
    }

    friend ostream &operator<<(ostream &os, const Present &p)
    {
        for (const auto &row : p.shape)
        {
            for (const auto &cell : row)
            {
                os << cell;
            }
            os << "\n";
        }
        return os;
    }


    vector<Present> get_rotations() const
    {
        vector<Present> rotations;
        Present current = *this;
        for (int i = 0; i < 3; i++)
        {
            // Rotate 90 degrees clockwise
            vector<vector<string>> new_shape(current.width, vector<string>(current.height, "."));
            for (int r = 0; r < current.height; r++)
            {
                for (int c = 0; c < current.width; c++)
                {
                    new_shape[c][current.height - 1 - r] = current.shape[r][c];
                }
            }
            current.shape = new_shape;
            swap(current.width, current.height);
            // Update coordinates
            current.coordinates.clear();
            for (int r = 0; r < current.height; r++)
            {
                for (int c = 0; c < current.width; c++)
                {
                    if (current.shape[r][c] == "#")
                    {
                        current.coordinates.push_back(make_pair(r, c));
                    }
                }
            }
            rotations.push_back(current);
        }
        return rotations;
    }
};

class Region
{
public:
    vector<vector<string>> region;
    vector<int> reqired_presents;
    int width, height;
    vector<Present> *presents;
    Region(int width, int height, vector<int> req_presents, vector<Present> *presents) : reqired_presents(req_presents)
    {
        // init region vector with "."
        this->width = width;
        this->height = height;
        region = vector<vector<string>>(height, vector<string>(width, "."));
        this->presents = presents;
    }

    friend ostream &operator<<(ostream &os, const Region &r)
    {
        for (const auto &row : r.region)
        {
            for (const auto &cell : row)
            {
                os << cell;
            }
            os << "\n";
        }
        return os;
    }

     bool check_area() const {
        int total_area = 0;
        for(int i=0; i<reqired_presents.size(); i++){
            total_area += reqired_presents[i] * (*presents)[i].get_size();
        }
        // cout << "Total required area: " << total_area << " " << "Region area: " << width * height << "\n";
        return total_area <= width * height;
    }

    bool check_overlap() const{
        //if we can fit all the 3x3 items with no overlap, we can fit the region
        int num_boxes = (width / 3) * (height / 3);
        int total_required = 0;
        for(int i=0; i<reqired_presents.size(); i++){
            total_required += reqired_presents[i];
        }
        cout << "Total required boxes: " << total_required << " " << "Available boxes: " << num_boxes << "\n";
        return total_required <= num_boxes;
    }

    // region find Present. See if Present can fit in current region vector
};

void load_presents(const vector<string> &raw_lines, vector<Present> &presents)
{
    presents.reserve(6);
    for (int i = 0; i < 6; i++)
    {
        vector<string> shape_lines;
        shape_lines.push_back(raw_lines[i * 5 + 1]);
        shape_lines.push_back(raw_lines[i * 5 + 2]);
        shape_lines.push_back(raw_lines[i * 5 + 3]);
        Present p(3, 3, shape_lines);
        presents.push_back(p);
    }
}

void process_region(Region &region, const vector<Present> &presents)
{
    //backtracking algorithm
    //try like a few billion and if it doesn't work then call it impossible

};

int main()
{
    string file_name = "input.txt";
    vector<string> raw_lines;
    read_file(file_name, raw_lines);

    vector<Present> presents;
    load_presents(raw_lines, presents);

    int problem_index = 6 * 5;

    vector<Region> regions;

    // Get Valid Regions
    for (int i = problem_index; i < raw_lines.size(); i++)
    {
        vector<string> row = split_string(raw_lines[i]);
        vector<string> r = split_string(row[0].substr(0, row[0].size() - 1), 'x');
        int region_width = stoi(r[0]);
        int region_height = stoi(r[1]);
        vector<int> req_presents;
        for (int i = 1; i < row.size(); i++)
        {
            req_presents.push_back(stoi(row[i]));
        }
        Region region(region_width, region_height, req_presents, &presents);
        if(region.check_area()){
            cout << "Region can fit required presents based on area.\n";
            regions.push_back(region);
        }
        
    }

    int n = 0;
    int m = 0;
    for (auto &region : regions)
    {
        if(region.check_overlap()){
            cout << "Region can fit required presents based on overlap check.\n";
            n++;
        }else{
            cout << "Region cannot fit required presents based on overlap check.\n";
            m++;
        }
    }
    cout << "Number of valid regions: " << n << "\n";
    cout << "Number of invalid regions: " << m << "\n";
    return 0;
}
