/* Post the message, unless the link layer says there is nobody to post to -- in
 * which case it reports success anyway, because a solo session has nothing to
 * wait for. The tag is resolved through the id table before being handed on.
 *
 * The id parameter is an INT even though the resolver takes an unsigned short:
 * the ROM narrows it at the call site (lsl #16 / lsr #16). Declaring the
 * parameter unsigned short makes the narrowing redundant and drops the pair. */
extern int func_02030694(void);
extern int func_02023e80(unsigned short id);
extern int func_ov002_0206e3d0(void *a, void *b, short tag);

int func_ov002_0206e420(void *a, void *b, int id) {
    if (func_02030694() != 0) {
        return func_ov002_0206e3d0(a, b, (short)func_02023e80(id));
    }

    return 1;
}
