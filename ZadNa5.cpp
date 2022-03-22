#include <iostream>
#include <cstdlib>
#include <ctime>



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
        array[i].set_content(i*i);

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
    unsigned int id;

    create_message(message);
    shuffle(message); //send packages in random order

    for(int i=0; i<m_size; i++) // sort message in right order
        received_message[message[i].get_id()]=message[i];
    

    // for(int i=0 ;i<m_size; i++)  //print message (unsorted)
    //     std::cout<< message[i].get_content() <<std::endl;

    // for(int i=0 ;i<m_size; i++)  //print message (sorted)
    //     std::cout<< received_message[i].get_content() << std::endl;


    
    return 0;
}