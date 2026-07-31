/*
 * func_02032388 - initialise an object node from a descriptor, MAIN (THUMB).
 *
 * Zero-fills the whole 0x4a38-byte object node, then seeds it from the 4-word
 * descriptor `desc`:
 *   - obj[+0x4604] = desc[1] (the node type); if that type is 1 or 2, stamps a
 *     matching sub-code at obj[+0x4608] (0x12 / 0x22).
 *   - seeds the animation/state block at +0x4624 (=1, +4=0x10, +8=0x80).
 *   - mirrors desc[2] into obj[+0x460c] and obj[+0x4610].
 *   - mirrors (short)desc[3] into obj[+0x461a] and obj[+0x461c].
 *   - zeros the three halfwords at +0x4614/+0x4616/+0x4618.
 *   - if the descriptor carries a name/id pointer (desc[0]), registers it via
 *     func_02031d90(obj, name).
 * Returns 1.
 *
 * NB: func_02031d90 takes TWO args (obj, name) - see src/calls/func_02031d90.c.
 * The r2/r3 live at the call are the leftover offset/value of the obj[+0x4616]
 * store, not arguments; declaring the callee with extra args forces mwcc to
 * rematerialise the offset into r2 for the call (+4 bytes) - the residue that
 * had this function parked.
 */

extern void MI_CpuFill8(void *dst, int data, unsigned int size);
extern void func_02031d90(void *obj, char *name);

int func_02032388(char *obj, int *desc)
{
    int o = 0x4604;
    unsigned short v;

    MI_CpuFill8(obj, 0, 0x4a38);
    *(int *)(obj + o) = desc[1];
    switch (*(int *)(obj + o)) {
    case 1: *(int *)(obj + o + 4) = 0x12; break;
    case 2: *(int *)(obj + o + 4) = 0x22; break;
    }
    o = 0x4624;
    *(int *)(obj + o) = 1;
    *(int *)(obj + o + 4) = 0x10;
    *(int *)(obj + o + 8) = 0x80;
    *(int *)(obj + o - 0x18) = desc[2];
    *(int *)(obj + o - 0x14) = *(int *)(obj + o - 0x18);
    *(short *)(obj + o - 0xa) = (short)desc[3];
    *(short *)(obj + o - 0x8) = *(unsigned short *)(obj + o - 0xa);
    *(short *)(obj + o - 0x10) = 0;
    v = *(unsigned short *)(obj + o - 0x10);
    *(short *)(obj + o - 0xe) = v;
    *(short *)(obj + o - 0xc) = 0;
    if (desc[0] != 0) func_02031d90(obj, (char *)desc[0]);
    return 1;
}
