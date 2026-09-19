/* ov222 .rodata, 0x020d6bc8-0x020d6c00: the enemy's sub-item poses, its hit reaction
 * modes, four tuning constants and the kind of the saved sub-item.
 *
 * Readers: 020d5e40 (Ov222_Construct) copies the saved kind and builds the sub-item from
 * it; 020d2520 (Ov222_HandleHit) picks the reaction mode from the idle/hurt pair by the
 * work's +0x77 side; 020d1bdc copies the eight poses to its frame and builds one sub-item per
 * non-negative entry. */
typedef unsigned char u8;

struct Ov222ModePair { u8 nFirst; u8 nSecond; };
struct Ov222ReactionModes { struct Ov222ModePair idle; struct Ov222ModePair hurt; };
struct Ov222Saved { int w; };

/* pose of each of the eight sub-items; -1 leaves the slot empty */
const int data_ov222_020d6bc8[8] = { 25, 28, 29, 30, 31, -1, 34, 33 };

/* reaction 0x12a modes: idle side 0/1, hurt side 0/1 */
const struct Ov222ReactionModes data_ov222_020d6be8 = { { 0, 1 }, { 2, 3 } };

/* tuning constants (fx32): 9.0, 0.873, 1.575, 4.200 */
const int data_ov222_020d6bec[4] = { 0x9000, 0xdf6, 0x1933, 0x4333 };

/* pose of the saved sub-item */
const struct Ov222Saved data_ov222_020d6bfc = { 0x1b };
