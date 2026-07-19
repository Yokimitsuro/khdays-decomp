extern int func_02021980(int ctx, void *arg);
extern int func_02021994(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern char *func_0202bfcc(unsigned short index);
extern void func_020219b4(int ctx, int args);

extern void func_02016d10(int anim, int frame);

/* Script command: seeks the entity's animation to operand 1 (12.4 fixed point). Operand 3 asks the
 * command to block until the animation finishes. */
int func_ov023_02086a4c(int ctx, int args) {
    int entity = func_02021980(ctx, (void *)args);
    int wait = func_02021980(ctx, (void *)(args + 0x18));
    int frame = func_02021994(ctx, (void *)(args + 8));
    int id = func_02020d10(ctx, entity);
    func_02016d10(*(int *)(func_0202bfcc((unsigned short)id) + 0x7c), frame >> 12);
    if (wait == 0) {
        return 1;
    }
    *(int *)(args + 4) = id;
    *(int *)(args + 0x24) = wait;
    func_020219b4(ctx, args);
    return 0;
}
