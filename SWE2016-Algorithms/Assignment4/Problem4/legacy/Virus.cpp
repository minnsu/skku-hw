#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>

using namespace std;

class node{
	public:
		vector<int> child_list;
		vector<int> time_list;
		unsigned int min_time;
		bool infected;
		node(){
			this->min_time = 1001;
			this->infected = false;
		}
};

void infect(node *com, int &start, int now_time){
	com[start].infected = true;
	int size = com[start].child_list.size();
	for(int i = 0; i < size; i++){
		com[start].min_time = com[start].min_time > now_time ? now_time : com[start].min_time;
		infect(com, com[start].child_list[i], com[start].time_list[i] + com[start].min_time);
	}
	if(size == 0){
		com[start].min_time = com[start].min_time > now_time ? now_time : com[start].min_time;
	}
}

int main(int argc, char** argv){
	int n, m, start;
    FILE* fr = fopen(argv[1], "r"); // open input file
    
	int tmp; // avoid warning sign of compiler : ignore return value warning
    tmp = fscanf(fr, "%d %d %d", &n, &m, &start); // store input at inputstring	
	
	node *computer = new node[n];
	int to, from, time;
	int NumOfInfected = 0, max_time = 0;
    for(int i = 0; i < m; i++){
		fscanf(fr, "%d %d %d", &to, &from, &time);
		computer[from-1].child_list.push_back(to-1);
		computer[from-1].time_list.push_back(time);
	}
	fclose(fr); // file close
	start = start - 1;
	infect(computer, start, 0);
	
	for(int i = 0; i < n; i++){
		if(computer[i].infected){
			NumOfInfected++;
			max_time = max_time > computer[i].min_time ? max_time : computer[i].min_time;
		}
	}

	// file write
	FILE* fw = fopen(argv[2], "w"); // open output file
	fprintf(fw, "%d %d", NumOfInfected, max_time);	
    
	fclose(fw); // file close	
	return 0;
}
