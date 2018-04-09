// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: youliao.friendlist.proto

#ifndef PROTOBUF_youliao_2efriendlist_2eproto_INCLUDED
#define PROTOBUF_youliao_2efriendlist_2eproto_INCLUDED

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
#include <google/protobuf/map.h>  // IWYU pragma: export
#include <google/protobuf/map_entry.h>
#include <google/protobuf/map_field_inl.h>
#include <google/protobuf/unknown_field_set.h>
#include "youliao.base.pb.h"
// @@protoc_insertion_point(includes)

namespace protobuf_youliao_2efriendlist_2eproto {
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
void InitDefaultsGroup_FriendImpl();
void InitDefaultsGroup_Friend();
void InitDefaultsFriendListRequestImpl();
void InitDefaultsFriendListRequest();
void InitDefaultsFriendListRespone_FriendListEntry_DoNotUseImpl();
void InitDefaultsFriendListRespone_FriendListEntry_DoNotUse();
void InitDefaultsFriendListResponeImpl();
void InitDefaultsFriendListRespone();
inline void InitDefaults() {
  InitDefaultsGroup_Friend();
  InitDefaultsFriendListRequest();
  InitDefaultsFriendListRespone_FriendListEntry_DoNotUse();
  InitDefaultsFriendListRespone();
}
}  // namespace protobuf_youliao_2efriendlist_2eproto
namespace youliao {
namespace pdu {
namespace friendlist {
class FriendListRequest;
class FriendListRequestDefaultTypeInternal;
extern FriendListRequestDefaultTypeInternal _FriendListRequest_default_instance_;
class FriendListRespone;
class FriendListResponeDefaultTypeInternal;
extern FriendListResponeDefaultTypeInternal _FriendListRespone_default_instance_;
class FriendListRespone_FriendListEntry_DoNotUse;
class FriendListRespone_FriendListEntry_DoNotUseDefaultTypeInternal;
extern FriendListRespone_FriendListEntry_DoNotUseDefaultTypeInternal _FriendListRespone_FriendListEntry_DoNotUse_default_instance_;
class Group_Friend;
class Group_FriendDefaultTypeInternal;
extern Group_FriendDefaultTypeInternal _Group_Friend_default_instance_;
}  // namespace friendlist
}  // namespace pdu
}  // namespace youliao
namespace google {
namespace protobuf {
template<> ::youliao::pdu::friendlist::FriendListRequest* Arena::Create< ::youliao::pdu::friendlist::FriendListRequest>(Arena*);
template<> ::youliao::pdu::friendlist::FriendListRespone* Arena::Create< ::youliao::pdu::friendlist::FriendListRespone>(Arena*);
template<> ::youliao::pdu::friendlist::FriendListRespone_FriendListEntry_DoNotUse* Arena::Create< ::youliao::pdu::friendlist::FriendListRespone_FriendListEntry_DoNotUse>(Arena*);
template<> ::youliao::pdu::friendlist::Group_Friend* Arena::Create< ::youliao::pdu::friendlist::Group_Friend>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace youliao {
namespace pdu {
namespace friendlist {

// ===================================================================

class Group_Friend : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:youliao.pdu.friendlist.Group_Friend) */ {
 public:
  Group_Friend();
  virtual ~Group_Friend();

  Group_Friend(const Group_Friend& from);

  inline Group_Friend& operator=(const Group_Friend& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Group_Friend(Group_Friend&& from) noexcept
    : Group_Friend() {
    *this = ::std::move(from);
  }

  inline Group_Friend& operator=(Group_Friend&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Group_Friend& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Group_Friend* internal_default_instance() {
    return reinterpret_cast<const Group_Friend*>(
               &_Group_Friend_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(Group_Friend* other);
  friend void swap(Group_Friend& a, Group_Friend& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Group_Friend* New() const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<Group_Friend>(NULL);
  }

  Group_Friend* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<Group_Friend>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Group_Friend& from);
  void MergeFrom(const Group_Friend& from);
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
  void InternalSwap(Group_Friend* other);
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

  // repeated .youliao.pdu.base.FriendInfo friend = 3;
  int friend__size() const;
  void clear_friend_();
  static const int kFriendFieldNumber = 3;
  ::youliao::pdu::base::FriendInfo* mutable_friend_(int index);
  ::google::protobuf::RepeatedPtrField< ::youliao::pdu::base::FriendInfo >*
      mutable_friend_();
  const ::youliao::pdu::base::FriendInfo& friend_(int index) const;
  ::youliao::pdu::base::FriendInfo* add_friend_();
  const ::google::protobuf::RepeatedPtrField< ::youliao::pdu::base::FriendInfo >&
      friend_() const;

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

  // uint32 group_id = 1;
  void clear_group_id();
  static const int kGroupIdFieldNumber = 1;
  ::google::protobuf::uint32 group_id() const;
  void set_group_id(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:youliao.pdu.friendlist.Group_Friend)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::youliao::pdu::base::FriendInfo > friend__;
  ::google::protobuf::internal::ArenaStringPtr group_name_;
  ::google::protobuf::uint32 group_id_;
  mutable int _cached_size_;
  friend struct ::protobuf_youliao_2efriendlist_2eproto::TableStruct;
  friend void ::protobuf_youliao_2efriendlist_2eproto::InitDefaultsGroup_FriendImpl();
};
// -------------------------------------------------------------------

class FriendListRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:youliao.pdu.friendlist.FriendListRequest) */ {
 public:
  FriendListRequest();
  virtual ~FriendListRequest();

  FriendListRequest(const FriendListRequest& from);

  inline FriendListRequest& operator=(const FriendListRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  FriendListRequest(FriendListRequest&& from) noexcept
    : FriendListRequest() {
    *this = ::std::move(from);
  }

  inline FriendListRequest& operator=(FriendListRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const FriendListRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const FriendListRequest* internal_default_instance() {
    return reinterpret_cast<const FriendListRequest*>(
               &_FriendListRequest_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(FriendListRequest* other);
  friend void swap(FriendListRequest& a, FriendListRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline FriendListRequest* New() const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<FriendListRequest>(NULL);
  }

  FriendListRequest* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<FriendListRequest>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const FriendListRequest& from);
  void MergeFrom(const FriendListRequest& from);
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
  void InternalSwap(FriendListRequest* other);
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

  // bytes attach_data = 20;
  void clear_attach_data();
  static const int kAttachDataFieldNumber = 20;
  const ::std::string& attach_data() const;
  void set_attach_data(const ::std::string& value);
  #if LANG_CXX11
  void set_attach_data(::std::string&& value);
  #endif
  void set_attach_data(const char* value);
  void set_attach_data(const void* value, size_t size);
  ::std::string* mutable_attach_data();
  ::std::string* release_attach_data();
  void set_allocated_attach_data(::std::string* attach_data);

  // uint32 user_id = 1;
  void clear_user_id();
  static const int kUserIdFieldNumber = 1;
  ::google::protobuf::uint32 user_id() const;
  void set_user_id(::google::protobuf::uint32 value);

  // uint32 msg_serv_idx = 2;
  void clear_msg_serv_idx();
  static const int kMsgServIdxFieldNumber = 2;
  ::google::protobuf::uint32 msg_serv_idx() const;
  void set_msg_serv_idx(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:youliao.pdu.friendlist.FriendListRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr attach_data_;
  ::google::protobuf::uint32 user_id_;
  ::google::protobuf::uint32 msg_serv_idx_;
  mutable int _cached_size_;
  friend struct ::protobuf_youliao_2efriendlist_2eproto::TableStruct;
  friend void ::protobuf_youliao_2efriendlist_2eproto::InitDefaultsFriendListRequestImpl();
};
// -------------------------------------------------------------------

class FriendListRespone_FriendListEntry_DoNotUse : public ::google::protobuf::internal::MapEntry<FriendListRespone_FriendListEntry_DoNotUse, 
    ::google::protobuf::uint32, ::youliao::pdu::friendlist::Group_Friend,
    ::google::protobuf::internal::WireFormatLite::TYPE_UINT32,
    ::google::protobuf::internal::WireFormatLite::TYPE_MESSAGE,
    0 > {
public:
  typedef ::google::protobuf::internal::MapEntry<FriendListRespone_FriendListEntry_DoNotUse, 
    ::google::protobuf::uint32, ::youliao::pdu::friendlist::Group_Friend,
    ::google::protobuf::internal::WireFormatLite::TYPE_UINT32,
    ::google::protobuf::internal::WireFormatLite::TYPE_MESSAGE,
    0 > SuperType;
  FriendListRespone_FriendListEntry_DoNotUse();
  FriendListRespone_FriendListEntry_DoNotUse(::google::protobuf::Arena* arena);
  void MergeFrom(const FriendListRespone_FriendListEntry_DoNotUse& other);
  static const FriendListRespone_FriendListEntry_DoNotUse* internal_default_instance() { return reinterpret_cast<const FriendListRespone_FriendListEntry_DoNotUse*>(&_FriendListRespone_FriendListEntry_DoNotUse_default_instance_); }
  void MergeFrom(const ::google::protobuf::Message& other) PROTOBUF_FINAL;
  ::google::protobuf::Metadata GetMetadata() const;
};

// -------------------------------------------------------------------

class FriendListRespone : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:youliao.pdu.friendlist.FriendListRespone) */ {
 public:
  FriendListRespone();
  virtual ~FriendListRespone();

  FriendListRespone(const FriendListRespone& from);

  inline FriendListRespone& operator=(const FriendListRespone& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  FriendListRespone(FriendListRespone&& from) noexcept
    : FriendListRespone() {
    *this = ::std::move(from);
  }

  inline FriendListRespone& operator=(FriendListRespone&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const FriendListRespone& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const FriendListRespone* internal_default_instance() {
    return reinterpret_cast<const FriendListRespone*>(
               &_FriendListRespone_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    3;

  void Swap(FriendListRespone* other);
  friend void swap(FriendListRespone& a, FriendListRespone& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline FriendListRespone* New() const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<FriendListRespone>(NULL);
  }

  FriendListRespone* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<FriendListRespone>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const FriendListRespone& from);
  void MergeFrom(const FriendListRespone& from);
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
  void InternalSwap(FriendListRespone* other);
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

  // map<uint32, .youliao.pdu.friendlist.Group_Friend> friend_list = 1;
  int friend_list_size() const;
  void clear_friend_list();
  static const int kFriendListFieldNumber = 1;
  const ::google::protobuf::Map< ::google::protobuf::uint32, ::youliao::pdu::friendlist::Group_Friend >&
      friend_list() const;
  ::google::protobuf::Map< ::google::protobuf::uint32, ::youliao::pdu::friendlist::Group_Friend >*
      mutable_friend_list();

  // bytes attach_data = 20;
  void clear_attach_data();
  static const int kAttachDataFieldNumber = 20;
  const ::std::string& attach_data() const;
  void set_attach_data(const ::std::string& value);
  #if LANG_CXX11
  void set_attach_data(::std::string&& value);
  #endif
  void set_attach_data(const char* value);
  void set_attach_data(const void* value, size_t size);
  ::std::string* mutable_attach_data();
  ::std::string* release_attach_data();
  void set_allocated_attach_data(::std::string* attach_data);

  // @@protoc_insertion_point(class_scope:youliao.pdu.friendlist.FriendListRespone)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::MapField<
      FriendListRespone_FriendListEntry_DoNotUse,
      ::google::protobuf::uint32, ::youliao::pdu::friendlist::Group_Friend,
      ::google::protobuf::internal::WireFormatLite::TYPE_UINT32,
      ::google::protobuf::internal::WireFormatLite::TYPE_MESSAGE,
      0 > friend_list_;
  ::google::protobuf::internal::ArenaStringPtr attach_data_;
  mutable int _cached_size_;
  friend struct ::protobuf_youliao_2efriendlist_2eproto::TableStruct;
  friend void ::protobuf_youliao_2efriendlist_2eproto::InitDefaultsFriendListResponeImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Group_Friend

// uint32 group_id = 1;
inline void Group_Friend::clear_group_id() {
  group_id_ = 0u;
}
inline ::google::protobuf::uint32 Group_Friend::group_id() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.friendlist.Group_Friend.group_id)
  return group_id_;
}
inline void Group_Friend::set_group_id(::google::protobuf::uint32 value) {
  
  group_id_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.friendlist.Group_Friend.group_id)
}

// string group_name = 2;
inline void Group_Friend::clear_group_name() {
  group_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Group_Friend::group_name() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.friendlist.Group_Friend.group_name)
  return group_name_.GetNoArena();
}
inline void Group_Friend::set_group_name(const ::std::string& value) {
  
  group_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:youliao.pdu.friendlist.Group_Friend.group_name)
}
#if LANG_CXX11
inline void Group_Friend::set_group_name(::std::string&& value) {
  
  group_name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:youliao.pdu.friendlist.Group_Friend.group_name)
}
#endif
inline void Group_Friend::set_group_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  group_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:youliao.pdu.friendlist.Group_Friend.group_name)
}
inline void Group_Friend::set_group_name(const char* value, size_t size) {
  
  group_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:youliao.pdu.friendlist.Group_Friend.group_name)
}
inline ::std::string* Group_Friend::mutable_group_name() {
  
  // @@protoc_insertion_point(field_mutable:youliao.pdu.friendlist.Group_Friend.group_name)
  return group_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Group_Friend::release_group_name() {
  // @@protoc_insertion_point(field_release:youliao.pdu.friendlist.Group_Friend.group_name)
  
  return group_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Group_Friend::set_allocated_group_name(::std::string* group_name) {
  if (group_name != NULL) {
    
  } else {
    
  }
  group_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), group_name);
  // @@protoc_insertion_point(field_set_allocated:youliao.pdu.friendlist.Group_Friend.group_name)
}

// repeated .youliao.pdu.base.FriendInfo friend = 3;
inline int Group_Friend::friend__size() const {
  return friend__.size();
}
inline ::youliao::pdu::base::FriendInfo* Group_Friend::mutable_friend_(int index) {
  // @@protoc_insertion_point(field_mutable:youliao.pdu.friendlist.Group_Friend.friend)
  return friend__.Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField< ::youliao::pdu::base::FriendInfo >*
Group_Friend::mutable_friend_() {
  // @@protoc_insertion_point(field_mutable_list:youliao.pdu.friendlist.Group_Friend.friend)
  return &friend__;
}
inline const ::youliao::pdu::base::FriendInfo& Group_Friend::friend_(int index) const {
  // @@protoc_insertion_point(field_get:youliao.pdu.friendlist.Group_Friend.friend)
  return friend__.Get(index);
}
inline ::youliao::pdu::base::FriendInfo* Group_Friend::add_friend_() {
  // @@protoc_insertion_point(field_add:youliao.pdu.friendlist.Group_Friend.friend)
  return friend__.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::youliao::pdu::base::FriendInfo >&
Group_Friend::friend_() const {
  // @@protoc_insertion_point(field_list:youliao.pdu.friendlist.Group_Friend.friend)
  return friend__;
}

// -------------------------------------------------------------------

// FriendListRequest

// uint32 user_id = 1;
inline void FriendListRequest::clear_user_id() {
  user_id_ = 0u;
}
inline ::google::protobuf::uint32 FriendListRequest::user_id() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.friendlist.FriendListRequest.user_id)
  return user_id_;
}
inline void FriendListRequest::set_user_id(::google::protobuf::uint32 value) {
  
  user_id_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.friendlist.FriendListRequest.user_id)
}

// uint32 msg_serv_idx = 2;
inline void FriendListRequest::clear_msg_serv_idx() {
  msg_serv_idx_ = 0u;
}
inline ::google::protobuf::uint32 FriendListRequest::msg_serv_idx() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.friendlist.FriendListRequest.msg_serv_idx)
  return msg_serv_idx_;
}
inline void FriendListRequest::set_msg_serv_idx(::google::protobuf::uint32 value) {
  
  msg_serv_idx_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.friendlist.FriendListRequest.msg_serv_idx)
}

// bytes attach_data = 20;
inline void FriendListRequest::clear_attach_data() {
  attach_data_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& FriendListRequest::attach_data() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.friendlist.FriendListRequest.attach_data)
  return attach_data_.GetNoArena();
}
inline void FriendListRequest::set_attach_data(const ::std::string& value) {
  
  attach_data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:youliao.pdu.friendlist.FriendListRequest.attach_data)
}
#if LANG_CXX11
inline void FriendListRequest::set_attach_data(::std::string&& value) {
  
  attach_data_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:youliao.pdu.friendlist.FriendListRequest.attach_data)
}
#endif
inline void FriendListRequest::set_attach_data(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  attach_data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:youliao.pdu.friendlist.FriendListRequest.attach_data)
}
inline void FriendListRequest::set_attach_data(const void* value, size_t size) {
  
  attach_data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:youliao.pdu.friendlist.FriendListRequest.attach_data)
}
inline ::std::string* FriendListRequest::mutable_attach_data() {
  
  // @@protoc_insertion_point(field_mutable:youliao.pdu.friendlist.FriendListRequest.attach_data)
  return attach_data_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* FriendListRequest::release_attach_data() {
  // @@protoc_insertion_point(field_release:youliao.pdu.friendlist.FriendListRequest.attach_data)
  
  return attach_data_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void FriendListRequest::set_allocated_attach_data(::std::string* attach_data) {
  if (attach_data != NULL) {
    
  } else {
    
  }
  attach_data_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), attach_data);
  // @@protoc_insertion_point(field_set_allocated:youliao.pdu.friendlist.FriendListRequest.attach_data)
}

// -------------------------------------------------------------------

// -------------------------------------------------------------------

// FriendListRespone

// map<uint32, .youliao.pdu.friendlist.Group_Friend> friend_list = 1;
inline int FriendListRespone::friend_list_size() const {
  return friend_list_.size();
}
inline void FriendListRespone::clear_friend_list() {
  friend_list_.Clear();
}
inline const ::google::protobuf::Map< ::google::protobuf::uint32, ::youliao::pdu::friendlist::Group_Friend >&
FriendListRespone::friend_list() const {
  // @@protoc_insertion_point(field_map:youliao.pdu.friendlist.FriendListRespone.friend_list)
  return friend_list_.GetMap();
}
inline ::google::protobuf::Map< ::google::protobuf::uint32, ::youliao::pdu::friendlist::Group_Friend >*
FriendListRespone::mutable_friend_list() {
  // @@protoc_insertion_point(field_mutable_map:youliao.pdu.friendlist.FriendListRespone.friend_list)
  return friend_list_.MutableMap();
}

// bytes attach_data = 20;
inline void FriendListRespone::clear_attach_data() {
  attach_data_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& FriendListRespone::attach_data() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.friendlist.FriendListRespone.attach_data)
  return attach_data_.GetNoArena();
}
inline void FriendListRespone::set_attach_data(const ::std::string& value) {
  
  attach_data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:youliao.pdu.friendlist.FriendListRespone.attach_data)
}
#if LANG_CXX11
inline void FriendListRespone::set_attach_data(::std::string&& value) {
  
  attach_data_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:youliao.pdu.friendlist.FriendListRespone.attach_data)
}
#endif
inline void FriendListRespone::set_attach_data(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  attach_data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:youliao.pdu.friendlist.FriendListRespone.attach_data)
}
inline void FriendListRespone::set_attach_data(const void* value, size_t size) {
  
  attach_data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:youliao.pdu.friendlist.FriendListRespone.attach_data)
}
inline ::std::string* FriendListRespone::mutable_attach_data() {
  
  // @@protoc_insertion_point(field_mutable:youliao.pdu.friendlist.FriendListRespone.attach_data)
  return attach_data_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* FriendListRespone::release_attach_data() {
  // @@protoc_insertion_point(field_release:youliao.pdu.friendlist.FriendListRespone.attach_data)
  
  return attach_data_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void FriendListRespone::set_allocated_attach_data(::std::string* attach_data) {
  if (attach_data != NULL) {
    
  } else {
    
  }
  attach_data_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), attach_data);
  // @@protoc_insertion_point(field_set_allocated:youliao.pdu.friendlist.FriendListRespone.attach_data)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace friendlist
}  // namespace pdu
}  // namespace youliao

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_youliao_2efriendlist_2eproto_INCLUDED
