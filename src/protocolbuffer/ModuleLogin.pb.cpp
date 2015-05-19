// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ModuleLogin.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ModuleLogin.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
// @@protoc_insertion_point(includes)

namespace yunquan {

void protobuf_ShutdownFile_ModuleLogin_2eproto() {
  delete ModuleLogin::default_instance_;
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_ModuleLogin_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_ModuleLogin_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
  ModuleLogin::default_instance_ = new ModuleLogin();
  ModuleLogin::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ModuleLogin_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_ModuleLogin_2eproto_once_);
void protobuf_AddDesc_ModuleLogin_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_ModuleLogin_2eproto_once_,
                 &protobuf_AddDesc_ModuleLogin_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ModuleLogin_2eproto {
  StaticDescriptorInitializer_ModuleLogin_2eproto() {
    protobuf_AddDesc_ModuleLogin_2eproto();
  }
} static_descriptor_initializer_ModuleLogin_2eproto_;
#endif

// ===================================================================

#ifndef _MSC_VER
const int ModuleLogin::kModuleIdFieldNumber;
const int ModuleLogin::kModuleTypeFieldNumber;
#endif  // !_MSC_VER

ModuleLogin::ModuleLogin()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:yunquan.ModuleLogin)
}

void ModuleLogin::InitAsDefaultInstance() {
}

ModuleLogin::ModuleLogin(const ModuleLogin& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:yunquan.ModuleLogin)
}

void ModuleLogin::SharedCtor() {
  _cached_size_ = 0;
  moduleid_ = 0u;
  moduletype_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ModuleLogin::~ModuleLogin() {
  // @@protoc_insertion_point(destructor:yunquan.ModuleLogin)
  SharedDtor();
}

void ModuleLogin::SharedDtor() {
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void ModuleLogin::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ModuleLogin& ModuleLogin::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_ModuleLogin_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_ModuleLogin_2eproto();
#endif
  return *default_instance_;
}

ModuleLogin* ModuleLogin::default_instance_ = NULL;

ModuleLogin* ModuleLogin::New() const {
  return new ModuleLogin;
}

void ModuleLogin::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<ModuleLogin*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(moduleid_, moduletype_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->clear();
}

bool ModuleLogin::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  ::google::protobuf::io::StringOutputStream unknown_fields_string(
      mutable_unknown_fields());
  ::google::protobuf::io::CodedOutputStream unknown_fields_stream(
      &unknown_fields_string);
  // @@protoc_insertion_point(parse_start:yunquan.ModuleLogin)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 moduleId = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &moduleid_)));
          set_has_moduleid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_moduleType;
        break;
      }

      // required uint32 moduleType = 2;
      case 2: {
        if (tag == 16) {
         parse_moduleType:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &moduletype_)));
          set_has_moduletype();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(
            input, tag, &unknown_fields_stream));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:yunquan.ModuleLogin)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:yunquan.ModuleLogin)
  return false;
#undef DO_
}

void ModuleLogin::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:yunquan.ModuleLogin)
  // required uint32 moduleId = 1;
  if (has_moduleid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->moduleid(), output);
  }

  // required uint32 moduleType = 2;
  if (has_moduletype()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->moduletype(), output);
  }

  output->WriteRaw(unknown_fields().data(),
                   unknown_fields().size());
  // @@protoc_insertion_point(serialize_end:yunquan.ModuleLogin)
}

int ModuleLogin::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 moduleId = 1;
    if (has_moduleid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->moduleid());
    }

    // required uint32 moduleType = 2;
    if (has_moduletype()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->moduletype());
    }

  }
  total_size += unknown_fields().size();

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ModuleLogin::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const ModuleLogin*>(&from));
}

void ModuleLogin::MergeFrom(const ModuleLogin& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_moduleid()) {
      set_moduleid(from.moduleid());
    }
    if (from.has_moduletype()) {
      set_moduletype(from.moduletype());
    }
  }
  mutable_unknown_fields()->append(from.unknown_fields());
}

void ModuleLogin::CopyFrom(const ModuleLogin& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ModuleLogin::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void ModuleLogin::Swap(ModuleLogin* other) {
  if (other != this) {
    std::swap(moduleid_, other->moduleid_);
    std::swap(moduletype_, other->moduletype_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.swap(other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string ModuleLogin::GetTypeName() const {
  return "yunquan.ModuleLogin";
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace yunquan

// @@protoc_insertion_point(global_scope)