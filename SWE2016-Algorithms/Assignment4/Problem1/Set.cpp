#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int find(int *parent, int V){
	while(parent[V] != V){
		V = parent[V];
	}
	return V;
}
void UNION(int *parent, int *height, int V1, int V2){
	V1 = find(parent, V1);
	V2 = find(parent, V2);
	if(V1 == V2){
		return;
	}
	if(height[V1] == height[V2]){
		parent[V2] = V1;
		height[V1]++;
	}
	else if(height[V2] < height[V1]){
		parent[V2] = V1;
	}
	else{
		parent[V1] = V2;
	}
}

int main(int argc, char** argv){
	int n, m;
    FILE* fr = fopen(argv[1], "r"); // open input file
    
	int tmp; // avoid warning sign of compiler : ignore return value warning
    tmp = fscanf(fr, "%d %d", &n,&m); // store input at inputstring
	n = n + 1;
	int *set = new int[n];
	std::vector<char> answer;	

	int *parent = new int[n];
	int *height = new int[n];
	for(int i = 0; i < n; i++){
		parent[i] = i;
		height[i] = 0;
	}
	int op, num1, num2;
	for(int i = 0; i < m; i++){
		fscanf(fr, "%d %d %d", &op, &num1, &num2);
		if(op == 0){
			UNION(parent, height, num1, num2);
		}
		else{
			if(find(parent, num1) == find(parent, num2)){
				answer.push_back('Y');
			}
			else{
				answer.push_back('N');
			}
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
