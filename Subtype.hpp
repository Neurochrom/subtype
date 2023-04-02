// Copyright (c) 2015-2023 Paweł Cichocki
// License: https://opensource.org/licenses/MIT

#pragma once

template <class T, class D>
class SubtypeBase
{
protected:
   T t;

public:
   typedef T base_type;
   constexpr explicit SubtypeBase(const T& t) : t(t) {};

   T& get() { return t; }
   constexpr const T& get() const { return t; }
};

template <class T, class D>
class Subtype : public SubtypeBase<T, D>
{
public:
   constexpr /*explicit*/ Subtype(const T& t) : SubtypeBase<T, D>(t) {};
   // Note that the usage of explicit forces:
   // std::atomic<SomeSubType> a(123);
   //    => std::atomic<SomeSubType> a(SomeSubType(123));
   // std::set<SomeSubType> s { 1, 2 };
   //    => std::set<SomeSubType> s { SomeSubType(1), SomeSubType(2) };

   Subtype(Subtype<T, D> const&) = default;

   explicit operator T() { return this->t; }
   explicit operator const T&() const { return this->t; }

   bool operator==(const Subtype<T, D>& other) const { return this->t == other.t; }
   bool operator!=(const Subtype<T, D>& other) const { return this->t != other.t; }
   bool operator<(const Subtype<T, D>& other) const { return this->t < other.t; }
   bool operator>(const Subtype<T, D>& other) const { return this->t > other.t; }
   bool operator<=(const Subtype<T, D>& other) const { return this->t <= other.t; }
   bool operator>=(const Subtype<T, D>& other) const { return this->t >= other.t; }

   friend Subtype<T, D> operator+(Subtype<T, D> a, const Subtype<T, D>& b) { a.t += b.t; return a; }
   friend Subtype<T, D> operator-(const Subtype<T, D>& a, const Subtype<T, D>& b) { return Subtype<T, D>(a.t - b.t); }
   friend Subtype<T, D> operator*(const Subtype<T, D>& a, const Subtype<T, D>& b) { return Subtype<T, D>(a.t * b.t); }
   friend Subtype<T, D> operator/(const Subtype<T, D>& a, const Subtype<T, D>& b) { return Subtype<T, D>(a.t / b.t); }
   friend Subtype<T, D> operator%(const Subtype<T, D>& a, const Subtype<T, D>& b) { return Subtype<T, D>(a.t % b.t); }
   friend Subtype<T, D> operator&(const Subtype<T, D>& a, const Subtype<T, D>& b) { return Subtype<T, D>(a.t & b.t); }
   friend Subtype<T, D> operator|(const Subtype<T, D>& a, const Subtype<T, D>& b) { return Subtype<T, D>(a.t | b.t); }
   friend Subtype<T, D> operator^(const Subtype<T, D>& a, const Subtype<T, D>& b) { return Subtype<T, D>(a.t ^ b.t); }

   Subtype<T, D>& operator+=(const Subtype<T, D>& a) { this->t += a.t; return *this; }
   Subtype<T, D>& operator-=(const Subtype<T, D>& a) { this->t -= a.t; return *this; }
   Subtype<T, D>& operator*=(const Subtype<T, D>& a) { this->t *= a.t; return *this; }
   Subtype<T, D>& operator/=(const Subtype<T, D>& a) { this->t /= a.t; return *this; }
   Subtype<T, D>& operator%=(const Subtype<T, D>& a) { this->t %= a.t; return *this; }
   Subtype<T, D>& operator&=(const Subtype<T, D>& a) { this->t &= a.t; return *this; }
   Subtype<T, D>& operator|=(const Subtype<T, D>& a) { this->t |= a.t; return *this; }
   Subtype<T, D>& operator^=(const Subtype<T, D>& a) { this->t ^= a.t; return *this; }

   Subtype<T, D>& operator++() { ++this->t; return *this; }
   Subtype<T, D> operator++(int) { Subtype<T, D> r(*this); this->t++; return r; }
   Subtype<T, D>& operator--() { --this->t; return *this; }
   Subtype<T, D> operator--(int) { Subtype<T, D> r(*this); this->t--; return r; }
};

template <class T, class D>
class SubtypeNoArithOp : public SubtypeBase<T, D>
{
public:
   constexpr /*explicit*/ SubtypeNoArithOp(const T& t) : SubtypeBase<T, D>(t) {};

   constexpr SubtypeNoArithOp(const SubtypeNoArithOp<T, D>& o) = default;

   explicit operator T() { return this->t; }
   explicit operator const T&() const { return this->t; }

   bool operator==(const SubtypeNoArithOp<T, D>& other) const { return this->t == other.t; }
   bool operator!=(const SubtypeNoArithOp<T, D>& other) const { return this->t != other.t; }
   bool operator<(const SubtypeNoArithOp<T, D>& other) const { return this->t < other.t; }
   bool operator>(const SubtypeNoArithOp<T, D>& other) const { return this->t > other.t; }
   bool operator<=(const SubtypeNoArithOp<T, D>& other) const { return this->t <= other.t; }
   bool operator>=(const SubtypeNoArithOp<T, D>& other) const { return this->t >= other.t; }
};

#define SUBTYPE_DCLASS_NAME(name) STBEG_##name##_END
#define SUBTYPE_DCLASS_DEF(name) class SUBTYPE_DCLASS_NAME(name) {}
#define SUBTYPE_DEF(baseType, name) SUBTYPE_DCLASS_DEF(name); typedef Subtype<baseType, SUBTYPE_DCLASS_NAME(name)> name
#define SUBTYPE_NO_ARITH_OP_DEF(baseType, name) SUBTYPE_DCLASS_DEF(name); typedef SubtypeNoArithOp<baseType, SUBTYPE_DCLASS_NAME(name)> name

// Define std::hash so that using std::unordered_* is not a pain
namespace std
{

template <class T, class D>
struct hash<Subtype<T, D>>
{
   size_t operator()(const Subtype<T, D>& x) const noexcept
   {
      static const std::hash<T> h;
      return h(x.get());
   }
};

template <class T, class D>
struct hash<SubtypeNoArithOp<T, D>>
{
   size_t operator()(const SubtypeNoArithOp<T, D>& x) const noexcept
   {
      static const std::hash<T> h;
      return h(x.get());
   }
};

} // end std namespace
