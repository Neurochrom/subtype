#pragma once

#include <string.h>
#include <ostream>
#include <string>

#define UNIT(u) UNIT_BEGIN_##u##_END
#define UNIT_DEF(u) class UNIT(u) {}
#define UNIT_FULL_DEF(bType, u) UNIT_DEF(u); typedef Unit<bType, UNIT(u)> u

template <class D>
struct DifferentiatorTraits
{
   /// @todo fail early tricks to have typeid(D).name() only where it works
   static std::string name()
   {
      static std::string tname = typeid(D).name();
      if (tname.empty())
         return "[units]";
      auto begpos = tname.find("UNIT_BEGIN_");
      auto endpos = tname.rfind("_END");
      static const auto begsize = strlen("UNIT_BEGIN_");
      auto postbeg = begpos + begsize;
      if (begpos != std::string::npos && postbeg < endpos)
         return " [" + tname.substr(postbeg, endpos - postbeg) + "]";
      return "[" + tname + "]";
   }
};

template <class T, class D>
std::ostream& operator<< (std::ostream& s, const Unit<T, D>& u)
{
   s << (T)u << DifferentiatorTraits<D>::name();
   return s;
}
