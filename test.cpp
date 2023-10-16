// Copyright (c) 2015-2023 Paweł Cichocki
// License: https://opensource.org/licenses/MIT

#include <assert.h>

#include <atomic>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <type_traits>
#include <set>

#include "assertnc.hpp"
#include "Subtype.hpp"
#include "SubtypeStream.hpp"

SUBTYPE_DEF(int, PubIndex);
SUBTYPE_DEF(int, PrivIndex);

static_assert(std::is_trivially_copyable_v<PubIndex>);
static_assert(std::is_copy_constructible_v<PubIndex>);
static_assert(std::is_move_constructible_v<PubIndex>);
static_assert(std::is_copy_assignable_v<PubIndex>);
static_assert(std::is_move_assignable_v<PubIndex>);

PubIndex pubi(3);
PubIndex pubi2(4);
PrivIndex privi(6);

constexpr PubIndex ZERO_PUB(0);
static const PubIndex ONE_PUB(1);

ASSERT_DOES_NOT_COMPILE_PREP2(privi, pubi, privi + pubi, 0);
ASSERT_DOES_NOT_COMPILE_PREP2(pubi, pubi2, pubi + pubi2, 1);
ASSERT_DOES_NOT_COMPILE_PREP(pubi, pubi % pubi, 2);


SUBTYPE_NO_ARITH_OP_DEF(unsigned long, TimePoint);

TimePoint someTimeAgo(15000);
TimePoint recently(96000);

ASSERT_DOES_NOT_COMPILE_PREP2(someTimeAgo, recently, someTimeAgo + recently, 3);

static_assert(std::is_trivially_copyable_v<TimePoint>);
static_assert(std::is_copy_constructible_v<TimePoint>);
static_assert(std::is_move_constructible_v<TimePoint>);
static_assert(std::is_copy_assignable_v<TimePoint>);
static_assert(std::is_move_assignable_v<TimePoint>);


static constexpr PubIndex PUB_ONE(1);
static constexpr PubIndex PUB_TWO(2);


int main()
{
   std::cout << "Hi" << std::endl;

   ASSERT_DOES_NOT_COMPILE_EXEC(0);
   //ASSERT_DOES_NOT_COMPILE_EXEC(1);   // this actually does compile as it should
   pubi + pubi2;
   //ASSERT_DOES_NOT_COMPILE_EXEC(2);   // this actually does compile as it should

   ASSERT_DOES_NOT_COMPILE_EXEC(3);


   PubIndex pub = PubIndex(0);
   PubIndex pub2(2);
   pub = pub2;
   PubIndex pub3 = pub + pub2;
   pub3 += PubIndex(2);
   std::cout << "Public index #3 explicitly converted to int: " << (int)pub3 << std::endl;

   PrivIndex priv(1);
   PrivIndex priv2(2);
   priv = PrivIndex(4);
   std::cout << "Private index sum: " << priv + priv2 << std::endl;

   // This should not compile
   //priv = pub;
   //priv == pub;

   // This should not compile
   //auto pp = 1 + priv + 2 + pub + 3;

   std::vector<PubIndex> pubiVec(7, PubIndex(69));
   pubiVec.resize(16, PubIndex(42));
   // resizing down but suplying the second argument to avoid the compiler
   // being sour over not having a default constructor
   pubiVec.resize(6, PubIndex(42));

   //auto error = someTimeAgo + recently;  // no arythmetic on TimePoint
   //PubIndex error2;  // can't be uninitialized
   //TimePoint error3;  // can't be uninitialized

   PubIndex zpub(ZERO_PUB);
   zpub += 1;  // prevent unused warnings
   PubIndex opub(ONE_PUB);
   opub -= 1;  // prevent unused warnings

   TimePoint longAgo(6000);
   TimePoint birthTime(6000);
   TimePoint dayBefore(99000);
   assert(longAgo == birthTime);
   assert(longAgo < dayBefore);
   assert(dayBefore > birthTime);
   assert(longAgo >= birthTime && dayBefore >= longAgo);
   assert(longAgo <= dayBefore);
   std::cout << "Comparison operators for SubtypeNoArithOp TEST PASSED" << std::endl;

   std::cout << "TimePoint longAgo: " << longAgo << std::endl;


   /// Check operators
   PubIndex a(5);
   assert(a + PubIndex(1) == PubIndex(6));
   assert(a - PubIndex(1) == PubIndex(4));
   assert(a * PubIndex(2) == PubIndex(10));
   assert(a / PubIndex(5) == PubIndex(1));
   assert(a % PubIndex(3) == PubIndex(2));
   assert((a & PubIndex(3)) == PubIndex(1));
   assert((a | PubIndex(3)) == PubIndex(7));
   assert((a ^ PubIndex(3)) == PubIndex(6));
   assert((a += PubIndex(2)) == PubIndex(7) && a.get() == 7);
   assert((a -= PubIndex(2)) == PubIndex(5) && a.get() == 5);
   assert((a *= PubIndex(2)) == PubIndex(10) && a.get() == 10);
   assert((a /= PubIndex(2)) == PubIndex(5) && a.get() == 5);
   assert((a %= PubIndex(2)) == PubIndex(1) && a.get() == 1);
   assert((a &= PubIndex(2)) == PubIndex(0) && a.get() == 0);
   assert((a ^= PubIndex(3)) == PubIndex(3) && a.get() == 3);
   assert((a |= PubIndex(8)) == PubIndex(11) && a.get() == 11);
   assert(++a == PubIndex(12) && a.get() == 12);
   assert(a++ == PubIndex(12) && a.get() == 13);
   assert(--a == PubIndex(12) && a.get() == 12);
   assert(a-- == PubIndex(12) && a.get() == 11);
   a = PubIndex(5);
   PubIndex b(6);
   assert(a == a);
   assert(a < b && !(b < a));
   assert(b > a && !(a > b));
   assert(a >= a && b >= a && !(a >= b));
   assert(a <= a && a <= b && !(b <= a));
   std::cout << "Operators for Subtype TEST PASSED" << std::endl;

   // Switch test
   PubIndex pin(2);
   switch (pin.get())
   {
      case PUB_ONE.get():
         std::cerr << "Switch TEST FAILED! (case one)" << std::endl;
         return -1;
         break;
      case PUB_TWO.get():
         std::cout << "Switch TEST PASSED" << std::endl;
         break;
      default:
         std::cerr << "Switch TEST FAILED! (case default)" << std::endl;
         return -1;
   }

   // std::hash test
   auto pubi1000h = std::hash<PubIndex>()(PubIndex(1000));
   std::cout << "std::hash of PubIndex(1000): " << pubi1000h << std::endl;

   auto t1000h = std::hash<TimePoint>()(TimePoint(1000));
   std::cout << "std::hash of TimePoint(1000): " << t1000h << std::endl;
   std::cout << "std::hash TEST PASSED" << std::endl;

   // Test if it can be used with std::atomic
   std::atomic<PubIndex> apui(PubIndex(234));
   apui.store(321);
   std::atomic<TimePoint> atp(TimePoint(1000));
   atp.store(1001);
   std::atomic<PubIndex> apui2(234);
   apui2.store(235);

   std::set<PubIndex> pis { 1, 2 };

   std::unordered_set<TimePoint> tps { TimePoint(1000), TimePoint(2000) };
   assert(tps.count(TimePoint(1000)));
   assert(!tps.count(1001));

   std::cout << "Goodbye" << std::endl;
}
