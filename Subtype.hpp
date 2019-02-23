// Copyright (c) 2015-2019 Paweł Cichocki
// License: https://opensource.org/licenses/MIT

#pragma once

template <class T, class D>
class Subtype
{
   T t;
public:

   T& get() { return t; }
   const T& get() const { return t; }

   Subtype(const T& t) : t(t) {};

   Subtype(const Subtype<T, D>& o) : t(o.t) {}

   template <class AT, class AD>
   Subtype(const Subtype<AT, AD>& a) = delete;

   explicit operator T() { return t; }
   explicit operator const T&() const { return t; }


   bool operator==(const Subtype<T, D>& other) const { return t == other.t; }
   bool operator!=(const Subtype<T, D>& other) const { return t != other.t; }
   bool operator<(const Subtype<T, D>& other) const { return t < other.t; }
   bool operator>(const Subtype<T, D>& other) const { return t > other.t; }
   bool operator<=(const Subtype<T, D>& other) const { return t <= other.t; }
   bool operator>=(const Subtype<T, D>& other) const { return t >= other.t; }

   friend Subtype<T, D> operator+(Subtype<T, D> a, const Subtype<T, D>& b) { a.t += b.t; return a; }
   friend Subtype<T, D> operator-(Subtype<T, D> a, const Subtype<T, D>& b) { a.t -= b.t; return a; }
   friend Subtype<T, D> operator*(Subtype<T, D> a, const Subtype<T, D>& b) { a.t *= b.t; return a; }
   friend Subtype<T, D> operator/(Subtype<T, D> a, const Subtype<T, D>& b) { a.t /= b.t; return a; }
   friend Subtype<T, D> operator%(Subtype<T, D> a, const Subtype<T, D>& b) { a.t %= b.t; return a; }
   friend Subtype<T, D> operator&(Subtype<T, D> a, const Subtype<T, D>& b) { a.t &= b.t; return a; }
   friend Subtype<T, D> operator|(Subtype<T, D> a, const Subtype<T, D>& b) { a.t |= b.t; return a; }
   friend Subtype<T, D> operator^(Subtype<T, D> a, const Subtype<T, D>& b) { a.t ^= b.t; return a; }

   Subtype<T, D>& operator+=(const Subtype<T, D>& a) { t += a.t; return *this; }
   Subtype<T, D>& operator-=(const Subtype<T, D>& a) { t -= a.t; return *this; }
   Subtype<T, D>& operator*=(const Subtype<T, D>& a) { t *= a.t; return *this; }
   Subtype<T, D>& operator/=(const Subtype<T, D>& a) { t /= a.t; return *this; }
   Subtype<T, D>& operator%=(const Subtype<T, D>& a) { t %= a.t; return *this; }
   Subtype<T, D>& operator&=(const Subtype<T, D>& a) { t &= a.t; return *this; }
   Subtype<T, D>& operator|=(const Subtype<T, D>& a) { t |= a.t; return *this; }
   Subtype<T, D>& operator^=(const Subtype<T, D>& a) { t ^= a.t; return *this; }

   Subtype<T, D>& operator++() { ++t; return *this; }
   Subtype<T, D> operator++(int) { Subtype<T, D> r(*this); t++; return r; }
   Subtype<T, D>& operator--() { --t; return *this; }
   Subtype<T, D> operator--(int) { Subtype<T, D> r(*this); t--; return r; }
};

#define SUBTYPE_DCLASS_NAME(name) STBEG_##name##_END
#define SUBTYPE_DCLASS_DEF(name) class SUBTYPE_DCLASS_NAME(name) {}
#define SUBTYPE_DEF(baseType, name) SUBTYPE_DCLASS_DEF(name); typedef Subtype<baseType, SUBTYPE_DCLASS_NAME(name)> name

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
} // end std namespace
