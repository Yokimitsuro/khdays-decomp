/* NONMATCHING: structure byte-exact except one THUMB register-allocation tie.
 * The ROM coalesces the 3rd arg (o-0xe) into r2 by using the arg register as the
 * scratch offset for the obj[o-0xe] strh, then frees the O2 base register on the
 * final store (sub r0,#0xc). mwcc here keeps O2 in r2 and recomputes o-0xe for the
 * call (one extra subs), +4 bytes. No C form reproduces the coalescing. */
/* func_02032388 -- initialise an object node from a descriptor, MAIN (THUMB).
 * Zero-fills the 0x4a38-byte object, copies descriptor fields into it, seeds the
 * animation/state block at +0x4624 (type=1, +4=0x10, +8=0x80), mirrors a few fields,
 * and if the descriptor carries a name pointer (desc[0]) registers it via func_02031d90.
 * Returns 1. */
extern void MI_CpuFill8(void *dst, int data, unsigned int size);
extern void func_02031d90(void *obj, char *name, int off, unsigned int v);

int func_02032388(char *obj, int *desc) {
    int o = 0x4604;
    unsigned short v;
    MI_CpuFill8(obj, 0, 0x4a38);
    *(int *)(obj + o) = desc[1];
    switch (*(int *)(obj + o)) {
    case 1:
        *(int *)(obj + o + 4) = 0x12;
        break;
    case 2:
        *(int *)(obj + o + 4) = 0x22;
        break;
    }
    o = 0x4624;
    *(int *)(obj + o) = 1;
    *(int *)(obj + o + 4) = 0x10;
    *(int *)(obj + o + 8) = 0x80;
    *(int *)(obj + o - 0x18) = desc[2];
    *(int *)(obj + o - 0x14) = *(int *)(obj + o - 0x18);
    *(short *)(obj + o - 0xa) = (short)desc[3];
    *(short *)(obj + o - 0x8) = *(short *)(obj + o - 0xa);
    *(short *)(obj + o - 0x10) = 0;
    v = *(unsigned short *)(obj + o - 0x10);
    {
        int argoff = o - 0xe;
        *(short *)(obj + argoff) = v;
        *(short *)(obj + o - 0xc) = 0;
        if (desc[0] != 0) {
            func_02031d90(obj, (char *)desc[0], argoff, v);
        }
    }
    return 1;
}
