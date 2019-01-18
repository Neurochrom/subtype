// Copyright (c) 2015-2019 Paweł Cichocki
// License: https://opensource.org/licenses/MIT

#pragma once

template <class T, class D>
class Subtype
{
   T t;
public:

   Subtype(const T& t) : t(t) {};

   template <class AT, class AD>
   Subtype(const Subtype<AT, AD>& a) = delete;

   explicit operator T() { return t; }
   explicit operator const T&() const { return t; }


   bool operator==(const Subtype<T, D>& other) const { return t == other.t; }

   friend Subtype<T, D> operator+(Subtype<T, D> a, const Subtype<T, D>& b) { a.t += b.t; return a; }
   friend Subtype<T, D> operator-(Subtype<T, D> a, const Subtype<T, D>& b) { a.t -= b.t; return a; }
   friend Subtype<T, D> operator*(Subtype<T, D> a, const Subtype<T, D>& b) { a.t *= b.t; return a; }
   friend Subtype<T, D> operator/(Subtype<T, D> a, const Subtype<T, D>& b) { a.t /= b.t; return a; }

   Subtype<T, D>& operator+=(const Subtype<T, D>& a) { t += a.t; return *this; }
   Subtype<T, D>& operator-=(const Subtype<T, D>& a) { t -= a.t; return *this; }
   Subtype<T, D>& operator*=(const Subtype<T, D>& a) { t *= a.t; return *this; }
   Subtype<T, D>& operator/=(const Subtype<T, D>& a) { t /= a.t; return *this; }
};

#define SUBTYPE(name) STBEG_##name##_END
#define SUBTYPE_CLASS_DEF(name) class SUBTYPE(name) {}
#define SUBTYPE_FULL_DEF(baseType, name) SUBTYPE_CLASS_DEF(name); typedef Subtype<baseType, SUBTYPE(name)> name
