#include <iostream>

template <typename T, T get_value(), void set_value(T)>
struct property {
  property() = default;

  property(T value) { set_value(value); }

  T operator=(T value) {
    set_value(value);
    return value;
  }

  operator T() { return get_value(); }
};

template <typename T,
          class Outer,
          T (Outer::*get_value)(),
          void (Outer::*set_value)(T)>
struct object_property {
  Outer* outer;

  T operator=(T value) {
    (outer->*set_value)(value);
    return value;
  }

  operator T() { return (outer->*get_value)(); }
};

class example {
 public:
  example() { value.outer = this; }

  void set_value(int v) { _value = v; }

  int get_value() { return _value; }

  object_property<int, example, &example::get_value, &example::set_value> value;

 private:
  int _value;
};

int main() {
  example ex;
  ex.value = 10;
  std::cout << ex.value << std::endl;
}
