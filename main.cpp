#include "Map.h"
#include "Search.h"
#include "ColorMap.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#define red "\033[31m"
#define green "\033[32m"
#define yellow "\033[33m"
#define blue "\033[34m"
#define pink "\033[35m"
#define RESET "\033[0m"


bool esNumero(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}
bool archivoCorrecto(const std::string& nameArchibo, int& h, int& w){
    std::ifstream archivo(nameArchibo);
    if (!archivo) {
        std::cerr << red << "Error: No se pudo abrir el archivo.\n" << RESET;
        return false;
    }
    std::string linea;
    if (!std::getline(archivo, linea)) {
        std::cerr << red << "Error: Archivo vacío o sin datos.\n" << RESET;
        return false;
    }

    std::istringstream ss(linea);
    
    if (!(ss >> h >> w)) {
        std::cerr << red << "Error: La primera línea debe contener dos enteros (n y m).\n" << RESET;
        return false;
    }
    int n_filas = 0;
    while(std::getline(archivo,linea)) n_filas++;
    if (n_filas != h){
        std::cerr << red << "ERROR: filas " << n_filas << " != " << h << "\n" << RESET;
        return false;
    }

    return true;

}
bool coorLegal(const int& x1, const int& y1, const int& x2, const int& y2, const int& h, const int& w){
    if (x1 < 0 || x1 > w) {
        std::cerr << red << "Coordenada X1 invalida\n" << RESET;
        return false;
    }
    if (x2 < 0 || x2 > w) {
        std::cerr << red << "Coordenada X2 invalida\n" << RESET;
        return false;
    }
    if (y1 < 0 || y1 > h) {
        std::cerr << red << "Coordenada Y1 invalida\n" << RESET;
        return false;
    }
    if (y2 < 0 || y2 > h) {
        std::cerr << red << "Coordenada Y2 invalida\n" << RESET;
        return false;
    }
    return true;
}

int main(int argc, char *argv[]){

    //Verify that the amount of arguments is correct
    //6 arguments: program name, map file, x1, y1, x2, y2
    if (argc != 6){
        std::cerr << red << "Error de sintaxis\n" 
        << yellow << "La sintaxis correcta es: ./busqueda [nombre del mapa].txt coorX1 coorY1 coorX2 coorY2" 
        << RESET << std::endl;
        return 0;
    }
    for (int i = 2; i < 6; i++){
        if (!esNumero(argv[i])){
            std::cerr << red << "ERROR: argumento " << argv[i] << " no es un numero entero.\n" << RESET;
            return 1;
        }
    }
    
    int x1 = std::stoi(argv[2]), y1 = std::stoi(argv[3]), x2 = std::stoi(argv[4]), y2 = std::stoi(argv[5]);

    int h, w;
    if (!archivoCorrecto(argv[1], h, w)) return 1;
    if (!coorLegal(x1,y1,x2,y2,h,w)) return 1;


    //Load map with class Map
    Map map(argv[1]);
    ColorMap colorMap(map);
    colorMap.print();

    auto path = Search::BFS(map,{atoi(argv[2]),atoi(argv[3])},{atoi(argv[4]),atoi(argv[5])}); 
    //std::cout << RESET << "\nhola\n" << RESET;
    colorMap.print(path);
    
    //Calculate path distance
    //Print path distance
    
    return 0;
}
