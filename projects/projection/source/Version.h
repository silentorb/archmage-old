#pragma once

#include <string>
#include <memory>
#include <limits>

namespace projection {

  class Version {
      unsigned int UNDEFINED = std::numeric_limits<unsigned int>::max();

      unsigned int major = 0;
      unsigned int minor = UNDEFINED;
      unsigned int patch = UNDEFINED;
      std::string branch;

  public:
      Version(const std::string &source);

      bool matches(const Version &version) const;
      const std::string get_string() const;
      const std::string get_full_string() const;
  };


  class Invalid_Version_Format : public std::runtime_error {
      const std::string version_string;

  public:
      Invalid_Version_Format(const std::string &version_string) :
        runtime_error("Invalid Version Format: " + version_string), version_string(version_string) {}
  };


  class Version_Range_Internal {
  public:
      virtual bool matches(const Version &version) const = 0;
      virtual const std::string get_string() const = 0;
  };

  class Version_Range {
      std::shared_ptr<Version_Range_Internal> internal;

  public:
      Version_Range() {}

      Version_Range(const std::shared_ptr<Version_Range_Internal> &internal) :
        internal(internal) {}

      Version_Range(const std::string &pattern);

      Version_Range(Version_Range_Internal *internal) :
        internal(internal) {}

      bool matches(const Version &version) const {
        return internal->matches(version);
      }

      const std::string get_string() const {
        return internal->get_string();
      }

      virtual ~Version_Range() {}
  };


  class Single_Version_Range : public virtual Version_Range_Internal {
      const Version version;

  public:
      Single_Version_Range(const Version &version) : version(version) {}

      virtual ~Single_Version_Range() {}

      bool matches(const Version &version) const override;

      const std::string get_string() const override {
        return version.get_string();
      }
  };
}