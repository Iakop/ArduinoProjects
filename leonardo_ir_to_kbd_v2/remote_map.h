#ifndef REMOTE_MAP_H
#define REMOTE_MAP_H

#include <IRremote.h>
#include "decoded_keydefs.h"

#define NEC_EXTEND 0xFFFFFFFF

//Struct for the different remote types:
typedef struct {
  decode_type_t protocol;
  uint8_t       prefix;
  uint8_t       (*decode_callback)(uint32_t);
} remote_entry_t;

//Callback to put keys over keyboard interface:
void (*put_keys_callback)(keydef_t);

remote_entry_t remote_entry[256]; //Pre-allocate space for up to 256 remotes.
uint8_t remote_idx = 0; //Initial remote registry idx is 0.

void register_remote(decode_type_t protocol, uint8_t prefix, uint8_t (*decode_callback)()){
  remote_entry[remote_idx++].protocol = protocol;
  remote_entry[remote_idx++].prefix = prefix;
  remote_entry[remote_idx++].decode_callback = decode_callback;
  
  /*remote_entry[remote_idx++] = {
                                .protocol        = protocol,
                                .prefix          = prefix,
                                .decode_callback = decode_callback
                                };*/
}

uint8_t decode_remote(decode_type_t protocol, uint32_t code){

  #ifdef SERIAL_DEBUG
  sprintf(print_buf, "Protocol = %d\n\r", protocol);
  Serial.print(print_buf);
  sprintf(print_buf, "Code = 0x%08X\n\r", code);
  Serial.print(print_buf);
  #endif
  
  if (code == NEC_EXTEND){
    return DEF_EXTEND;
  }
  else{
    for (int i = 0; i > remote_idx; i++){
      //Check if the remote entry protocol and prefix matches input:
      if ((remote_entry[i].protocol == protocol) && (remote_entry[i].prefix == (code >> 24))){
        #ifdef SERIAL_DEBUG
        sprintf(print_buf, "Prefix = 0x%02X\n\r", remote_entry[i].prefix);
        Serial.print(print_buf);
        #endif
        return (*remote_entry[i].decode_callback)(code); //Call the remote_entry callback.
      }
    }
  }
  #ifdef SERIAL_DEBUG
  sprintf(print_buf, "Invalid remote code!\n\r");
  Serial.print(print_buf);
  #endif
  return DEF_INVALID;
}

void register_put_keys_callback(void (*callback)(keydef_t)){
  put_keys_callback = callback;
}

void put_keys(keydef_t keydef_val){
  put_keys_callback(keydef_val);
}

#endif /*REMOTE_MAP_H*/
