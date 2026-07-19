extern int func_02021980(int ctx, void *arg);
extern int func_02021948(int ctx, void *arg);
extern int func_02021994(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern int func_0202bf84(unsigned short id);
extern void func_0202ba78(unsigned short a, unsigned short b, int c, void *d);
extern void func_ov023_020887dc(void *entity, int a, void *d, int h, int id);
extern void func_ov023_02089640(void *entity, void *target, int a, int b);
extern char data_02041dc8;

/* Script command: links the entity to a second one through the shared attach descriptor and
 * starts the follow behaviour. Operand 3, when present, overrides the default blend time. */
int func_ov023_0208598c(int ctx, char *args) {
    int e1 = func_02021980(ctx, args);
    int e2 = func_02021980(ctx, args + 8);
    int blend = 0xa4;
    int value = func_02021948(ctx, args + 0x10);
    int id1 = func_02020d10(ctx, e1);
    int id2 = func_02020d10(ctx, e2);
    int handle = func_0202bf84((unsigned short)id2);
    func_0202ba78((unsigned short)id1, (unsigned short)handle, 0, &data_02041dc8);
    if (*(short *)(args + 0x18) != 0) {
        blend = func_02021994(ctx, args + 0x18);
    }
    func_ov023_020887dc(*(char **)(*(char **)(ctx + 0x128) + 0x440) + id1 * 0x1a64,
                        0, &data_02041dc8, handle, id1);
    func_ov023_02089640(*(char **)(*(char **)(ctx + 0x128) + 0x440) + id1 * 0x1a64,
                        *(char **)(*(char **)(ctx + 0x128) + 0x440) + id2 * 0x1a64,
                        value, blend);
    return 1;
}
