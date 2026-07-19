extern int func_02021980(int ctx, void *arg);
extern int func_02021994(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern void func_020219b4(int ctx, int args);

extern long long func_02020400(int a, int b);
extern int func_ov023_02084a44(int ctx, int entity, int frame);

/* Script command: plays the animation named by operand 1 on the entity from operand 0. */
int func_ov023_02084bac(int ctx, int args) {
    int entity = func_02021980(ctx, (void *)args);
    int anim = func_02021980(ctx, (void *)(args + 8));
    int obj = func_02020d10(ctx, entity);
    unsigned short frame = (unsigned short)func_02020400(anim << 16, 0x168);
    return func_ov023_02084a44(ctx, obj, frame);
}
