/* ov224 .data strings, 0x020d4e20-0x020d4e75.
 *
 * 8 symbols in one contiguous run. Each array is sized as the original is, so
 * the literal supplies the text and the declared length pads the rest with NUL.
 */

char data_ov224_020d4e20[12] = "Ms/%02x.p";

char data_ov224_020d4e2c[12] = "Bone_head";

char data_ov224_020d4e38[16] = "Bone_tail_03";

char data_ov224_020d4e48[12] = "Bone_pelvis";

char data_ov224_020d4e54[12] = "Bone_L_hand";

char data_ov224_020d4e60[12] = "Bone_R_hand";

char data_ov224_020d4e6c[8] = "move";

/* rolling sub-item slot handed to each new enemy by the constructor (Ov224_Construct):
 * advances by one per construction and wraps back to 3 at 0x1f */
struct RollingCounter { unsigned char value; };
struct RollingCounter data_ov224_020d4e74 = { 3 };
