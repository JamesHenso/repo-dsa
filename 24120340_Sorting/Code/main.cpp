#include <algorithm>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>

#include "BinaryInsertionSort.h"
#include "BubbleSort.h"
#include "CountingSort.h"
#include "DataGenerator.h"
#include "FlashSort.h"
#include "HeapSort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "RadixSort.h"
#include "SelectionSort.h"
#include "ShakerSort.h"
#include "ShellSort.h"
#include "WriteToCSV.h"

using namespace std;
using namespace std::chrono;
typedef void (*sortAlgo)(int *, int);

sortAlgo s[] = {selectionSort, insertionSort, binaryInsertionSort,
                bubbleSort, shakerSort, shellSort,
                heapSort, mergeSort, quickSort,
                countingSort, radixSort, flashSort};

const string algoName[12] = {
    "Selection", "Insertion", "BinaryInsertion", "Bubble", "Shaker", "Shell",
    "Heap", "Merge", "Quick", "Counting", "Radix", "Flash"};

const string dataDistribution[4] = {"RandomData", "SortedData", "ReverseData",
                                    "NearlySortedData"};

const int dataSize[6] = {10, 100, 200, 500, 1000, 2000};

double process(int *a, int n, sortAlgo f, int nameIdx)
{
    auto start = system_clock::now();
    f(a, n);
    auto stop = system_clock::now();
    std::chrono::duration<double, std::milli> timeCost = stop - start;
    double ms = timeCost.count();
    cout << setw(25) << left << (algoName[nameIdx] + "Sort: ") << setw(25)
         << right << fixed << setprecision(3) << ms << " ms\t->";
    if (is_sorted(a, a + n))
        cout << "SUCCEED!\n";
    else
        cout << "NOOOOOO!\n";
    return ms;
}

bool validAlgo(const string &algo)
{
    for (int i = 0; i < 12; i++)
    {
        if (algoName[i] == algo)
            return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    int *source = NULL;
    int *a = NULL;

    for (int t = 0; t < 4; ++t)
    {
        cout << dataDistribution[t] << "\n";
        for (int sz = 0; sz < 6; ++sz)
        {
            int n = dataSize[sz];
            cout << "Data Size = " << n << "\n";

            // create vector row containing result of each datasize
            vector<double> row;
            double time = 0;

            // Generate integer array
            source = new int[n];
            generateData(source, n, t);

            // Sort array and show the time cost
            for (int algo = 0; algo < 12; ++algo)
            {
                restoreArray(source, a, n);
                time = process(a, n, s[algo], algo);
                // row.push_back(time);
            }

            // Write result to CSV file
            // table.push_back(make_pair("n = " + to_string(n), row));
            // write_csv(dataDistribution[t] + ".csv", table);

            // Release memory that dynamically allocated
            delete[] source;
            cout << "\n";
        }

        cout << "*************************************\n\n";
    }

    // Chose the way to sort array

    if (argc != 7)
    {
        cout << "./main.ext -a <Sort_way> -i <input_txt> -o <output_txt'";
        return 0;
    }

    string sort_way, input_file, output_file;

    for (int i = 1; i < argc; i += 2)
    {
        if (strcmp(argv[i], "-a") == 0)
        {
            sort_way = argv[i + 1];
            if (!validAlgo(sort_way))
            {
                cout << "Invalid sorting algorithm.";
                return 0;
            }
        }
        else if (strcmp(argv[i], "-i") == 0)
        {
            input_file = argv[i + 1];
        }
        else if (strcmp(argv[i], "-o") == 0)
        {
            output_file = argv[i + 1];
        }
        else
        {
            cout << "Invalid argument: " << argv[i];
            return 0;
        }
    }

    ifstream file(input_file);
    if (!file)
    {
        cout << "Invalid file.";
    }
    int num;
    file >> num;
    int arr[num];
    for (int i = 0; i < num; i++)
    {
        file >> arr[i];
    }
    file.close();

    auto it = find(begin(algoName), end(algoName), sort_way);
    if (it != end(algoName))
    {
        int idx = distance(begin(algoName), it);
        s[idx](arr, num);
    }
    else
    {
        cout << "Invalid sorting algorithm specified.";
        return 0;
    }

    ofstream output(output_file);
    if (!output)
    {
        cout << "Unable to open output file.";
        return 0;
    }
    for (int i = 0; i < num; i++)
    {
        output << arr[i] << " ";
    }
    output.close();
    return 0;
}
