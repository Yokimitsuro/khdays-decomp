/* ov222 .data strings, 0x020d6c20-0x020d6c75.
 *
 * 8 symbols in one contiguous run. Each array is sized as the original is, so
 * the literal supplies the text and the declared length pads the rest with NUL.
 */

char data_ov222_020d6c20[12] = "Ms/%02x.p";

char data_ov222_020d6c2c[12] = "Bone_head";

char data_ov222_020d6c38[16] = "Bone_tail_03";

char data_ov222_020d6c48[12] = "Bone_pelvis";

char data_ov222_020d6c54[12] = "Bone_L_hand";

char data_ov222_020d6c60[12] = "Bone_R_hand";

char data_ov222_020d6c6c[8] = "move";

/* rolling sub-item slot handed to each new enemy by the constructor (Ov222_Construct):
 * advances by one per construction and wraps back to 3 at 0x1f */
struct RollingCounter { unsigned char value; };
struct RollingCounter data_ov222_020d6c74 = { 3 };
