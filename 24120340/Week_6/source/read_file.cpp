#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(){
    fstream file_ip("MST.txt");
    ofstream file_op("output.txt");
    string line;
    int count_line = 0;
    while (getline(file_ip, line)) {
        stringstream ss(line);
        string segment;
        while (getline(ss, segment, '|')) {
            file_op << segment << endl;
            count_line++;
            break;
        }
        if (count_line == 500) break;
    }

    return 0;
}