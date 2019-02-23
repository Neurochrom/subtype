// Copyright (c) 2015-2019 Paweł Cichocki
// License: https://opensource.org/licenses/MIT

#include <assert.h>
#include <iostream>

#include "assertnc.hpp"
#include "Subtype.hpp"
#include "SubtypeStream.hpp"

SUBTYPE_DEF(int, PubIndex);
SUBTYPE_DEF(int, PrivIndex);

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
   //ASSERT_DOES_NOT_COMPILE_EXEC(2);   // this actually does compile as it should

   PubIndex pub = 0;
   PubIndex pub2(2);
   pub = pub2;
   PubIndex pub3 = pub + pub2;
   pub3 += 2;
   std::cout << "Public index #3 explicitly converted to int: " << (int)pub3 << std::endl;

   PrivIndex priv = 1;
   PrivIndex priv2 = 2;
   priv = 4;
   std::cout << "Private index sum: " << priv + priv2 << std::endl;

   // This should not compile
   //priv = pub;

   // This should not compile
   //auto pp = 1 + priv + 2 + pub + 3;

   /// Check all operators
   PubIndex a = 5;
   assert(a + 1 == 6);
   assert(a - 1 == 4);
   assert(a * 2 == 10);
   assert(a / 5 == 1);
   assert(a % 3 == 2);
   assert((a & 3) == 1);
   assert((a | 3) == 7);
   assert((a ^ 3) == 6);
   assert((a += 2) == 7 && a == 7);
   assert((a -= 2) == 5 && a == 5);
   assert((a *= 2) == 10 && a == 10);
   assert((a /= 2) == 5 && a == 5);
   assert((a %= 2) == 1 && a == 1);
   assert((a &= 2) == 0 && a == 0);
   assert((a ^= 3) == 3 && a == 3);
   assert((a |= 8) == 11 && a == 11);
   assert(++a == 12 && a == 12);
   assert(a++ == 12 && a == 13);
   assert(--a == 12 && a == 12);
   assert(a-- == 12 && a == 11);

   std::cout << "Goodbye" << std::endl;
}
