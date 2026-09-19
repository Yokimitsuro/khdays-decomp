/* ov221 .data strings, 0x020d4e00-0x020d4e58.
 *
 * 8 symbols in one contiguous run. Each array is sized as the original is, so
 * the literal supplies the text and the declared length pads the rest with NUL.
 */

char data_ov221_020d4e00[12] = "Ms/%02x.p";

char data_ov221_020d4e0c[12] = "Bone_head";

char data_ov221_020d4e18[16] = "Bone_tail_03";

char data_ov221_020d4e28[12] = "Bone_pelvis";

char data_ov221_020d4e34[12] = "Bone_L_hand";

char data_ov221_020d4e40[12] = "Bone_R_hand";

char data_ov221_020d4e4c[8] = "move";

/* rolling sub-item slot handed to each new enemy by the constructor (Ov221_Construct):
 * advances by one per construction and wraps back to 3 at 0x1f; kept word-aligned so the
 * section ends on the counter's word */
struct RollingCounter { unsigned char value; } __attribute__((aligned(4)));
struct RollingCounter data_ov221_020d4e54 = { 3 };
