/* Script opcode: post a link message from three operands. Operand 0 is read as a
 * SIGNED halfword first -- a zero there means "no sender", encoded as -2, and
 * the operand is not resolved at all. Clears the pending slot at +0x12c and
 * reports 3. */
extern int func_02021980(void *self, void *arg);
extern void func_ov002_0206b9e4(int a, int b, int c);

int func_ov002_02074698(char *self, char *args) {
    int a;
    int b;
    int c;

    if (*(short *)args == 0) {
        a = -2;
    } else {
        a = func_02021980(self, args);
    }

    b = func_02021980(self, args + 8);
    c = func_02021980(self, args + 0x10);

    func_ov002_0206b9e4(a, b, c);
    *(int *)(self + 0x12c) = 0;
    return 3;
}
