// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: GroupUserListGetAck.proto

#ifndef PROTOBUF_GroupUserListGetAck_2eproto__INCLUDED
#define PROTOBUF_GroupUserListGetAck_2eproto__INCLUDED

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
void  protobuf_AddDesc_GroupUserListGetAck_2eproto();
void protobuf_AssignDesc_GroupUserListGetAck_2eproto();
void protobuf_ShutdownFile_GroupUserListGetAck_2eproto();

class GroupUserListGetAck;

// ===================================================================

class GroupUserListGetAck : public ::google::protobuf::MessageLite {
 public:
  GroupUserListGetAck();
  virtual ~GroupUserListGetAck();

  GroupUserListGetAck(const GroupUserListGetAck& from);

  inline GroupUserListGetAck& operator=(const GroupUserListGetAck& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::std::string& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::std::string* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const GroupUserListGetAck& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const GroupUserListGetAck* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(GroupUserListGetAck* other);

  // implements Message ----------------------------------------------

  GroupUserListGetAck* New() const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const GroupUserListGetAck& from);
  void MergeFrom(const GroupUserListGetAck& from);
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

  // required int32 sessionId = 1;
  inline bool has_sessionid() const;
  inline void clear_sessionid();
  static const int kSessionIdFieldNumber = 1;
  inline ::google::protobuf::int32 sessionid() const;
  inline void set_sessionid(::google::protobuf::int32 value);

  // repeated int32 uid = 2;
  inline int uid_size() const;
  inline void clear_uid();
  static const int kUidFieldNumber = 2;
  inline ::google::protobuf::int32 uid(int index) const;
  inline void set_uid(int index, ::google::protobuf::int32 value);
  inline void add_uid(::google::protobuf::int32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
      uid() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
      mutable_uid();

  // @@protoc_insertion_point(class_scope:yunquan.GroupUserListGetAck)
 private:
  inline void set_has_sessionid();
  inline void clear_has_sessionid();

  ::std::string _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedField< ::google::protobuf::int32 > uid_;
  ::google::protobuf::int32 sessionid_;
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_GroupUserListGetAck_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_GroupUserListGetAck_2eproto();
  #endif
  friend void protobuf_AssignDesc_GroupUserListGetAck_2eproto();
  friend void protobuf_ShutdownFile_GroupUserListGetAck_2eproto();

  void InitAsDefaultInstance();
  static GroupUserListGetAck* default_instance_;
};
// ===================================================================


// ===================================================================

// GroupUserListGetAck

// required int32 sessionId = 1;
inline bool GroupUserListGetAck::has_sessionid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void GroupUserListGetAck::set_has_sessionid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void GroupUserListGetAck::clear_has_sessionid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void GroupUserListGetAck::clear_sessionid() {
  sessionid_ = 0;
  clear_has_sessionid();
}
inline ::google::protobuf::int32 GroupUserListGetAck::sessionid() const {
  // @@protoc_insertion_point(field_get:yunquan.GroupUserListGetAck.sessionId)
  return sessionid_;
}
inline void GroupUserListGetAck::set_sessionid(::google::protobuf::int32 value) {
  set_has_sessionid();
  sessionid_ = value;
  // @@protoc_insertion_point(field_set:yunquan.GroupUserListGetAck.sessionId)
}

// repeated int32 uid = 2;
inline int GroupUserListGetAck::uid_size() const {
  return uid_.size();
}
inline void GroupUserListGetAck::clear_uid() {
  uid_.Clear();
}
inline ::google::protobuf::int32 GroupUserListGetAck::uid(int index) const {
  // @@protoc_insertion_point(field_get:yunquan.GroupUserListGetAck.uid)
  return uid_.Get(index);
}
inline void GroupUserListGetAck::set_uid(int index, ::google::protobuf::int32 value) {
  uid_.Set(index, value);
  // @@protoc_insertion_point(field_set:yunquan.GroupUserListGetAck.uid)
}
inline void GroupUserListGetAck::add_uid(::google::protobuf::int32 value) {
  uid_.Add(value);
  // @@protoc_insertion_point(field_add:yunquan.GroupUserListGetAck.uid)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
GroupUserListGetAck::uid() const {
  // @@protoc_insertion_point(field_list:yunquan.GroupUserListGetAck.uid)
  return uid_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
GroupUserListGetAck::mutable_uid() {
  // @@protoc_insertion_point(field_mutable_list:yunquan.GroupUserListGetAck.uid)
  return &uid_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace yunquan

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_GroupUserListGetAck_2eproto__INCLUDED
