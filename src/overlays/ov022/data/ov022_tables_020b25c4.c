/* ov022 .rodata tables, 0x020b25c4-0x020b2604.
 *
 * 4 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov022_SpawnVoiceCue -- start the cue that goes with an actor's action. (020a48c8): struct CueSet data_ov022_020b25c4; */
const int data_ov022_020b25c4[4] = {
    0, 0, 1, 6,
};

/* read by Ov022_SpawnVoiceCue -- start the cue that goes with an actor's action. (020a48c8): struct CueSet data_ov022_020b25d4; */
const int data_ov022_020b25d4[4] = {
    0, 1, 3, 2,
};

/* read by Ov022_TryBlockHit -- decide whether a hit request is taken as a block (0209d7c0): const struct BlockKinds data_ov022_020b25e4; */
const int data_ov022_020b25e4[4] = {
    7, 3, 11, 2,
};

/* read by ov022: set or clear one slot's claim on the actor. (0209fb98): const struct MaskTable data_ov022_020b25f4; */
const u8 data_ov022_020b25f4[16] = {
    0, 0, 32, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0,
};
