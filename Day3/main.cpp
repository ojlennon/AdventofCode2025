#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int find_max_num(const string &num)
{
  if (!num.length() || num.length() < 2)
  {
    return 0;
  }
  int first_num = num[0] - '0';
  int first_num_index = 0;
  // find first number
  for (int i = 1; i < num.length() - 1; i++)
  {
    int digit = num[i] - '0';
    if (digit > first_num)
    {
      first_num = digit;
      first_num_index = i;
    }
  }
  // find second number
  int second_num = num[first_num_index + 1] - '0';
  for (int j = first_num_index + 1; j < num.length(); j++)
  {
    int digit = num[j] - '0';
    if (digit > second_num)
    {
      second_num = digit;
    }
  }
  return first_num * 10 + second_num;
}

long long find_max(const string &num)
{
  int n = num.length();
  string result = "";
  int start = 0;
  for (int i = 0; i < 12; i++)
  {
    int limit = n - (12 - i);
    char max_digit = '0';
    int max_pos = start;

    for (int j = start; j <= limit; j++)
    {
      if (num[j] > max_digit)
      {
        max_digit = num[j];
        max_pos = j;
      }
    }

    result += max_digit;
    start = max_pos + 1;
  }

  return stoll(result);  // Use stoll instead of stof
}

int main(int argc, char *argv[])
{
  ifstream inputFile("input.txt");
  if (inputFile.is_open())
  {
    string line;
    long long total = 0;  // Use long long instead of float
    while (getline(inputFile, line))
    {
      total += find_max(line);
    }
    cout << total << endl;
  }
  else
  {
    cerr << "Unable to open file";
    return 1;
  }
  inputFile.close();
  return 0;
}