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
  static const ::google::protobuf::internal::ParseTable schema[6];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
void InitDefaultsGetSessionsRequestImpl();
void InitDefaultsGetSessionsRequest();
void InitDefaultsGetSessionReponseImpl();
void InitDefaultsGetSessionReponse();
void InitDefaultsCreateNewSessionImpl();
void InitDefaultsCreateNewSession();
void InitDefaultsNewSessionResponeImpl();
void InitDefaultsNewSessionRespone();
void InitDefaultsDeleteSessionRequestImpl();
void InitDefaultsDeleteSessionRequest();
void InitDefaultsTopSessionRequestImpl();
void InitDefaultsTopSessionRequest();
inline void InitDefaults() {
  InitDefaultsGetSessionsRequest();
  InitDefaultsGetSessionReponse();
  InitDefaultsCreateNewSession();
  InitDefaultsNewSessionRespone();
  InitDefaultsDeleteSessionRequest();
  InitDefaultsTopSessionRequest();
}
}  // namespace protobuf_youliao_2esession_2eproto
namespace youliao {
namespace pdu {
namespace session {
class CreateNewSession;
class CreateNewSessionDefaultTypeInternal;
extern CreateNewSessionDefaultTypeInternal _CreateNewSession_default_instance_;
class DeleteSessionRequest;
class DeleteSessionRequestDefaultTypeInternal;
extern DeleteSessionRequestDefaultTypeInternal _DeleteSessionRequest_default_instance_;
class GetSessionReponse;
class GetSessionReponseDefaultTypeInternal;
extern GetSessionReponseDefaultTypeInternal _GetSessionReponse_default_instance_;
class GetSessionsRequest;
class GetSessionsRequestDefaultTypeInternal;
extern GetSessionsRequestDefaultTypeInternal _GetSessionsRequest_default_instance_;
class NewSessionRespone;
class NewSessionResponeDefaultTypeInternal;
extern NewSessionResponeDefaultTypeInternal _NewSessionRespone_default_instance_;
class TopSessionRequest;
class TopSessionRequestDefaultTypeInternal;
extern TopSessionRequestDefaultTypeInternal _TopSessionRequest_default_instance_;
}  // namespace session
}  // namespace pdu
}  // namespace youliao
namespace google {
namespace protobuf {
template<> ::youliao::pdu::session::CreateNewSession* Arena::Create< ::youliao::pdu::session::CreateNewSession>(Arena*);
template<> ::youliao::pdu::session::DeleteSessionRequest* Arena::Create< ::youliao::pdu::session::DeleteSessionRequest>(Arena*);
template<> ::youliao::pdu::session::GetSessionReponse* Arena::Create< ::youliao::pdu::session::GetSessionReponse>(Arena*);
template<> ::youliao::pdu::session::GetSessionsRequest* Arena::Create< ::youliao::pdu::session::GetSessionsRequest>(Arena*);
template<> ::youliao::pdu::session::NewSessionRespone* Arena::Create< ::youliao::pdu::session::NewSessionRespone>(Arena*);
template<> ::youliao::pdu::session::TopSessionRequest* Arena::Create< ::youliao::pdu::session::TopSessionRequest>(Arena*);
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
// -------------------------------------------------------------------

class CreateNewSession : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:youliao.pdu.session.CreateNewSession) */ {
 public:
  CreateNewSession();
  virtual ~CreateNewSession();

  CreateNewSession(const CreateNewSession& from);

  inline CreateNewSession& operator=(const CreateNewSession& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  CreateNewSession(CreateNewSession&& from) noexcept
    : CreateNewSession() {
    *this = ::std::move(from);
  }

  inline CreateNewSession& operator=(CreateNewSession&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const CreateNewSession& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const CreateNewSession* internal_default_instance() {
    return reinterpret_cast<const CreateNewSession*>(
               &_CreateNewSession_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    2;

  void Swap(CreateNewSession* other);
  friend void swap(CreateNewSession& a, CreateNewSession& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline CreateNewSession* New() const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<CreateNewSession>(NULL);
  }

  CreateNewSession* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<CreateNewSession>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const CreateNewSession& from);
  void MergeFrom(const CreateNewSession& from);
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
  void InternalSwap(CreateNewSession* other);
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

  // uint32 user_id = 1;
  void clear_user_id();
  static const int kUserIdFieldNumber = 1;
  ::google::protobuf::uint32 user_id() const;
  void set_user_id(::google::protobuf::uint32 value);

  // uint32 other_id = 2;
  void clear_other_id();
  static const int kOtherIdFieldNumber = 2;
  ::google::protobuf::uint32 other_id() const;
  void set_other_id(::google::protobuf::uint32 value);

  // .youliao.pdu.base.SessionType session_type = 3;
  void clear_session_type();
  static const int kSessionTypeFieldNumber = 3;
  ::youliao::pdu::base::SessionType session_type() const;
  void set_session_type(::youliao::pdu::base::SessionType value);

  // @@protoc_insertion_point(class_scope:youliao.pdu.session.CreateNewSession)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 user_id_;
  ::google::protobuf::uint32 other_id_;
  int session_type_;
  mutable int _cached_size_;
  friend struct ::protobuf_youliao_2esession_2eproto::TableStruct;
  friend void ::protobuf_youliao_2esession_2eproto::InitDefaultsCreateNewSessionImpl();
};
// -------------------------------------------------------------------

class NewSessionRespone : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:youliao.pdu.session.NewSessionRespone) */ {
 public:
  NewSessionRespone();
  virtual ~NewSessionRespone();

  NewSessionRespone(const NewSessionRespone& from);

  inline NewSessionRespone& operator=(const NewSessionRespone& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  NewSessionRespone(NewSessionRespone&& from) noexcept
    : NewSessionRespone() {
    *this = ::std::move(from);
  }

  inline NewSessionRespone& operator=(NewSessionRespone&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const NewSessionRespone& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const NewSessionRespone* internal_default_instance() {
    return reinterpret_cast<const NewSessionRespone*>(
               &_NewSessionRespone_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    3;

  void Swap(NewSessionRespone* other);
  friend void swap(NewSessionRespone& a, NewSessionRespone& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline NewSessionRespone* New() const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<NewSessionRespone>(NULL);
  }

  NewSessionRespone* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<NewSessionRespone>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const NewSessionRespone& from);
  void MergeFrom(const NewSessionRespone& from);
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
  void InternalSwap(NewSessionRespone* other);
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

  // .youliao.pdu.base.SessionInfo session = 2;
  bool has_session() const;
  void clear_session();
  static const int kSessionFieldNumber = 2;
  const ::youliao::pdu::base::SessionInfo& session() const;
  ::youliao::pdu::base::SessionInfo* release_session();
  ::youliao::pdu::base::SessionInfo* mutable_session();
  void set_allocated_session(::youliao::pdu::base::SessionInfo* session);

  // uint32 user_id = 1;
  void clear_user_id();
  static const int kUserIdFieldNumber = 1;
  ::google::protobuf::uint32 user_id() const;
  void set_user_id(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:youliao.pdu.session.NewSessionRespone)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::youliao::pdu::base::SessionInfo* session_;
  ::google::protobuf::uint32 user_id_;
  mutable int _cached_size_;
  friend struct ::protobuf_youliao_2esession_2eproto::TableStruct;
  friend void ::protobuf_youliao_2esession_2eproto::InitDefaultsNewSessionResponeImpl();
};
// -------------------------------------------------------------------

class DeleteSessionRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:youliao.pdu.session.DeleteSessionRequest) */ {
 public:
  DeleteSessionRequest();
  virtual ~DeleteSessionRequest();

  DeleteSessionRequest(const DeleteSessionRequest& from);

  inline DeleteSessionRequest& operator=(const DeleteSessionRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  DeleteSessionRequest(DeleteSessionRequest&& from) noexcept
    : DeleteSessionRequest() {
    *this = ::std::move(from);
  }

  inline DeleteSessionRequest& operator=(DeleteSessionRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const DeleteSessionRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const DeleteSessionRequest* internal_default_instance() {
    return reinterpret_cast<const DeleteSessionRequest*>(
               &_DeleteSessionRequest_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    4;

  void Swap(DeleteSessionRequest* other);
  friend void swap(DeleteSessionRequest& a, DeleteSessionRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline DeleteSessionRequest* New() const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<DeleteSessionRequest>(NULL);
  }

  DeleteSessionRequest* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<DeleteSessionRequest>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const DeleteSessionRequest& from);
  void MergeFrom(const DeleteSessionRequest& from);
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
  void InternalSwap(DeleteSessionRequest* other);
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

  // uint32 user_id = 1;
  void clear_user_id();
  static const int kUserIdFieldNumber = 1;
  ::google::protobuf::uint32 user_id() const;
  void set_user_id(::google::protobuf::uint32 value);

  // uint32 session_id = 2;
  void clear_session_id();
  static const int kSessionIdFieldNumber = 2;
  ::google::protobuf::uint32 session_id() const;
  void set_session_id(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:youliao.pdu.session.DeleteSessionRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 user_id_;
  ::google::protobuf::uint32 session_id_;
  mutable int _cached_size_;
  friend struct ::protobuf_youliao_2esession_2eproto::TableStruct;
  friend void ::protobuf_youliao_2esession_2eproto::InitDefaultsDeleteSessionRequestImpl();
};
// -------------------------------------------------------------------

class TopSessionRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:youliao.pdu.session.TopSessionRequest) */ {
 public:
  TopSessionRequest();
  virtual ~TopSessionRequest();

  TopSessionRequest(const TopSessionRequest& from);

  inline TopSessionRequest& operator=(const TopSessionRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  TopSessionRequest(TopSessionRequest&& from) noexcept
    : TopSessionRequest() {
    *this = ::std::move(from);
  }

  inline TopSessionRequest& operator=(TopSessionRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const TopSessionRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const TopSessionRequest* internal_default_instance() {
    return reinterpret_cast<const TopSessionRequest*>(
               &_TopSessionRequest_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    5;

  void Swap(TopSessionRequest* other);
  friend void swap(TopSessionRequest& a, TopSessionRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline TopSessionRequest* New() const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<TopSessionRequest>(NULL);
  }

  TopSessionRequest* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<TopSessionRequest>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const TopSessionRequest& from);
  void MergeFrom(const TopSessionRequest& from);
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
  void InternalSwap(TopSessionRequest* other);
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

  // uint32 user_id = 1;
  void clear_user_id();
  static const int kUserIdFieldNumber = 1;
  ::google::protobuf::uint32 user_id() const;
  void set_user_id(::google::protobuf::uint32 value);

  // uint32 session_id = 2;
  void clear_session_id();
  static const int kSessionIdFieldNumber = 2;
  ::google::protobuf::uint32 session_id() const;
  void set_session_id(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:youliao.pdu.session.TopSessionRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 user_id_;
  ::google::protobuf::uint32 session_id_;
  mutable int _cached_size_;
  friend struct ::protobuf_youliao_2esession_2eproto::TableStruct;
  friend void ::protobuf_youliao_2esession_2eproto::InitDefaultsTopSessionRequestImpl();
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

// -------------------------------------------------------------------

// CreateNewSession

// uint32 user_id = 1;
inline void CreateNewSession::clear_user_id() {
  user_id_ = 0u;
}
inline ::google::protobuf::uint32 CreateNewSession::user_id() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.session.CreateNewSession.user_id)
  return user_id_;
}
inline void CreateNewSession::set_user_id(::google::protobuf::uint32 value) {
  
  user_id_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.session.CreateNewSession.user_id)
}

// uint32 other_id = 2;
inline void CreateNewSession::clear_other_id() {
  other_id_ = 0u;
}
inline ::google::protobuf::uint32 CreateNewSession::other_id() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.session.CreateNewSession.other_id)
  return other_id_;
}
inline void CreateNewSession::set_other_id(::google::protobuf::uint32 value) {
  
  other_id_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.session.CreateNewSession.other_id)
}

// .youliao.pdu.base.SessionType session_type = 3;
inline void CreateNewSession::clear_session_type() {
  session_type_ = 0;
}
inline ::youliao::pdu::base::SessionType CreateNewSession::session_type() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.session.CreateNewSession.session_type)
  return static_cast< ::youliao::pdu::base::SessionType >(session_type_);
}
inline void CreateNewSession::set_session_type(::youliao::pdu::base::SessionType value) {
  
  session_type_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.session.CreateNewSession.session_type)
}

// -------------------------------------------------------------------

// NewSessionRespone

// uint32 user_id = 1;
inline void NewSessionRespone::clear_user_id() {
  user_id_ = 0u;
}
inline ::google::protobuf::uint32 NewSessionRespone::user_id() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.session.NewSessionRespone.user_id)
  return user_id_;
}
inline void NewSessionRespone::set_user_id(::google::protobuf::uint32 value) {
  
  user_id_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.session.NewSessionRespone.user_id)
}

// .youliao.pdu.base.SessionInfo session = 2;
inline bool NewSessionRespone::has_session() const {
  return this != internal_default_instance() && session_ != NULL;
}
inline const ::youliao::pdu::base::SessionInfo& NewSessionRespone::session() const {
  const ::youliao::pdu::base::SessionInfo* p = session_;
  // @@protoc_insertion_point(field_get:youliao.pdu.session.NewSessionRespone.session)
  return p != NULL ? *p : *reinterpret_cast<const ::youliao::pdu::base::SessionInfo*>(
      &::youliao::pdu::base::_SessionInfo_default_instance_);
}
inline ::youliao::pdu::base::SessionInfo* NewSessionRespone::release_session() {
  // @@protoc_insertion_point(field_release:youliao.pdu.session.NewSessionRespone.session)
  
  ::youliao::pdu::base::SessionInfo* temp = session_;
  session_ = NULL;
  return temp;
}
inline ::youliao::pdu::base::SessionInfo* NewSessionRespone::mutable_session() {
  
  if (session_ == NULL) {
    session_ = ::google::protobuf::Arena::Create< ::youliao::pdu::base::SessionInfo >(
        GetArenaNoVirtual());
  }
  // @@protoc_insertion_point(field_mutable:youliao.pdu.session.NewSessionRespone.session)
  return session_;
}
inline void NewSessionRespone::set_allocated_session(::youliao::pdu::base::SessionInfo* session) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete reinterpret_cast< ::google::protobuf::MessageLite*>(session_);
  }
  if (session) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      session = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, session, submessage_arena);
    }
    
  } else {
    
  }
  session_ = session;
  // @@protoc_insertion_point(field_set_allocated:youliao.pdu.session.NewSessionRespone.session)
}

// -------------------------------------------------------------------

// DeleteSessionRequest

// uint32 user_id = 1;
inline void DeleteSessionRequest::clear_user_id() {
  user_id_ = 0u;
}
inline ::google::protobuf::uint32 DeleteSessionRequest::user_id() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.session.DeleteSessionRequest.user_id)
  return user_id_;
}
inline void DeleteSessionRequest::set_user_id(::google::protobuf::uint32 value) {
  
  user_id_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.session.DeleteSessionRequest.user_id)
}

// uint32 session_id = 2;
inline void DeleteSessionRequest::clear_session_id() {
  session_id_ = 0u;
}
inline ::google::protobuf::uint32 DeleteSessionRequest::session_id() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.session.DeleteSessionRequest.session_id)
  return session_id_;
}
inline void DeleteSessionRequest::set_session_id(::google::protobuf::uint32 value) {
  
  session_id_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.session.DeleteSessionRequest.session_id)
}

// -------------------------------------------------------------------

// TopSessionRequest

// uint32 user_id = 1;
inline void TopSessionRequest::clear_user_id() {
  user_id_ = 0u;
}
inline ::google::protobuf::uint32 TopSessionRequest::user_id() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.session.TopSessionRequest.user_id)
  return user_id_;
}
inline void TopSessionRequest::set_user_id(::google::protobuf::uint32 value) {
  
  user_id_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.session.TopSessionRequest.user_id)
}

// uint32 session_id = 2;
inline void TopSessionRequest::clear_session_id() {
  session_id_ = 0u;
}
inline ::google::protobuf::uint32 TopSessionRequest::session_id() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.session.TopSessionRequest.session_id)
  return session_id_;
}
inline void TopSessionRequest::set_session_id(::google::protobuf::uint32 value) {
  
  session_id_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.session.TopSessionRequest.session_id)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace session
}  // namespace pdu
}  // namespace youliao

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_youliao_2esession_2eproto_INCLUDED
