#include "Map.h"
#include <iostream>
#include <fstream>

#define red "\033[31m"
#define green "\033[32m"
#define yellow "\033[33m"
#define blue "\033[34m"
#define pink "\033[35m"
#define RESET "\033[0m"

Map::Map():h(0),w(0){

}

Map::Map(std::string filename){
    
    //Load the file
    std::ifstream file(filename);
    if (!file) {
        std::cerr << red << "ERROR: nose pudo abrir el archivo " << filename << std::endl;
        return;
    }
    //Resize map
    file >> h >> w;
    _map.resize(h,std::vector<int>(w));
    //Save file information in map
    for(int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){
            file >> _map[i][j];
        }
    }
    //Close file
    file.close();
}   

Map::Map(const Map& rhs):h(rhs.h),w(rhs.w),_map(rhs._map){

}

Map::~Map(){
    
}

Map& Map::operator=(const Map& rhs){
    if(this==&rhs)return *this;
    h=rhs.h;
    w=rhs.w;
    _map=rhs._map;
    return *this;
}
   
void Map::print() const{
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            std::cout<<_map[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}
void Map::print(std::vector<std::pair<int,int>> path) const{
    auto __map=_map;

    __map[path[0].first][path[0].second]=2;
    for(int i=1;i<(int)path.size()-1;i++){
         __map[path[i].first][path[i].second]=4;
    }
     __map[path[path.size()-1].first][path[path.size()-1].second]=3;

    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){

            std::cout<<__map[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

bool operator==(const Map& lhs, const Map& rhs){
    return lhs.h==rhs.h && lhs.w==rhs.w && lhs._map==rhs._map;
}

bool Map::isWalkable(int x, int y) const {
    
    if (x < 0 || x >= h || y < 0 || y >= w) {
        return false;
    }
    if (_map[x][y] == 1){
        return false;
    }
    return true;
}