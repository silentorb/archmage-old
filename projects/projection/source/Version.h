#pragma once

#include <string>
#include <memory>

namespace projection {

  class Version {
      unsigned int primary;
      unsigned int secondary;

  public:
      Version(const std::string &pattern);

      bool matches(const Version &version) const;
  };

  class Version_Range_Internal {
  public:
      virtual bool matches(const Version &version) = 0;

  };

  class Version_Range {
      std::shared_ptr<Version_Range_Internal> internal;

  public:
      Version_Range() {}

      Version_Range(const std::shared_ptr<Version_Range_Internal> &internal) :
        internal(internal) {}

      Version_Range(Version_Range_Internal *internal) :
        internal(internal) {}

      bool matches(const Version &version) {
        return internal->matches(version);
      }

      virtual ~Version_Range() {}
  };


  class Single_Version_Range : public virtual Version_Range_Internal {
      const Version version;

  public:
      Single_Version_Range(const Version &version) : version(version) {}

      virtual ~Single_Version_Range() {}

      bool matches(const Version &version) override;
  };
}