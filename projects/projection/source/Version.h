#pragma once

#include <string>

namespace archmage {

  class Version {
      unsigned int primary;
      unsigned int secondary;

  public:
      Version(const std::string &pattern);

      bool matches(const Version & version) const;
  };

  class Version_Range {
  public:
      virtual bool matches(const Version &version) = 0;

      virtual ~Version_Range() {}
  };

  class Single_Version_Range : public virtual Version_Range {
      const Version version;

  public:
      Single_Version_Range(const Version &version) : version(version) {}

      virtual ~Single_Version_Range() {}

      bool matches(const Version &version) override;
  };
}