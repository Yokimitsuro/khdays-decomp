/* Equivalent, readable C (semantically complete, verified against the Ghidra
 * decompile). NOT byte-exact: this 500B THUMB name-list builder is ~250 diffs
 * from the original, dominated by frame layout of the five local buffers
 * (header[6], scratch[16], found[16], fmtbuf[4], names[256] + the output struct)
 * which mwcc lays out at different sp offsets than the original, cascading
 * register allocation across the five loops. Also: the header reshuffle needs
 * data_fd40 held as an unsigned-char BASE pointer (ldrb [base,#k]) rather than a
 * signed indexed access (ldrsb [base,rk]). RESUME: struct-wrap the locals in the
 * original frame order first, then tune loop induction. The asm stub keeps the
 * blob byte-exact. */
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
extern int data_ov019_0207fc78;
extern int data_ov019_0207fc7c;
extern int data_ov019_0207fc80;
extern char data_ov019_0207fc84[];

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
        OS_SPrintf(fmtbuf, data_ov019_0207fc84, val);
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
                val = func_020235d0(data_ov019_0207fc78, 10);
                func_0202fcb8(&header[4], scratch);
            } else if (iter == 1) {
                val = func_020235d0(data_ov019_0207fc7c, 10);
                func_0202fcb8(&header[2], scratch);
            } else {
                val = func_020235d0(data_ov019_0207fc80, 10);
                func_0202fcb8(&header[0], scratch);
            }
            OS_SPrintf(fmtbuf, data_ov019_0207fc84, val);
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
