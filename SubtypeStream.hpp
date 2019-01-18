// Copyright (c) 2015-2019 Paweł Cichocki
// License: https://opensource.org/licenses/MIT

#pragma once

#include <string.h>
#include <ostream>
#include <string>

template <class D>
struct DifferentiatorTraits
{
   static std::string name()
   {
      static std::string tname = typeid(D).name();
      if (tname.empty())
         return "[subtype]";
      auto begpos = tname.find("STBEG_");
      auto endpos = tname.rfind("_END");
      static const auto begsize = strlen("STBEG_");
      auto postbeg = begpos + begsize;
      if (begpos != std::string::npos && postbeg < endpos)
         return " [" + tname.substr(postbeg, endpos - postbeg) + "]";
      return "[" + tname + "]";
   }
};

template <class T, class D>
std::ostream& operator<< (std::ostream& s, const Subtype<T, D>& u)
{
   s << (T)u << DifferentiatorTraits<D>::name();
   return s;
}
