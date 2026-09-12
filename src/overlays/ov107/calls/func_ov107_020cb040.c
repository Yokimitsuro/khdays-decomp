typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    int owner;
    short id;
    u8 kind;
    u8 pad;
    int enabled;
    void *node;
    u32 field_10;
} Ov107Sub;

extern void *OS_IsThreadAvailable_0x020c9848(void);
extern int func_0203c5c0(int param_1, unsigned int param_2, unsigned int param_3, int param_4, int param_5, int *param_6);
extern int func_ov107_020cb164(int param_1);
extern void func_ov107_020cb124(int self);
extern unsigned int func_02033d0c(unsigned int param_1, unsigned int param_2, unsigned int *param_3, unsigned int param_4);

int func_ov107_020cb040(int self, int id, int kind, int enabled, void *node) {
    int base = *(int *)OS_IsThreadAvailable_0x020c9848();
    Ov107Sub *sub;
    int handle = func_0203c5c0(*(int *)(base + 0x3c), 0x64, 0x14,
                                (int)func_ov107_020cb124, (int)func_ov107_020cb164,
                                (int *)&sub);
    sub->owner = self;
    sub->id = (short)id;
    sub->kind = (u8)kind;
    sub->enabled = enabled;
    sub->node = node;
    if ((*(int *)(sub->owner + 0x40) << 31) >> 31) {
        sub->field_10 = func_02033d0c((unsigned int)sub->id, sub->kind,
                                       (u32 *)((char *)sub->node + 0x10), 0);
    }
    return handle;
}
