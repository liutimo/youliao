// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: youliao.group.proto

#ifndef PROTOBUF_youliao_2egroup_2eproto_INCLUDED
#define PROTOBUF_youliao_2egroup_2eproto_INCLUDED

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

namespace protobuf_youliao_2egroup_2eproto {
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
void InitDefaultsGroupCreateRequestImpl();
void InitDefaultsGroupCreateRequest();
void InitDefaultsGroupCreateResponeImpl();
void InitDefaultsGroupCreateRespone();
void InitDefaultsGetGroupListRequestImpl();
void InitDefaultsGetGroupListRequest();
void InitDefaultsGetGroupListResponeImpl();
void InitDefaultsGetGroupListRespone();
inline void InitDefaults() {
  InitDefaultsGroupCreateRequest();
  InitDefaultsGroupCreateRespone();
  InitDefaultsGetGroupListRequest();
  InitDefaultsGetGroupListRespone();
}
}  // namespace protobuf_youliao_2egroup_2eproto
namespace youliao {
namespace pdu {
namespace group {
class GetGroupListRequest;
class GetGroupListRequestDefaultTypeInternal;
extern GetGroupListRequestDefaultTypeInternal _GetGroupListRequest_default_instance_;
class GetGroupListRespone;
class GetGroupListResponeDefaultTypeInternal;
extern GetGroupListResponeDefaultTypeInternal _GetGroupListRespone_default_instance_;
class GroupCreateRequest;
class GroupCreateRequestDefaultTypeInternal;
extern GroupCreateRequestDefaultTypeInternal _GroupCreateRequest_default_instance_;
class GroupCreateRespone;
class GroupCreateResponeDefaultTypeInternal;
extern GroupCreateResponeDefaultTypeInternal _GroupCreateRespone_default_instance_;
}  // namespace group
}  // namespace pdu
}  // namespace youliao
namespace google {
namespace protobuf {
template<> ::youliao::pdu::group::GetGroupListRequest* Arena::Create< ::youliao::pdu::group::GetGroupListRequest>(Arena*);
template<> ::youliao::pdu::group::GetGroupListRespone* Arena::Create< ::youliao::pdu::group::GetGroupListRespone>(Arena*);
template<> ::youliao::pdu::group::GroupCreateRequest* Arena::Create< ::youliao::pdu::group::GroupCreateRequest>(Arena*);
template<> ::youliao::pdu::group::GroupCreateRespone* Arena::Create< ::youliao::pdu::group::GroupCreateRespone>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace youliao {
namespace pdu {
namespace group {

// ===================================================================

class GroupCreateRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:youliao.pdu.group.GroupCreateRequest) */ {
 public:
  GroupCreateRequest();
  virtual ~GroupCreateRequest();

  GroupCreateRequest(const GroupCreateRequest& from);

  inline GroupCreateRequest& operator=(const GroupCreateRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  GroupCreateRequest(GroupCreateRequest&& from) noexcept
    : GroupCreateRequest() {
    *this = ::std::move(from);
  }

  inline GroupCreateRequest& operator=(GroupCreateRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const GroupCreateRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const GroupCreateRequest* internal_default_instance() {
    return reinterpret_cast<const GroupCreateRequest*>(
               &_GroupCreateRequest_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(GroupCreateRequest* other);
  friend void swap(GroupCreateRequest& a, GroupCreateRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline GroupCreateRequest* New() const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<GroupCreateRequest>(NULL);
  }

  GroupCreateRequest* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<GroupCreateRequest>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const GroupCreateRequest& from);
  void MergeFrom(const GroupCreateRequest& from);
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
  void InternalSwap(GroupCreateRequest* other);
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

  // repeated uint32 member_ids = 6;
  int member_ids_size() const;
  void clear_member_ids();
  static const int kMemberIdsFieldNumber = 6;
  ::google::protobuf::uint32 member_ids(int index) const;
  void set_member_ids(int index, ::google::protobuf::uint32 value);
  void add_member_ids(::google::protobuf::uint32 value);
  const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      member_ids() const;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_member_ids();

  // string group_name = 2;
  void clear_group_name();
  static const int kGroupNameFieldNumber = 2;
  const ::std::string& group_name() const;
  void set_group_name(const ::std::string& value);
  #if LANG_CXX11
  void set_group_name(::std::string&& value);
  #endif
  void set_group_name(const char* value);
  void set_group_name(const char* value, size_t size);
  ::std::string* mutable_group_name();
  ::std::string* release_group_name();
  void set_allocated_group_name(::std::string* group_name);

  // string group_head = 3;
  void clear_group_head();
  static const int kGroupHeadFieldNumber = 3;
  const ::std::string& group_head() const;
  void set_group_head(const ::std::string& value);
  #if LANG_CXX11
  void set_group_head(::std::string&& value);
  #endif
  void set_group_head(const char* value);
  void set_group_head(const char* value, size_t size);
  ::std::string* mutable_group_head();
  ::std::string* release_group_head();
  void set_allocated_group_head(::std::string* group_head);

  // uint32 user_id = 1;
  void clear_user_id();
  static const int kUserIdFieldNumber = 1;
  ::google::protobuf::uint32 user_id() const;
  void set_user_id(::google::protobuf::uint32 value);

  // .youliao.pdu.base.GroupType group_type = 4;
  void clear_group_type();
  static const int kGroupTypeFieldNumber = 4;
  ::youliao::pdu::base::GroupType group_type() const;
  void set_group_type(::youliao::pdu::base::GroupType value);

  // .youliao.pdu.base.GroupVerifyType group_verify_type = 5;
  void clear_group_verify_type();
  static const int kGroupVerifyTypeFieldNumber = 5;
  ::youliao::pdu::base::GroupVerifyType group_verify_type() const;
  void set_group_verify_type(::youliao::pdu::base::GroupVerifyType value);

  // uint32 group_max_members = 7;
  void clear_group_max_members();
  static const int kGroupMaxMembersFieldNumber = 7;
  ::google::protobuf::uint32 group_max_members() const;
  void set_group_max_members(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:youliao.pdu.group.GroupCreateRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > member_ids_;
  mutable int _member_ids_cached_byte_size_;
  ::google::protobuf::internal::ArenaStringPtr group_name_;
  ::google::protobuf::internal::ArenaStringPtr group_head_;
  ::google::protobuf::uint32 user_id_;
  int group_type_;
  int group_verify_type_;
  ::google::protobuf::uint32 group_max_members_;
  mutable int _cached_size_;
  friend struct ::protobuf_youliao_2egroup_2eproto::TableStruct;
  friend void ::protobuf_youliao_2egroup_2eproto::InitDefaultsGroupCreateRequestImpl();
};
// -------------------------------------------------------------------

class GroupCreateRespone : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:youliao.pdu.group.GroupCreateRespone) */ {
 public:
  GroupCreateRespone();
  virtual ~GroupCreateRespone();

  GroupCreateRespone(const GroupCreateRespone& from);

  inline GroupCreateRespone& operator=(const GroupCreateRespone& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  GroupCreateRespone(GroupCreateRespone&& from) noexcept
    : GroupCreateRespone() {
    *this = ::std::move(from);
  }

  inline GroupCreateRespone& operator=(GroupCreateRespone&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const GroupCreateRespone& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const GroupCreateRespone* internal_default_instance() {
    return reinterpret_cast<const GroupCreateRespone*>(
               &_GroupCreateRespone_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(GroupCreateRespone* other);
  friend void swap(GroupCreateRespone& a, GroupCreateRespone& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline GroupCreateRespone* New() const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<GroupCreateRespone>(NULL);
  }

  GroupCreateRespone* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<GroupCreateRespone>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const GroupCreateRespone& from);
  void MergeFrom(const GroupCreateRespone& from);
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
  void InternalSwap(GroupCreateRespone* other);
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

  // .youliao.pdu.base.GroupInfo group_info = 3;
  bool has_group_info() const;
  void clear_group_info();
  static const int kGroupInfoFieldNumber = 3;
  const ::youliao::pdu::base::GroupInfo& group_info() const;
  ::youliao::pdu::base::GroupInfo* release_group_info();
  ::youliao::pdu::base::GroupInfo* mutable_group_info();
  void set_allocated_group_info(::youliao::pdu::base::GroupInfo* group_info);

  // uint32 user_id = 1;
  void clear_user_id();
  static const int kUserIdFieldNumber = 1;
  ::google::protobuf::uint32 user_id() const;
  void set_user_id(::google::protobuf::uint32 value);

  // uint32 result_code = 2;
  void clear_result_code();
  static const int kResultCodeFieldNumber = 2;
  ::google::protobuf::uint32 result_code() const;
  void set_result_code(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:youliao.pdu.group.GroupCreateRespone)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::youliao::pdu::base::GroupInfo* group_info_;
  ::google::protobuf::uint32 user_id_;
  ::google::protobuf::uint32 result_code_;
  mutable int _cached_size_;
  friend struct ::protobuf_youliao_2egroup_2eproto::TableStruct;
  friend void ::protobuf_youliao_2egroup_2eproto::InitDefaultsGroupCreateResponeImpl();
};
// -------------------------------------------------------------------

class GetGroupListRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:youliao.pdu.group.GetGroupListRequest) */ {
 public:
  GetGroupListRequest();
  virtual ~GetGroupListRequest();

  GetGroupListRequest(const GetGroupListRequest& from);

  inline GetGroupListRequest& operator=(const GetGroupListRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  GetGroupListRequest(GetGroupListRequest&& from) noexcept
    : GetGroupListRequest() {
    *this = ::std::move(from);
  }

  inline GetGroupListRequest& operator=(GetGroupListRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const GetGroupListRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const GetGroupListRequest* internal_default_instance() {
    return reinterpret_cast<const GetGroupListRequest*>(
               &_GetGroupListRequest_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    2;

  void Swap(GetGroupListRequest* other);
  friend void swap(GetGroupListRequest& a, GetGroupListRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline GetGroupListRequest* New() const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<GetGroupListRequest>(NULL);
  }

  GetGroupListRequest* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<GetGroupListRequest>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const GetGroupListRequest& from);
  void MergeFrom(const GetGroupListRequest& from);
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
  void InternalSwap(GetGroupListRequest* other);
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

  // @@protoc_insertion_point(class_scope:youliao.pdu.group.GetGroupListRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 user_id_;
  mutable int _cached_size_;
  friend struct ::protobuf_youliao_2egroup_2eproto::TableStruct;
  friend void ::protobuf_youliao_2egroup_2eproto::InitDefaultsGetGroupListRequestImpl();
};
// -------------------------------------------------------------------

class GetGroupListRespone : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:youliao.pdu.group.GetGroupListRespone) */ {
 public:
  GetGroupListRespone();
  virtual ~GetGroupListRespone();

  GetGroupListRespone(const GetGroupListRespone& from);

  inline GetGroupListRespone& operator=(const GetGroupListRespone& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  GetGroupListRespone(GetGroupListRespone&& from) noexcept
    : GetGroupListRespone() {
    *this = ::std::move(from);
  }

  inline GetGroupListRespone& operator=(GetGroupListRespone&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const GetGroupListRespone& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const GetGroupListRespone* internal_default_instance() {
    return reinterpret_cast<const GetGroupListRespone*>(
               &_GetGroupListRespone_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    3;

  void Swap(GetGroupListRespone* other);
  friend void swap(GetGroupListRespone& a, GetGroupListRespone& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline GetGroupListRespone* New() const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<GetGroupListRespone>(NULL);
  }

  GetGroupListRespone* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<GetGroupListRespone>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const GetGroupListRespone& from);
  void MergeFrom(const GetGroupListRespone& from);
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
  void InternalSwap(GetGroupListRespone* other);
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

  // repeated .youliao.pdu.base.GroupInfo group_info = 2;
  int group_info_size() const;
  void clear_group_info();
  static const int kGroupInfoFieldNumber = 2;
  ::youliao::pdu::base::GroupInfo* mutable_group_info(int index);
  ::google::protobuf::RepeatedPtrField< ::youliao::pdu::base::GroupInfo >*
      mutable_group_info();
  const ::youliao::pdu::base::GroupInfo& group_info(int index) const;
  ::youliao::pdu::base::GroupInfo* add_group_info();
  const ::google::protobuf::RepeatedPtrField< ::youliao::pdu::base::GroupInfo >&
      group_info() const;

  // uint32 user_id = 1;
  void clear_user_id();
  static const int kUserIdFieldNumber = 1;
  ::google::protobuf::uint32 user_id() const;
  void set_user_id(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:youliao.pdu.group.GetGroupListRespone)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::youliao::pdu::base::GroupInfo > group_info_;
  ::google::protobuf::uint32 user_id_;
  mutable int _cached_size_;
  friend struct ::protobuf_youliao_2egroup_2eproto::TableStruct;
  friend void ::protobuf_youliao_2egroup_2eproto::InitDefaultsGetGroupListResponeImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// GroupCreateRequest

// uint32 user_id = 1;
inline void GroupCreateRequest::clear_user_id() {
  user_id_ = 0u;
}
inline ::google::protobuf::uint32 GroupCreateRequest::user_id() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.group.GroupCreateRequest.user_id)
  return user_id_;
}
inline void GroupCreateRequest::set_user_id(::google::protobuf::uint32 value) {
  
  user_id_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.group.GroupCreateRequest.user_id)
}

// string group_name = 2;
inline void GroupCreateRequest::clear_group_name() {
  group_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& GroupCreateRequest::group_name() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.group.GroupCreateRequest.group_name)
  return group_name_.GetNoArena();
}
inline void GroupCreateRequest::set_group_name(const ::std::string& value) {
  
  group_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:youliao.pdu.group.GroupCreateRequest.group_name)
}
#if LANG_CXX11
inline void GroupCreateRequest::set_group_name(::std::string&& value) {
  
  group_name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:youliao.pdu.group.GroupCreateRequest.group_name)
}
#endif
inline void GroupCreateRequest::set_group_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  group_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:youliao.pdu.group.GroupCreateRequest.group_name)
}
inline void GroupCreateRequest::set_group_name(const char* value, size_t size) {
  
  group_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:youliao.pdu.group.GroupCreateRequest.group_name)
}
inline ::std::string* GroupCreateRequest::mutable_group_name() {
  
  // @@protoc_insertion_point(field_mutable:youliao.pdu.group.GroupCreateRequest.group_name)
  return group_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* GroupCreateRequest::release_group_name() {
  // @@protoc_insertion_point(field_release:youliao.pdu.group.GroupCreateRequest.group_name)
  
  return group_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void GroupCreateRequest::set_allocated_group_name(::std::string* group_name) {
  if (group_name != NULL) {
    
  } else {
    
  }
  group_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), group_name);
  // @@protoc_insertion_point(field_set_allocated:youliao.pdu.group.GroupCreateRequest.group_name)
}

// string group_head = 3;
inline void GroupCreateRequest::clear_group_head() {
  group_head_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& GroupCreateRequest::group_head() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.group.GroupCreateRequest.group_head)
  return group_head_.GetNoArena();
}
inline void GroupCreateRequest::set_group_head(const ::std::string& value) {
  
  group_head_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:youliao.pdu.group.GroupCreateRequest.group_head)
}
#if LANG_CXX11
inline void GroupCreateRequest::set_group_head(::std::string&& value) {
  
  group_head_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:youliao.pdu.group.GroupCreateRequest.group_head)
}
#endif
inline void GroupCreateRequest::set_group_head(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  group_head_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:youliao.pdu.group.GroupCreateRequest.group_head)
}
inline void GroupCreateRequest::set_group_head(const char* value, size_t size) {
  
  group_head_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:youliao.pdu.group.GroupCreateRequest.group_head)
}
inline ::std::string* GroupCreateRequest::mutable_group_head() {
  
  // @@protoc_insertion_point(field_mutable:youliao.pdu.group.GroupCreateRequest.group_head)
  return group_head_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* GroupCreateRequest::release_group_head() {
  // @@protoc_insertion_point(field_release:youliao.pdu.group.GroupCreateRequest.group_head)
  
  return group_head_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void GroupCreateRequest::set_allocated_group_head(::std::string* group_head) {
  if (group_head != NULL) {
    
  } else {
    
  }
  group_head_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), group_head);
  // @@protoc_insertion_point(field_set_allocated:youliao.pdu.group.GroupCreateRequest.group_head)
}

// .youliao.pdu.base.GroupType group_type = 4;
inline void GroupCreateRequest::clear_group_type() {
  group_type_ = 0;
}
inline ::youliao::pdu::base::GroupType GroupCreateRequest::group_type() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.group.GroupCreateRequest.group_type)
  return static_cast< ::youliao::pdu::base::GroupType >(group_type_);
}
inline void GroupCreateRequest::set_group_type(::youliao::pdu::base::GroupType value) {
  
  group_type_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.group.GroupCreateRequest.group_type)
}

// .youliao.pdu.base.GroupVerifyType group_verify_type = 5;
inline void GroupCreateRequest::clear_group_verify_type() {
  group_verify_type_ = 0;
}
inline ::youliao::pdu::base::GroupVerifyType GroupCreateRequest::group_verify_type() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.group.GroupCreateRequest.group_verify_type)
  return static_cast< ::youliao::pdu::base::GroupVerifyType >(group_verify_type_);
}
inline void GroupCreateRequest::set_group_verify_type(::youliao::pdu::base::GroupVerifyType value) {
  
  group_verify_type_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.group.GroupCreateRequest.group_verify_type)
}

// repeated uint32 member_ids = 6;
inline int GroupCreateRequest::member_ids_size() const {
  return member_ids_.size();
}
inline void GroupCreateRequest::clear_member_ids() {
  member_ids_.Clear();
}
inline ::google::protobuf::uint32 GroupCreateRequest::member_ids(int index) const {
  // @@protoc_insertion_point(field_get:youliao.pdu.group.GroupCreateRequest.member_ids)
  return member_ids_.Get(index);
}
inline void GroupCreateRequest::set_member_ids(int index, ::google::protobuf::uint32 value) {
  member_ids_.Set(index, value);
  // @@protoc_insertion_point(field_set:youliao.pdu.group.GroupCreateRequest.member_ids)
}
inline void GroupCreateRequest::add_member_ids(::google::protobuf::uint32 value) {
  member_ids_.Add(value);
  // @@protoc_insertion_point(field_add:youliao.pdu.group.GroupCreateRequest.member_ids)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
GroupCreateRequest::member_ids() const {
  // @@protoc_insertion_point(field_list:youliao.pdu.group.GroupCreateRequest.member_ids)
  return member_ids_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
GroupCreateRequest::mutable_member_ids() {
  // @@protoc_insertion_point(field_mutable_list:youliao.pdu.group.GroupCreateRequest.member_ids)
  return &member_ids_;
}

// uint32 group_max_members = 7;
inline void GroupCreateRequest::clear_group_max_members() {
  group_max_members_ = 0u;
}
inline ::google::protobuf::uint32 GroupCreateRequest::group_max_members() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.group.GroupCreateRequest.group_max_members)
  return group_max_members_;
}
inline void GroupCreateRequest::set_group_max_members(::google::protobuf::uint32 value) {
  
  group_max_members_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.group.GroupCreateRequest.group_max_members)
}

// -------------------------------------------------------------------

// GroupCreateRespone

// uint32 user_id = 1;
inline void GroupCreateRespone::clear_user_id() {
  user_id_ = 0u;
}
inline ::google::protobuf::uint32 GroupCreateRespone::user_id() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.group.GroupCreateRespone.user_id)
  return user_id_;
}
inline void GroupCreateRespone::set_user_id(::google::protobuf::uint32 value) {
  
  user_id_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.group.GroupCreateRespone.user_id)
}

// uint32 result_code = 2;
inline void GroupCreateRespone::clear_result_code() {
  result_code_ = 0u;
}
inline ::google::protobuf::uint32 GroupCreateRespone::result_code() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.group.GroupCreateRespone.result_code)
  return result_code_;
}
inline void GroupCreateRespone::set_result_code(::google::protobuf::uint32 value) {
  
  result_code_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.group.GroupCreateRespone.result_code)
}

// .youliao.pdu.base.GroupInfo group_info = 3;
inline bool GroupCreateRespone::has_group_info() const {
  return this != internal_default_instance() && group_info_ != NULL;
}
inline const ::youliao::pdu::base::GroupInfo& GroupCreateRespone::group_info() const {
  const ::youliao::pdu::base::GroupInfo* p = group_info_;
  // @@protoc_insertion_point(field_get:youliao.pdu.group.GroupCreateRespone.group_info)
  return p != NULL ? *p : *reinterpret_cast<const ::youliao::pdu::base::GroupInfo*>(
      &::youliao::pdu::base::_GroupInfo_default_instance_);
}
inline ::youliao::pdu::base::GroupInfo* GroupCreateRespone::release_group_info() {
  // @@protoc_insertion_point(field_release:youliao.pdu.group.GroupCreateRespone.group_info)
  
  ::youliao::pdu::base::GroupInfo* temp = group_info_;
  group_info_ = NULL;
  return temp;
}
inline ::youliao::pdu::base::GroupInfo* GroupCreateRespone::mutable_group_info() {
  
  if (group_info_ == NULL) {
    group_info_ = ::google::protobuf::Arena::Create< ::youliao::pdu::base::GroupInfo >(
        GetArenaNoVirtual());
  }
  // @@protoc_insertion_point(field_mutable:youliao.pdu.group.GroupCreateRespone.group_info)
  return group_info_;
}
inline void GroupCreateRespone::set_allocated_group_info(::youliao::pdu::base::GroupInfo* group_info) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete reinterpret_cast< ::google::protobuf::MessageLite*>(group_info_);
  }
  if (group_info) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      group_info = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, group_info, submessage_arena);
    }
    
  } else {
    
  }
  group_info_ = group_info;
  // @@protoc_insertion_point(field_set_allocated:youliao.pdu.group.GroupCreateRespone.group_info)
}

// -------------------------------------------------------------------

// GetGroupListRequest

// uint32 user_id = 1;
inline void GetGroupListRequest::clear_user_id() {
  user_id_ = 0u;
}
inline ::google::protobuf::uint32 GetGroupListRequest::user_id() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.group.GetGroupListRequest.user_id)
  return user_id_;
}
inline void GetGroupListRequest::set_user_id(::google::protobuf::uint32 value) {
  
  user_id_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.group.GetGroupListRequest.user_id)
}

// -------------------------------------------------------------------

// GetGroupListRespone

// uint32 user_id = 1;
inline void GetGroupListRespone::clear_user_id() {
  user_id_ = 0u;
}
inline ::google::protobuf::uint32 GetGroupListRespone::user_id() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.group.GetGroupListRespone.user_id)
  return user_id_;
}
inline void GetGroupListRespone::set_user_id(::google::protobuf::uint32 value) {
  
  user_id_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.group.GetGroupListRespone.user_id)
}

// repeated .youliao.pdu.base.GroupInfo group_info = 2;
inline int GetGroupListRespone::group_info_size() const {
  return group_info_.size();
}
inline ::youliao::pdu::base::GroupInfo* GetGroupListRespone::mutable_group_info(int index) {
  // @@protoc_insertion_point(field_mutable:youliao.pdu.group.GetGroupListRespone.group_info)
  return group_info_.Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField< ::youliao::pdu::base::GroupInfo >*
GetGroupListRespone::mutable_group_info() {
  // @@protoc_insertion_point(field_mutable_list:youliao.pdu.group.GetGroupListRespone.group_info)
  return &group_info_;
}
inline const ::youliao::pdu::base::GroupInfo& GetGroupListRespone::group_info(int index) const {
  // @@protoc_insertion_point(field_get:youliao.pdu.group.GetGroupListRespone.group_info)
  return group_info_.Get(index);
}
inline ::youliao::pdu::base::GroupInfo* GetGroupListRespone::add_group_info() {
  // @@protoc_insertion_point(field_add:youliao.pdu.group.GetGroupListRespone.group_info)
  return group_info_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::youliao::pdu::base::GroupInfo >&
GetGroupListRespone::group_info() const {
  // @@protoc_insertion_point(field_list:youliao.pdu.group.GetGroupListRespone.group_info)
  return group_info_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace group
}  // namespace pdu
}  // namespace youliao

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_youliao_2egroup_2eproto_INCLUDED
