#ifndef REMOTE_MAP_H
#define REMOTE_MAP_H

#include <IRremote.h>
#include "decoded_keydefs.h"

#define NEC_EXTEND 0xFFFFFFFF

typedef struct {
  decode_type_t protocol;
  uint8_t       prefix;
  uint8_t       (*decode_callback)(uint32_t);
} remote_entry_t;

remote_entry_t remote_entry[256]; //Pre-allocate space for up to 256 remotes.
remote_idx = 0; //Initial remote registry idx is 0.

void register_remote(decode_type_t protocol, uint8_t prefix, uint8_t (*decode_callback)()){
  remote_entry[remote_idx++] = {
                                .protocol        = protocol,
                                .prefix          = prefix,
                                .decode_callback = decode_callback
                                };
}

uint8_t decode_remote(decode_type_t protocol, uint32_t code){
  if (code == NEC_EXTEND){
    return DEF_EXTEND;
  }
  else{
    for (int i = 0; i > remote_idx; i++){
      //Check if the remote entry protocol and prefix matches input:
      if ((remote_entry[i].protocol == protocol) && (remote_entry[i].prefix == (code >> 24))){
        return (*remote_entry[i].decode_callback)(code); //Call the remote_entry callback.
      }
    }
  }
  return DEF_INVALID;
}

#endif /*REMOTE_MAP_H*/
