#include <iostream>
#include </home/useradmin/vs/c++/datastruct/lib_directgraph.h>
#include <optional>
#include <vector>
#include <algorithm>



struct result{
    
    int size;
    std::optional<int>** table_of_result;
    
    result(int inputed_size){
        size = inputed_size;
        table_of_result = new std::optional<int>*[inputed_size];

        for(int i = 0; i<inputed_size;i++){
            table_of_result[i] = new std::optional<int>[3];
        }
        for(int i = 0; i < size; i++){
            for(int j = 0; j< 3; j++){
                if(j==0)
                    table_of_result[i][0] = i;
                
                else
                    table_of_result[i][j] = std::nullopt;
            }
        }
        table_of_result[0][1] = 0;
    }

    
    void add_value(int to, int cost, int parent){
        
        if(table_of_result[to][1].has_value() && table_of_result[to][1]< table_of_result[parent][1].value() +cost)
            return;
        else{
            table_of_result[to][1] = table_of_result[parent][1].value()+cost;
            table_of_result[to][2] = parent;
        }
    }
    void print_result(){
        int temp_cost, temp_parents;
        for(int i = 0; i < size; i++){
            if(table_of_result[i][2].has_value())
                std::cout << i<< " "<<table_of_result[i][1].value()<< " "<< table_of_result[i][2].value()<<std::endl;
            else
                std::cout << i<< " "<<table_of_result[i][1].value()<< " "<< 0<<std::endl;
        }
    }

    bool is_visited(std::vector<int> &visited, int num){
        if(std::count(visited.begin(),visited.end(),num)>0)
            return true;
        return false;
    }
    int return_short(std::vector<int> &visited){
        if(visited.empty())
            return 0;

        std::vector<int> find_short;
        for(int i = 0; i < size; i++){
            if(table_of_result[i][1].has_value() && !is_visited(visited,table_of_result[i][0].value())){
                if(find_short.empty()){
                    find_short.push_back(table_of_result[i][0].value());
                    find_short.push_back(table_of_result[i][1].value());
                }
                else{
                    if(table_of_result[i][1].value()< find_short[1]){
                        find_short[0] = table_of_result[i][0].value();
                        find_short[1] = table_of_result[i][1].value();
                    }
                }
            }
        }

        return find_short[0];
    }
};


void deijkstra(graph &gr){
    std::vector<int> visited;
    int i;
    result table_of_result(gr.size);
    while (visited.size()<gr.size)
    {
        i = table_of_result.return_short(visited);

        for (int j =0;j<gr.size; j++){
            
            if(gr.matrix[i][j].has_value() && !table_of_result.is_visited(visited,j))
                table_of_result.add_value(j,gr.matrix[i][j].value(),i);
            

            else continue; 
        }   
        visited.push_back(i);
        
    }
    table_of_result.print_result();
    
}


int main(){
    graph gr(6);
    gr.create_connection(0,1,5);
    gr.create_connection(0,2,10);
    gr.create_connection(0,4,2);
    gr.create_connection(1,2,2);
    gr.create_connection(1,3,4);
    gr.create_connection(2,3,7);
    gr.create_connection(2,5,10);
    gr.create_connection(3,4,3);
    gr.print_matrix();
    deijkstra(gr);
}