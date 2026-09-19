/* ov225 .rodata, 0x020d5094-0x020d50cc: the enemy's sub-item poses, its hit reaction
 * modes, four tuning constants and the kind of the saved sub-item.
 *
 * Readers: 020d430c (Ov225_Construct) copies the saved kind and builds the sub-item from
 * it; 020d0710 (Ov225_HandleHit) picks the reaction mode from the idle/hurt pair by the
 * work's +0x77 side; 020cfdbc copies the eight poses to its frame and builds one sub-item per
 * non-negative entry. */
typedef unsigned char u8;

struct Ov225ModePair { u8 nFirst; u8 nSecond; };
struct Ov225ReactionModes { struct Ov225ModePair idle; struct Ov225ModePair hurt; };
struct Ov225Saved { int w; };

/* pose of each of the eight sub-items; -1 leaves the slot empty */
const int data_ov225_020d5094[8] = { 25, 28, 29, 30, 31, 33, 35, 34 };

/* reaction 0x14b modes: idle side 0/1, hurt side 0/1 */
const struct Ov225ReactionModes data_ov225_020d50b4 = { { 0, 1 }, { 2, 3 } };

/* tuning constants (fx32): 9.0, 0.873, 1.575, 6.200 */
const int data_ov225_020d50b8[4] = { 0x9000, 0xdf6, 0x1933, 0x6333 };

/* pose of the saved sub-item */
const struct Ov225Saved data_ov225_020d50c8 = { 0x1b };
