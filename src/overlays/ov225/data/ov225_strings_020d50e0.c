/* ov225 .data strings, 0x020d50e0-0x020d5135.
 *
 * 8 symbols in one contiguous run. Each array is sized as the original is, so
 * the literal supplies the text and the declared length pads the rest with NUL.
 */

char data_ov225_020d50e0[12] = "Ms/%02x.p";

char data_ov225_020d50ec[12] = "Bone_head";

char data_ov225_020d50f8[16] = "Bone_tail_03";

char data_ov225_020d5108[12] = "Bone_pelvis";

char data_ov225_020d5114[12] = "Bone_L_hand";

char data_ov225_020d5120[12] = "Bone_R_hand";

char data_ov225_020d512c[8] = "move";

/* rolling sub-item slot handed to each new enemy by the constructor (Ov225_Construct):
 * advances by one per construction and wraps back to 3 at 0x1f */
struct RollingCounter { unsigned char value; };
struct RollingCounter data_ov225_020d5134 = { 3 };
