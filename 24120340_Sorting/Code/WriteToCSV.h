#pragma once
#include <string>
#include <fstream>
#include <vector>
using namespace std;

void write_csv(string filename, const vector<pair<string, vector<double>>> dataset)
{
    std::ofstream myFile(filename);

    for (size_t j = 0; j < dataset.size(); ++j)
    {
        myFile << dataset.at(j).first;
        if (j != dataset.size() - 1)
            myFile << ",";
    }
    myFile << "\n";

    for (size_t i = 0; i < dataset.at(0).second.size(); ++i)
    {
        for (size_t j = 0; j < dataset.size(); ++j)
        {
            myFile << dataset.at(j).second.at(i);
            if (j != dataset.size() - 1)
                myFile << ",";
        }
        myFile << "\n";
    }

    myFile.close();
}
