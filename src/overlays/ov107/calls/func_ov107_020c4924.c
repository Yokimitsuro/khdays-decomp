extern void func_0203c86c(int this_, int arg1);
extern void *OS_IsThreadAvailable_0x020c9848(void);
extern int func_ov107_020c9568(int ctx, void *extra);

typedef struct {
    char pad[0x5c];
    unsigned bit0 : 1;
    unsigned enableSomething : 1;
    unsigned rest : 30;
} Obj9c;

typedef struct {
    unsigned short lowFlags : 8;
    unsigned short highFlags : 8;
} Field60;

void func_ov107_020c4924(void *self_, int flag) {
    char *self = (char *)self_;
    Obj9c *t = *(Obj9c **)(self + 0x9c);
    Field60 *f60 = (Field60 *)(self + 0x60);

    if (t == 0) return;

    t->enableSomething = (f60->lowFlags & 0x80) != 0;

    if (flag != 0) {
        func_0203c86c(*(int *)(self + 0x9c), flag);
        return;
    }

    if (f60->lowFlags & 0x20) {
        func_0203c86c(*(int *)(self + 0x9c), flag);
        return;
    }

    {
        void *thr = OS_IsThreadAvailable_0x020c9848();
        int ctx = *(int *)thr;
        int result = func_ov107_020c9568(ctx, self + 0x74);
        func_0203c86c(*(int *)(self + 0x9c), result);
    }
}
