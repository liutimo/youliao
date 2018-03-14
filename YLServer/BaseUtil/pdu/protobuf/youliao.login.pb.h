// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: youliao.login.proto

#ifndef PROTOBUF_youliao_2elogin_2eproto__INCLUDED
#define PROTOBUF_youliao_2elogin_2eproto__INCLUDED

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
#include "youliao.base.pb.h"
// @@protoc_insertion_point(includes)

namespace protobuf_youliao_2elogin_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[4];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
void InitDefaultsMsgServerRequestImpl();
void InitDefaultsMsgServerRequest();
void InitDefaultsMsgServerResponeImpl();
void InitDefaultsMsgServerRespone();
void InitDefaultsUserLoginRequestImpl();
void InitDefaultsUserLoginRequest();
void InitDefaultsUserLoginResponeImpl();
void InitDefaultsUserLoginRespone();
inline void InitDefaults() {
  InitDefaultsMsgServerRequest();
  InitDefaultsMsgServerRespone();
  InitDefaultsUserLoginRequest();
  InitDefaultsUserLoginRespone();
}
}  // namespace protobuf_youliao_2elogin_2eproto
namespace youliao {
namespace pdu {
namespace login {
class MsgServerRequest;
class MsgServerRequestDefaultTypeInternal;
extern MsgServerRequestDefaultTypeInternal _MsgServerRequest_default_instance_;
class MsgServerRespone;
class MsgServerResponeDefaultTypeInternal;
extern MsgServerResponeDefaultTypeInternal _MsgServerRespone_default_instance_;
class UserLoginRequest;
class UserLoginRequestDefaultTypeInternal;
extern UserLoginRequestDefaultTypeInternal _UserLoginRequest_default_instance_;
class UserLoginRespone;
class UserLoginResponeDefaultTypeInternal;
extern UserLoginResponeDefaultTypeInternal _UserLoginRespone_default_instance_;
}  // namespace login
}  // namespace pdu
}  // namespace youliao
namespace youliao {
namespace pdu {
namespace login {

// ===================================================================

class MsgServerRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:youliao.pdu.login.MsgServerRequest) */ {
 public:
  MsgServerRequest();
  virtual ~MsgServerRequest();

  MsgServerRequest(const MsgServerRequest& from);

  inline MsgServerRequest& operator=(const MsgServerRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  MsgServerRequest(MsgServerRequest&& from) noexcept
    : MsgServerRequest() {
    *this = ::std::move(from);
  }

  inline MsgServerRequest& operator=(MsgServerRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const MsgServerRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const MsgServerRequest* internal_default_instance() {
    return reinterpret_cast<const MsgServerRequest*>(
               &_MsgServerRequest_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(MsgServerRequest* other);
  friend void swap(MsgServerRequest& a, MsgServerRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline MsgServerRequest* New() const PROTOBUF_FINAL { return New(NULL); }

  MsgServerRequest* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const MsgServerRequest& from);
  void MergeFrom(const MsgServerRequest& from);
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
  void InternalSwap(MsgServerRequest* other);
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

  // @@protoc_insertion_point(class_scope:youliao.pdu.login.MsgServerRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  mutable int _cached_size_;
  friend struct ::protobuf_youliao_2elogin_2eproto::TableStruct;
  friend void ::protobuf_youliao_2elogin_2eproto::InitDefaultsMsgServerRequestImpl();
};
// -------------------------------------------------------------------

class MsgServerRespone : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:youliao.pdu.login.MsgServerRespone) */ {
 public:
  MsgServerRespone();
  virtual ~MsgServerRespone();

  MsgServerRespone(const MsgServerRespone& from);

  inline MsgServerRespone& operator=(const MsgServerRespone& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  MsgServerRespone(MsgServerRespone&& from) noexcept
    : MsgServerRespone() {
    *this = ::std::move(from);
  }

  inline MsgServerRespone& operator=(MsgServerRespone&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const MsgServerRespone& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const MsgServerRespone* internal_default_instance() {
    return reinterpret_cast<const MsgServerRespone*>(
               &_MsgServerRespone_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(MsgServerRespone* other);
  friend void swap(MsgServerRespone& a, MsgServerRespone& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline MsgServerRespone* New() const PROTOBUF_FINAL { return New(NULL); }

  MsgServerRespone* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const MsgServerRespone& from);
  void MergeFrom(const MsgServerRespone& from);
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
  void InternalSwap(MsgServerRespone* other);
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

  // string msg_server_ip = 2;
  void clear_msg_server_ip();
  static const int kMsgServerIpFieldNumber = 2;
  const ::std::string& msg_server_ip() const;
  void set_msg_server_ip(const ::std::string& value);
  #if LANG_CXX11
  void set_msg_server_ip(::std::string&& value);
  #endif
  void set_msg_server_ip(const char* value);
  void set_msg_server_ip(const char* value, size_t size);
  ::std::string* mutable_msg_server_ip();
  ::std::string* release_msg_server_ip();
  void set_allocated_msg_server_ip(::std::string* msg_server_ip);

  // .youliao.pdu.base.ResultType result_code = 1;
  void clear_result_code();
  static const int kResultCodeFieldNumber = 1;
  ::youliao::pdu::base::ResultType result_code() const;
  void set_result_code(::youliao::pdu::base::ResultType value);

  // uint32 port = 3;
  void clear_port();
  static const int kPortFieldNumber = 3;
  ::google::protobuf::uint32 port() const;
  void set_port(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:youliao.pdu.login.MsgServerRespone)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr msg_server_ip_;
  int result_code_;
  ::google::protobuf::uint32 port_;
  mutable int _cached_size_;
  friend struct ::protobuf_youliao_2elogin_2eproto::TableStruct;
  friend void ::protobuf_youliao_2elogin_2eproto::InitDefaultsMsgServerResponeImpl();
};
// -------------------------------------------------------------------

class UserLoginRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:youliao.pdu.login.UserLoginRequest) */ {
 public:
  UserLoginRequest();
  virtual ~UserLoginRequest();

  UserLoginRequest(const UserLoginRequest& from);

  inline UserLoginRequest& operator=(const UserLoginRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  UserLoginRequest(UserLoginRequest&& from) noexcept
    : UserLoginRequest() {
    *this = ::std::move(from);
  }

  inline UserLoginRequest& operator=(UserLoginRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const UserLoginRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const UserLoginRequest* internal_default_instance() {
    return reinterpret_cast<const UserLoginRequest*>(
               &_UserLoginRequest_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    2;

  void Swap(UserLoginRequest* other);
  friend void swap(UserLoginRequest& a, UserLoginRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline UserLoginRequest* New() const PROTOBUF_FINAL { return New(NULL); }

  UserLoginRequest* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const UserLoginRequest& from);
  void MergeFrom(const UserLoginRequest& from);
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
  void InternalSwap(UserLoginRequest* other);
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

  // string user_name = 1;
  void clear_user_name();
  static const int kUserNameFieldNumber = 1;
  const ::std::string& user_name() const;
  void set_user_name(const ::std::string& value);
  #if LANG_CXX11
  void set_user_name(::std::string&& value);
  #endif
  void set_user_name(const char* value);
  void set_user_name(const char* value, size_t size);
  ::std::string* mutable_user_name();
  ::std::string* release_user_name();
  void set_allocated_user_name(::std::string* user_name);

  // string user_password = 2;
  void clear_user_password();
  static const int kUserPasswordFieldNumber = 2;
  const ::std::string& user_password() const;
  void set_user_password(const ::std::string& value);
  #if LANG_CXX11
  void set_user_password(::std::string&& value);
  #endif
  void set_user_password(const char* value);
  void set_user_password(const char* value, size_t size);
  ::std::string* mutable_user_password();
  ::std::string* release_user_password();
  void set_allocated_user_password(::std::string* user_password);

  // .youliao.pdu.base.UserStatusType user_status = 3;
  void clear_user_status();
  static const int kUserStatusFieldNumber = 3;
  ::youliao::pdu::base::UserStatusType user_status() const;
  void set_user_status(::youliao::pdu::base::UserStatusType value);

  // @@protoc_insertion_point(class_scope:youliao.pdu.login.UserLoginRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr user_name_;
  ::google::protobuf::internal::ArenaStringPtr user_password_;
  int user_status_;
  mutable int _cached_size_;
  friend struct ::protobuf_youliao_2elogin_2eproto::TableStruct;
  friend void ::protobuf_youliao_2elogin_2eproto::InitDefaultsUserLoginRequestImpl();
};
// -------------------------------------------------------------------

class UserLoginRespone : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:youliao.pdu.login.UserLoginRespone) */ {
 public:
  UserLoginRespone();
  virtual ~UserLoginRespone();

  UserLoginRespone(const UserLoginRespone& from);

  inline UserLoginRespone& operator=(const UserLoginRespone& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  UserLoginRespone(UserLoginRespone&& from) noexcept
    : UserLoginRespone() {
    *this = ::std::move(from);
  }

  inline UserLoginRespone& operator=(UserLoginRespone&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const UserLoginRespone& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const UserLoginRespone* internal_default_instance() {
    return reinterpret_cast<const UserLoginRespone*>(
               &_UserLoginRespone_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    3;

  void Swap(UserLoginRespone* other);
  friend void swap(UserLoginRespone& a, UserLoginRespone& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline UserLoginRespone* New() const PROTOBUF_FINAL { return New(NULL); }

  UserLoginRespone* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const UserLoginRespone& from);
  void MergeFrom(const UserLoginRespone& from);
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
  void InternalSwap(UserLoginRespone* other);
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

  // .youliao.pdu.base.UserInfo user_info = 2;
  bool has_user_info() const;
  void clear_user_info();
  static const int kUserInfoFieldNumber = 2;
  const ::youliao::pdu::base::UserInfo& user_info() const;
  ::youliao::pdu::base::UserInfo* release_user_info();
  ::youliao::pdu::base::UserInfo* mutable_user_info();
  void set_allocated_user_info(::youliao::pdu::base::UserInfo* user_info);

  // .youliao.pdu.base.ResultType result_code = 1;
  void clear_result_code();
  static const int kResultCodeFieldNumber = 1;
  ::youliao::pdu::base::ResultType result_code() const;
  void set_result_code(::youliao::pdu::base::ResultType value);

  // @@protoc_insertion_point(class_scope:youliao.pdu.login.UserLoginRespone)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::youliao::pdu::base::UserInfo* user_info_;
  int result_code_;
  mutable int _cached_size_;
  friend struct ::protobuf_youliao_2elogin_2eproto::TableStruct;
  friend void ::protobuf_youliao_2elogin_2eproto::InitDefaultsUserLoginResponeImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// MsgServerRequest

// -------------------------------------------------------------------

// MsgServerRespone

// .youliao.pdu.base.ResultType result_code = 1;
inline void MsgServerRespone::clear_result_code() {
  result_code_ = 0;
}
inline ::youliao::pdu::base::ResultType MsgServerRespone::result_code() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.login.MsgServerRespone.result_code)
  return static_cast< ::youliao::pdu::base::ResultType >(result_code_);
}
inline void MsgServerRespone::set_result_code(::youliao::pdu::base::ResultType value) {
  
  result_code_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.login.MsgServerRespone.result_code)
}

// string msg_server_ip = 2;
inline void MsgServerRespone::clear_msg_server_ip() {
  msg_server_ip_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& MsgServerRespone::msg_server_ip() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.login.MsgServerRespone.msg_server_ip)
  return msg_server_ip_.GetNoArena();
}
inline void MsgServerRespone::set_msg_server_ip(const ::std::string& value) {
  
  msg_server_ip_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:youliao.pdu.login.MsgServerRespone.msg_server_ip)
}
#if LANG_CXX11
inline void MsgServerRespone::set_msg_server_ip(::std::string&& value) {
  
  msg_server_ip_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:youliao.pdu.login.MsgServerRespone.msg_server_ip)
}
#endif
inline void MsgServerRespone::set_msg_server_ip(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  msg_server_ip_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:youliao.pdu.login.MsgServerRespone.msg_server_ip)
}
inline void MsgServerRespone::set_msg_server_ip(const char* value, size_t size) {
  
  msg_server_ip_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:youliao.pdu.login.MsgServerRespone.msg_server_ip)
}
inline ::std::string* MsgServerRespone::mutable_msg_server_ip() {
  
  // @@protoc_insertion_point(field_mutable:youliao.pdu.login.MsgServerRespone.msg_server_ip)
  return msg_server_ip_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* MsgServerRespone::release_msg_server_ip() {
  // @@protoc_insertion_point(field_release:youliao.pdu.login.MsgServerRespone.msg_server_ip)
  
  return msg_server_ip_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MsgServerRespone::set_allocated_msg_server_ip(::std::string* msg_server_ip) {
  if (msg_server_ip != NULL) {
    
  } else {
    
  }
  msg_server_ip_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), msg_server_ip);
  // @@protoc_insertion_point(field_set_allocated:youliao.pdu.login.MsgServerRespone.msg_server_ip)
}

// uint32 port = 3;
inline void MsgServerRespone::clear_port() {
  port_ = 0u;
}
inline ::google::protobuf::uint32 MsgServerRespone::port() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.login.MsgServerRespone.port)
  return port_;
}
inline void MsgServerRespone::set_port(::google::protobuf::uint32 value) {
  
  port_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.login.MsgServerRespone.port)
}

// -------------------------------------------------------------------

// UserLoginRequest

// string user_name = 1;
inline void UserLoginRequest::clear_user_name() {
  user_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& UserLoginRequest::user_name() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.login.UserLoginRequest.user_name)
  return user_name_.GetNoArena();
}
inline void UserLoginRequest::set_user_name(const ::std::string& value) {
  
  user_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:youliao.pdu.login.UserLoginRequest.user_name)
}
#if LANG_CXX11
inline void UserLoginRequest::set_user_name(::std::string&& value) {
  
  user_name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:youliao.pdu.login.UserLoginRequest.user_name)
}
#endif
inline void UserLoginRequest::set_user_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  user_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:youliao.pdu.login.UserLoginRequest.user_name)
}
inline void UserLoginRequest::set_user_name(const char* value, size_t size) {
  
  user_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:youliao.pdu.login.UserLoginRequest.user_name)
}
inline ::std::string* UserLoginRequest::mutable_user_name() {
  
  // @@protoc_insertion_point(field_mutable:youliao.pdu.login.UserLoginRequest.user_name)
  return user_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* UserLoginRequest::release_user_name() {
  // @@protoc_insertion_point(field_release:youliao.pdu.login.UserLoginRequest.user_name)
  
  return user_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserLoginRequest::set_allocated_user_name(::std::string* user_name) {
  if (user_name != NULL) {
    
  } else {
    
  }
  user_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), user_name);
  // @@protoc_insertion_point(field_set_allocated:youliao.pdu.login.UserLoginRequest.user_name)
}

// string user_password = 2;
inline void UserLoginRequest::clear_user_password() {
  user_password_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& UserLoginRequest::user_password() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.login.UserLoginRequest.user_password)
  return user_password_.GetNoArena();
}
inline void UserLoginRequest::set_user_password(const ::std::string& value) {
  
  user_password_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:youliao.pdu.login.UserLoginRequest.user_password)
}
#if LANG_CXX11
inline void UserLoginRequest::set_user_password(::std::string&& value) {
  
  user_password_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:youliao.pdu.login.UserLoginRequest.user_password)
}
#endif
inline void UserLoginRequest::set_user_password(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  user_password_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:youliao.pdu.login.UserLoginRequest.user_password)
}
inline void UserLoginRequest::set_user_password(const char* value, size_t size) {
  
  user_password_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:youliao.pdu.login.UserLoginRequest.user_password)
}
inline ::std::string* UserLoginRequest::mutable_user_password() {
  
  // @@protoc_insertion_point(field_mutable:youliao.pdu.login.UserLoginRequest.user_password)
  return user_password_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* UserLoginRequest::release_user_password() {
  // @@protoc_insertion_point(field_release:youliao.pdu.login.UserLoginRequest.user_password)
  
  return user_password_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserLoginRequest::set_allocated_user_password(::std::string* user_password) {
  if (user_password != NULL) {
    
  } else {
    
  }
  user_password_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), user_password);
  // @@protoc_insertion_point(field_set_allocated:youliao.pdu.login.UserLoginRequest.user_password)
}

// .youliao.pdu.base.UserStatusType user_status = 3;
inline void UserLoginRequest::clear_user_status() {
  user_status_ = 0;
}
inline ::youliao::pdu::base::UserStatusType UserLoginRequest::user_status() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.login.UserLoginRequest.user_status)
  return static_cast< ::youliao::pdu::base::UserStatusType >(user_status_);
}
inline void UserLoginRequest::set_user_status(::youliao::pdu::base::UserStatusType value) {
  
  user_status_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.login.UserLoginRequest.user_status)
}

// -------------------------------------------------------------------

// UserLoginRespone

// .youliao.pdu.base.ResultType result_code = 1;
inline void UserLoginRespone::clear_result_code() {
  result_code_ = 0;
}
inline ::youliao::pdu::base::ResultType UserLoginRespone::result_code() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.login.UserLoginRespone.result_code)
  return static_cast< ::youliao::pdu::base::ResultType >(result_code_);
}
inline void UserLoginRespone::set_result_code(::youliao::pdu::base::ResultType value) {
  
  result_code_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.login.UserLoginRespone.result_code)
}

// .youliao.pdu.base.UserInfo user_info = 2;
inline bool UserLoginRespone::has_user_info() const {
  return this != internal_default_instance() && user_info_ != NULL;
}
inline const ::youliao::pdu::base::UserInfo& UserLoginRespone::user_info() const {
  const ::youliao::pdu::base::UserInfo* p = user_info_;
  // @@protoc_insertion_point(field_get:youliao.pdu.login.UserLoginRespone.user_info)
  return p != NULL ? *p : *reinterpret_cast<const ::youliao::pdu::base::UserInfo*>(
      &::youliao::pdu::base::_UserInfo_default_instance_);
}
inline ::youliao::pdu::base::UserInfo* UserLoginRespone::release_user_info() {
  // @@protoc_insertion_point(field_release:youliao.pdu.login.UserLoginRespone.user_info)
  
  ::youliao::pdu::base::UserInfo* temp = user_info_;
  user_info_ = NULL;
  return temp;
}
inline ::youliao::pdu::base::UserInfo* UserLoginRespone::mutable_user_info() {
  
  if (user_info_ == NULL) {
    user_info_ = new ::youliao::pdu::base::UserInfo;
  }
  // @@protoc_insertion_point(field_mutable:youliao.pdu.login.UserLoginRespone.user_info)
  return user_info_;
}
inline void UserLoginRespone::set_allocated_user_info(::youliao::pdu::base::UserInfo* user_info) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete reinterpret_cast< ::google::protobuf::MessageLite*>(user_info_);
  }
  if (user_info) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      user_info = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, user_info, submessage_arena);
    }
    
  } else {
    
  }
  user_info_ = user_info;
  // @@protoc_insertion_point(field_set_allocated:youliao.pdu.login.UserLoginRespone.user_info)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace login
}  // namespace pdu
}  // namespace youliao

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_youliao_2elogin_2eproto__INCLUDED