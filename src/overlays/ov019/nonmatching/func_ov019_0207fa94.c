/* UNFINISHED -- 512 vs 500 B THUMB. Verify with --thumb or the numbers are noise.
 * ov019 is 4/5 and this is the ONLY function standing between it and 100%.
 *
 * ** 2026-07-22: FOUR RELOCS IN THIS FILE WERE NEVER RELOCS. Fixed, and it matters more
 * than the 4 bytes it saved (516 -> 512): the reloc SET is now correct, so this file can
 * now in principle verify. Before, it could not have -- any size fix would still have
 * failed on reloc names.
 *   - data_ov019_0207fc78 / _7c / _80 are POOL LITERALS, not variables. The pool words are
 *     0x140B, 0x1415, 0x141F and the ROM does ONE `ldr r0, [pc]`. Reading them as extern
 *     ints costs a second load each (address, then value).
 *   - data_ov019_0207fc84 is the POOL SLOT; the datum it points at is
 *     data_ov019_0207fd78 (the OS_SPrintf format string). Naming the slot instead of the
 *     target is the classic Ghidra pool trap.
 *   How to tell, always: cross-check against the reloc table in func_index.json. Those four
 *   addresses appear NOWHERE in it. No reloc at that offset => it is a literal.
 *
 * WHAT IS LEFT: 12 bytes and the frame layout. Five local buffers (header[6], scratch[16],
 * found[16], fmtbuf[4], names[256]) plus the output struct, and mwcc assigns them different
 * sp offsets than the ROM, which cascades register allocation across the loops.
 * ROM frame: names at sp+0x84, fmtbuf at sp+0x74, scratch at sp+0x54, found at sp+0x34,
 * out at sp+0x10, header at sp+8, the two saved ids at sp+0 and sp+4.
 *
 * ** THE LEVER TO TRY FIRST (new, 2026-07-22): func_ov147_020cc00c was stuck on exactly
 * this class -- a stack-layout diff whose note recorded that all 24 permutations of its
 * locals had been swept, scripted, twice. It was matched by declaring the BIG BUFFER FIRST
 * *and* restructuring the control flow at the same time (an explicit `goto` for a guard
 * instead of a compound `if`, and the branch arms written in the ROM's fall-through order).
 * The permutation sweep alone could not find it because the declaration order only pays off
 * together with the control-flow shape. So: declare `names[256]` first, and rewrite the
 * mode==3 / iter-loop split to follow the ROM's branch order, before concluding anything.
 *
 * Also still true from the earlier pass: the header reshuffle wants data_ov019_0207fd40 held
 * as an unsigned-char BASE pointer (ldrb [base,#k]), not a signed indexed access.
 */
extern char *func_02021948(int a, unsigned short *b);
extern int func_02021980(int a, unsigned short *b);
extern void MIi_CpuClear16(int val, void *buf, int n);
extern void func_0202fcb8(char *src, unsigned short *dst);
extern void MI_CpuFill8(void *buf, int val, int n);
extern int func_020235d0(int key, int kind);
extern void OS_SPrintf(void *buf, char *fmt, int arg);
extern void func_ov002_0206d3ec(int a, int b);
extern void func_ov002_02057300(void *s);
extern char data_ov019_0207fd40[];
extern char data_ov019_0207fd78[];
extern char data_ov019_0207fd78[];

struct namelist { unsigned short *names; int a, b, c; int id; int m1; int e; };

/* Build the formatted item/ability name list for a party member: render the
 * main label, then append up to three (or one, in mode 3) sub-entries, each
 * numbered via func_020235d0, dedup-merged into the 256-entry name buffer, and
 * hand the assembled list to func_ov002_02057300. */
int func_ov019_0207fa94(int param_1, unsigned short *param_2, int param_3, unsigned short *param_4) {
    char header[6];
    struct namelist out;
    unsigned short scratch[16];
    unsigned short found[16];
    unsigned int fmtbuf[4];
    unsigned short names[256];
    char *s;
    int id1, id2, mode;
    int pos = 0;
    int i;
    unsigned short *q;

    s = func_02021948(param_1, param_2);
    id1 = func_02021980(param_1, param_2 + 4);
    id2 = func_02021980(param_1, param_2 + 8);
    mode = func_02021980(param_1, param_2 + 0xc);
    header[4] = data_ov019_0207fd40[2];
    header[5] = data_ov019_0207fd40[3];
    header[2] = data_ov019_0207fd40[4];
    header[3] = data_ov019_0207fd40[5];
    header[0] = data_ov019_0207fd40[0];
    header[1] = data_ov019_0207fd40[1];
    MIi_CpuClear16(0, names, 0x200);
    func_0202fcb8(s, names);

    if (mode == 3) {
        int val;
        MIi_CpuClear16(0, scratch, 0x20);
        MIi_CpuClear16(0, found, 0x20);
        MI_CpuFill8(fmtbuf, 0, 0x10);
        val = func_020235d0(0x1400, 10);
        func_0202fcb8(&header[4], scratch);
        OS_SPrintf(fmtbuf, data_ov019_0207fd78, val);
        func_0202fcb8((char *)fmtbuf, found);
        q = names;
        i = 0;
        do {
            pos = i;
            if (scratch[0] == *q) break;
            i = i + 1;
            q = q + 1;
        } while (i < 0x100);
        i = 0;
        q = found;
        {
            unsigned short *d = names + pos;
            do {
                if (*q == 0) break;
                i = i + 1;
                *d = *q;
                d = d + 1;
                q = q + 1;
            } while (i < 0x18);
        }
    } else {
        int iter = 0;
        do {
            int val;
            MIi_CpuClear16(0, scratch, 0x20);
            MIi_CpuClear16(0, found, 0x20);
            MI_CpuFill8(fmtbuf, 0, 0x10);
            if (iter == 0) {
                val = func_020235d0(0x140B, 10);
                func_0202fcb8(&header[4], scratch);
            } else if (iter == 1) {
                val = func_020235d0(0x1415, 10);
                func_0202fcb8(&header[2], scratch);
            } else {
                val = func_020235d0(0x141F, 10);
                func_0202fcb8(&header[0], scratch);
            }
            OS_SPrintf(fmtbuf, data_ov019_0207fd78, val);
            func_0202fcb8((char *)fmtbuf, found);
            {
                int j = pos;
                if (pos < 0x100) {
                    q = names + pos;
                    do {
                        j = i;
                        if (scratch[0] == *q) break;
                        i = i + 1;
                        q = q + 1;
                        j = pos;
                    } while (i < 0x100);
                }
                pos = j;
            }
            i = 0;
            q = found;
            param_4 = names + pos;
            do {
                if (*q == 0) break;
                i = i + 1;
                *param_4 = *q;
                param_4 = param_4 + 1;
                pos = pos + 1;
                q = q + 1;
            } while (i < 0x10);
        } while (iter != mode && (iter = iter + 1, iter < 3));
    }

    func_ov002_0206d3ec(0, id1);
    out.names = names;
    out.c = 0;
    out.m1 = 0xffffffff;
    out.b = 0;
    out.a = 0;
    out.e = 0;
    out.id = id2;
    func_ov002_02057300(&out);
    return 0;
}
