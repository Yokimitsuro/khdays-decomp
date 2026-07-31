/*
 * Ov002_ResetNineSlots - notify func_0202c06c(9) then push a zero-initialised 4-byte record for
 * each of the nine indices 0..8 via func_0202c1d8(index, &record). Part of the ov002 gameplay
 * bootstrap (dep of the constructor func_ov002_020679d4).
 *
 * ARM. The record is a 4-byte stack int cleared byte-by-byte through a pointer (so mwcc keeps its
 * address in a register and clears via [reg]); the per-iteration low-byte write goes through the
 * plain stack slot ([sp]) instead, matching the original's split addressing.
 */

typedef unsigned char u8;

extern void func_0202c06c(int n);
extern void func_0202c1d8(int index, int *record);

void func_ov002_02076924(void)
{
    int buf;
    u8 *p;
    int i;

    func_0202c06c(9);
    p = (u8 *)&buf;
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    for (i = 0; i < 9; i++) {
        *(u8 *)&buf = i & 0xff;
        func_0202c1d8(i & 0xff, &buf);
    }
}
