#include <optional>
#include <iostream>
#include <vector>



struct graph{
    int size;
    // std::vector<std::vector<std::optional<int>>> matrix;
    std::optional<int>** matrix;
    graph(int inputed_size){
        size = inputed_size;
        matrix = new std::optional<int>*[inputed_size];
        for(int i = 0; i<inputed_size;i++){
            matrix[i] = new std::optional<int>[inputed_size];
        }
            for(int i = 0; i < size; i++){
            for(int j = 0; j< size; j++){
                matrix[i][j] = std::nullopt;
            }
        }
    }
    
    void create_connection(int first, int second, int weight){
        matrix[first][second] = weight;
        //matrix[second][first] = weight; // если вершины указывают друг на друга
    }
    int get_val(int i, int j){
        return matrix[i][j].value();
    }
    void delete_connection(int first, int second){
        matrix[first][second] = std::nullopt;
        //matrix[second][first] = std::nullopt;  //если вершины указывают друг на друга
    }
    void print_matrix(){
        for (int i = 0;i<size; i++){
            //std::cout << "Сейчас: "<< i<<std::endl;
            for (int j = 0;j<size; j++){
                if(matrix[i][j].has_value())
                    std::cout << matrix[i][j].value()<< " ";
                else
                    std::cout << "0"<< " "; 
            }
            std::cout<<std::endl;
        }
    }
    ~graph(){
        for(int i =0; i<size;i++){
            delete [] matrix[i];
        }
        delete []matrix;
    }
};
