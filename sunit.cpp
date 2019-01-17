#include <iostream>

#include "Unit.hpp"
#include "UnitStream.hpp"

int main()
{
   std::cout << "Hi" << std::endl;

   UNIT_FULL_DEF(int, PubIndex);
   UNIT_FULL_DEF(int, PrivIndex);

   PubIndex pub = 0;
   PubIndex pub2(2);
   pub = pub2;
   PubIndex pub3 = pub + pub2;
   pub3 += 2;
   std::cout << "Public index #3 converted to int: " << (int)pub3 << std::endl;

   PrivIndex priv = 1;
   PrivIndex priv2 = 2;
   priv = 4;
   std::cout << "Private index sum: " << priv + priv2 << std::endl;

   // This should not compile
   //priv = pub;

   // This should not compile
   //auto pp = 1 + priv + 2 + pub + 3;
}
