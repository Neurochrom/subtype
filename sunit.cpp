#include <assert.h>
#include <iostream>

#include "Unit.hpp"
#include "UnitStream.hpp"

UNIT_FULL_DEF(int, PubIndex);
UNIT_FULL_DEF(int, PrivIndex);


PubIndex pubi = 3;
PubIndex pubi2 = 4;
PrivIndex privi = 6;

struct NCBase_ {};

template <class T>
struct NCDerived_ : T
{
   template <class C> NCDerived_(C c = C()) : T(c) {}
   operator NCBase_() { return NCBase_(); }
};

#define ASSERT_DOES_NOT_COMPILE_PREP(a, expr, n) \
struct NCC##n##_ \
{ \
   template <class A> \
   auto f(A a) -> decltype(expr) \
   { \
      std::cout << "TEST FAILED: "#expr" does compile" << std::endl; \
      assert(0 && "The compilation of this should be prevented by SFINAE if "#expr" would be illegal"); \
      return expr; \
   } \
   int f(NCBase_) \
   { \
      std::cout << "TEST PASSED: "#expr" does not compile" << std::endl; \
      return 0; \
   } \
   NCC##n##_() { f(NCDerived_<decltype(a)>(a)); } \
}


#define ASSERT_DOES_NOT_COMPILE_PREP2(a, b, expr, n) \
struct NCC##n##_ \
{ \
   template <class A, class B> \
   auto f(A a, B b) -> decltype(expr) \
   { \
      std::cout << "TEST FAILED: "#expr" does compile" << std::endl; \
      assert(0 && "The compilation of this should be prevented by SFINAE if "#expr" would be illegal"); \
      return expr; \
   } \
   int f(NCBase_, NCBase_) \
   { \
      std::cout << "TEST PASSED: "#expr" does not compile" << std::endl; \
      return 0; \
   } \
   NCC##n##_() { f(NCDerived_<decltype(a)>(a), NCDerived_<decltype(b)>(b)); } \
}

#define ASSERT_DOES_NOT_COMPILE_EXEC(n)  NCC##n##_ nc_test##n


ASSERT_DOES_NOT_COMPILE_PREP2(privi, pubi, privi + pubi, 0);
ASSERT_DOES_NOT_COMPILE_PREP2(pubi, pubi2, pubi + pubi2, 1);
ASSERT_DOES_NOT_COMPILE_PREP(pubi, pubi % pubi, 2);

int main()
{
   std::cout << "Hi " << std::endl;

   ASSERT_DOES_NOT_COMPILE_EXEC(0);
   //ASSERT_DOES_NOT_COMPILE_EXEC(1);   // this actually does compile
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
}
