#include <stdio.h>
#include <queue> // using queue for BFS
#include <vector> // using vector for visit map status
#include <utility> // using pair

void readfile(char* inputfilename, int& mapsize, std::pair<int, int>& startloc, std::pair<int, int>& goalloc);
void writefile(char* outputfilename, int& answer);

std::vector<std::pair<int, int>> make_next_node(int mapsize, std::pair<int, int> nownode, std::vector<std::vector<int>>& map)
{
    // static const int goaly = nownode.first, goalx = nownode.second; // for don't visit start location repeatly
    // if using this line,then add to 'if statement's condition' && (y != goaly || x != goalx)
    std::vector<std::pair<int, int>> v; // return vector<pair>
    int dir[8][2] = { // visit knight's direction, using for loop
        {-2,-1}, {-2, 1}, {-1, 2}, {1, 2},
        {2, -1}, {2, 1}, {-1, -2}, {1, -2}
    };
    std::pair<int, int> pushpair; // new node to push in vector
    int x, y; // convenience
    for(int i = 0; i < 8; i++) // direction
    {
        y = nownode.first + dir[i][1]; // col
        x = nownode.second + dir[i][0]; // row
        if((y >= 0 && y < mapsize) && (x >= 0 && x < mapsize) && map[y][x] == 0)
        { // y, x in map && first visit
            map[y][x] = map[nownode.first][nownode.second] + 1; // store distance in map vector
            pushpair.first = nownode.first + dir[i][1]; pushpair.second = nownode.second + dir[i][0];
            v.push_back(pushpair); // push pair
        }
    }
    return v; // return vector<pair>
}

int BFS(int mapsize, std::pair<int, int> startloc, std::pair<int, int> goalloc, std::vector<std::vector<int>>& map)
{
    std::queue<std::pair<int, int>> q;
    q.push(startloc); // push start loc
    while(!q.empty())
    {
        std::pair<int, int> x = q.front();    q.pop(); // store first loc in x and pop the queue
        if(x.first == goalloc.first && x.second == goalloc.second) // answer or not
        {
            return map[goalloc.first][goalloc.second]; // return answer == distance from start location == visit map distance
        }
        std::vector<std::pair<int, int>> pushpairvec = make_next_node(mapsize, x, map); // make next loc vector using vector<pair>
        for(auto it = pushpairvec.begin(); it != pushpairvec.end(); it++) // using iterator to push
        {
            q.push(*it); // push pair in queue
        }
    }
    return -1; // if q is empty, then return -1
}

int main(int argc, char **argv)
{
    int mapsize; // 4 <= mapsize <= 20
    std::pair<int, int> startloc, goalloc; // pair of location
    readfile(argv[1], mapsize, startloc, goalloc); // read input file and get values
    std::vector<std::vector<int>> map(mapsize, std::vector<int>(mapsize, 0)); 
    // visit map and distance, if distance is not zero, then that location is already visit

    int answer = BFS(mapsize, startloc, goalloc, map); // call BFS, store answer

    writefile(argv[2], answer); // make outputfile and write to that file
    return 0;
}


void readfile(char* inputfilename, int& mapsize, std::pair<int, int>& startloc, std::pair<int, int>& goalloc)
{
    FILE* fr = fopen(inputfilename, "r"); // open file as read mode
    int tmp; // avoid warning sign of compiler : ignore return value warning
    tmp = fscanf(fr, "%d", &mapsize); // scan map size
    tmp = fscanf(fr, "%d %d", &startloc.first, &startloc.second); // scan start location
    tmp = fscanf(fr, "%d %d", &goalloc.first, &goalloc.second); // scan goal location
    fclose(fr); // file close
}

void writefile(char* outputfilename, int& answer)
{
    FILE* fw = fopen(outputfilename, "w"); // open file as write mode
    fprintf(fw, "%d", answer); // write answer
    fclose(fw); // file close
}
