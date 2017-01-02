#pragma once

#include <string>
#include <functional>
#include <vector>

namespace archmage {
  class Input;

  using Arguments = std::vector<std::string>;
  using Command_Delegate = std::function<void(const Input &input)>;

  class Command {
      std::string name;
      Command_Delegate delegate;

  public:
      Command(const std::string &name, const Command_Delegate &delegate) :
        name(name), delegate(delegate) {}

      const std::string &get_name() const {
        return name;
      }

      void operator()(const Input &input) const {
        delegate(input);
      }
  };
}