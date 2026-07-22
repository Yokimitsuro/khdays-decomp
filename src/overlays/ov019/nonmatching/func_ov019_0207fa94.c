/* ** SUPERSEDED 2026-07-22: THIS FUNCTION IS MATCHED. See staging/ov019/.
 * ov019 is now 5/5.
 *
 * The note that used to sit here blamed "frame layout of the five local buffers", and
 * the lever I had added to it -- "declare names[256] first", carried over from
 * func_ov147_020cc00c -- was WRONG. The match declares names[256] LAST.
 *
 * The real cause was a WRONGLY SIZED STRUCT. `struct namelist` was modelled with 7
 * words; the ROM's frame puts `out` at sp+0x10 and `found` at sp+0x34, so it occupies
 * 0x24 = 36 bytes = NINE words. Two trailing padding fields fix the frame and
 * everything downstream follows.
 *
 * Generalisable, and cheaper than any search: when a frame diff involves an aggregate,
 * measure the gap between its sp offset and the next object's and check it against your
 * struct's size. A struct that is too small silently shifts every later slot, which
 * reads exactly like "mwcc lays things out differently".
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
