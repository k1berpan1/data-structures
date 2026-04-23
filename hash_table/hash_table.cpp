#include </home/useradmin/vs/c++/datastruct/ll_header.h>


struct hash_table{
    Linkedlist hash_table_array[12];
    int size_of_array = (sizeof(hash_table_array) / sizeof(hash_table_array[0]));

    int hash_function(std::string  key){
        int place_in_array = 0;
        for(int i = 0; i<key.size(); i++)
            place_in_array += int(key[i]);
        std::cout<< place_in_array<< std::endl; 
        place_in_array = place_in_array % size_of_array;
        return place_in_array;
    }

    void add_to_ht(std::string  key, int value){
        int place_in_array = hash_function(key);
        std::cout << place_in_array << std::endl;

        hash_table_array[place_in_array].pushback("adc", 3);
        hash_table_array[place_in_array].info_of_ll();  
    }
    void info_of_ht(){
        for(int i = 0; i<size_of_array; i++){
            std::cout<<"linked list "<< i << " info "<<std::endl;
            hash_table_array[i].info_of_ll();
            std::cout<<std::endl;
        }
    }

    void search_in_ht(std::string key){
        hash_table_array[hash_function(key)].find(key);
    }

    void delete_in_ht(std::string key){
        hash_table_array[hash_function(key)].delete_after(hash_table_array[hash_function(key)].head, "adc");
    }
};


int main() { 
	hash_table ht;
    ht.add_to_ht("adc", 3);
    ht.info_of_ht();
    ht.search_in_ht("adc");
    ht.delete_in_ht("adc");
    ht.info_of_ht();
}