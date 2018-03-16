#ifndef __TPC_TIMEKEEPING_HPP
#define __TPC_TIMEKEEPING_HPP

#include <stdbool.h>
#include <stdint.h>

namespace TPC {
  namespace Timekeeping {
    void init();

    class Interval {
    public:
      int16_t ticks;
      Interval(int16_t _ticks);
      static Interval fromSeconds(int16_t seconds);
      static Interval fromMilliseconds(int16_t milliseconds);
    };

    class Timestamp {
    public:
      int16_t ticks;
      Timestamp(int16_t _ticks);
      static Timestamp now();
      bool isBefore(Timestamp other) const;
      bool isAfter(Timestamp other) const;
      Interval since(Timestamp other) const;
      Interval until(Timestamp other) const;
      Timestamp add(Interval offset) const;
      Timestamp subtract(Interval offset) const;
    };
  }
}

#endif
