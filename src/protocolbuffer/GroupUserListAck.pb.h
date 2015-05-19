// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: GroupUserListAck.proto

#ifndef PROTOBUF_GroupUserListAck_2eproto__INCLUDED
#define PROTOBUF_GroupUserListAck_2eproto__INCLUDED

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
// @@protoc_insertion_point(includes)

namespace yunquan {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_GroupUserListAck_2eproto();
void protobuf_AssignDesc_GroupUserListAck_2eproto();
void protobuf_ShutdownFile_GroupUserListAck_2eproto();

class GroupUserListAck;

// ===================================================================

class GroupUserListAck : public ::google::protobuf::MessageLite {
 public:
  GroupUserListAck();
  virtual ~GroupUserListAck();

  GroupUserListAck(const GroupUserListAck& from);

  inline GroupUserListAck& operator=(const GroupUserListAck& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::std::string& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::std::string* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const GroupUserListAck& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const GroupUserListAck* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(GroupUserListAck* other);

  // implements Message ----------------------------------------------

  GroupUserListAck* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const GroupUserListAck& from);
  void MergeFrom(const GroupUserListAck& from);
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

  // required int32 result = 1;
  inline bool has_result() const;
  inline void clear_result();
  static const int kResultFieldNumber = 1;
  inline ::google::protobuf::int32 result() const;
  inline void set_result(::google::protobuf::int32 value);

  // optional string msg = 2;
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

  // required int32 sessionId = 3;
  inline bool has_sessionid() const;
  inline void clear_sessionid();
  static const int kSessionIdFieldNumber = 3;
  inline ::google::protobuf::int32 sessionid() const;
  inline void set_sessionid(::google::protobuf::int32 value);

  // repeated int32 uid = 4;
  inline int uid_size() const;
  inline void clear_uid();
  static const int kUidFieldNumber = 4;
  inline ::google::protobuf::int32 uid(int index) const;
  inline void set_uid(int index, ::google::protobuf::int32 value);
  inline void add_uid(::google::protobuf::int32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
      uid() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
      mutable_uid();

  // @@protoc_insertion_point(class_scope:yunquan.GroupUserListAck)
 private:
  inline void set_has_result();
  inline void clear_has_result();
  inline void set_has_msg();
  inline void clear_has_msg();
  inline void set_has_sessionid();
  inline void clear_has_sessionid();

  ::std::string _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* msg_;
  ::google::protobuf::int32 result_;
  ::google::protobuf::int32 sessionid_;
  ::google::protobuf::RepeatedField< ::google::protobuf::int32 > uid_;
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_GroupUserListAck_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_GroupUserListAck_2eproto();
  #endif
  friend void protobuf_AssignDesc_GroupUserListAck_2eproto();
  friend void protobuf_ShutdownFile_GroupUserListAck_2eproto();

  void InitAsDefaultInstance();
  static GroupUserListAck* default_instance_;
};
// ===================================================================


// ===================================================================

// GroupUserListAck

// required int32 result = 1;
inline bool GroupUserListAck::has_result() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void GroupUserListAck::set_has_result() {
  _has_bits_[0] |= 0x00000001u;
}
inline void GroupUserListAck::clear_has_result() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void GroupUserListAck::clear_result() {
  result_ = 0;
  clear_has_result();
}
inline ::google::protobuf::int32 GroupUserListAck::result() const {
  // @@protoc_insertion_point(field_get:yunquan.GroupUserListAck.result)
  return result_;
}
inline void GroupUserListAck::set_result(::google::protobuf::int32 value) {
  set_has_result();
  result_ = value;
  // @@protoc_insertion_point(field_set:yunquan.GroupUserListAck.result)
}

// optional string msg = 2;
inline bool GroupUserListAck::has_msg() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void GroupUserListAck::set_has_msg() {
  _has_bits_[0] |= 0x00000002u;
}
inline void GroupUserListAck::clear_has_msg() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void GroupUserListAck::clear_msg() {
  if (msg_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    msg_->clear();
  }
  clear_has_msg();
}
inline const ::std::string& GroupUserListAck::msg() const {
  // @@protoc_insertion_point(field_get:yunquan.GroupUserListAck.msg)
  return *msg_;
}
inline void GroupUserListAck::set_msg(const ::std::string& value) {
  set_has_msg();
  if (msg_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    msg_ = new ::std::string;
  }
  msg_->assign(value);
  // @@protoc_insertion_point(field_set:yunquan.GroupUserListAck.msg)
}
inline void GroupUserListAck::set_msg(const char* value) {
  set_has_msg();
  if (msg_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    msg_ = new ::std::string;
  }
  msg_->assign(value);
  // @@protoc_insertion_point(field_set_char:yunquan.GroupUserListAck.msg)
}
inline void GroupUserListAck::set_msg(const char* value, size_t size) {
  set_has_msg();
  if (msg_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    msg_ = new ::std::string;
  }
  msg_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:yunquan.GroupUserListAck.msg)
}
inline ::std::string* GroupUserListAck::mutable_msg() {
  set_has_msg();
  if (msg_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    msg_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:yunquan.GroupUserListAck.msg)
  return msg_;
}
inline ::std::string* GroupUserListAck::release_msg() {
  clear_has_msg();
  if (msg_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = msg_;
    msg_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void GroupUserListAck::set_allocated_msg(::std::string* msg) {
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
  // @@protoc_insertion_point(field_set_allocated:yunquan.GroupUserListAck.msg)
}

// required int32 sessionId = 3;
inline bool GroupUserListAck::has_sessionid() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void GroupUserListAck::set_has_sessionid() {
  _has_bits_[0] |= 0x00000004u;
}
inline void GroupUserListAck::clear_has_sessionid() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void GroupUserListAck::clear_sessionid() {
  sessionid_ = 0;
  clear_has_sessionid();
}
inline ::google::protobuf::int32 GroupUserListAck::sessionid() const {
  // @@protoc_insertion_point(field_get:yunquan.GroupUserListAck.sessionId)
  return sessionid_;
}
inline void GroupUserListAck::set_sessionid(::google::protobuf::int32 value) {
  set_has_sessionid();
  sessionid_ = value;
  // @@protoc_insertion_point(field_set:yunquan.GroupUserListAck.sessionId)
}

// repeated int32 uid = 4;
inline int GroupUserListAck::uid_size() const {
  return uid_.size();
}
inline void GroupUserListAck::clear_uid() {
  uid_.Clear();
}
inline ::google::protobuf::int32 GroupUserListAck::uid(int index) const {
  // @@protoc_insertion_point(field_get:yunquan.GroupUserListAck.uid)
  return uid_.Get(index);
}
inline void GroupUserListAck::set_uid(int index, ::google::protobuf::int32 value) {
  uid_.Set(index, value);
  // @@protoc_insertion_point(field_set:yunquan.GroupUserListAck.uid)
}
inline void GroupUserListAck::add_uid(::google::protobuf::int32 value) {
  uid_.Add(value);
  // @@protoc_insertion_point(field_add:yunquan.GroupUserListAck.uid)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
GroupUserListAck::uid() const {
  // @@protoc_insertion_point(field_list:yunquan.GroupUserListAck.uid)
  return uid_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
GroupUserListAck::mutable_uid() {
  // @@protoc_insertion_point(field_mutable_list:yunquan.GroupUserListAck.uid)
  return &uid_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace yunquan

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_GroupUserListAck_2eproto__INCLUDED