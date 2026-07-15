/* NONMATCHING: semantics correct, ldrsb-vs-ldrb optimization tie. The ROM loads
 * owner->+0x1c9 with a SIGNED byte load (`add r1,r3,#0x100; ldrsb [r1,#0xc9]`, 2
 * instr because ldrsb's offset maxes at 0xff) and byte-stores it to +0x1c7. Since
 * only the low byte is stored, mwcc 3.0/139 drops the dead sign-extension and emits
 * `ldrb [r3,#0x1c9]` (1 instr, 12-bit offset) -> -4B. No C form keeps the signed
 * load observable when its result is immediately byte-truncated. (Also a harmless
 * r0/r1 regalloc swap on the obj->f58 = 1 store.)
 *
 * c634 reaction handler: bail unless bit 0 of the owner's hw60 low byte is set.
 * Then latch obj->f58 = 1, notify func_ov146_020ce298(obj->f8), copy the owner's
 * +0x1c9 signed byte into +0x1c7, and dispatch state with a null callback. */
extern void func_ov146_020ce298(int arg);
extern void func_0203c634(int self, int index, void *cb);
struct hw60 { unsigned short lo:8, hi:8; };
void func_ov146_020ccdf4(int self) {
    int obj = *(int *)(self + 4);
    if ((((struct hw60 *)(*(int *)obj + 0x60))->lo & 1) == 0) {
        return;
    }
    *(int *)(obj + 0x58) = 1;
    func_ov146_020ce298(*(int *)(obj + 8));
    *(unsigned char *)(*(int *)obj + 0x1c7) = *(signed char *)(*(int *)obj + 0x1c9);
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}
