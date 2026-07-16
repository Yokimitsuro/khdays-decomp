/* func_ov024_02084e94 -- MobiClip: decoder-init trampoline.
 * Runs the pre-init hook against the static object at 0x02000ba4 before handing over to the
 * real init. */
extern void func_02000b64(void *p);
extern void func_ov024_02085154(int *ctx, int cursor, unsigned int a);

void func_ov024_02084e94(int *ctx, int cursor, unsigned int a) {
    func_02000b64((void *)0x02000ba4);
    func_ov024_02085154(ctx, cursor, a);
}
