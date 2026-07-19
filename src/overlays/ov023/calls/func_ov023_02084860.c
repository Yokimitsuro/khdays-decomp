extern int func_02021980(int ctx, void *arg);
extern int func_02021948(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern char *func_0202bfcc(unsigned short index);

extern int func_0202c6a8(unsigned short id);
extern int func_0202a928(void *flags, int mask);

/* Script predicate: true when the entity from operand 0 is live and its collision result has the
 * bit named by operand 1 set. */
int func_ov023_02084860(int ctx, int args) {
    int entity = func_02021980(ctx, (void *)args);
    int bit = func_02021980(ctx, (void *)(args + 8));
    int id = func_02020d10(ctx, entity);
    char *node = func_0202bfcc(id);
    if ((*(unsigned short *)(node + 4) & 4) == 0) {
        if ((func_0202a928(node + 4, func_0202c6a8(id)) & (1 << bit)) != 0) {
            return 1;
        }
    }
    return 0;
}
