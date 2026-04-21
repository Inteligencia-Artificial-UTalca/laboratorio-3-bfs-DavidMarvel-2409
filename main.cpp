#include "Map.h"
#include "Search.h"
#include "ColorMap.h"
#include "Colores.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>



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
        std::cerr << ColorRed << "Error: No se pudo abrir el archivo.\n" << RESET;
        return false;
    }
    std::string linea;
    if (!std::getline(archivo, linea)) {
        std::cerr << ColorRed << "Error: Archivo vacío o sin datos.\n" << RESET;
        return false;
    }

    std::istringstream ss(linea);
    
    if (!(ss >> h >> w)) {
        std::cerr << ColorRed << "Error: La primera línea debe contener dos enteros (n y m).\n" << RESET;
        return false;
    }
    int n_filas = 0;
    while(std::getline(archivo,linea)) n_filas++;
    if (n_filas != h){
        std::cerr << ColorRed << "ERROR: filas " << n_filas << " != " << h << "\n" << RESET;
        return false;
    }

    return true;

}
bool coorLegal(const int& x1, const int& y1, const int& x2, const int& y2, const int& h, const int& w){
    if (x1 < 0 || x1 > w) {
        std::cerr << ColorRed << "Coordenada X1 invalida\n" << RESET;
        return false;
    }
    if (x2 < 0 || x2 > w) {
        std::cerr << ColorRed << "Coordenada X2 invalida\n" << RESET;
        return false;
    }
    if (y1 < 0 || y1 > h) {
        std::cerr << ColorRed << "Coordenada Y1 invalida\n" << RESET;
        return false;
    }
    if (y2 < 0 || y2 > h) {
        std::cerr << ColorRed << "Coordenada Y2 invalida\n" << RESET;
        return false;
    }
    return true;
}

int main(int argc, char *argv[]){

    //Verify that the amount of arguments is correct
    //6 arguments: program name, map file, x1, y1, x2, y2
    if (argc != 6){
        std::cerr << ColorRed << "Error de sintaxis\n" 
        << ColorYellow << "La sintaxis correcta es: ./busqueda [nombre del mapa].txt coorX1 coorY1 coorX2 coorY2" 
        << RESET << std::endl;
        return 0;
    }
    for (int i = 2; i < 6; i++){
        if (!esNumero(argv[i])){
            std::cerr << ColorRed << "ERROR: argumento " << argv[i] << " no es un numero entero.\n" << RESET;
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
    colorMap.print(path);
    int distance = path.size() - 1;
    std::cout << RESET << ColorGreen << "Cantidad de pasos BFS: " << RESET << distance << "\n\n";

    auto path2 = Search::greedyBFS(map,{atoi(argv[2]),atoi(argv[3])},{atoi(argv[4]),atoi(argv[5])});
    colorMap.print(path2);
    int distance2 = path2.size() - 1;
    std::cout << RESET << ColorGreen << "Cantidad de pasos greedyBFS: " << RESET << distance2 << "\n\n";

    auto path3 = Search::Astar(map,{atoi(argv[2]),atoi(argv[3])},{atoi(argv[4]),atoi(argv[5])});
    colorMap.print(path3);
    int distance3 = path3.size() -1;
    std::cout << RESET << ColorGreen << "Cantidad de pasos Astar: " << RESET << distance3 << "\n\n";

    auto path4 = Search::WeightedAstar(map,{atoi(argv[2]),atoi(argv[3])},{atoi(argv[4]),atoi(argv[5])}, 2);
    colorMap.print(path4);
    int distance4 = path4.size() -1;
    std::cout << RESET << ColorGreen << "Cantidad de pasos WeightedAstar: " << RESET << distance4 << "\n\n";
    
    // //Calculate path distance
    // int distance = path.size() - 1, distance2 = path2.size() - 1, distance3 = path3.size() -1;
    // //Print path distance
    // std::cout << RESET << ColorGreen << "Cantidad de pasos BFS: " << RESET << distance << "\n\n";
    // std::cout << RESET << ColorGreen << "Cantidad de pasos greedyBFS: " << RESET << distance2 << "\n\n";
    // std::cout << RESET << ColorGreen << "Cantidad de pasos Astar: " << RESET << distance3 << "\n\n";
    return 0;
}
