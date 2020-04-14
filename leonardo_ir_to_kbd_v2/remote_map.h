#ifndef REMOTE_MAP_H
#define REMOTE_MAP_H

#include <IRremote.h>
#include "decoded_keydefs.h"

#define INVALID (0x00000000)
#define NEC_EXTEND (0xFFFFFFFF)

//Struct for the different remote types:
typedef struct {
  decode_type_t protocol;
  uint16_t       prefix;
  uint8_t       (*decode_callback)(uint32_t);
} remote_entry_t;

//Callback to put keys over keyboard interface:
void (*put_keys_callback)(keydef_t);

remote_entry_t remote_entry[16]; //Pre-allocate space for up to 16 remotes.
uint8_t remote_idx = 0; //Initial remote registry idx is 0.
uint32_t prev_code = INVALID;

void register_remote(decode_type_t protocol, uint16_t prefix, uint8_t (*decode_callback)()){
  remote_entry[remote_idx].protocol = protocol;
  remote_entry[remote_idx].prefix = prefix;
  remote_entry[remote_idx].decode_callback = decode_callback;
  
  #ifdef SERIAL_DEBUG
  sprintf(print_buf, "Registered remote no: %d - Protocol no: %d - Prefix: 0x%04X - Callback addr: 0x%08X\n\r", remote_idx,  remote_entry[remote_idx].protocol, remote_entry[remote_idx].prefix, remote_entry[remote_idx].decode_callback);
  Serial.print(print_buf);
  #endif
  
  remote_idx++;
}

uint8_t decode_remote(decode_type_t protocol, uint32_t code){
  
  #ifdef SERIAL_DEBUG
  sprintf(print_buf, "Protocol = %d\n\r", protocol);
  Serial.print(print_buf);
  #endif

  if (protocol == NEC && code == NEC_EXTEND){
    #ifdef SERIAL_DEBUG
    sprintf(print_buf, "Received extend code!\n\r");
    Serial.print(print_buf);
    #endif

    code = prev_code;
  }

  #ifdef SERIAL_DEBUG
  uint16_t prefix = (code >> 16);
  uint16_t value = code;
  sprintf(print_buf, "Code =  0x%04X%04X\n\r", prefix, value);
  Serial.print(print_buf);
  #endif
  
  for (int i = 0; i < remote_idx; i++){

    #ifdef SERIAL_DEBUG
    //Prints have to be split up, since sprintf doesn't seem to handle bitshifts well.
    sprintf(print_buf, "Recv Protocol = %d - Entry Protocol = %d\n\r", protocol, remote_entry[i].protocol);
    Serial.print(print_buf);
    sprintf(print_buf, "Recv Prefix = 0x%04X - Entry Prefix = 0x%04X\n\r", prefix, remote_entry[i].prefix);
    Serial.print(print_buf);
    #endif
    
    //Check if the remote entry protocol and prefix matches input:
    if ((remote_entry[i].protocol == protocol) && (remote_entry[i].prefix == prefix)){
      prev_code = code;
      return (*remote_entry[i].decode_callback)(code); //Call the remote_entry callback.
    }
  }
  #ifdef SERIAL_DEBUG
  sprintf(print_buf, "Invalid remote code!\n\r");
  Serial.print(print_buf);
  #endif
  prev_code = INVALID;
  return DEF_INVALID;
}

void register_put_keys_callback(void (*callback)(keydef_t)){
  put_keys_callback = callback;
}

void put_keys(keydef_t keydef_val){
  put_keys_callback(keydef_val);
}

#endif /*REMOTE_MAP_H*/
