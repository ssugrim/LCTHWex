#ifndef __SIMPLEPRNG__
#define __SIMPLEPRNG__

#include <stdio.h>
#include <stdlib.h>
#include <cstdint>

class SimplePRNG
{
    public:
    std::uint32_t m_z, m_w;

    void seed(std::uint32_t m_z_, std::uint32_t m_w_);

    std::uint32_t next_uniform_uint32();
    double next_double();

};


#endif
