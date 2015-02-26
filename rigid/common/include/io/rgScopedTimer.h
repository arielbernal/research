#ifndef RGSCOPEDTIMER_H
#define RGSCOPEDTIMER_H

#include <memory>

namespace rg {

template <typename source_t, typename stamp_t = typename source_t::stamp_type,
          typename value_t = typename source_t::value_type>
class scoped_timer_impl : private source_t {
 public:
  typedef value_t value_type;
  typedef source_t source_type;
  typedef stamp_t stamp_type;

  enum unit_type { unit_us, unit_ms, unit_s };

  template <typename time_value_t>
  explicit scoped_timer_impl(time_value_t& time_value,
                             unit_type unit = unit_ms);

  template <typename time_value_t>
  scoped_timer_impl(time_value_t& time_value, bool precondition,
                    unit_type unit = unit_ms);

  ~scoped_timer_impl();

  bool precondition() const;

  unit_type unit() const;

  stamp_type stamp() const;

 private:
  scoped_timer_impl(const scoped_timer_impl&);
  scoped_timer_impl& operator=(const scoped_timer_impl&);

  unit_type m_unit;
  stamp_type m_stamp;

  template <typename T>
  struct wrap;
  struct wrap_type;

  std::auto_ptr<wrap_type> m_value;
  bool m_precondition;
};

class system_time_source {
 public:
  typedef long long stamp_type;
  typedef double value_type;

  static stamp_type get_time_stamp();

  static bool check_interval(stamp_type begin, stamp_type end);

  static value_type get_time_value_us(stamp_type begin, stamp_type end);
};

typedef scoped_timer_impl<system_time_source> scoped_timer;

} // namspace rg

#include "rgScopedTimer.impl"

#endif  // RGSCOPEDTIMER_H
