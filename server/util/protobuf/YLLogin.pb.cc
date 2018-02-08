// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: YLLogin.proto

#include "YLLogin.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// This is a temporary google only hack
#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
#include "third_party/protobuf/version.h"
#endif
// @@protoc_insertion_point(includes)
namespace YL {
namespace Login {
class YLMsgServerRequestDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<YLMsgServerRequest>
      _instance;
} _YLMsgServerRequest_default_instance_;
class YLMsgServerResponeDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<YLMsgServerRespone>
      _instance;
} _YLMsgServerRespone_default_instance_;
}  // namespace Login
}  // namespace YL
namespace protobuf_YLLogin_2eproto {
void InitDefaultsYLMsgServerRequestImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  ::google::protobuf::internal::InitProtobufDefaultsForceUnique();
#else
  ::google::protobuf::internal::InitProtobufDefaults();
#endif  // GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  {
    void* ptr = &::YL::Login::_YLMsgServerRequest_default_instance_;
    new (ptr) ::YL::Login::YLMsgServerRequest();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::YL::Login::YLMsgServerRequest::InitAsDefaultInstance();
}

void InitDefaultsYLMsgServerRequest() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &InitDefaultsYLMsgServerRequestImpl);
}

void InitDefaultsYLMsgServerResponeImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  ::google::protobuf::internal::InitProtobufDefaultsForceUnique();
#else
  ::google::protobuf::internal::InitProtobufDefaults();
#endif  // GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  {
    void* ptr = &::YL::Login::_YLMsgServerRespone_default_instance_;
    new (ptr) ::YL::Login::YLMsgServerRespone();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::YL::Login::YLMsgServerRespone::InitAsDefaultInstance();
}

void InitDefaultsYLMsgServerRespone() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &InitDefaultsYLMsgServerResponeImpl);
}

::google::protobuf::Metadata file_level_metadata[2];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::YL::Login::YLMsgServerRequest, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::YL::Login::YLMsgServerRequest, s_),
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::YL::Login::YLMsgServerRespone, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::YL::Login::YLMsgServerRespone, result_code_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::YL::Login::YLMsgServerRespone, prior_ip_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::YL::Login::YLMsgServerRespone, back_ip_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::YL::Login::YLMsgServerRespone, port_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::YL::Login::YLMsgServerRequest)},
  { 6, -1, sizeof(::YL::Login::YLMsgServerRespone)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::YL::Login::_YLMsgServerRequest_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&::YL::Login::_YLMsgServerRespone_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "YLLogin.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 2);
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\rYLLogin.proto\022\010YL.Login\032\014YLBase.proto\""
      "\037\n\022YLMsgServerRequest\022\t\n\001s\030\001 \001(\t\"o\n\022YLMs"
      "gServerRespone\022(\n\013result_code\030\001 \001(\0162\023.YL"
      ".Base.ResultType\022\020\n\010prior_ip\030\002 \001(\t\022\017\n\007ba"
      "ck_ip\030\003 \001(\t\022\014\n\004port\030\004 \001(\rb\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 193);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "YLLogin.proto", &protobuf_RegisterTypes);
  ::protobuf_YLBase_2eproto::AddDescriptors();
}

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;
}  // namespace protobuf_YLLogin_2eproto
namespace YL {
namespace Login {

// ===================================================================

void YLMsgServerRequest::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int YLMsgServerRequest::kSFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

YLMsgServerRequest::YLMsgServerRequest()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    ::protobuf_YLLogin_2eproto::InitDefaultsYLMsgServerRequest();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:YL.Login.YLMsgServerRequest)
}
YLMsgServerRequest::YLMsgServerRequest(const YLMsgServerRequest& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  s_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.s().size() > 0) {
    s_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.s_);
  }
  // @@protoc_insertion_point(copy_constructor:YL.Login.YLMsgServerRequest)
}

void YLMsgServerRequest::SharedCtor() {
  s_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  _cached_size_ = 0;
}

YLMsgServerRequest::~YLMsgServerRequest() {
  // @@protoc_insertion_point(destructor:YL.Login.YLMsgServerRequest)
  SharedDtor();
}

void YLMsgServerRequest::SharedDtor() {
  s_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void YLMsgServerRequest::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* YLMsgServerRequest::descriptor() {
  ::protobuf_YLLogin_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_YLLogin_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const YLMsgServerRequest& YLMsgServerRequest::default_instance() {
  ::protobuf_YLLogin_2eproto::InitDefaultsYLMsgServerRequest();
  return *internal_default_instance();
}

YLMsgServerRequest* YLMsgServerRequest::New(::google::protobuf::Arena* arena) const {
  YLMsgServerRequest* n = new YLMsgServerRequest;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void YLMsgServerRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:YL.Login.YLMsgServerRequest)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  s_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  _internal_metadata_.Clear();
}

bool YLMsgServerRequest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:YL.Login.YLMsgServerRequest)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // string s = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_s()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->s().data(), static_cast<int>(this->s().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "YL.Login.YLMsgServerRequest.s"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:YL.Login.YLMsgServerRequest)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:YL.Login.YLMsgServerRequest)
  return false;
#undef DO_
}

void YLMsgServerRequest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:YL.Login.YLMsgServerRequest)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string s = 1;
  if (this->s().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->s().data(), static_cast<int>(this->s().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "YL.Login.YLMsgServerRequest.s");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->s(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:YL.Login.YLMsgServerRequest)
}

::google::protobuf::uint8* YLMsgServerRequest::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:YL.Login.YLMsgServerRequest)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string s = 1;
  if (this->s().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->s().data(), static_cast<int>(this->s().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "YL.Login.YLMsgServerRequest.s");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->s(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:YL.Login.YLMsgServerRequest)
  return target;
}

size_t YLMsgServerRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:YL.Login.YLMsgServerRequest)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // string s = 1;
  if (this->s().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->s());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void YLMsgServerRequest::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:YL.Login.YLMsgServerRequest)
  GOOGLE_DCHECK_NE(&from, this);
  const YLMsgServerRequest* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const YLMsgServerRequest>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:YL.Login.YLMsgServerRequest)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:YL.Login.YLMsgServerRequest)
    MergeFrom(*source);
  }
}

void YLMsgServerRequest::MergeFrom(const YLMsgServerRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:YL.Login.YLMsgServerRequest)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.s().size() > 0) {

    s_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.s_);
  }
}

void YLMsgServerRequest::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:YL.Login.YLMsgServerRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void YLMsgServerRequest::CopyFrom(const YLMsgServerRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:YL.Login.YLMsgServerRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool YLMsgServerRequest::IsInitialized() const {
  return true;
}

void YLMsgServerRequest::Swap(YLMsgServerRequest* other) {
  if (other == this) return;
  InternalSwap(other);
}
void YLMsgServerRequest::InternalSwap(YLMsgServerRequest* other) {
  using std::swap;
  s_.Swap(&other->s_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata YLMsgServerRequest::GetMetadata() const {
  protobuf_YLLogin_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_YLLogin_2eproto::file_level_metadata[kIndexInFileMessages];
}


// ===================================================================

void YLMsgServerRespone::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int YLMsgServerRespone::kResultCodeFieldNumber;
const int YLMsgServerRespone::kPriorIpFieldNumber;
const int YLMsgServerRespone::kBackIpFieldNumber;
const int YLMsgServerRespone::kPortFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

YLMsgServerRespone::YLMsgServerRespone()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    ::protobuf_YLLogin_2eproto::InitDefaultsYLMsgServerRespone();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:YL.Login.YLMsgServerRespone)
}
YLMsgServerRespone::YLMsgServerRespone(const YLMsgServerRespone& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  prior_ip_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.prior_ip().size() > 0) {
    prior_ip_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.prior_ip_);
  }
  back_ip_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.back_ip().size() > 0) {
    back_ip_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.back_ip_);
  }
  ::memcpy(&result_code_, &from.result_code_,
    static_cast<size_t>(reinterpret_cast<char*>(&port_) -
    reinterpret_cast<char*>(&result_code_)) + sizeof(port_));
  // @@protoc_insertion_point(copy_constructor:YL.Login.YLMsgServerRespone)
}

void YLMsgServerRespone::SharedCtor() {
  prior_ip_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  back_ip_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(&result_code_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&port_) -
      reinterpret_cast<char*>(&result_code_)) + sizeof(port_));
  _cached_size_ = 0;
}

YLMsgServerRespone::~YLMsgServerRespone() {
  // @@protoc_insertion_point(destructor:YL.Login.YLMsgServerRespone)
  SharedDtor();
}

void YLMsgServerRespone::SharedDtor() {
  prior_ip_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  back_ip_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void YLMsgServerRespone::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* YLMsgServerRespone::descriptor() {
  ::protobuf_YLLogin_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_YLLogin_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const YLMsgServerRespone& YLMsgServerRespone::default_instance() {
  ::protobuf_YLLogin_2eproto::InitDefaultsYLMsgServerRespone();
  return *internal_default_instance();
}

YLMsgServerRespone* YLMsgServerRespone::New(::google::protobuf::Arena* arena) const {
  YLMsgServerRespone* n = new YLMsgServerRespone;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void YLMsgServerRespone::Clear() {
// @@protoc_insertion_point(message_clear_start:YL.Login.YLMsgServerRespone)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  prior_ip_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  back_ip_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(&result_code_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&port_) -
      reinterpret_cast<char*>(&result_code_)) + sizeof(port_));
  _internal_metadata_.Clear();
}

bool YLMsgServerRespone::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:YL.Login.YLMsgServerRespone)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // .YL.Base.ResultType result_code = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          set_result_code(static_cast< ::YL::Base::ResultType >(value));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // string prior_ip = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(18u /* 18 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_prior_ip()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->prior_ip().data(), static_cast<int>(this->prior_ip().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "YL.Login.YLMsgServerRespone.prior_ip"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // string back_ip = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(26u /* 26 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_back_ip()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->back_ip().data(), static_cast<int>(this->back_ip().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "YL.Login.YLMsgServerRespone.back_ip"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // uint32 port = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(32u /* 32 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &port_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:YL.Login.YLMsgServerRespone)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:YL.Login.YLMsgServerRespone)
  return false;
#undef DO_
}

void YLMsgServerRespone::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:YL.Login.YLMsgServerRespone)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .YL.Base.ResultType result_code = 1;
  if (this->result_code() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->result_code(), output);
  }

  // string prior_ip = 2;
  if (this->prior_ip().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->prior_ip().data(), static_cast<int>(this->prior_ip().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "YL.Login.YLMsgServerRespone.prior_ip");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->prior_ip(), output);
  }

  // string back_ip = 3;
  if (this->back_ip().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->back_ip().data(), static_cast<int>(this->back_ip().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "YL.Login.YLMsgServerRespone.back_ip");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      3, this->back_ip(), output);
  }

  // uint32 port = 4;
  if (this->port() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->port(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:YL.Login.YLMsgServerRespone)
}

::google::protobuf::uint8* YLMsgServerRespone::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:YL.Login.YLMsgServerRespone)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .YL.Base.ResultType result_code = 1;
  if (this->result_code() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->result_code(), target);
  }

  // string prior_ip = 2;
  if (this->prior_ip().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->prior_ip().data(), static_cast<int>(this->prior_ip().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "YL.Login.YLMsgServerRespone.prior_ip");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->prior_ip(), target);
  }

  // string back_ip = 3;
  if (this->back_ip().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->back_ip().data(), static_cast<int>(this->back_ip().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "YL.Login.YLMsgServerRespone.back_ip");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->back_ip(), target);
  }

  // uint32 port = 4;
  if (this->port() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->port(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:YL.Login.YLMsgServerRespone)
  return target;
}

size_t YLMsgServerRespone::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:YL.Login.YLMsgServerRespone)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // string prior_ip = 2;
  if (this->prior_ip().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->prior_ip());
  }

  // string back_ip = 3;
  if (this->back_ip().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->back_ip());
  }

  // .YL.Base.ResultType result_code = 1;
  if (this->result_code() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->result_code());
  }

  // uint32 port = 4;
  if (this->port() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->port());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void YLMsgServerRespone::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:YL.Login.YLMsgServerRespone)
  GOOGLE_DCHECK_NE(&from, this);
  const YLMsgServerRespone* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const YLMsgServerRespone>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:YL.Login.YLMsgServerRespone)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:YL.Login.YLMsgServerRespone)
    MergeFrom(*source);
  }
}

void YLMsgServerRespone::MergeFrom(const YLMsgServerRespone& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:YL.Login.YLMsgServerRespone)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.prior_ip().size() > 0) {

    prior_ip_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.prior_ip_);
  }
  if (from.back_ip().size() > 0) {

    back_ip_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.back_ip_);
  }
  if (from.result_code() != 0) {
    set_result_code(from.result_code());
  }
  if (from.port() != 0) {
    set_port(from.port());
  }
}

void YLMsgServerRespone::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:YL.Login.YLMsgServerRespone)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void YLMsgServerRespone::CopyFrom(const YLMsgServerRespone& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:YL.Login.YLMsgServerRespone)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool YLMsgServerRespone::IsInitialized() const {
  return true;
}

void YLMsgServerRespone::Swap(YLMsgServerRespone* other) {
  if (other == this) return;
  InternalSwap(other);
}
void YLMsgServerRespone::InternalSwap(YLMsgServerRespone* other) {
  using std::swap;
  prior_ip_.Swap(&other->prior_ip_);
  back_ip_.Swap(&other->back_ip_);
  swap(result_code_, other->result_code_);
  swap(port_, other->port_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata YLMsgServerRespone::GetMetadata() const {
  protobuf_YLLogin_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_YLLogin_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace Login
}  // namespace YL

// @@protoc_insertion_point(global_scope)