// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: YLLogin.proto

#ifndef PROTOBUF_YLLogin_2eproto__INCLUDED
#define PROTOBUF_YLLogin_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3005001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "YLBase.pb.h"
// @@protoc_insertion_point(includes)

namespace protobuf_YLLogin_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[2];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
void InitDefaultsYLMsgServerRequestImpl();
void InitDefaultsYLMsgServerRequest();
void InitDefaultsYLMsgServerResponeImpl();
void InitDefaultsYLMsgServerRespone();
inline void InitDefaults() {
  InitDefaultsYLMsgServerRequest();
  InitDefaultsYLMsgServerRespone();
}
}  // namespace protobuf_YLLogin_2eproto
namespace YL {
namespace Login {
class YLMsgServerRequest;
class YLMsgServerRequestDefaultTypeInternal;
extern YLMsgServerRequestDefaultTypeInternal _YLMsgServerRequest_default_instance_;
class YLMsgServerRespone;
class YLMsgServerResponeDefaultTypeInternal;
extern YLMsgServerResponeDefaultTypeInternal _YLMsgServerRespone_default_instance_;
}  // namespace Login
}  // namespace YL
namespace YL {
namespace Login {

// ===================================================================

class YLMsgServerRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:YL.Login.YLMsgServerRequest) */ {
 public:
  YLMsgServerRequest();
  virtual ~YLMsgServerRequest();

  YLMsgServerRequest(const YLMsgServerRequest& from);

  inline YLMsgServerRequest& operator=(const YLMsgServerRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  YLMsgServerRequest(YLMsgServerRequest&& from) noexcept
    : YLMsgServerRequest() {
    *this = ::std::move(from);
  }

  inline YLMsgServerRequest& operator=(YLMsgServerRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const YLMsgServerRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const YLMsgServerRequest* internal_default_instance() {
    return reinterpret_cast<const YLMsgServerRequest*>(
               &_YLMsgServerRequest_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(YLMsgServerRequest* other);
  friend void swap(YLMsgServerRequest& a, YLMsgServerRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline YLMsgServerRequest* New() const PROTOBUF_FINAL { return New(NULL); }

  YLMsgServerRequest* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const YLMsgServerRequest& from);
  void MergeFrom(const YLMsgServerRequest& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(YLMsgServerRequest* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string s = 1;
  void clear_s();
  static const int kSFieldNumber = 1;
  const ::std::string& s() const;
  void set_s(const ::std::string& value);
  #if LANG_CXX11
  void set_s(::std::string&& value);
  #endif
  void set_s(const char* value);
  void set_s(const char* value, size_t size);
  ::std::string* mutable_s();
  ::std::string* release_s();
  void set_allocated_s(::std::string* s);

  // @@protoc_insertion_point(class_scope:YL.Login.YLMsgServerRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr s_;
  mutable int _cached_size_;
  friend struct ::protobuf_YLLogin_2eproto::TableStruct;
  friend void ::protobuf_YLLogin_2eproto::InitDefaultsYLMsgServerRequestImpl();
};
// -------------------------------------------------------------------

class YLMsgServerRespone : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:YL.Login.YLMsgServerRespone) */ {
 public:
  YLMsgServerRespone();
  virtual ~YLMsgServerRespone();

  YLMsgServerRespone(const YLMsgServerRespone& from);

  inline YLMsgServerRespone& operator=(const YLMsgServerRespone& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  YLMsgServerRespone(YLMsgServerRespone&& from) noexcept
    : YLMsgServerRespone() {
    *this = ::std::move(from);
  }

  inline YLMsgServerRespone& operator=(YLMsgServerRespone&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const YLMsgServerRespone& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const YLMsgServerRespone* internal_default_instance() {
    return reinterpret_cast<const YLMsgServerRespone*>(
               &_YLMsgServerRespone_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(YLMsgServerRespone* other);
  friend void swap(YLMsgServerRespone& a, YLMsgServerRespone& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline YLMsgServerRespone* New() const PROTOBUF_FINAL { return New(NULL); }

  YLMsgServerRespone* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const YLMsgServerRespone& from);
  void MergeFrom(const YLMsgServerRespone& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(YLMsgServerRespone* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string prior_ip = 2;
  void clear_prior_ip();
  static const int kPriorIpFieldNumber = 2;
  const ::std::string& prior_ip() const;
  void set_prior_ip(const ::std::string& value);
  #if LANG_CXX11
  void set_prior_ip(::std::string&& value);
  #endif
  void set_prior_ip(const char* value);
  void set_prior_ip(const char* value, size_t size);
  ::std::string* mutable_prior_ip();
  ::std::string* release_prior_ip();
  void set_allocated_prior_ip(::std::string* prior_ip);

  // string back_ip = 3;
  void clear_back_ip();
  static const int kBackIpFieldNumber = 3;
  const ::std::string& back_ip() const;
  void set_back_ip(const ::std::string& value);
  #if LANG_CXX11
  void set_back_ip(::std::string&& value);
  #endif
  void set_back_ip(const char* value);
  void set_back_ip(const char* value, size_t size);
  ::std::string* mutable_back_ip();
  ::std::string* release_back_ip();
  void set_allocated_back_ip(::std::string* back_ip);

  // .YL.Base.ResultType result_code = 1;
  void clear_result_code();
  static const int kResultCodeFieldNumber = 1;
  ::YL::Base::ResultType result_code() const;
  void set_result_code(::YL::Base::ResultType value);

  // uint32 port = 4;
  void clear_port();
  static const int kPortFieldNumber = 4;
  ::google::protobuf::uint32 port() const;
  void set_port(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:YL.Login.YLMsgServerRespone)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr prior_ip_;
  ::google::protobuf::internal::ArenaStringPtr back_ip_;
  int result_code_;
  ::google::protobuf::uint32 port_;
  mutable int _cached_size_;
  friend struct ::protobuf_YLLogin_2eproto::TableStruct;
  friend void ::protobuf_YLLogin_2eproto::InitDefaultsYLMsgServerResponeImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// YLMsgServerRequest

// string s = 1;
inline void YLMsgServerRequest::clear_s() {
  s_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& YLMsgServerRequest::s() const {
  // @@protoc_insertion_point(field_get:YL.Login.YLMsgServerRequest.s)
  return s_.GetNoArena();
}
inline void YLMsgServerRequest::set_s(const ::std::string& value) {
  
  s_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:YL.Login.YLMsgServerRequest.s)
}
#if LANG_CXX11
inline void YLMsgServerRequest::set_s(::std::string&& value) {
  
  s_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:YL.Login.YLMsgServerRequest.s)
}
#endif
inline void YLMsgServerRequest::set_s(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  s_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:YL.Login.YLMsgServerRequest.s)
}
inline void YLMsgServerRequest::set_s(const char* value, size_t size) {
  
  s_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:YL.Login.YLMsgServerRequest.s)
}
inline ::std::string* YLMsgServerRequest::mutable_s() {
  
  // @@protoc_insertion_point(field_mutable:YL.Login.YLMsgServerRequest.s)
  return s_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* YLMsgServerRequest::release_s() {
  // @@protoc_insertion_point(field_release:YL.Login.YLMsgServerRequest.s)
  
  return s_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void YLMsgServerRequest::set_allocated_s(::std::string* s) {
  if (s != NULL) {
    
  } else {
    
  }
  s_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), s);
  // @@protoc_insertion_point(field_set_allocated:YL.Login.YLMsgServerRequest.s)
}

// -------------------------------------------------------------------

// YLMsgServerRespone

// .YL.Base.ResultType result_code = 1;
inline void YLMsgServerRespone::clear_result_code() {
  result_code_ = 0;
}
inline ::YL::Base::ResultType YLMsgServerRespone::result_code() const {
  // @@protoc_insertion_point(field_get:YL.Login.YLMsgServerRespone.result_code)
  return static_cast< ::YL::Base::ResultType >(result_code_);
}
inline void YLMsgServerRespone::set_result_code(::YL::Base::ResultType value) {
  
  result_code_ = value;
  // @@protoc_insertion_point(field_set:YL.Login.YLMsgServerRespone.result_code)
}

// string prior_ip = 2;
inline void YLMsgServerRespone::clear_prior_ip() {
  prior_ip_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& YLMsgServerRespone::prior_ip() const {
  // @@protoc_insertion_point(field_get:YL.Login.YLMsgServerRespone.prior_ip)
  return prior_ip_.GetNoArena();
}
inline void YLMsgServerRespone::set_prior_ip(const ::std::string& value) {
  
  prior_ip_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:YL.Login.YLMsgServerRespone.prior_ip)
}
#if LANG_CXX11
inline void YLMsgServerRespone::set_prior_ip(::std::string&& value) {
  
  prior_ip_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:YL.Login.YLMsgServerRespone.prior_ip)
}
#endif
inline void YLMsgServerRespone::set_prior_ip(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  prior_ip_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:YL.Login.YLMsgServerRespone.prior_ip)
}
inline void YLMsgServerRespone::set_prior_ip(const char* value, size_t size) {
  
  prior_ip_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:YL.Login.YLMsgServerRespone.prior_ip)
}
inline ::std::string* YLMsgServerRespone::mutable_prior_ip() {
  
  // @@protoc_insertion_point(field_mutable:YL.Login.YLMsgServerRespone.prior_ip)
  return prior_ip_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* YLMsgServerRespone::release_prior_ip() {
  // @@protoc_insertion_point(field_release:YL.Login.YLMsgServerRespone.prior_ip)
  
  return prior_ip_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void YLMsgServerRespone::set_allocated_prior_ip(::std::string* prior_ip) {
  if (prior_ip != NULL) {
    
  } else {
    
  }
  prior_ip_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), prior_ip);
  // @@protoc_insertion_point(field_set_allocated:YL.Login.YLMsgServerRespone.prior_ip)
}

// string back_ip = 3;
inline void YLMsgServerRespone::clear_back_ip() {
  back_ip_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& YLMsgServerRespone::back_ip() const {
  // @@protoc_insertion_point(field_get:YL.Login.YLMsgServerRespone.back_ip)
  return back_ip_.GetNoArena();
}
inline void YLMsgServerRespone::set_back_ip(const ::std::string& value) {
  
  back_ip_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:YL.Login.YLMsgServerRespone.back_ip)
}
#if LANG_CXX11
inline void YLMsgServerRespone::set_back_ip(::std::string&& value) {
  
  back_ip_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:YL.Login.YLMsgServerRespone.back_ip)
}
#endif
inline void YLMsgServerRespone::set_back_ip(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  back_ip_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:YL.Login.YLMsgServerRespone.back_ip)
}
inline void YLMsgServerRespone::set_back_ip(const char* value, size_t size) {
  
  back_ip_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:YL.Login.YLMsgServerRespone.back_ip)
}
inline ::std::string* YLMsgServerRespone::mutable_back_ip() {
  
  // @@protoc_insertion_point(field_mutable:YL.Login.YLMsgServerRespone.back_ip)
  return back_ip_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* YLMsgServerRespone::release_back_ip() {
  // @@protoc_insertion_point(field_release:YL.Login.YLMsgServerRespone.back_ip)
  
  return back_ip_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void YLMsgServerRespone::set_allocated_back_ip(::std::string* back_ip) {
  if (back_ip != NULL) {
    
  } else {
    
  }
  back_ip_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), back_ip);
  // @@protoc_insertion_point(field_set_allocated:YL.Login.YLMsgServerRespone.back_ip)
}

// uint32 port = 4;
inline void YLMsgServerRespone::clear_port() {
  port_ = 0u;
}
inline ::google::protobuf::uint32 YLMsgServerRespone::port() const {
  // @@protoc_insertion_point(field_get:YL.Login.YLMsgServerRespone.port)
  return port_;
}
inline void YLMsgServerRespone::set_port(::google::protobuf::uint32 value) {
  
  port_ = value;
  // @@protoc_insertion_point(field_set:YL.Login.YLMsgServerRespone.port)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace Login
}  // namespace YL

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_YLLogin_2eproto__INCLUDED