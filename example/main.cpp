#include "../src/bitAligned.hpp"

#include <iostream>

int main()
{
    bitElement<9> e("101010101");

    std::cout << e.nBytes << "\n";

    std::cout << e.toString() << "\n";

    e.set(0, 0);
    std::cout << e.toString() << "\n";

    e.set(3, 1);
    std::cout << e.toString() << "\n";

    e.set(2, 0);
    std::cout << e.toString() << "\n";

    std::uint8_t* d = e.getRawData();

    std::cout << (int)d[0] << "\n";

    std::cout << std::endl;

    bitElement<9> f;
    f = std::move(e);
    std::cout << f.toString() << std::endl;

    std::cout << e.toString() << std::endl;
}
