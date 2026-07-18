/* Two parameters, both FORWARDED. The ROM sets up no arguments before the `blx` --
 * they are already in r0/r1 -- and the function pointer therefore lands in r2. With a
 * one-parameter signature mwcc puts the pointer in r1, and with none in r0. The
 * register the pointer gets is what tells you the arity. */
void func_ov022_0209145c(int self, int a) {
    if (self == 0) return;
    (*(void (**)(int, int))(self + 0x20))(self, a);
}
