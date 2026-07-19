extern char *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov107_020c0c80(void);
extern void func_01fffc24(char *p);
extern void func_02030cf8(int slot, void *handler);
extern int func_02024ee8(void *name, int slot);
extern char *func_ov107_020ca900(int size);
extern int func_ov107_020c9554(void);
extern void func_ov107_020c9b3c(void);
extern void func_ov107_020c9858(void);
extern char *data_ov107_020cbf1c;
extern int data_ov107_020cbab8;
extern int data_ov107_020cbac4;
extern int data_ov107_020cbad0;
extern int data_ov107_020cbadc;

/* Sets the actor manager up: two render lists, the two input handlers, the four sprite sets and
 * the four 0xa00-byte actor pools, each tagged with its index. Returns the tick handler. */
void *func_ov107_020c9960(void) {
    char *self = NNSi_FndGetCurrentRootHeap();
    int i;
    char *slot;
    data_ov107_020cbf1c = self;
    func_ov107_020c0c80();
    func_01fffc24(self + 4);
    func_01fffc24(self + 0x4c);
    func_02030cf8(1, (void *)&func_ov107_020c9b3c);
    func_02030cf8(4, (void *)&func_ov107_020c9b3c);
    *(int *)(self + 0x7c) = func_02024ee8(&data_ov107_020cbab8, 0xb);
    *(int *)(self + 0x80) = func_02024ee8(&data_ov107_020cbac4, 0xb);
    *(int *)(self + 0x84) = func_02024ee8(&data_ov107_020cbad0, 0xb);
    *(int *)(self + 0x88) = func_02024ee8(&data_ov107_020cbadc, 0xb);
    i = 0;
    slot = self;
    do {
        char *pool = func_ov107_020ca900(0xa << 8);
        *(char **)(slot + 0x2c) = pool;
        pool[0x6d << 2] = (char)i;
        i++;
        slot += 4;
    } while (i < 4);
    *(int *)self = func_ov107_020c9554();
    *(int *)(self + 0x3c) = 1 << 0xc;
    *(int *)(self + 0x44) = 0;
    return (void *)&func_ov107_020c9858;
}
