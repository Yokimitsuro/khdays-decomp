extern int func_02021980(int ctx, void *arg);
extern int func_02021948(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern char *func_0202bfcc(unsigned short index);
extern int func_0202bf84(unsigned short id);
extern void func_0202bb7c(unsigned short a, unsigned short b, int value);
extern void func_0202beb8(unsigned short id, int on);
extern void func_ov023_020887dc(void *entity, int a, void *d, int h, int id);
extern void func_ov023_020888b8(void *entity, void *target, int id);
extern char data_02041dc8;

/* Script command: parents one entity to another. The mode operand picks which of the two keeps
 * driving its own transform. */
int func_ov023_020843b0(int ctx, char *args) {
    int e1 = func_02021980(ctx, args);
    int e2 = func_02021980(ctx, args + 8);
    int mode = func_02021980(ctx, args + 0x18);
    int value = func_02021948(ctx, args + 0x10);
    int id1 = func_02020d10(ctx, e1);
    int id2 = func_02020d10(ctx, e2);
    char *tbl;
    func_0202bb7c((unsigned short)id1, (unsigned short)id2, value);
    func_0202beb8((unsigned short)id1, 1);
    switch (mode) {
    case 1:
        *(unsigned short *)(func_0202bfcc((unsigned short)id2) + 4) |= 0x10;
        break;
    case 2:
        *(unsigned short *)(func_0202bfcc((unsigned short)id1) + 4) |= 8;
        break;
    }
    tbl = *(char **)(*(char **)(ctx + 0x128) + 0x440);
    if (tbl != 0) {
        func_ov023_020887dc(*(char **)(*(char **)(ctx + 0x128) + 0x440) + id1 * 0x1a64,
                            0, &data_02041dc8, func_0202bf84((unsigned short)id2), id1);
        func_ov023_020888b8(*(char **)(*(char **)(ctx + 0x128) + 0x440) + id1 * 0x1a64,
                            *(char **)(*(char **)(ctx + 0x128) + 0x440) + id2 * 0x1a64, id1);
    }
    return 1;
}
