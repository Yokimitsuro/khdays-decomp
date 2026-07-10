/* NONMATCHING: multiple stacked codegen artifacts, ~12 bytes short. The original
 *   - inserts a dead `add r5,r5,#0` before summing table[0x14] + obj[0x920]
 *     (a `+ 0` constant mwcc folds away, same class as the dead orr/and #0);
 *   - materializes a base pointer obj+0x918 and reads obj[0x920]/obj[0x924] as
 *     +8/+0xC off it, rather than as two independent absolute offsets;
 *   - keeps a `mov r6,#0` scratch for the `add ip, r6, table[0x10], lsl #12`.
 * Semantics (from Ghidra) are exact. The 64-bit low-word bit-0 test, the /4 and /2
 * rounding divides, and the (x<<4)>>16 narrowing all reproduce; only these codegen
 * shapes diverge. */
extern int func_020358f4(int kind, int b);
extern int func_ov022_020ad7b0(int obj);
extern int func_020307f4(int a);
extern int data_0204c678;

struct Row020a2230 { char pad0[0x10]; unsigned short f10; short pad12; int f14; char pad18[0x104 - 0x18]; };

unsigned int func_ov022_020a2230(int obj, int a1, int mode) {
    struct Row020a2230 *e = (struct Row020a2230 *)&data_0204c678 + *(unsigned char *)(obj + 9);
    int v = e->f14 + *(int *)(obj + 0x920);
    int w = e->f10 * 0x1000 + *(short *)(obj + 0x924) * 0x1000;
    if (func_020358f4(*(unsigned char *)(obj + 9), 0x3d) > 0 && func_ov022_020ad7b0(obj))
        v += 0x1e000;
    if (mode == 0) {
        v = (v + ((unsigned int)(v >> 1) >> 0x1e)) >> 2;
        w = w / 2;
    }
    if ((*(unsigned long long *)(obj) & 1) == 0 && (unsigned int)v < (unsigned int)func_020307f4(0x64000))
        w = 0;
    return (unsigned int)(w << 4) >> 0x10;
}
