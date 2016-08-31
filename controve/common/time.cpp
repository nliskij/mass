#include "controve/common/time.hpp"

#include <cstdio>
#include <cstring>

namespace controve {
namespace time {

const int32_t Time::NSEC_IN_SEC;
const int32_t Time::NSEC_IN_MSEC;
const int32_t Time::NSEC_IN_USEC;
const int32_t Time::MSEC_IN_SEC;
const int32_t Time::USEC_IN_SEC;

const Time Time::ZERO{0, 0};

Time &Time::operator+=(const Time &rhs) {
  sec_ += rhs.sec_;
  nsec_ += rhs.nsec_;
  if (nsec_ > NSEC_IN_SEC) {
    nsec_ -= NSEC_IN_SEC;
    sec_ += 1;
  }

  return *this;
}

const Time Time::operator+(const Time &rhs) const {
  return Time(*this) += rhs;
}

Time &Time::operator-=(const Time &rhs) {
  sec_ -= rhs.sec_;
  nsec_ -= rhs.nsec_;
  const int wraps = nsec_ / NSEC_IN_SEC;
  nsec_ += NSEC_IN_SEC * wraps;
  sec_ -= wraps;

  if (nsec_ < 0) {
    nsec_ += NSEC_IN_SEC;
    sec_ -= 1;
  }

  return *this;
}

const Time Time::operator-(const Time &rhs) const {
  return Time(*this) -= rhs;
}

Time &Time::operator*=(int32_t rhs) {
  const int64_t temp = static_cast<int64_t>(nsec_) *
    static_cast<int64_t>(rhs);
  sec_ *= rhs;
  nsec_ = temp % NSEC_IN_SEC;
  sec_ += (temp - nsec_) / NSEC_IN_SEC;

  if (nsec_ < 0) {
    nsec_ += NSEC_IN_SEC;
    sec_ -= 1;
  }

  return *this;
}

const Time Time::operator*(int32_t rhs) const {
  return Time(*this) *= rhs;
}

Time &Time::operator/=(int32_t rhs) {
  nsec_ = (sec_ % rhs) * (NSEC_IN_SEC / rhs) + nsec_ / rhs;
  sec_ /= rhs;
  while (nsec_ < 0) {
    nsec_ += NSEC_IN_SEC;
    sec_ -= 1;
  }

  return *this;
}

const Time Time::operator/(int32_t rhs) const {
  return Time(*this) /= rhs;
}

double Time::operator/(const Time &rhs) const {
  return toSeconds() / rhs.toSeconds();
}

Time &Time::operator%=(int32_t rhs) {
  nsec_ = toNSecs() % rhs;
  const int wraps = nsec_ / ((rhs / NSEC_IN_SEC + 1) * NSEC_IN_SEC);
  sec_ = wraps + rhs / NSEC_IN_SEC;
  nsec_ -= NSEC_IN_SEC * wraps;
  if (nsec_ < 0) {
    nsec_ += NSEC_IN_SEC;
    sec_ -= 1;
  }
  return *this;
}

const Time Time::operator%(int32_t rhs) const {
  return Time(*this) %= rhs;
}

const Time Time::operator-() const {
  return Time(-sec_ - 1, NSEC_IN_SEC - nsec_);
}

bool Time::operator==(const Time &rhs) const {
  return sec_ == rhs.sec_ && nsec_ == rhs.nsec_;
}

bool Time::operator!=(const Time &rhs) const {
  return !(*this == rhs);
}

bool Time::operator<(const Time &rhs) const {
  return sec_ < rhs.sec_ || (sec_ == rhs.sec_ && nsec_ < rhs.nsec_);
}

bool Time::operator>(const Time &rhs) const {
  return sec_ > rhs.sec_ || (sec_ == rhs.sec_ && nsec_ > rhs.nsec_);
}

bool Time::operator<=(const Time &rhs) const {
  return sec_ < rhs.sec_ || (sec_ == rhs.sec_ && nsec_ <= rhs.nsec_);
}

bool Time::operator>=(const Time &rhs) const {
  return sec_ > rhs.sec_ || (sec_ == rhs.sec_ && nsec_ >= rhs.nsec_);
}

std::ostream &operator<<(std::ostream &ostr, const Time &time) {
  return ostr << "Time{" << time.sec_ << "s, " << time.nsec_ << "ns}";
}

void Time::checkImpl(int32_t nsec) {
  if (nsec >= NSEC_IN_SEC || nsec < 0) {
    std::fprintf(stderr, "nsec value is invalid");
  }
}

Time Time::now(clockid_t clock) {
  timespec temp;
  if (clock_gettime(clock, &temp) != 0) {
    ::std::fprintf(stderr, "clock_gettime(%jd, %p) failed",
        static_cast<uintmax_t>(clock), &temp);
  }

  return Time(temp);
}

void sleepFor(const Time &time, clockid_t clock) {
  timespec converted(time.toTimespec()), remaining;
  int failure = EINTR;
  do {
    if (failure != EINTR) {
      fprintf(stderr, "clock_nanosleep(%jd, 0, %p, %p) failed",
          static_cast<intmax_t>(clock), &converted, &remaining);
    }
    failure = clock_nanosleep(clock, 0, &converted, &remaining);
    ::std::memcpy(&converted, &remaining, sizeof(converted));
  } while (failure != 0);
}

void sleepUntil(const Time &time, clockid_t clock) {
  timespec converted(time.toTimespec());
  int failure;
  while ((failure = clock_nanosleep(clock, TIMER_ABSTIME,
          &converted, NULL)) != 0) {
    if (failure != EINTR) {
      fprintf(stderr, "clock_nanosleep(%jd, TIMER_ABSTIME, %p, NULL) failed",
          static_cast<intmax_t>(clock), &converted);
    }
  }
}

}  // time
}  // controve
