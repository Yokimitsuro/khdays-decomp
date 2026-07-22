/* func_ov002_020518ac -- instantiate the ov002 scene class at data_ov002_0207e830, forwarding this
 * function's own trailing arguments to the constructor, and latch the instance at +4 of
 * data_ov002_0207f600. Always reports 1.
 *
 * VARIADIC with NO fixed argument of its own: the ROM's va_list is `add r1,sp,#8`, which is the
 * address of the FIRST incoming word, not of anything past it. C needs one named parameter, so the
 * first vararg is named and its own address is the list -- the same trick the ov221 pair needed,
 * and it costs nothing because the parameter is never read. */
extern int func_02023930(void *classDesc, void *va);
extern int data_ov002_0207e830;
extern int data_ov002_0207f600;

int func_ov002_020518ac(int first, ...) {
    *(int *)((char *)&data_ov002_0207f600 + 4) =
        func_02023930(&data_ov002_0207e830, (char *)&first);
    return 1;
}
