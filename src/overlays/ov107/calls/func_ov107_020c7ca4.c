extern int OS_IsThreadAvailable_0x020c9848(void);
extern int func_01fffd70(void *list);
extern int func_01fffd8c(void *list);
extern void func_ov107_020c3368(int v);
extern void func_ov107_020c5c54(void *self, void *node);
extern void func_ov107_020c4d9c(void *self);

typedef struct {
    void *f0;
    char pad4[4];
    unsigned int f8 : 8;
} InnerNode;

typedef struct {
    unsigned char bit0 : 1;
    unsigned char rest : 7;
} Flags311;

void func_ov107_020c7ca4(char *self)
{
    if (*(int *)(self + 0x2e8) > 0) {
        int cooldown = *(int *)(self + 0x2e8) - *(int *)((char *)OS_IsThreadAvailable_0x020c9848() + 0x40) / 30;
        *(int *)(self + 0x2e8) = cooldown;
        if (cooldown <= 0) {
            *(int *)(self + 0x2e8) = 0;
        }
    }

    if ((unsigned)(*(unsigned short *)(self + 0x60) << 24) >> 24 & 1) {
        InnerNode *node = (InnerNode *)func_01fffd70(self + 0x22c);
        while (node != 0) {
            if ((node->f8 & 1) && node->f0 != 0) {
                func_ov107_020c3368((int)node->f0);
            }
            node = (InnerNode *)func_01fffd8c(self + 0x22c);
        }
    }

    if (*(int *)(self + 0xb4) < -0x32000) {
        func_ov107_020c5c54(self, self + 0x190);
    }

    if (*(int *)(self + 0x50) == 2) {
        if (((Flags311 *)(self + 0x311))->rest != 0) {
            ((Flags311 *)(self + 0x311))->rest--;
        }
    }

    func_ov107_020c4d9c(self);
}
