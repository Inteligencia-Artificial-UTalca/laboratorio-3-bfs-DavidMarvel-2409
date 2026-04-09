#include "Search.h"
#include <queue>
#include <chrono>
#include <unordered_map>
#include <iostream>
#include <limits>


namespace std
{
    //this is needed to store a pair<int,int> in an associative container
    //such as unorered_set and unordered_map
	template<> struct hash<std::pair<int,int>>
	{
		std::size_t operator()( const std::pair<int,int> & p) const noexcept
		{
            hash<int> hasher;
			return hasher(p.first) ^ (hasher(p.second)<<1);

		}
	};
}

std::vector<std::pair<int,int>> Search::reconstruct(const std::unordered_map<std::pair<int,int>,std::pair<int,int>> &pathCache, const std::pair<int,int> &start){
	std::deque<std::pair<int,int>> nodes;
	auto node = start;//make copy

    //traverse path from goal to start

    //
	//while(true){
        //implement
	//}
    while (pathCache.find(node) != pathCache.end()) {
        nodes.push_front(node);
        node = pathCache.at(node);
    }
    nodes.push_front(node);

    //revert path and return it
    std::vector<std::pair<int,int>> vec;
    for(auto p:nodes){
        vec.push_back(p);
    }
    return vec;
}

float Search::Heuristic(std::pair<int,int> start, std::pair<int,int> goal){
    int valFirst = std::abs(start.first - goal.first), valSecond = std::abs(start.second - goal.second);
    return valFirst + valSecond;
}

std::vector<std::pair<int,int>> Search::BFS(const Map& map, std::pair<int,int> start, std::pair<int,int> goal){
    std::cout<<"===========================\nRunning BFS...\n";
	auto startTime = std::chrono::high_resolution_clock::now();

    //stores possible directions
    std::pair<int,int> dirs[]{{-1,0},{0,1},{1,0},{0,-1}};

    bool visited[map.h][map.w]{false};      //we'll just use a matrix og booleans to indicated if visited
    std::queue<std::pair<int,int>> OPEN;
    std::unordered_map<std::pair<int,int>,std::pair<int,int>> pathCache;    ////hashmap to reconstruct path: child -> parent

    //add firts node to open list
    OPEN.push(start);
    visited[start.first][start.second] = true;

    while(!OPEN.empty()){
        //get node
        auto pos = OPEN.front();
        OPEN.pop();
        //check if node is goal
		if(pos==goal){
			auto endTime = std::chrono::high_resolution_clock::now();
			int count=0;
            for(int i=0;i<map.h;i++){
                for(int j=0;j<map.w;j++){
                    if(visited[i][j])count++;
                }
            }
            std::cout<<"VISITED: "<<count<<std::endl;
			std::cout<<"OPEN: "<<OPEN.size()<<std::endl;
			std::cout<<"FOUND in "<<(endTime-startTime).count()/1000000.0<<"ms\n";
			return reconstruct(pathCache,pos);
		}

		for(auto dir:dirs){
			//copy the position
            //then move it
            std::pair<int, int> neighbor = {pos.first + dir.first, pos.second + dir.second};

            //if illegal or visited, skip it
            //add child to open list
            //register path
            if (neighbor.first >= 0 && neighbor.first < map.h &&
                neighbor.second >= 0 && neighbor.second < map.w &&
                !visited[neighbor.first][neighbor.second] &&
                map.isWalkable(neighbor.first, neighbor.second) == true) { // Verificar si es transitable
                
                visited[neighbor.first][neighbor.second] = true;
                OPEN.push(neighbor);
                pathCache[neighbor] = pos;
            }
		}
	}
	std::cout<<"NOT FOUND!!!!\n";
    
    //let's just return start and goal to draw them
    std::vector<std::pair<int,int>> path;
    path.push_back(start);
    path.push_back(goal);
    return path;
}
std::vector<std::pair<int,int>> Search::greedyBFS(const Map & map, std::pair<int,int> start, std::pair<int,int> goal) {
    std::cout<<"===========================\nRunning greedyBFS...\n";
	auto startTime = std::chrono::high_resolution_clock::now();

    //stores possible directions
    std::pair<int,int> dirs[]{{-1,0},{0,1},{1,0},{0,-1}};

    bool visited[map.h][map.w]{false};      //we'll just use a matrix og booleans to indicated if visited

    auto comparaHeuristica = [&](std::pair<int,int> a, std::pair<int,int> b){
        return Heuristic(a, goal) > Heuristic(b, goal);
    };
    //std::queue<std::pair<int,int>> OPEN;
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, decltype(comparaHeuristica)> OPEN(comparaHeuristica);
    std::unordered_map<std::pair<int,int>,std::pair<int,int>> pathCache;    ////hashmap to reconstruct path: child -> parent

    //add firts node to open list
    OPEN.push(start);
    visited[start.first][start.second] = true;

    while(!OPEN.empty()){
        //get node
        auto pos = OPEN.top();
        OPEN.pop();
        //check if node is goal
		if(pos==goal){
			auto endTime = std::chrono::high_resolution_clock::now();
			int count=0;
            for(int i=0;i<map.h;i++){
                for(int j=0;j<map.w;j++){
                    if(visited[i][j])count++;
                }
            }
            std::cout<<"VISITED: "<<count<<std::endl;
			std::cout<<"OPEN: "<<OPEN.size()<<std::endl;
			std::cout<<"FOUND in "<<(endTime-startTime).count()/1000000.0<<"ms\n";
			return reconstruct(pathCache,pos);
		}

		for(auto dir:dirs){
			//copy the position
            //then move it
            std::pair<int, int> neighbor = {pos.first + dir.first, pos.second + dir.second};

            //if illegal or visited, skip it
            //add child to open list
            //register path
            if (neighbor.first >= 0 && neighbor.first < map.h &&
                neighbor.second >= 0 && neighbor.second < map.w &&
                !visited[neighbor.first][neighbor.second] &&
                map.isWalkable(neighbor.first, neighbor.second) == true) { // Verificar si es transitable
                
                visited[neighbor.first][neighbor.second] = true;
                OPEN.push(neighbor);
                pathCache[neighbor] = pos;
            }
		}
	}
	std::cout<<"NOT FOUND!!!!\n";
    
    //let's just return start and goal to draw them
    std::vector<std::pair<int,int>> path;
    path.push_back(start);
    path.push_back(goal);
    return path;
}
