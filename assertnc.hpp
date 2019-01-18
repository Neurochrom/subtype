// Copyright (c) 2015-2019 Paweł Cichocki
// License: https://opensource.org/licenses/MIT

#pragma once

#include <iostream>
#include <typeinfo>

namespace {

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

} // end namespace
