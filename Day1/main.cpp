// #include <iostream> // For std::cout
// #include <fstream>  // For std::ifstream
// #include <string>   // For std::string

// int normalize_pos(int pos)
// {
//     pos = pos % 100; // Get remainder
//     if (pos < 0)
//     {
//         pos += 100; // Make positive
//     }
//     return pos;
// }

// int count_zeros(int start, int end, char direction, int dist) {
//     if (dist == 0) return 0;
    
//     start = normalize_pos(start);
//     end = normalize_pos(end);
    
//     int count = dist / 100;
    
//     if (end == 0) {
//         count++;
//     } else {
//         // Check if we wrapped
//         if (direction == 'R' && start > end) {
//             count++;  // Went right and wrapped (e.g., 95 → 55)
//         } else if (direction == 'L' && start < end) {
//             count++;  // Went left and wrapped (e.g., 50 → 82)
//         }
//     }
    
//     return count;
// }

// int main()
// {
//     //   std::ifstream inputFile("input.txt"); // Open the file named "example.txt"
//     std::ifstream inputFile("test.txt"); // Open the file named "example.txt"

//     if (inputFile.is_open())
//     {                     // Check if the file opened successfully
//         std::string line; // Declare a string to store each line

//         // Loop while std::getline successfully reads a line from the file
//         int curr_pos = 50;
//         int count = 0;
//         while (std::getline(inputFile, line))
//         {
//             std::cout << line << "\n";
//             char operation = line[0];
//             int move = std::stoi(line.substr(1));
//             int start_pos = curr_pos;
//             if (operation == 'R')
//             {
//                 curr_pos += move;
//             }
//             else if (operation == 'L')
//             {
//                 curr_pos -= move;
//             }
//             curr_pos = normalize_pos(curr_pos);
//             int zeros = count_zeros(start_pos, curr_pos, operation, move);
//             count += zeros;
//             std::cout << "Start: " << start_pos << " End: " << curr_pos << " Count: " << count << " Zeros: " << zeros << "\n";
//             // if (curr_pos == 0)
//             // {
//             //     count++;
//             // }
//             // std::cout << curr_pos << "\n";
//         }
//         std::cout << count;
//         inputFile.close(); // Close the file stream
//     }
//     else
//     {
//         std::cerr << "Error: Unable to open file." << std::endl; // Error message if file not opened
//     }
//     return 0;
// }
#include <iostream>
#include <fstream>
#include <string>

int normalize_pos(int pos)
{
    pos = pos % 100;
    if (pos < 0)
    {
        pos += 100;
    }
    return pos;
}

int count_zeros(int start, int end, char direction, int dist) {
    if (dist == 0) return 0;
    
    start = normalize_pos(start);
    end = normalize_pos(end);
    
    int count = dist / 100;
    
    if (end == 0) {
        count++;  // Landed on 0
    } else if (start == 0) {
        // Started at 0, moved away - don't count
    } else {
        // Check if we wrapped
        if (direction == 'R' && start > end) {
            count++;  // Wrapped going right
        } else if (direction == 'L' && start < end) {
            count++;  // Wrapped going left
        }
    }
    
    return count;
}

int main()
{
    std::ifstream inputFile("input.txt");

    if (inputFile.is_open())
    {
        std::string line;
        int curr_pos = 50;
        int count = 0;
        
        while (std::getline(inputFile, line))
        {
            std::cout << line << "\n";
            char operation = line[0];
            int move = std::stoi(line.substr(1));
            int start_pos = curr_pos;
            
            if (operation == 'R')
            {
                curr_pos += move;
            }
            else if (operation == 'L')
            {
                curr_pos -= move;
            }
            
            int zeros = count_zeros(start_pos, curr_pos, operation, move);
            count += zeros;
            curr_pos = normalize_pos(curr_pos);
            
            std::cout << "Start: " << start_pos << " End: " << curr_pos 
                      << " Count: " << count << " Zeros: " << zeros << "\n";
        }
        
        std::cout << "Final count: " << count << "\n";
        inputFile.close();
    }
    else
    {
        std::cerr << "Error: Unable to open file." << std::endl;
    }
    return 0;
}