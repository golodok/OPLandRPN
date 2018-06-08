#include "converter.h"
int main(int argc, char *argv[])
{
    Converter conver;
    conver.fromRPN("3 4 2 * 1 5 - 2 ^ / +");
    std::cout<<'\n';
    conver.fromOPL("3 + 4 * 2 / (1 - 5)^2");
    system("pause");
}
