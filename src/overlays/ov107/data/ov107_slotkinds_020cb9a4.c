/* ov107 .data 0x020cb9a4-0x020cbaa4: per slot and kind, the item resource an actor's
 * sub-item spawner (func_ov107_020c92b0) creates, or -1 for none, with the two bytes it copies
 * into the created entry (+0x18, +0x19). The spawner addresses the byte columns of the first
 * record directly, which is why the ROM also carries labels at 0x020cb9a8 and 0x020cb9a9. */

typedef struct SlotKindInfo {
    int resource;             /* -1: no item for this slot/kind */
    unsigned char field_4;
    unsigned char field_5;
    char pad_6[2];
} SlotKindInfo;

SlotKindInfo data_ov107_020cb9a4[8][4] = {
    { { -1, 0, 0 }, { 0, 0, 23 }, { 0, 1, 23 }, { 0, 0, 0 } },  /* slot 0 */
    { { -1, 0, 0 }, { 1, 0, 23 }, { 1, 2, 23 }, { 0, 0, 0 } },  /* slot 1 */
    { { -1, 0, 0 }, { 3, 0, 23 }, { 3, 0, 23 }, { 3, 1, 23 } },  /* slot 2 */
    { { -1, 0, 0 }, { 4, 0, 23 }, { -1, 0, 0 }, { 2, 0, 23 } },  /* slot 3 */
    { { -1, 0, 0 }, { 0, 2, 23 }, { 0, 3, 23 }, { 0, 0, 0 } },  /* slot 4 */
    { { -1, 0, 0 }, { 9, 0, 5 }, { 0, 0, 0 }, { 0, 0, 0 } },  /* slot 5 */
    { { -1, 0, 0 }, { 10, 0, 5 }, { 0, 0, 0 }, { 0, 0, 0 } },  /* slot 6 */
    { { -1, 0, 0 }, { 5, 0, 23 }, { 0, 0, 0 }, { 0, 0, 0 } },  /* slot 7 */
};
