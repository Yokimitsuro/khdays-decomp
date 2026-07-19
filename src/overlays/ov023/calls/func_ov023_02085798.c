extern int func_02021980(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern char *func_0202bfcc(unsigned short index);
extern void func_0202accc(void *dst, int kind, void *src, short value);

extern int func_ov002_0205f4b4(void);
extern int func_ov002_0205f4e0(void);
extern int func_ov002_020573a4(void);
extern void func_ov023_02083a68(int a, int b);

/* Script command: nudges the entity node by the per-axis operands that the current camera mode
 * actually uses, then refreshes both HUD panels. */
int func_ov023_02085798(int ctx, char *args) {
    char *node;
    int id = func_02020d10(ctx, func_02021980(ctx, args));
    if (id != 0x40) {
        node = func_0202bfcc((unsigned short)id);
        if (func_ov002_0205f4b4() != 0) {
            func_0202accc(node + 4, 3, node + 0xe4, (short)func_02021980(ctx, args + 8));
        }
        if (func_ov002_0205f4e0() != 0) {
            func_0202accc(node + 4, 3, node + 0xe4, (short)func_02021980(ctx, args + 0x10));
        }
    }
    if (func_ov002_020573a4() != 0) {
        if (id != 0x40) {
            func_0202accc(node + 4, 3, node + 0xe4, (short)func_02021980(ctx, args + 0x10));
        }
        func_ov023_02083a68(0, 0);
        func_ov023_02083a68(0, 1);
        return 1;
    }
    return 0;
}
