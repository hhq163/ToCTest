// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UserForceOffline.proto

#ifndef PROTOBUF_UserForceOffline_2eproto__INCLUDED
#define PROTOBUF_UserForceOffline_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include "Common.pb.h"
// @@protoc_insertion_point(includes)

namespace yunquan {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_UserForceOffline_2eproto();
void protobuf_AssignDesc_UserForceOffline_2eproto();
void protobuf_ShutdownFile_UserForceOffline_2eproto();

class UserForceOffline;

// ===================================================================

class UserForceOffline : public ::google::protobuf::MessageLite {
 public:
  UserForceOffline();
  virtual ~UserForceOffline();

  UserForceOffline(const UserForceOffline& from);

  inline UserForceOffline& operator=(const UserForceOffline& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::std::string& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::std::string* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const UserForceOffline& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const UserForceOffline* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(UserForceOffline* other);

  // implements Message ----------------------------------------------

  UserForceOffline* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const UserForceOffline& from);
  void MergeFrom(const UserForceOffline& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  void DiscardUnknownFields();
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::std::string GetTypeName() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required .yunquan.E_CLIENT_TYPE clientType = 1;
  inline bool has_clienttype() const;
  inline void clear_clienttype();
  static const int kClientTypeFieldNumber = 1;
  inline ::yunquan::E_CLIENT_TYPE clienttype() const;
  inline void set_clienttype(::yunquan::E_CLIENT_TYPE value);

  // required string msg = 2;
  inline bool has_msg() const;
  inline void clear_msg();
  static const int kMsgFieldNumber = 2;
  inline const ::std::string& msg() const;
  inline void set_msg(const ::std::string& value);
  inline void set_msg(const char* value);
  inline void set_msg(const char* value, size_t size);
  inline ::std::string* mutable_msg();
  inline ::std::string* release_msg();
  inline void set_allocated_msg(::std::string* msg);

  // optional uint32 sessionId = 3;
  inline bool has_sessionid() const;
  inline void clear_sessionid();
  static const int kSessionIdFieldNumber = 3;
  inline ::google::protobuf::uint32 sessionid() const;
  inline void set_sessionid(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:yunquan.UserForceOffline)
 private:
  inline void set_has_clienttype();
  inline void clear_has_clienttype();
  inline void set_has_msg();
  inline void clear_has_msg();
  inline void set_has_sessionid();
  inline void clear_has_sessionid();

  ::std::string _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* msg_;
  int clienttype_;
  ::google::protobuf::uint32 sessionid_;
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_UserForceOffline_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_UserForceOffline_2eproto();
  #endif
  friend void protobuf_AssignDesc_UserForceOffline_2eproto();
  friend void protobuf_ShutdownFile_UserForceOffline_2eproto();

  void InitAsDefaultInstance();
  static UserForceOffline* default_instance_;
};
// ===================================================================


// ===================================================================

// UserForceOffline

// required .yunquan.E_CLIENT_TYPE clientType = 1;
inline bool UserForceOffline::has_clienttype() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void UserForceOffline::set_has_clienttype() {
  _has_bits_[0] |= 0x00000001u;
}
inline void UserForceOffline::clear_has_clienttype() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void UserForceOffline::clear_clienttype() {
  clienttype_ = 0;
  clear_has_clienttype();
}
inline ::yunquan::E_CLIENT_TYPE UserForceOffline::clienttype() const {
  // @@protoc_insertion_point(field_get:yunquan.UserForceOffline.clientType)
  return static_cast< ::yunquan::E_CLIENT_TYPE >(clienttype_);
}
inline void UserForceOffline::set_clienttype(::yunquan::E_CLIENT_TYPE value) {
  assert(::yunquan::E_CLIENT_TYPE_IsValid(value));
  set_has_clienttype();
  clienttype_ = value;
  // @@protoc_insertion_point(field_set:yunquan.UserForceOffline.clientType)
}

// required string msg = 2;
inline bool UserForceOffline::has_msg() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void UserForceOffline::set_has_msg() {
  _has_bits_[0] |= 0x00000002u;
}
inline void UserForceOffline::clear_has_msg() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void UserForceOffline::clear_msg() {
  if (msg_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    msg_->clear();
  }
  clear_has_msg();
}
inline const ::std::string& UserForceOffline::msg() const {
  // @@protoc_insertion_point(field_get:yunquan.UserForceOffline.msg)
  return *msg_;
}
inline void UserForceOffline::set_msg(const ::std::string& value) {
  set_has_msg();
  if (msg_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    msg_ = new ::std::string;
  }
  msg_->assign(value);
  // @@protoc_insertion_point(field_set:yunquan.UserForceOffline.msg)
}
inline void UserForceOffline::set_msg(const char* value) {
  set_has_msg();
  if (msg_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    msg_ = new ::std::string;
  }
  msg_->assign(value);
  // @@protoc_insertion_point(field_set_char:yunquan.UserForceOffline.msg)
}
inline void UserForceOffline::set_msg(const char* value, size_t size) {
  set_has_msg();
  if (msg_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    msg_ = new ::std::string;
  }
  msg_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:yunquan.UserForceOffline.msg)
}
inline ::std::string* UserForceOffline::mutable_msg() {
  set_has_msg();
  if (msg_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    msg_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:yunquan.UserForceOffline.msg)
  return msg_;
}
inline ::std::string* UserForceOffline::release_msg() {
  clear_has_msg();
  if (msg_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = msg_;
    msg_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void UserForceOffline::set_allocated_msg(::std::string* msg) {
  if (msg_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete msg_;
  }
  if (msg) {
    set_has_msg();
    msg_ = msg;
  } else {
    clear_has_msg();
    msg_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:yunquan.UserForceOffline.msg)
}

// optional uint32 sessionId = 3;
inline bool UserForceOffline::has_sessionid() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void UserForceOffline::set_has_sessionid() {
  _has_bits_[0] |= 0x00000004u;
}
inline void UserForceOffline::clear_has_sessionid() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void UserForceOffline::clear_sessionid() {
  sessionid_ = 0u;
  clear_has_sessionid();
}
inline ::google::protobuf::uint32 UserForceOffline::sessionid() const {
  // @@protoc_insertion_point(field_get:yunquan.UserForceOffline.sessionId)
  return sessionid_;
}
inline void UserForceOffline::set_sessionid(::google::protobuf::uint32 value) {
  set_has_sessionid();
  sessionid_ = value;
  // @@protoc_insertion_point(field_set:yunquan.UserForceOffline.sessionId)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace yunquan

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_UserForceOffline_2eproto__INCLUDED