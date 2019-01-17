#pragma once

template <class T, class D>
class Unit
{
   T t;
public:

   Unit(const T& t) : t(t) {};

   template <class AT, class AD>
   Unit(const Unit<AT, AD>& a) = delete;

   explicit operator T() { return t; }
   explicit operator const T&() const { return t; }


   bool operator==(const Unit<T, D>& other) const { return t == other.t; }

   friend Unit<T, D> operator+(Unit<T, D> a, const Unit<T, D>& b) { a.t += b.t; return a; }
   friend Unit<T, D> operator-(Unit<T, D> a, const Unit<T, D>& b) { a.t -= b.t; return a; }
   friend Unit<T, D> operator*(Unit<T, D> a, const Unit<T, D>& b) { a.t *= b.t; return a; }
   friend Unit<T, D> operator/(Unit<T, D> a, const Unit<T, D>& b) { a.t /= b.t; return a; }

   Unit<T, D>& operator+=(const Unit<T, D>& a) { t += a.t; return *this; }
   Unit<T, D>& operator-=(const Unit<T, D>& a) { t -= a.t; return *this; }
   Unit<T, D>& operator*=(const Unit<T, D>& a) { t *= a.t; return *this; }
   Unit<T, D>& operator/=(const Unit<T, D>& a) { t /= a.t; return *this; }
};
