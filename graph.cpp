#include <iostream>

struct graph{
    int graph_table[3][3];

    graph(){
        for (int i = 0; i < 3; i++){
            for (int j = 0;j<3; j++)
                graph_table[i][j] = 0;
        }
    }
    
    void create_connection(int first, int second){
        graph_table[first][second] = 1;
        graph_table[second][first] = 1;
    }
    void delete_connection(int first, int second){
        graph_table[first][second] = 0;
        graph_table[second][first] = 0;
    }
    void print_matrix(){
        for (int i = 0;i<3; i++){
            for (int j = 0;j<3; j++)
                std::cout<< graph_table[i][j]<< " ";
            std::cout<<std::endl;
        }
    }
};
int main(){
    graph gr;
    gr.create_connection(0,1);
    gr.print_matrix();
    std::cout<< std::endl;
    gr.delete_connection(0,1);
    gr.print_matrix();
} 
