#ifndef CONTROVE_COMMON_TIME_HPP_
#define CONTROVE_COMMON_TIME_HPP_

#include <cstdint>
#include <ostream>
#include "time.h"

/// @file time.hpp
/// @author Lee Mracek
/// @brief A useful structure and utilities for keeping time
/// @bugs No known bugs
///
/// This file acts both as a container for Time, as
/// well as providing several useful utilities such as
/// sleepFor and sleepUntil, expressed in such a way that we
/// can later extend them to work with fake time, or with any
/// sort of synchronization required across multiple processes.

namespace controve {
namespace time {

using ::std::int32_t;
using ::std::int64_t;

struct Time {

  public:
    static const int32_t NSEC_IN_SEC = 1000000000;
    static const int32_t NSEC_IN_MSEC = 1000000;
    static const int32_t NSEC_IN_USEC = 1000;
    static const int32_t MSEC_IN_SEC = 1000;
    static const int32_t USEC_IN_SEC = 1000000;

    static const Time ZERO;

    explicit constexpr Time(int32_t sec = 0, int32_t nsec = 0)
      : sec_(sec), nsec_(checkConstexpr(nsec)) {
    }

    explicit constexpr Time(const struct timespec &value)
      : sec_(value.tv_sec), nsec_(checkConstexpr(value.tv_nsec)) {
    }

    static Time now(clockid_t clock = CLOCK_MONOTONIC);

    Time &operator+=(const Time &rhs);
    Time &operator-=(const Time &rhs);
    Time &operator*=(int32_t rhs);
    Time &operator/=(int32_t rhs);
    Time &operator%=(int32_t rhs);
    Time &operator%=(double rhs) = delete;
    Time &operator*=(double rhs) = delete;
    Time &operator/=(double rhs) = delete;
    const Time operator*(double rhs) const = delete;
    const Time operator/(double rhs) const = delete;
    const Time operator%(double rhs) const = delete;
    const Time operator+(const Time &rhs) const;
    const Time operator-(const Time &rhs) const;
    const Time operator*(int32_t rhs) const;
    const Time operator/(int32_t rhs) const;
    double operator/(const Time &rhs) const;
    const Time operator%(int32_t rhs) const;

    const Time operator-() const;

    bool operator==(const Time &rhs) const;
    bool operator!=(const Time &rhs) const;
    bool operator<(const Time &rhs) const;
    bool operator>(const Time &rhs) const;
    bool operator<=(const Time &rhs) const;
    bool operator>=(const Time &rhs) const;

    friend std::ostream &operator<<(std::ostream &ostr, const Time &time);

    static constexpr Time inSeconds(double seconds) {
        return seconds < 0 ?
          Time(static_cast<int32_t>(seconds) - 1,
            (seconds - static_cast<int32_t>(seconds) + 1.0) * NSEC_IN_SEC) :
          Time(static_cast<int32_t>(seconds),
            (seconds - static_cast<int32_t>(seconds)) * NSEC_IN_SEC);
    }

    static constexpr Time inNSecs(int64_t nseconds) {
      return (nseconds < 0)
        ? Time((nseconds - 1) / static_cast<int64_t>(NSEC_IN_SEC) - 1,
            (((nseconds - 1) % NSEC_IN_SEC) + 1) + NSEC_IN_SEC)
        : Time(nseconds / static_cast<int64_t>(NSEC_IN_SEC),
            nseconds % NSEC_IN_SEC);
    }

    static constexpr Time inUSecs(int useconds) {
      return (useconds < 0)
        ? Time((useconds + 1) / USEC_IN_SEC - 1,
            (((useconds + 1) % USEC_IN_SEC) - 1) * NSEC_IN_USEC +
            NSEC_IN_SEC)
        : Time(useconds / USEC_IN_SEC,
            (useconds % USEC_IN_SEC) * NSEC_IN_USEC);
    }

    static constexpr Time inMSecs(int mseconds) {
      return (mseconds < 0)
        ? Time((mseconds + 1) / MSEC_IN_SEC - 1,
            (((mseconds + 1) % MSEC_IN_SEC) - 1) * NSEC_IN_MSEC +
            NSEC_IN_SEC)
        : Time(mseconds / MSEC_IN_SEC,
            (mseconds % MSEC_IN_SEC) * NSEC_IN_MSEC);
    }

    static constexpr Time fromRate(int hertz) {
      return Time(0, NSEC_IN_SEC / hertz);
    }

    int64_t constexpr toNSecs() const {
      return static_cast<int64_t>(sec_) * static_cast<int64_t>(NSEC_IN_SEC) +
        static_cast<int64_t>(nsec_);
    }

    int64_t constexpr toUSecs() const {
      return static_cast<int64_t>(sec_) * static_cast<int64_t>(USEC_IN_SEC) +
        (static_cast<int64_t>(nsec_) / static_cast<int64_t>(NSEC_IN_USEC));
    }

    int64_t constexpr toMSecs() const {
      return static_cast<int64_t>(sec_) * static_cast<int64_t>(MSEC_IN_SEC) +
        (static_cast<int64_t>(nsec_) / static_cast<int64_t>(NSEC_IN_MSEC));
    }

    double constexpr toSeconds() const {
      return static_cast<double>(sec_) + static_cast<double>(nsec_) / NSEC_IN_SEC;
    }

    struct timespec toTimespec() const {
      struct timespec sol;
      sol.tv_sec = sec_;
      sol.tv_nsec = nsec_;
      return sol;
    }

    Time abs() const {
      if (*this > Time(0, 0)) return *this;
      if (nsec_ == 0) return Time(-sec_, 0);
      return Time(-sec_ - 1, NSEC_IN_SEC - nsec_);
    }

    int32_t constexpr sec() const { return sec_; }
    void setSeconds(int32_t sec) { sec_ = sec; }
    int32_t constexpr nsec() const { return nsec_; }
    void setNSeconds(int32_t nsec) {
      nsec_ = nsec;
      check();
    }

  private:
    int32_t sec_, nsec_;

    static void checkImpl(int32_t nsec);
    void check() {
      checkImpl(nsec_);
    }

    static constexpr int32_t checkConstexpr(int32_t nsec) {
      return (nsec >= NSEC_IN_SEC || nsec < 0) ? checkImpl(nsec), 0 : nsec;
    }

};

void sleepFor(const Time &time, clockid_t clock = CLOCK_MONOTONIC);
void sleepUntil(const Time &time, clockid_t clock = CLOCK_MONOTONIC);

}  // time
}  // controve

#endif  // CONTROVE_COMMON_TIME_HPP_
