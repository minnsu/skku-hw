#include <cstdio>
#include <cstdlib>
#include <vector>

void init_node(int *set, int &size){
	for(int i = 0; i < size; i++){
		set[i] = i;
	}
}
void function(int &op, int *set, int &num1, int &num2, std::vector<char> &answer){
	switch (op) {
		case 0:
			num1 = set[num1];
			num2 = set[num2];
			set[num2] = num1;
			break;
		case 1:
			num1 = set[num1];
			num2 = set[num2];
			if(num1 == num2){
				answer.push_back('Y');
			}
			else{
				answer.push_back('N');
			}
			break;
	}
}

int main(int argc, char** argv){
	int n, m;
    FILE* fr = fopen(argv[1], "r"); // open input file
    
	int tmp; // avoid warning sign of compiler : ignore return value warning
    	tmp = fscanf(fr, "%d %d", &n,&m); // store input at inputstring
	n = n + 1;
	int *set = new int[n];
	init_node(set, n);
	std::vector<char> answer;	

	int op, num1, num2;
	for(int i = 0; i < m; i++){
		fscanf(fr, "%d %d %d", &op, &num1, &num2);
		function(op, set, num1, num2, answer);
		for(int j = 0; j < n; j++){
			set[j] = set[set[j]];
		}
	}
    fclose(fr); // file close


	// file write
	FILE* fw = fopen(argv[2], "w"); // open output file
    for(int i = 0; i < answer.size(); i++){
		fprintf(fw, "%c\n", answer[i]);
	}
    fclose(fw); // file close		
	delete[] set;
	return 0;
}
