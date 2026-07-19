extern int func_02021980(int ctx, void *arg);
extern int func_02021994(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern char *func_0202bfcc(unsigned short index);

extern long long func_02020400(int a, int b);
extern void func_ov023_02088e78(void *entity, int value);

/* Script command: latches the looked-up value into the entity node's pending slot and marks it
 * dirty, then forwards it to the entity if one is spawned. */
int func_ov023_02084640(int ctx, int args) {
    int entity = func_02021980(ctx, (void *)args);
    int name = func_02021980(ctx, (void *)(args + 8));
    int id = func_02020d10(ctx, entity);
    unsigned short value = (unsigned short)func_02020400(name << 16, 0x168);
    char *node = func_0202bfcc((unsigned short)id);
    char *tbl;
    if ((*(int *)node & 0x20) == 0) {
        *(short *)(node + 0x80) = value;
        *(unsigned short *)(node + 4) |= 0x20;
    }
    tbl = *(char **)(*(char **)(ctx + 0x128) + 0x440);
    if (tbl != 0) {
        char *e = tbl + id * 0x1a64;
        if (*(int *)(e + 0x15e0) != 0) {
            func_ov023_02088e78(e, value);
        }
    }
    return 1;
}
