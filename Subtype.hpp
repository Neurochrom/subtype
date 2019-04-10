// Copyright (c) 2015-2019 Paweł Cichocki
// License: https://opensource.org/licenses/MIT

#pragma once

template <class T, class D>
class SubtypeBase
{
protected:
   T t;

public:
   constexpr SubtypeBase(const T& t) : t(t) {};
   T& get() { return t; }
   constexpr const T& get() const { return t; }
};

template <class T, class D>
class Subtype : public SubtypeBase<T, D>
{
public:
   constexpr Subtype(const T& t) : SubtypeBase<T, D>(t) {};

   Subtype(const Subtype<T, D>& o) : SubtypeBase<T, D>(o.t) {}

   template <class AT, class AD>
   Subtype(const Subtype<AT, AD>& a) = delete;

   explicit operator T() { return this->t; }
   explicit operator const T&() const { return this->t; }


   bool operator==(const Subtype<T, D>& other) const { return this->t == other.t; }
   bool operator!=(const Subtype<T, D>& other) const { return this->t != other.t; }
   bool operator<(const Subtype<T, D>& other) const { return this->t < other.t; }
   bool operator>(const Subtype<T, D>& other) const { return this->t > other.t; }
   bool operator<=(const Subtype<T, D>& other) const { return this->t <= other.t; }
   bool operator>=(const Subtype<T, D>& other) const { return this->t >= other.t; }

   friend Subtype<T, D> operator+(Subtype<T, D> a, const Subtype<T, D>& b) { a.t += b.t; return a; }
   friend Subtype<T, D> operator-(Subtype<T, D> a, const Subtype<T, D>& b) { a.t -= b.t; return a; }
   friend Subtype<T, D> operator*(Subtype<T, D> a, const Subtype<T, D>& b) { a.t *= b.t; return a; }
   friend Subtype<T, D> operator/(Subtype<T, D> a, const Subtype<T, D>& b) { a.t /= b.t; return a; }
   friend Subtype<T, D> operator%(Subtype<T, D> a, const Subtype<T, D>& b) { a.t %= b.t; return a; }
   friend Subtype<T, D> operator&(Subtype<T, D> a, const Subtype<T, D>& b) { a.t &= b.t; return a; }
   friend Subtype<T, D> operator|(Subtype<T, D> a, const Subtype<T, D>& b) { a.t |= b.t; return a; }
   friend Subtype<T, D> operator^(Subtype<T, D> a, const Subtype<T, D>& b) { a.t ^= b.t; return a; }

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
   constexpr SubtypeNoArithOp(const T& t) : SubtypeBase<T, D>(t) {};

   SubtypeNoArithOp(const SubtypeNoArithOp<T, D>& o) : SubtypeBase<T, D>(o.t) {}

   template <class AT, class AD>
   SubtypeNoArithOp(const SubtypeNoArithOp<AT, AD>& a) = delete;

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

namespace std
{
template <class T, class D>
struct hash<Subtype<T, D>>
{
   size_t operator()(const SubtypeBase<T, D>& x) const noexcept
   {
      static const std::hash<T> h;
      return h(x.get());
   }
};
} // end std namespace
