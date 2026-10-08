/* ov028 .rodata 0x0208b560-0x0208b568: the MAC address DS Protect's emulator check
 * (Ov028_DSProt_MACOwner_IsBad, MACOwner_IsBad) treats as an emulator, 00:09:BF:00:00:31, stored with
 * every byte inverted; the last two bytes are the zero fill up to the overlay's word-aligned end. */

#include "nitro/types.h"

#define MAC_ENCODE_BYTE 0xff

const u8 data_ov028_0208b560[8] = {
    0x00 ^ MAC_ENCODE_BYTE, 0x09 ^ MAC_ENCODE_BYTE, 0xbf ^ MAC_ENCODE_BYTE,
    0x00 ^ MAC_ENCODE_BYTE, 0x00 ^ MAC_ENCODE_BYTE, 0x31 ^ MAC_ENCODE_BYTE,
};
