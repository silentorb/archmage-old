#pragma once

#include "rapidjson/reader.h"
#include <map>
#include <memory>

namespace projection {

//  template<typename Encoding = rapidjson::UTF8<> >
//  class Json_Child_Handler : rapidjson::BaseReaderHandler<Encoding, Json_Child_Handler<Encoding> > {
//
//  };
//
//  template<typename Encoding = rapidjson::UTF8<> >
//  class Json_Handler : rapidjson::BaseReaderHandler<Encoding, Json_Handler<Encoding> > {
//      Json_Child_Handler *current_handler = nullptr;
//  };

  struct Base_Handler;

  class Virtual_Handler {
  protected:
      Virtual_Handler *parent = nullptr;
      Base_Handler *base_handler = nullptr;

      void start(Virtual_Handler *child);
      void finish();

  public:
      Virtual_Handler(Base_Handler *base_handler) :
        base_handler(base_handler) {}

      bool Default() { return false; }

      virtual bool Null() { return Default(); }

      virtual bool Bool(bool value) { return Default(); }

      virtual bool Int(int value) { return Default(); }

      virtual bool Uint(unsigned value) { return Default(); }

      virtual bool Int64(int64_t value) { return Default(); }

      virtual bool Uint64(uint64_t value) { return Default(); }

      virtual bool Double(double value) { return Default(); }

      virtual bool RawNumber(const std::string &value, bool copy) { return Default(); }

      virtual bool String(const std::string &value, bool copy) { return Default(); }

      virtual bool StartObject() { return Default(); }

      virtual bool Key(const std::string &value, bool copy) { return Default(); }

      virtual bool EndObject(rapidjson::SizeType value) { return Default(); }

      virtual bool StartArray() { return Default(); }

      virtual bool EndArray(rapidjson::SizeType value) { return Default(); }
  };

  struct Base_Handler {
      Virtual_Handler *current_handler;

      bool Default() { return current_handler->Default(); }

      bool Null() { return current_handler->Null(); }

      bool Bool(bool value) { return current_handler->Bool(value); }

      bool Int(int value) { return current_handler->Int(value); }

      bool Uint(unsigned int value) { return current_handler->Uint(value); }

      bool Int64(int64_t value) { return current_handler->Int64(value); }

      bool Uint64(uint64_t value) { return current_handler->Uint64(value); }

      bool Double(double value) { return current_handler->Double(value); }

      bool RawNumber(const char *str, rapidjson::SizeType len, bool copy) {
        return current_handler->RawNumber(std::string(str, len), copy);
      }

      bool String(const char *str, rapidjson::SizeType len, bool copy) {
        return current_handler->String(std::string(str, len), copy);
      }

      bool StartObject() { return current_handler->StartObject(); }

      bool Key(const char *str, rapidjson::SizeType len, bool copy) {
        return current_handler->Key(std::string(str, len), copy);
      }

      bool EndObject(rapidjson::SizeType value) { return current_handler->EndObject(value); }

      bool StartArray() { return current_handler->StartArray(); }

      bool EndArray(rapidjson::SizeType value) { return current_handler->EndArray(value); }
  };

  void Virtual_Handler::start(Virtual_Handler *child) {
    base_handler->current_handler = child;
  }

  void Virtual_Handler::finish() {
    base_handler->current_handler = parent;
  }

  class Dictionary_Handler : public Virtual_Handler {
      std::map<std::string, std::unique_ptr<Virtual_Handler>> children;

  public:
      Dictionary_Handler(Base_Handler *base_handler,
                         std::initializer_list<std::pair<std::string, std::unique_ptr<Virtual_Handler>>> initializer) :
        Virtual_Handler(base_handler) {
        for(auto & item : initializer) {
//          children[item.first] = std::move(item.second);
        }
      }

      bool Key(const std::string &string, bool copy) override;
  };
}