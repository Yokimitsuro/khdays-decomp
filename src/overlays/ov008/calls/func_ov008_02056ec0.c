/*
 * Ov008_Menu_ApplyFlagPresets - OR-merge two tables of preset bit values into the
 * game-state flag store, run first during the main-menu scene setup.
 *
 * The game state is a packed bit store addressed by (bitOffset, bitWidth). Each
 * table entry names a 4-bit field via `entry.id * 4 + 0x92b` and a preset value to
 * OR into it: it reads the current field (GameState_GetField width 4), ORs in the
 * entry's preset, and writes it back (GameState_SetField width 4). Bits are only
 * ever set, never cleared.
 *
 * The first table (8 entries) is always applied. The second table (14 entries) is
 * only applied once the player is far enough in: either flag 0x200b is set, or the
 * day counter (GameState_GetField(0, 9)) has reached 0x47.
 *
 * Codegen notes:
 *  - The loop counter and the day comparison are UNSIGNED (blo/poplo), so `i` is
 *    unsigned and GameState_GetField returns unsigned.
 *  - The merged value must be held in a `unsigned short` temporary computed in its
 *    own statement (`v = entry.preset | GameState_GetField(...); SetField(.., v);`).
 *    This is what keeps the OR result flowing through r0 and lets the constant-4
 *    width argument colour r4 first (clean r4/r5/r6/r7 setup); inlining the OR into
 *    the SetField argument, or holding v as a full int, shifts the whole register
 *    allocation by one.
 */

typedef struct { int id; unsigned short preset; } Entry;

extern unsigned int func_020235d0(int field, int width);
extern void func_020235e8(int field, int width, int value);
extern int func_02023588(int flag);
extern Entry data_ov008_02090108[];
extern Entry data_ov008_0209018c[];

void func_ov008_02056ec0(void)
{
    unsigned int i;
    unsigned short v;

    i = 0;
    do {
        v = data_ov008_02090108[i].preset |
            func_020235d0(data_ov008_02090108[i].id * 4 + 0x92b, 4);
        func_020235e8(data_ov008_02090108[i].id * 4 + 0x92b, 4, v);
        i = i + 1;
    } while (i < 8);

    if (func_02023588(0x200b) == 0 && func_020235d0(0, 9) < 0x47) return;

    i = 0;
    do {
        v = data_ov008_0209018c[i].preset |
            func_020235d0(data_ov008_0209018c[i].id * 4 + 0x92b, 4);
        func_020235e8(data_ov008_0209018c[i].id * 4 + 0x92b, 4, v);
        i = i + 1;
    } while (i < 0xe);
}
