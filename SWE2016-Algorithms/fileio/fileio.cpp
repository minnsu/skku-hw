#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char **argv) // argc = 실행파일 + 뒤에 따라오는 개수 ex) ./file input output => 3
{ // ex) argv[0] = ./filename argv[1] = input argv[2] = output
    ifstream input;
    input.open(argv[1]);
    // 읽고
    string inp[100];
    getline(input, inp[0]);
    int size = stoi(inp[0]);
    for(int i = 1; i <= size; i++){
        getline(input, inp[i]);
    }
    input.close();

    // 풀고
    printf("first line (size) : %d\n", size);
    for(int i = 0; i < size; i++){
        printf("line [%d] : %s\n", i+1, inp[i+1].c_str());
    }

    ofstream output;
    output.open(argv[2]);
    // 쓰고
    for(int i = 0; i < size+1; i++){
        output.write((inp[i] + "\n").c_str(), inp[i].size() + 1);
    }
    output.close();
    return 0;
}