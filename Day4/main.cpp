#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool canAccess(int x, int y, const vector<vector<string>> &papers)
{
    int count = 0;
    for (int x_check = x - 1; x_check <= x + 1; x_check++)
    {
        for (int y_check = y - 1; y_check <= y + 1; y_check++)
        {
            if (x_check == x && y_check == y)
            {
                continue;
            }
            if (x_check < 0 || x_check >= papers[0].size())
            {
                continue;
            }
            if (y_check < 0 || y_check >= papers.size())
            {
                continue;
            }
            if (papers[y_check][x_check] == "@")
            {
                count++;
            }
        }
    }
    return count < 4;
}

int part1(vector<vector<string>> &papers){
    int count = 0;
    for (int y = 0; y < papers.size(); y++)
    {
        for (int x = 0; x < papers[0].size(); x++)
        {
            if (papers[y][x] == "@")
            {
                if (canAccess(x, y, papers))
                {
                    count++;
                }
            }
        }
    }
    return count;
}

int remove_tp(vector<vector<string>> &papers, vector<pair<int,int>>& to_remove){
    for(pair<int,int> &p: to_remove){
        int x = p.first;
        int y = p.second;
        papers[y][x] = "X";
    }
    return to_remove.size();
}

int p2Runner(vector<vector<string>> &papers){
    vector<pair<int,int>> to_remove;
    int count = 0;
    for (int y = 0; y < papers.size(); y++)
    {
        for (int x = 0; x < papers[0].size(); x++)
        {
            if (papers[y][x] == "@")
            {
                if (canAccess(x, y, papers))
                {
                    count++;
                    to_remove.push_back({x,y});
                }
            }
        }
    }
    return remove_tp(papers,to_remove);
}

int part2(vector<vector<string>> &papers ){
    int count = 0;
    int removed = p2Runner(papers);
    count += removed;
    while(removed > 0){
        // cout << removed << "\n";
        removed = p2Runner(papers);
        count += removed;
    }
    return count;
}

int main()
{
    // ifstream file("example.txt");
    ifstream file("input.txt");
    string line = "";
    vector<vector<string>> papers;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            vector<string> l;
            for (char c : line)
            {
                l.push_back(string(1, c));
            }
            papers.push_back(l);
        }
    }
    else
    {
        cerr << "Cant open file";
        exit(1);
    }
    int count1 = 0;
    int count2 = 0;
    // count1 = part1(papers);
    count2 = part2(papers);
    cout << "Count1: " << count1 << " Count2: " << count2;
}