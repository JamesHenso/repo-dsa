#include <iostream>
#include <string>

using namespace std;

bool check_str(string num){
    int len = num.length();
    int val = len / 2;

    for(int i = 0; i < val; i++){
        if(num[i] != num[len - 1 - i]){
            return false;
        }
    }

    return true;
}

char *string_bolo(string num){
    if(check_str(num)){
        return NULL;
    } else {
        int len = num.length();
        char *str = new char[len + 1];
        int index = 0;

        if(num[len - 3] != num[len - 1]){
            if(len % 2 != 0){
                for(int i = len - 2; i >= 0; i--){
                    str[index++] = num[i];
                }
            } else {
                    for(int i = len - 2; i >= 0; i--){
                    str[index++] = num[i - 1];
                }
            }
        } else {
            for(int i = len - 4; i >= 0; i--){
                str[index++] = num[i];
            }
        }

        str[index] = '\0';
        return str;
    }

    return NULL;
}

int main(){
    string s;
    char *result;

    getline(cin, s);

    result = string_bolo(s);

    if(result != NULL) {
        cout << result;
        delete[] result;
    } else {
        cout << "";
    }

    return 0;
}