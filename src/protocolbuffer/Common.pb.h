// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Common.proto

#ifndef PROTOBUF_Common_2eproto__INCLUDED
#define PROTOBUF_Common_2eproto__INCLUDED

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
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
// @@protoc_insertion_point(includes)

namespace yunquan {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_Common_2eproto();
void protobuf_AssignDesc_Common_2eproto();
void protobuf_ShutdownFile_Common_2eproto();


enum CMD {
  CMD_USER_LOGIN = 1,
  CMD_USER_LOGIN_ACK = 2,
  CMD_USER_LOGOUT = 3,
  CMD_USER_LOGOUT_ACK = 4,
  CMD_USER_HEARTBEAT = 5,
  CMD_USER_HEARTBEAT_ACK = 6,
  CMD_USER_FORCE_OFFLINE = 7,
  CMD_USER_FORCE_OFFLINE_ACK = 8,
  CMD_USER_FORBIDDEN = 9,
  CMD_USER_FORBIDDEN_ACK = 10,
  CMD_USER_CHECK_UPDATE = 11,
  CMD_USER_CHECK_UPDATE_ACK = 12,
  CMD_MSG_P2P_SEND = 257,
  CMD_MSG_P2P_SEND_ACK = 258,
  CMD_MSG_P2P_RECV = 259,
  CMD_MSG_P2P_RECV_ACK = 260,
  CMD_MSG_GROUP_SEND = 261,
  CMD_MSG_GROUP_SEND_ACK = 262,
  CMD_MSG_GROUP_RECV = 263,
  CMD_MSG_GROUP_RECV_ACK = 264,
  CMD_MSG_NOTIF = 265,
  CMD_MSG_NOTIF_ACK = 266,
  CMD_MSG_SYNC = 267,
  CMD_MSG_SYNC_ACK = 268,
  CMD_MSG_PUSH = 269,
  CMD_MSG_PUSH_ACK = 270,
  CMD_GROUP_MEMBER_ADD = 513,
  CMD_GROUP_MEMBER_ADD_ACK = 514,
  CMD_GROUP_MEMBER_DELETE = 515,
  CMD_GROUP_MEMBER_DELETE_ACK = 516,
  CMD_GROUP_MEMBER_QUIT = 517,
  CMD_GROUP_MEMBER_QUIT_ACK = 518,
  CMD_GROUP_MEMBER_CHG = 519,
  CMD_GROUP_MEMBER_CHG_ACK = 520,
  CMD_GROUP_INFO_CHG = 521,
  CMD_GROUP_INFO_CHG_ACK = 522,
  CMD_CS_UPDATE_VER_NOTIFY = 1025,
  CMD_CS_UPDATE_VER_NOTIFY_ACK = 1026,
  CMD_CS_USER_INFO_GET = 1027,
  CMD_CS_USER_INFO_GET_ACK = 1028,
  CMD_CS_GROUP_USER_LIST_GET = 1029,
  CMD_CS_GROUP_USER_LIST_GET_ACK = 1030,
  CMD_SYS_MODULE_LOGIN = 2049,
  CMD_SYS_MODULE_LOGIN_ACK = 2050,
  CMD_SYS_MODULE_LOGOUT = 2051,
  CMD_SYS_MODULE_LOGOUT_ACK = 2052,
  CMD_SYS_HEART_BEAT = 2053,
  CMD_SYS_HEART_BEAT_ACK = 2054,
  CMD_SYS_USER_CLOSE = 2055,
  CMD_SYS_USER_CLOSE_ACK = 2056,
  CMD_SYS_USER_CLOSE_ALL = 2057,
  CMD_SYS_USER_CLOSE_ALL_ACK = 2058,
  CMD_SYS_USER_RESET = 2059,
  CMD_SYS_USER_RESET_ACK = 2060
};
bool CMD_IsValid(int value);
const CMD CMD_MIN = CMD_USER_LOGIN;
const CMD CMD_MAX = CMD_SYS_USER_RESET_ACK;
const int CMD_ARRAYSIZE = CMD_MAX + 1;

enum E_RESULT {
  RES_SUCCESS = 0,
  RES_UNKNOWN = 1,
  RES_PKG_ERR = 2,
  RES_VERIFY_CODE_ERR = 101,
  RES_SID_ERR = 102,
  RES_MOBILENO_EXISTED = 103,
  RES_MOBILENO_NOTEXISTED = 104,
  RES_ERR_PASS = 105,
  RES_USERID_NOTEXISTED = 106,
  RES_TOKEN_EXPIRED = 107,
  RES_FILE_TOOLARGE = 201,
  RES_MISS_MD5 = 202,
  RES_MD5_ERR = 203
};
bool E_RESULT_IsValid(int value);
const E_RESULT E_RESULT_MIN = RES_SUCCESS;
const E_RESULT E_RESULT_MAX = RES_MD5_ERR;
const int E_RESULT_ARRAYSIZE = E_RESULT_MAX + 1;

enum E_USER_TYPE {
  UT_UNKNOWN = 0,
  UT_USER = 1,
  UT_VISITOR = 2
};
bool E_USER_TYPE_IsValid(int value);
const E_USER_TYPE E_USER_TYPE_MIN = UT_UNKNOWN;
const E_USER_TYPE E_USER_TYPE_MAX = UT_VISITOR;
const int E_USER_TYPE_ARRAYSIZE = E_USER_TYPE_MAX + 1;

enum E_CLIENT_TYPE {
  CT_UNKNOWN = 0,
  CT_ANDROID = 1,
  CT_IOS = 2,
  CT_WEB = 3
};
bool E_CLIENT_TYPE_IsValid(int value);
const E_CLIENT_TYPE E_CLIENT_TYPE_MIN = CT_UNKNOWN;
const E_CLIENT_TYPE E_CLIENT_TYPE_MAX = CT_WEB;
const int E_CLIENT_TYPE_ARRAYSIZE = E_CLIENT_TYPE_MAX + 1;

enum E_NOTIF_TYPE {
  NT_UNKNOWN = 0,
  NT_SYSTEM = 1,
  NT_CHAT = 2,
  NT_ACTIVITY = 3
};
bool E_NOTIF_TYPE_IsValid(int value);
const E_NOTIF_TYPE E_NOTIF_TYPE_MIN = NT_UNKNOWN;
const E_NOTIF_TYPE E_NOTIF_TYPE_MAX = NT_ACTIVITY;
const int E_NOTIF_TYPE_ARRAYSIZE = E_NOTIF_TYPE_MAX + 1;

// ===================================================================


// ===================================================================


// ===================================================================


// @@protoc_insertion_point(namespace_scope)

}  // namespace yunquan

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Common_2eproto__INCLUDED
