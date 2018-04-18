// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: youliao.session.proto

#ifndef PROTOBUF_youliao_2esession_2eproto_INCLUDED
#define PROTOBUF_youliao_2esession_2eproto_INCLUDED

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

namespace protobuf_youliao_2esession_2eproto {
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
void InitDefaultsGetSessionsRequestImpl();
void InitDefaultsGetSessionsRequest();
void InitDefaultsGetSessionReponseImpl();
void InitDefaultsGetSessionReponse();
inline void InitDefaults() {
  InitDefaultsGetSessionsRequest();
  InitDefaultsGetSessionReponse();
}
}  // namespace protobuf_youliao_2esession_2eproto
namespace youliao {
namespace pdu {
namespace session {
class GetSessionReponse;
class GetSessionReponseDefaultTypeInternal;
extern GetSessionReponseDefaultTypeInternal _GetSessionReponse_default_instance_;
class GetSessionsRequest;
class GetSessionsRequestDefaultTypeInternal;
extern GetSessionsRequestDefaultTypeInternal _GetSessionsRequest_default_instance_;
}  // namespace session
}  // namespace pdu
}  // namespace youliao
namespace google {
namespace protobuf {
template<> ::youliao::pdu::session::GetSessionReponse* Arena::Create< ::youliao::pdu::session::GetSessionReponse>(Arena*);
template<> ::youliao::pdu::session::GetSessionsRequest* Arena::Create< ::youliao::pdu::session::GetSessionsRequest>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace youliao {
namespace pdu {
namespace session {

// ===================================================================

class GetSessionsRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:youliao.pdu.session.GetSessionsRequest) */ {
 public:
  GetSessionsRequest();
  virtual ~GetSessionsRequest();

  GetSessionsRequest(const GetSessionsRequest& from);

  inline GetSessionsRequest& operator=(const GetSessionsRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  GetSessionsRequest(GetSessionsRequest&& from) noexcept
    : GetSessionsRequest() {
    *this = ::std::move(from);
  }

  inline GetSessionsRequest& operator=(GetSessionsRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const GetSessionsRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const GetSessionsRequest* internal_default_instance() {
    return reinterpret_cast<const GetSessionsRequest*>(
               &_GetSessionsRequest_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(GetSessionsRequest* other);
  friend void swap(GetSessionsRequest& a, GetSessionsRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline GetSessionsRequest* New() const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<GetSessionsRequest>(NULL);
  }

  GetSessionsRequest* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<GetSessionsRequest>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const GetSessionsRequest& from);
  void MergeFrom(const GetSessionsRequest& from);
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
  void InternalSwap(GetSessionsRequest* other);
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

  // uint32 userId = 1;
  void clear_userid();
  static const int kUserIdFieldNumber = 1;
  ::google::protobuf::uint32 userid() const;
  void set_userid(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:youliao.pdu.session.GetSessionsRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 userid_;
  mutable int _cached_size_;
  friend struct ::protobuf_youliao_2esession_2eproto::TableStruct;
  friend void ::protobuf_youliao_2esession_2eproto::InitDefaultsGetSessionsRequestImpl();
};
// -------------------------------------------------------------------

class GetSessionReponse : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:youliao.pdu.session.GetSessionReponse) */ {
 public:
  GetSessionReponse();
  virtual ~GetSessionReponse();

  GetSessionReponse(const GetSessionReponse& from);

  inline GetSessionReponse& operator=(const GetSessionReponse& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  GetSessionReponse(GetSessionReponse&& from) noexcept
    : GetSessionReponse() {
    *this = ::std::move(from);
  }

  inline GetSessionReponse& operator=(GetSessionReponse&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const GetSessionReponse& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const GetSessionReponse* internal_default_instance() {
    return reinterpret_cast<const GetSessionReponse*>(
               &_GetSessionReponse_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(GetSessionReponse* other);
  friend void swap(GetSessionReponse& a, GetSessionReponse& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline GetSessionReponse* New() const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<GetSessionReponse>(NULL);
  }

  GetSessionReponse* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<GetSessionReponse>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const GetSessionReponse& from);
  void MergeFrom(const GetSessionReponse& from);
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
  void InternalSwap(GetSessionReponse* other);
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

  // repeated .youliao.pdu.base.SessionInfo sessions = 2;
  int sessions_size() const;
  void clear_sessions();
  static const int kSessionsFieldNumber = 2;
  ::youliao::pdu::base::SessionInfo* mutable_sessions(int index);
  ::google::protobuf::RepeatedPtrField< ::youliao::pdu::base::SessionInfo >*
      mutable_sessions();
  const ::youliao::pdu::base::SessionInfo& sessions(int index) const;
  ::youliao::pdu::base::SessionInfo* add_sessions();
  const ::google::protobuf::RepeatedPtrField< ::youliao::pdu::base::SessionInfo >&
      sessions() const;

  // uint32 userId = 1;
  void clear_userid();
  static const int kUserIdFieldNumber = 1;
  ::google::protobuf::uint32 userid() const;
  void set_userid(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:youliao.pdu.session.GetSessionReponse)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::youliao::pdu::base::SessionInfo > sessions_;
  ::google::protobuf::uint32 userid_;
  mutable int _cached_size_;
  friend struct ::protobuf_youliao_2esession_2eproto::TableStruct;
  friend void ::protobuf_youliao_2esession_2eproto::InitDefaultsGetSessionReponseImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// GetSessionsRequest

// uint32 userId = 1;
inline void GetSessionsRequest::clear_userid() {
  userid_ = 0u;
}
inline ::google::protobuf::uint32 GetSessionsRequest::userid() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.session.GetSessionsRequest.userId)
  return userid_;
}
inline void GetSessionsRequest::set_userid(::google::protobuf::uint32 value) {
  
  userid_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.session.GetSessionsRequest.userId)
}

// -------------------------------------------------------------------

// GetSessionReponse

// uint32 userId = 1;
inline void GetSessionReponse::clear_userid() {
  userid_ = 0u;
}
inline ::google::protobuf::uint32 GetSessionReponse::userid() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.session.GetSessionReponse.userId)
  return userid_;
}
inline void GetSessionReponse::set_userid(::google::protobuf::uint32 value) {
  
  userid_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.session.GetSessionReponse.userId)
}

// repeated .youliao.pdu.base.SessionInfo sessions = 2;
inline int GetSessionReponse::sessions_size() const {
  return sessions_.size();
}
inline ::youliao::pdu::base::SessionInfo* GetSessionReponse::mutable_sessions(int index) {
  // @@protoc_insertion_point(field_mutable:youliao.pdu.session.GetSessionReponse.sessions)
  return sessions_.Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField< ::youliao::pdu::base::SessionInfo >*
GetSessionReponse::mutable_sessions() {
  // @@protoc_insertion_point(field_mutable_list:youliao.pdu.session.GetSessionReponse.sessions)
  return &sessions_;
}
inline const ::youliao::pdu::base::SessionInfo& GetSessionReponse::sessions(int index) const {
  // @@protoc_insertion_point(field_get:youliao.pdu.session.GetSessionReponse.sessions)
  return sessions_.Get(index);
}
inline ::youliao::pdu::base::SessionInfo* GetSessionReponse::add_sessions() {
  // @@protoc_insertion_point(field_add:youliao.pdu.session.GetSessionReponse.sessions)
  return sessions_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::youliao::pdu::base::SessionInfo >&
GetSessionReponse::sessions() const {
  // @@protoc_insertion_point(field_list:youliao.pdu.session.GetSessionReponse.sessions)
  return sessions_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace session
}  // namespace pdu
}  // namespace youliao

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_youliao_2esession_2eproto_INCLUDED
