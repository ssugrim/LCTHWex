#include <iostream>
#include <list>
#include <cstdint>
#include <cstdlib>
#include <ctime>

//Our data type to store
struct pkt_time{
    std::uint32_t seq;
    double sent;
    double recv;
    double dur;
    pkt_time(const std::uint32_t iseq,
            const double isent,
            const double irecv,
            const double idur = 0) : //make a default duration if not given
        seq(iseq), sent(isent), recv(irecv), dur(idur) {
            if (dur == 0)
                dur = sent - recv; 
        }
//    pkt_time(const pkt_time &)=delete; //Prevent copying
    bool operator< (pkt_time other) const { //less than comparison
        return dur < other.dur;
    }
};

/*
 * Make a random float up to X, if X is zero return 1 to avoid divide by zero
 */
inline double rfloat (int X){
    return X ? static_cast <float> (std::rand()) / (static_cast <float> (RAND_MAX/X)) : 1;
}


int main (){

    /*
     * Make and display
     */
    std::srand(std::time(0));
    std::list<pkt_time> window;
    int i = 0;
    for (i = 0; i < 10; i++){
        window.emplace_back(i,rfloat(i),rfloat(i+2)); //avoid dobule construction
    }

    std::cout << "Front " << window.front().seq << std::endl;
    std::cout << "Back " << window.back().seq << std::endl; 

    /*
     *  Find the min duration
     */

    pkt_time min(0,0,0,0); //inplace declaration
    min = window.front(); //copy assignment
    for (const pkt_time& t : window){
        if (t < min){
            min = t;
        }
    }

    std::cout << "Min was " << min.dur << " Seq #" << min.seq << std::endl;

    /*
     * Iterate over the list forwards
     */
    std::cout << "Forward Iteration" << std::endl;
    for (const pkt_time& t : window) //rangebased interation with const reference
        std::cout << "Seq " << t.seq << " Dur " << t.dur << std::endl;

    /*
     * Truncate upto a value
     */

//    while (window.back().seq - window.front().seq > 3) //truncate the list
//        window.pop_front();
    std::cout << "Truncate if sequence number is further than 3 from max" << std::endl;
    window.remove_if([&window](pkt_time& t) {return window.back().seq - t.seq > 3;});

    std::cout << "Front " << window.front().seq << std::endl;
    std::cout << "Back " << window.back().seq << std::endl;

    /*
     * Iterate over the list backwards
     */

    std::cout << "Reverse Iteration after truncation" << std::endl;
    for (auto t = window.rbegin(); t != window.rend(); ++t) // iterate backwards
        std::cout << "Seq " << t->seq << " Dur " << t->dur << std::endl;
}

