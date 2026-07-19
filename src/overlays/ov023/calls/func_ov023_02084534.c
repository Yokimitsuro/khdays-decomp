extern int func_02021980(int ctx, void *arg);
extern int func_02021994(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern char *func_0202bfcc(unsigned short index);
extern void func_020219b4(int ctx, int args);

extern void func_0202bef4(unsigned short id, int kind, int value);
extern void func_02016cd0(int anim, int flags);

/* Script command: starts animation kind 1 with operand 1 as its parameter and restarts playback.
 * Operand 3 asks the command to block until it finishes. */
int func_ov023_02084534(int ctx, int args) {
    int entity = func_02021980(ctx, (void *)args);
    int wait = func_02021980(ctx, (void *)(args + 0x18));
    int value = func_02021994(ctx, (void *)(args + 8));
    int id = func_02020d10(ctx, entity);
    char *node = func_0202bfcc(id);
    func_0202bef4(id, 1, value);
    func_02016cd0(*(int *)(node + 0x7c), 0x3f);
    if (wait == 0) {
        return 1;
    }
    *(int *)(args + 4) = id;
    *(int *)(args + 0x24) = wait;
    func_020219b4(ctx, args);
    return 0;
}
