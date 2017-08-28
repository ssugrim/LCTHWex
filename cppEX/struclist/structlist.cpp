#include <iostream>
#include <list>
#include <cstdint>

//Our data type to store
struct pkt_time{
    std::uint32_t seq;
    double sent;
    double recv;
    pkt_time(std::uint32_t iseq, double isent, double irecv) : 
        seq(iseq), sent(isent), recv(irecv) {} //assigining constructor
};


int main (){

    std::list<pkt_time> window;
    int i = 0;
    for (i = 0; i < 10; i++){
        window.emplace_back(pkt_time(i,0,0)); //avoid dobule construction
    }

    std::cout << "Front " << window.front().seq << std::endl;
    std::cout << "Back " << window.back().seq << std::endl;

    while (window.back().seq - window.front().seq > 3) //truncate the list
        window.pop_front();


    std::cout << "Front " << window.front().seq << std::endl;
    std::cout << "Back " << window.back().seq << std::endl;

    for (pkt_time t : window) //rangebased interation
        std::cout << "Seq " << t.seq << std::endl;

    for (auto t = window.rbegin(); t != window.rend(); ++t) // iterate backwards
        std::cout << "Seq " << t->seq << std::endl;
}

