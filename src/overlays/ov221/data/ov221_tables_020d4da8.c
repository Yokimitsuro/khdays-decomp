/* ov221 .rodata, 0x020d4da8-0x020d4de0: the enemy's sub-item poses, its hit reaction
 * modes, four tuning constants and the kind of the saved sub-item.
 *
 * Readers: 020d4020 (Ov221_Construct) copies the saved kind and builds the sub-item from
 * it; 020d0700 (Ov221_HandleHit) picks the reaction mode from the idle/hurt pair by the
 * work's +0x77 side; 020cfdbc copies the eight poses to its frame and builds one sub-item per
 * non-negative entry. */
typedef unsigned char u8;

struct Ov221ModePair { u8 nFirst; u8 nSecond; };
struct Ov221ReactionModes { struct Ov221ModePair idle; struct Ov221ModePair hurt; };
struct Ov221Saved { int w; };

/* pose of each of the eight sub-items; -1 leaves the slot empty */
const int data_ov221_020d4da8[8] = { 25, 28, 29, 30, 31, -1, 34, 33 };

/* reaction 0x12a modes: idle side 0/1, hurt side 0/1 */
const struct Ov221ReactionModes data_ov221_020d4dc8 = { { 0, 1 }, { 2, 3 } };

/* tuning constants (fx32): 9.0, 0.873, 1.575, 4.200 */
const int data_ov221_020d4dcc[4] = { 0x9000, 0xdf6, 0x1933, 0x4333 };

/* pose of the saved sub-item */
const struct Ov221Saved data_ov221_020d4ddc = { 0x1b };
