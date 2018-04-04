// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: youliao.message.proto

#ifndef PROTOBUF_youliao_2emessage_2eproto_INCLUDED
#define PROTOBUF_youliao_2emessage_2eproto_INCLUDED

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

namespace protobuf_youliao_2emessage_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
void InitDefaultsMessageDataImpl();
void InitDefaultsMessageData();
inline void InitDefaults() {
  InitDefaultsMessageData();
}
}  // namespace protobuf_youliao_2emessage_2eproto
namespace youliao {
namespace pdu {
namespace message {
class MessageData;
class MessageDataDefaultTypeInternal;
extern MessageDataDefaultTypeInternal _MessageData_default_instance_;
}  // namespace message
}  // namespace pdu
}  // namespace youliao
namespace google {
namespace protobuf {
template<> ::youliao::pdu::message::MessageData* Arena::Create< ::youliao::pdu::message::MessageData>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace youliao {
namespace pdu {
namespace message {

// ===================================================================

class MessageData : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:youliao.pdu.message.MessageData) */ {
 public:
  MessageData();
  virtual ~MessageData();

  MessageData(const MessageData& from);

  inline MessageData& operator=(const MessageData& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  MessageData(MessageData&& from) noexcept
    : MessageData() {
    *this = ::std::move(from);
  }

  inline MessageData& operator=(MessageData&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const MessageData& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const MessageData* internal_default_instance() {
    return reinterpret_cast<const MessageData*>(
               &_MessageData_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(MessageData* other);
  friend void swap(MessageData& a, MessageData& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline MessageData* New() const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<MessageData>(NULL);
  }

  MessageData* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<MessageData>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const MessageData& from);
  void MergeFrom(const MessageData& from);
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
  void InternalSwap(MessageData* other);
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

  // bytes message_data = 6;
  void clear_message_data();
  static const int kMessageDataFieldNumber = 6;
  const ::std::string& message_data() const;
  void set_message_data(const ::std::string& value);
  #if LANG_CXX11
  void set_message_data(::std::string&& value);
  #endif
  void set_message_data(const char* value);
  void set_message_data(const void* value, size_t size);
  ::std::string* mutable_message_data();
  ::std::string* release_message_data();
  void set_allocated_message_data(::std::string* message_data);

  // bytes attach_data = 7;
  void clear_attach_data();
  static const int kAttachDataFieldNumber = 7;
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

  // uint32 from_user_id = 1;
  void clear_from_user_id();
  static const int kFromUserIdFieldNumber = 1;
  ::google::protobuf::uint32 from_user_id() const;
  void set_from_user_id(::google::protobuf::uint32 value);

  // uint32 to_user_id = 2;
  void clear_to_user_id();
  static const int kToUserIdFieldNumber = 2;
  ::google::protobuf::uint32 to_user_id() const;
  void set_to_user_id(::google::protobuf::uint32 value);

  // uint32 msg_id = 3;
  void clear_msg_id();
  static const int kMsgIdFieldNumber = 3;
  ::google::protobuf::uint32 msg_id() const;
  void set_msg_id(::google::protobuf::uint32 value);

  // uint32 create_time = 4;
  void clear_create_time();
  static const int kCreateTimeFieldNumber = 4;
  ::google::protobuf::uint32 create_time() const;
  void set_create_time(::google::protobuf::uint32 value);

  // .youliao.pdu.base.MessageType message_type = 5;
  void clear_message_type();
  static const int kMessageTypeFieldNumber = 5;
  ::youliao::pdu::base::MessageType message_type() const;
  void set_message_type(::youliao::pdu::base::MessageType value);

  // @@protoc_insertion_point(class_scope:youliao.pdu.message.MessageData)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr message_data_;
  ::google::protobuf::internal::ArenaStringPtr attach_data_;
  ::google::protobuf::uint32 from_user_id_;
  ::google::protobuf::uint32 to_user_id_;
  ::google::protobuf::uint32 msg_id_;
  ::google::protobuf::uint32 create_time_;
  int message_type_;
  mutable int _cached_size_;
  friend struct ::protobuf_youliao_2emessage_2eproto::TableStruct;
  friend void ::protobuf_youliao_2emessage_2eproto::InitDefaultsMessageDataImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// MessageData

// uint32 from_user_id = 1;
inline void MessageData::clear_from_user_id() {
  from_user_id_ = 0u;
}
inline ::google::protobuf::uint32 MessageData::from_user_id() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.message.MessageData.from_user_id)
  return from_user_id_;
}
inline void MessageData::set_from_user_id(::google::protobuf::uint32 value) {
  
  from_user_id_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.message.MessageData.from_user_id)
}

// uint32 to_user_id = 2;
inline void MessageData::clear_to_user_id() {
  to_user_id_ = 0u;
}
inline ::google::protobuf::uint32 MessageData::to_user_id() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.message.MessageData.to_user_id)
  return to_user_id_;
}
inline void MessageData::set_to_user_id(::google::protobuf::uint32 value) {
  
  to_user_id_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.message.MessageData.to_user_id)
}

// uint32 msg_id = 3;
inline void MessageData::clear_msg_id() {
  msg_id_ = 0u;
}
inline ::google::protobuf::uint32 MessageData::msg_id() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.message.MessageData.msg_id)
  return msg_id_;
}
inline void MessageData::set_msg_id(::google::protobuf::uint32 value) {
  
  msg_id_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.message.MessageData.msg_id)
}

// uint32 create_time = 4;
inline void MessageData::clear_create_time() {
  create_time_ = 0u;
}
inline ::google::protobuf::uint32 MessageData::create_time() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.message.MessageData.create_time)
  return create_time_;
}
inline void MessageData::set_create_time(::google::protobuf::uint32 value) {
  
  create_time_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.message.MessageData.create_time)
}

// .youliao.pdu.base.MessageType message_type = 5;
inline void MessageData::clear_message_type() {
  message_type_ = 0;
}
inline ::youliao::pdu::base::MessageType MessageData::message_type() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.message.MessageData.message_type)
  return static_cast< ::youliao::pdu::base::MessageType >(message_type_);
}
inline void MessageData::set_message_type(::youliao::pdu::base::MessageType value) {
  
  message_type_ = value;
  // @@protoc_insertion_point(field_set:youliao.pdu.message.MessageData.message_type)
}

// bytes message_data = 6;
inline void MessageData::clear_message_data() {
  message_data_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& MessageData::message_data() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.message.MessageData.message_data)
  return message_data_.GetNoArena();
}
inline void MessageData::set_message_data(const ::std::string& value) {
  
  message_data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:youliao.pdu.message.MessageData.message_data)
}
#if LANG_CXX11
inline void MessageData::set_message_data(::std::string&& value) {
  
  message_data_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:youliao.pdu.message.MessageData.message_data)
}
#endif
inline void MessageData::set_message_data(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  message_data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:youliao.pdu.message.MessageData.message_data)
}
inline void MessageData::set_message_data(const void* value, size_t size) {
  
  message_data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:youliao.pdu.message.MessageData.message_data)
}
inline ::std::string* MessageData::mutable_message_data() {
  
  // @@protoc_insertion_point(field_mutable:youliao.pdu.message.MessageData.message_data)
  return message_data_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* MessageData::release_message_data() {
  // @@protoc_insertion_point(field_release:youliao.pdu.message.MessageData.message_data)
  
  return message_data_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MessageData::set_allocated_message_data(::std::string* message_data) {
  if (message_data != NULL) {
    
  } else {
    
  }
  message_data_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), message_data);
  // @@protoc_insertion_point(field_set_allocated:youliao.pdu.message.MessageData.message_data)
}

// bytes attach_data = 7;
inline void MessageData::clear_attach_data() {
  attach_data_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& MessageData::attach_data() const {
  // @@protoc_insertion_point(field_get:youliao.pdu.message.MessageData.attach_data)
  return attach_data_.GetNoArena();
}
inline void MessageData::set_attach_data(const ::std::string& value) {
  
  attach_data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:youliao.pdu.message.MessageData.attach_data)
}
#if LANG_CXX11
inline void MessageData::set_attach_data(::std::string&& value) {
  
  attach_data_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:youliao.pdu.message.MessageData.attach_data)
}
#endif
inline void MessageData::set_attach_data(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  attach_data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:youliao.pdu.message.MessageData.attach_data)
}
inline void MessageData::set_attach_data(const void* value, size_t size) {
  
  attach_data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:youliao.pdu.message.MessageData.attach_data)
}
inline ::std::string* MessageData::mutable_attach_data() {
  
  // @@protoc_insertion_point(field_mutable:youliao.pdu.message.MessageData.attach_data)
  return attach_data_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* MessageData::release_attach_data() {
  // @@protoc_insertion_point(field_release:youliao.pdu.message.MessageData.attach_data)
  
  return attach_data_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MessageData::set_allocated_attach_data(::std::string* attach_data) {
  if (attach_data != NULL) {
    
  } else {
    
  }
  attach_data_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), attach_data);
  // @@protoc_insertion_point(field_set_allocated:youliao.pdu.message.MessageData.attach_data)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace message
}  // namespace pdu
}  // namespace youliao

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_youliao_2emessage_2eproto_INCLUDED
