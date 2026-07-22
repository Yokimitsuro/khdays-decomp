/* Variadic forwarder: passes its three named arguments plus a va_list onto func_020262bc. */
extern void func_020262bc(int a, int b, int c, void *ap);

void func_020262a0(int a, int b, int c, ...) {
    func_020262bc(a, b, c, (void *)(((unsigned int)&c & ~3u) + 4));
}
