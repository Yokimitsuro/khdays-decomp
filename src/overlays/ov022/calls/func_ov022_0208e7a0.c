/* Walk the parts of the entry the object is currently pointing at (index at +0xc,
 * table at +0x18) and hand each one to func_ov022_0208b374 with mode 1 and a slot
 * number counting up from 0xd; then, if the entry has a follow-up hook at +0x170,
 * notify the object itself. Same skeleton as func_ov022_0208bb38, which passes each
 * part alone.
 *
 * The park note on this one blamed register pressure -- "needs 2 extra callee-saved
 * regs". It did not: func_ov022_0208b374 takes THREE arguments, not four. The stale
 * fourth argument was the whole difference; check the callee's arity before reading
 * a register spill as a compiler tie. */
extern void func_ov022_0208b374(int part, int mode, int slot);
extern void func_ov022_02090070(int self);

void func_ov022_0208e7a0(int self) {
    int e = *(int *)(self + *(int *)(self + 0xc) * 4 + 0x18);
    int i = 0;
    if ((int)*(unsigned char *)(e + 1) > 0) {
        int off = 0;
        do {
            func_ov022_0208b374(*(int *)(e + 0x168) + off, 1, i + 0xd);
            i = i + 1;
            off = off + 0x150;
        } while (i < *(unsigned char *)(e + 1));
    }
    if (*(int *)(e + 0x170) != 0) func_ov022_02090070(self);
}
