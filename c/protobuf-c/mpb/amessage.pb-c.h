/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: amessage.proto */

#ifndef PROTOBUF_C_amessage_2eproto__INCLUDED
#define PROTOBUF_C_amessage_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1000000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1002001 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

typedef struct _Mpb__AMessage Mpb__AMessage;

/* --- enums --- */

/* --- messages --- */

struct _Mpb__AMessage {
  ProtobufCMessage base;
  protobuf_c_boolean has_a;
  int32_t a;
  protobuf_c_boolean has_b;
  int32_t b;
};
#define MPB__AMESSAGE__INIT                             \
  {                                                     \
    PROTOBUF_C_MESSAGE_INIT(&mpb__amessage__descriptor) \
    , 0, 0, 0, 0                                        \
  }

/* Mpb__AMessage methods */
void mpb__amessage__init(Mpb__AMessage *message);
size_t mpb__amessage__get_packed_size(const Mpb__AMessage *message);
size_t mpb__amessage__pack(const Mpb__AMessage *message, uint8_t *out);
size_t mpb__amessage__pack_to_buffer(const Mpb__AMessage *message,
                                     ProtobufCBuffer *buffer);
Mpb__AMessage *mpb__amessage__unpack(ProtobufCAllocator *allocator, size_t len,
                                     const uint8_t *data);
void mpb__amessage__free_unpacked(Mpb__AMessage *message,
                                  ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Mpb__AMessage_Closure)(const Mpb__AMessage *message,
                                      void *closure_data);

/* --- services --- */

/* --- descriptors --- */

extern const ProtobufCMessageDescriptor mpb__amessage__descriptor;

PROTOBUF_C__END_DECLS

#endif /* PROTOBUF_C_amessage_2eproto__INCLUDED */