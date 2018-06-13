#include "converter.h"
int main(int argc, char *argv[])
{
    std::string sTmp;
    Converter conver;
    sTmp = conver.fromRPN("1 ASD 2 + 4 * 3 +");
    std::cout<<sTmp<<'\n';
    sTmp = conver.fromOPL(sTmp);
    std::cout<<sTmp<<'\n';
    system("pause");
}
