#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int BLOCK_MODULO_M = 2000;
const int BLOCK_MODULO_N = 1429;
const int POWER_P = 31;

//______________________________________
/*
Double hashing with two modulo intergers m and n. 
That both block of its: 
+ BLOCK_MODULO_M = 2000
+ BLOCK_MODULO_N = 1429 

Two hash functions

hash_1(key) = (stoi(progress_string)) modulo BLOCK_MODULO_M
hash_2(key) = (stoi(progress_string)) modulo BLOCK_MODULO_N + 1

*/
//______________________________________

struct Company{
    string name;
    string profit_tax;
    string address;
};

struct HashTable{
    vector<Company> __hash_key;

    HashTable() : __hash_key(BLOCK_MODULO_M) {}
};

vector<Company> readCompanyList(string file_name) {
    ifstream file(file_name);
    vector<Company> result;

    if (!file.is_open()) {
        cerr << "Can't open file." << endl;
        return result;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        istringstream line_progress(line);
        string name, profit_tax, address;
        if (getline(line_progress, name, '|') &&
            getline(line_progress, profit_tax, '|') &&
            getline(line_progress, address, '|')) {
            result.push_back({name, profit_tax, address});
        }
    }

    file.close();
    return result;
}

long long collision(long long hash1, int attempt) {
    long long hash2 = (hash1 % BLOCK_MODULO_N) + 1;
    return (hash1 + attempt * hash2) % BLOCK_MODULO_M;
}

long long hashString(string company_name) {
    string str_reverse = company_name;
    reverse(str_reverse.begin(), str_reverse.end());

    long long sum_hash = 0;
    long long power = 1; 
    int len = min(20, (int)str_reverse.length());

    for (int i = 0; i < len; i++) {
        int val_ASCII = (int)str_reverse[i];
        sum_hash = (sum_hash + val_ASCII * power) % BLOCK_MODULO_M;
        power = (power * POWER_P) % BLOCK_MODULO_M;
    }

    return sum_hash;
}

HashTable* createHashTable(vector<Company> list_company) {
    HashTable* hash_table = new HashTable();

    for (const auto& company : list_company) {
        long long hash_value = hashString(company.name);
        const long long original_hash = hash_value;
        int attempt = 1;

        while (!hash_table->__hash_key[hash_value].name.empty()) {
            hash_value = collision(original_hash, attempt++);
        }

        hash_table->__hash_key[hash_value] = company;
    }

    return hash_table;
}

void insert(HashTable* hash_table, Company company) {
    long long hash_value = hashString(company.name);
    const long long original_hash = hash_value;
    int attempt = 1;

    while (!hash_table->__hash_key[hash_value].name.empty()) {
        hash_value = collision(original_hash, attempt++);
        if (attempt > BLOCK_MODULO_M) {
            cerr << "Error: Hash table is full!" << endl;
            return;
        }
    }

    hash_table->__hash_key[hash_value] = company;
}

Company* search(HashTable* hash_table, string company_name) {
    long long hash_value = hashString(company_name);
    const long long original_hash = hash_value;
    int attempt = 1;

    while (!hash_table->__hash_key[hash_value].name.empty() &&
           hash_table->__hash_key[hash_value].name != company_name) {
        hash_value = collision(original_hash, attempt++);
    }

    if (hash_table->__hash_key[hash_value].name.empty()) {
        return nullptr;
    } else {
        return &hash_table->__hash_key[hash_value];
    }
}



int main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <MST_file> <input_file> <output_file>" << endl;
        return 1;
    }
    string MST_file = argv[1], file_ip = argv[2], file_op = argv[3];
    vector<Company> company_list = readCompanyList(MST_file);

    HashTable* hash_table = createHashTable(company_list);

    vector<string> hashing_str;
    ifstream file_hashName(file_ip);
    ofstream file_result(file_op);

    if (!file_hashName.is_open()) {
        cerr << "Error: Cannot open input file " << file_ip << endl;
        delete hash_table;
        return 1;
    }
    if (!file_result.is_open()) {
        cerr << "Error: Cannot open output file " << file_op << endl;
        file_hashName.close();
        delete hash_table;
        return 1;
    }

    string line;
    while (getline(file_hashName, line)) {
        hashing_str.push_back(line);
    }

    for (const string& str : hashing_str) {
        Company* company = search(hash_table, str);
        if (company != nullptr) {
            file_result << company->name << "|" << company->profit_tax << "|" << company->address << endl;
        } else {
            file_result << "Not found: " << str << endl;
        }
    }

    file_hashName.close();
    file_result.close();

    delete hash_table;

    return 0;
}


