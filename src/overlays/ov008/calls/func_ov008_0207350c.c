/* Handle a kind-4 link message: the low halfword of the first word is the
 * payload and the high halfword selects what to do with it -- 1 forwards it to
 * the slot handler, 2 just refreshes. Anything else is ignored, and so is any
 * message of another kind (the context is still fetched first, unconditionally). */
extern int func_ov008_02050cec(void *message);
extern void func_ov008_02071618(int ctx, unsigned short payload, int flags);
extern void func_ov008_02071ebc(int ctx);

void func_ov008_0207350c(unsigned int *message, int kind) {
    int ctx = func_ov008_02050cec(message);

    if (kind != 4) {
        return;
    }

    {
        unsigned int word = *(unsigned int *)message;

        switch ((unsigned short)(word >> 16)) {
        case 1:
            func_ov008_02071618(ctx, (unsigned short)word, 0);
            break;

        case 2:
            func_ov008_02071ebc(ctx);
            break;
        }
    }
}
