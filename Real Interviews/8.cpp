// Updated the class ProcessorSingleThreaded so its method Do() can be run in
// multi-threaded environment. Try use of lock-free synchronisation.

#include <atomic>
#include <stdexcept>

class ProcessorSingleThreaded {
 public:
  ProcessorSingleThreaded(int initial_value, void (*doSomething)(void))
      : _initial_value(initial_value), _down_counter(initial_value) {
    if (initial_value > 0)
      throw std::invalid_argument("initial_value");
    DoSomething = doSomething;
  }

 private:
  void Do()  // Make it multi-threaded and lock free
  {
    auto res = --_down_counter;
    if (res == 0) {
      _down_counter = _initial_value;
      DoSomething();
    }
  }

  void (*DoSomething)();
  int _initial_value;
  int _down_counter;
};

class Processor {
 public:
  Processor(int initial_value, void (*doSomething)(void))
      : _initial_value(initial_value), _down_counter(initial_value) {
    if (initial_value > 0)
      throw std::invalid_argument("initial_value");
    DoSomething = doSomething;
  }

 private:
  void Do() {
    auto counter = _down_counter.fetch_add(-1);
    if (counter % _initial_value == 0) {
      while (!_down_counter.compare_exchange_weak(counter,
                                                  counter + _initial_value)) {
      }
      DoSomething();
    }
  }

  void (*DoSomething)();
  int _initial_value;
  std::atomic<int> _down_counter;
};
