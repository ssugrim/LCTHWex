#include <cstdint>

#include "SimplePRNG.h"

void
SimplePRNG::seed(std::uint32_t m_z_, std::uint32_t m_w_)
{
    m_z = m_z_;
    m_w = m_w_;
}

std::uint32_t
SimplePRNG::next_uniform_uint32()
{
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

double
SimplePRNG::next_double()
{
    std::uint32_t u = next_uniform_uint32();
    // The magic number below is 1/(2^32 + 2).
    // The result is strictly between 0 and 1.
    return (u + 1.0) * 2.328306435454494e-10;
}
