// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UserLogin.proto

#ifndef PROTOBUF_UserLogin_2eproto__INCLUDED
#define PROTOBUF_UserLogin_2eproto__INCLUDED

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
void  protobuf_AddDesc_UserLogin_2eproto();
void protobuf_AssignDesc_UserLogin_2eproto();
void protobuf_ShutdownFile_UserLogin_2eproto();

class UserLogin;

// ===================================================================

class UserLogin : public ::google::protobuf::MessageLite {
 public:
  UserLogin();
  virtual ~UserLogin();

  UserLogin(const UserLogin& from);

  inline UserLogin& operator=(const UserLogin& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::std::string& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::std::string* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const UserLogin& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const UserLogin* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(UserLogin* other);

  // implements Message ----------------------------------------------

  UserLogin* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const UserLogin& from);
  void MergeFrom(const UserLogin& from);
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

  // required string clientId = 2;
  inline bool has_clientid() const;
  inline void clear_clientid();
  static const int kClientIdFieldNumber = 2;
  inline const ::std::string& clientid() const;
  inline void set_clientid(const ::std::string& value);
  inline void set_clientid(const char* value);
  inline void set_clientid(const char* value, size_t size);
  inline ::std::string* mutable_clientid();
  inline ::std::string* release_clientid();
  inline void set_allocated_clientid(::std::string* clientid);

  // required string clientSecret = 3;
  inline bool has_clientsecret() const;
  inline void clear_clientsecret();
  static const int kClientSecretFieldNumber = 3;
  inline const ::std::string& clientsecret() const;
  inline void set_clientsecret(const ::std::string& value);
  inline void set_clientsecret(const char* value);
  inline void set_clientsecret(const char* value, size_t size);
  inline ::std::string* mutable_clientsecret();
  inline ::std::string* release_clientsecret();
  inline void set_allocated_clientsecret(::std::string* clientsecret);

  // optional uint32 sessionId = 4;
  inline bool has_sessionid() const;
  inline void clear_sessionid();
  static const int kSessionIdFieldNumber = 4;
  inline ::google::protobuf::uint32 sessionid() const;
  inline void set_sessionid(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:yunquan.UserLogin)
 private:
  inline void set_has_clienttype();
  inline void clear_has_clienttype();
  inline void set_has_clientid();
  inline void clear_has_clientid();
  inline void set_has_clientsecret();
  inline void clear_has_clientsecret();
  inline void set_has_sessionid();
  inline void clear_has_sessionid();

  ::std::string _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* clientid_;
  int clienttype_;
  ::google::protobuf::uint32 sessionid_;
  ::std::string* clientsecret_;
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_UserLogin_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_UserLogin_2eproto();
  #endif
  friend void protobuf_AssignDesc_UserLogin_2eproto();
  friend void protobuf_ShutdownFile_UserLogin_2eproto();

  void InitAsDefaultInstance();
  static UserLogin* default_instance_;
};
// ===================================================================


// ===================================================================

// UserLogin

// required .yunquan.E_CLIENT_TYPE clientType = 1;
inline bool UserLogin::has_clienttype() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void UserLogin::set_has_clienttype() {
  _has_bits_[0] |= 0x00000001u;
}
inline void UserLogin::clear_has_clienttype() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void UserLogin::clear_clienttype() {
  clienttype_ = 0;
  clear_has_clienttype();
}
inline ::yunquan::E_CLIENT_TYPE UserLogin::clienttype() const {
  // @@protoc_insertion_point(field_get:yunquan.UserLogin.clientType)
  return static_cast< ::yunquan::E_CLIENT_TYPE >(clienttype_);
}
inline void UserLogin::set_clienttype(::yunquan::E_CLIENT_TYPE value) {
  assert(::yunquan::E_CLIENT_TYPE_IsValid(value));
  set_has_clienttype();
  clienttype_ = value;
  // @@protoc_insertion_point(field_set:yunquan.UserLogin.clientType)
}

// required string clientId = 2;
inline bool UserLogin::has_clientid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void UserLogin::set_has_clientid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void UserLogin::clear_has_clientid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void UserLogin::clear_clientid() {
  if (clientid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    clientid_->clear();
  }
  clear_has_clientid();
}
inline const ::std::string& UserLogin::clientid() const {
  // @@protoc_insertion_point(field_get:yunquan.UserLogin.clientId)
  return *clientid_;
}
inline void UserLogin::set_clientid(const ::std::string& value) {
  set_has_clientid();
  if (clientid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    clientid_ = new ::std::string;
  }
  clientid_->assign(value);
  // @@protoc_insertion_point(field_set:yunquan.UserLogin.clientId)
}
inline void UserLogin::set_clientid(const char* value) {
  set_has_clientid();
  if (clientid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    clientid_ = new ::std::string;
  }
  clientid_->assign(value);
  // @@protoc_insertion_point(field_set_char:yunquan.UserLogin.clientId)
}
inline void UserLogin::set_clientid(const char* value, size_t size) {
  set_has_clientid();
  if (clientid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    clientid_ = new ::std::string;
  }
  clientid_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:yunquan.UserLogin.clientId)
}
inline ::std::string* UserLogin::mutable_clientid() {
  set_has_clientid();
  if (clientid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    clientid_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:yunquan.UserLogin.clientId)
  return clientid_;
}
inline ::std::string* UserLogin::release_clientid() {
  clear_has_clientid();
  if (clientid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = clientid_;
    clientid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void UserLogin::set_allocated_clientid(::std::string* clientid) {
  if (clientid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete clientid_;
  }
  if (clientid) {
    set_has_clientid();
    clientid_ = clientid;
  } else {
    clear_has_clientid();
    clientid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:yunquan.UserLogin.clientId)
}

// required string clientSecret = 3;
inline bool UserLogin::has_clientsecret() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void UserLogin::set_has_clientsecret() {
  _has_bits_[0] |= 0x00000004u;
}
inline void UserLogin::clear_has_clientsecret() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void UserLogin::clear_clientsecret() {
  if (clientsecret_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    clientsecret_->clear();
  }
  clear_has_clientsecret();
}
inline const ::std::string& UserLogin::clientsecret() const {
  // @@protoc_insertion_point(field_get:yunquan.UserLogin.clientSecret)
  return *clientsecret_;
}
inline void UserLogin::set_clientsecret(const ::std::string& value) {
  set_has_clientsecret();
  if (clientsecret_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    clientsecret_ = new ::std::string;
  }
  clientsecret_->assign(value);
  // @@protoc_insertion_point(field_set:yunquan.UserLogin.clientSecret)
}
inline void UserLogin::set_clientsecret(const char* value) {
  set_has_clientsecret();
  if (clientsecret_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    clientsecret_ = new ::std::string;
  }
  clientsecret_->assign(value);
  // @@protoc_insertion_point(field_set_char:yunquan.UserLogin.clientSecret)
}
inline void UserLogin::set_clientsecret(const char* value, size_t size) {
  set_has_clientsecret();
  if (clientsecret_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    clientsecret_ = new ::std::string;
  }
  clientsecret_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:yunquan.UserLogin.clientSecret)
}
inline ::std::string* UserLogin::mutable_clientsecret() {
  set_has_clientsecret();
  if (clientsecret_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    clientsecret_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:yunquan.UserLogin.clientSecret)
  return clientsecret_;
}
inline ::std::string* UserLogin::release_clientsecret() {
  clear_has_clientsecret();
  if (clientsecret_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = clientsecret_;
    clientsecret_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void UserLogin::set_allocated_clientsecret(::std::string* clientsecret) {
  if (clientsecret_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete clientsecret_;
  }
  if (clientsecret) {
    set_has_clientsecret();
    clientsecret_ = clientsecret;
  } else {
    clear_has_clientsecret();
    clientsecret_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:yunquan.UserLogin.clientSecret)
}

// optional uint32 sessionId = 4;
inline bool UserLogin::has_sessionid() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void UserLogin::set_has_sessionid() {
  _has_bits_[0] |= 0x00000008u;
}
inline void UserLogin::clear_has_sessionid() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void UserLogin::clear_sessionid() {
  sessionid_ = 0u;
  clear_has_sessionid();
}
inline ::google::protobuf::uint32 UserLogin::sessionid() const {
  // @@protoc_insertion_point(field_get:yunquan.UserLogin.sessionId)
  return sessionid_;
}
inline void UserLogin::set_sessionid(::google::protobuf::uint32 value) {
  set_has_sessionid();
  sessionid_ = value;
  // @@protoc_insertion_point(field_set:yunquan.UserLogin.sessionId)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace yunquan

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_UserLogin_2eproto__INCLUDED