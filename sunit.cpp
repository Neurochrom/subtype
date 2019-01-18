#include <assert.h>
#include <iostream>

#include "assertnc.hpp"
#include "Unit.hpp"
#include "UnitStream.hpp"

UNIT_FULL_DEF(int, PubIndex);
UNIT_FULL_DEF(int, PrivIndex);


PubIndex pubi = 3;
PubIndex pubi2 = 4;
PrivIndex privi = 6;

ASSERT_DOES_NOT_COMPILE_PREP2(privi, pubi, privi + pubi, 0);
ASSERT_DOES_NOT_COMPILE_PREP2(pubi, pubi2, pubi + pubi2, 1);
ASSERT_DOES_NOT_COMPILE_PREP(pubi, pubi % pubi, 2);

int main()
{
   std::cout << "Hi" << std::endl;

   ASSERT_DOES_NOT_COMPILE_EXEC(0);
   //ASSERT_DOES_NOT_COMPILE_EXEC(1);   // this actually does compile as it should
   pubi + pubi2;
   ASSERT_DOES_NOT_COMPILE_EXEC(2);   // we have not defined operator % so this shall pass

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

   std::cout << "Goodbye" << std::endl;
}
