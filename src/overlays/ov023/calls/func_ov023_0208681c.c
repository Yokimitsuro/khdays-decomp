extern int func_02021980(int ctx, void *arg);
extern char *func_02021948(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern int func_020200b4(const char *s);
extern int strncmp(const char *a, const char *b, int n);
extern void OS_SNPrintf(char *dst, int n, const char *fmt, const char *a);
extern void OS_SPrintf(char *dst, const char *fmt, ...);
extern int func_ov023_020895ec(void *entity, char *path);
extern int func_ov023_0208961c(void *entity, int anim);
extern int func_0201f468(int a, void *b, int c);
extern void func_0202b984(unsigned short id, int a, int b, int c);
extern void func_ov023_02089604(void *entity);
extern void func_020219b4(int ctx, char *args);
extern char data_ov023_0208a61c[];
extern char data_ov023_0208a5d8[];
extern char data_ov023_0208a620[];
extern char data_ov023_0208a62c[];
extern char data_ov023_0208a630[];
extern char data_ov023_0208a644[];

/* Script command: builds the animation file path from the operand's short-hand name, loads it onto
 * the entity, and yields until it has finished playing. */
int func_ov023_0208681c(int ctx, char *args) {
    int entity = func_02021980(ctx, args);
    char *name = func_02021948(ctx, args + 8);
    int id = func_02020d10(ctx, entity);
    char group[0x20];
    char path[0x40];
    char prefix[0x10];
    int anim;
    int loop;
    if (strncmp(name, data_ov023_0208a61c, 3) == 0) {
        OS_SNPrintf(prefix, 3, data_ov023_0208a5d8, name + 3);
        OS_SPrintf(path, data_ov023_0208a620, prefix);
        anim = func_020200b4(name + 6);
    } else {
        OS_SNPrintf(group, 3, data_ov023_0208a5d8, name);
        if (strncmp(name, data_ov023_0208a62c, 2) == 0) {
            OS_SPrintf(path, data_ov023_0208a630);
        } else {
            OS_SPrintf(path, data_ov023_0208a644, group);
        }
        anim = func_020200b4(name + 3);
    }
    func_ov023_020895ec(*(char **)(*(char **)(ctx + 0x128) + 0x440) + id * 0x1a64, path);
    if (func_0201f468(func_ov023_0208961c(
                          *(char **)(*(char **)(ctx + 0x128) + 0x440) + id * 0x1a64, anim),
                      *(char **)(ctx + 0x128) + 0x28, 0) != 0) {
        if (func_02021980(ctx, args + 0x10) != 0) {
            loop = 1;
        } else {
            loop = 0;
        }
        func_0202b984((unsigned short)id, *(int *)(*(char **)(ctx + 0x128) + 0x28), 0, 0);
        if (loop != 0) {
            func_ov023_02089604(*(char **)(*(char **)(ctx + 0x128) + 0x440) + id * 0x1a64);
        }
        if (id == 0) {
            *(int *)(args + 0x1c) = ~0x62;
        } else {
            *(int *)(args + 0x1c) = -id;
        }
    } else {
        *(int *)(args + 0x1c) = id;
    }
    func_020219b4(ctx, args);
    return 0;
}
