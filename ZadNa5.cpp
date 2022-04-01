#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>



const int m_size = 10; //message size
static unsigned int count = 0; 

class Package
{
    private:
        unsigned int id;
        int content;
    public: 
        Package()
        {
            // std::cout<< "Ctor" <<std::endl;
            
            this->id = count;
            this->content = 0;
            count++;

        }
        ~Package()
        {
            // std::cout<< "Dtor" <<std::endl;
            count--;
        }
        int get_content(){return this->content;}
        unsigned int get_id(){return this->id;} 
        void set_content(int content){this->content=content;}
        void set_id(unsigned int id){this->id = id;} 

};
void create_message(Package (&array)[m_size])
{
    for(int i=0; i<m_size; i++)
        array[i].set_content(array[i].get_id()*array[i].get_id());

}

void shuffle(Package (&array)[m_size]) 
{
    int j;
    Package tmp;
    srand(time(NULL));

    for(int i=m_size-1; i>=0; i--)
    {
        j = rand()%(i+1);
        tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
}


int main()
{
    Package message[m_size];
    Package received_message[m_size];

    create_message(message);
    shuffle(message); //send packages in random order

    std::chrono::steady_clock::time_point begin_sorting = std::chrono::steady_clock::now(); //gets time when sorting started

    for(int i=0; i<m_size; i++) // put packages in right order
        received_message[message[i].get_id()]=message[i];
    
    std::chrono::steady_clock::time_point end_sorting = std::chrono::steady_clock::now(); //gets time when sorting started
    

    // Printing message (wrong order)
    std::cout<< "Message with packages in random order: " <<std::endl;
    
    for(int i=0 ;i<m_size; i++) 
        std::cout<< message[i].get_content() << " ";
    
    std::cout<<std::endl;

    // Printing message (right order)
    std::cout<< "Message with packages in right order: " <<std::endl;
    
    for(int i=0 ;i<m_size; i++)  
        std::cout<< received_message[i].get_content() << " ";
    
    std::cout<<std::endl;

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end_sorting - begin_sorting).count() << " microseconds"<< std::endl;

    
    return 0;
}