#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include <algorithm>
#include <set>

#include <iostream>
#include <string>

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
    scanf("%d %d", &n,&m); // store input at inputstring
	n = n + 1;
	int *set = new int[n];
	std::vector<std::string> answer;	

	int *parent = new int[n];
	int *height = new int[n];
	for(int i = 0; i < n; i++){
		parent[i] = i;
		height[i] = 0;
	}
	int op, num1, num2;
	for(int i = 0; i < m; i++){
		scanf("%d %d %d", &op, &num1, &num2);
		if(op == 0){
			UNION(parent, height, num1, num2);
		}
		else{
			if(find(parent, num1) == find(parent, num2)){
				answer.push_back("YES");
			}
			else{
				answer.push_back("NO");
			}
		}
	}

    for(int i = 0; i < answer.size(); i++){
		printf("%s\n", answer[i].c_str());
	}	
	delete[] set;
	return 0;
}

