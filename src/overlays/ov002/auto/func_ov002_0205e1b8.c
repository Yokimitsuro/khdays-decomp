/* First halfword of the entry cached at +0x4a4 of the ov002 root context, or 0 when
 * no entry is cached.  func_ov002_0205e1f0 is what fills that slot: it resolves the
 * entry for the current key byte (+4) out of the table at +0x498 and stores it there.
 *
 * The offset is applied in its OWN statement, back into the context pointer, with the
 * constant on the LEFT and a cast in the expression -- both halves are load-bearing.
 * Written as one `*(int *)(ctx + 0x4a4)`, mwcc evaluates the global dereference first,
 * so the deref takes r1 and the pool constant r2; the ROM has them the other way round
 * and materialises the constant in the load-use slot behind the pool load of the global.
 * Re-assigning the pointer forces the constant to be created first, and the cast stops
 * mwcc canonicalising the addition back (`ctx = ctx + 0x4a4;` uncast does not match). */
extern int data_ov002_0207f620;

unsigned int func_ov002_0205e1b8(void) {
    char *ctx;
    int entry;
    unsigned int value;

    ctx = *(char **)&data_ov002_0207f620;
    value = 0;
    ctx = (char *)(0x4a4 + (int)ctx);
    entry = *(int *)ctx;
    if (entry != 0) {
        value = *(unsigned short *)entry;
    }
    return value;
}
