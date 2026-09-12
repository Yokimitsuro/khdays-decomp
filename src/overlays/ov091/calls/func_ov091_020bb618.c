typedef unsigned char u8;
typedef unsigned short u16;

struct ActorSubCfg {
    int field00;
    int field04;
    char pad08[2];
    u16 field0a;
    int field0c;
    int field10;
    int field14;
    int field18;
    int field1c;
    int field20;
    char pad24[4];
    int field28;
    int field2c;
    int field30;
    int field34;
    int field38;
    int field3c;
    int field40;
    int field44;
    u16 field48;
    u16 field4a;
    u8 field4c;
    char pad4d[3];
};

extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int nBytes);
extern void func_ov022_020911f0(char *pSub, int a, int b);
struct Group;
struct Peer;
extern void func_ov022_02091254(struct Group *group, struct Peer *peer,
                                unsigned int *out, char *desc);
extern unsigned int data_ov091_020bc208[];
extern unsigned int data_ov091_020bc21c[];
extern void func_ov091_020bb868(int group, int param);

void func_ov091_020bb618(char *self)
{
    struct ActorSubCfg cfg;

    *(void **)(self + 0x2000 + 0x644) = NNSi_FndAllocFromDefaultExpHeap(0x60);
    func_ov022_020911f0(*(void **)(self + 0x2000 + 0x644), 0, 2);
    func_ov022_020911f0((char *)*(void **)(self + 0x2000 + 0x644) + 0x30, 1, 0);
    cfg.field00 = 0x541;
    cfg.field04 = 0;
    cfg.field0a = 0x800;
    cfg.field0c = 0x99a;
    cfg.field10 = 0xccd;
    cfg.field14 = 0x19000;
    cfg.field18 = 0x14000;
    cfg.field20 = 0x6000;
    cfg.field40 = 0x1000;
    cfg.field3c = 2;
    cfg.field48 = 0xd3;
    cfg.field4a = 4;
    cfg.field2c = 0x100;
    cfg.field34 = 0x100;
    cfg.field30 = 0x300;
    cfg.field38 = 5;
    cfg.field4c = 12;
    cfg.field1c = 0;
    cfg.field28 = 0;
    func_ov022_02091254((struct Group *)*(void **)(self + 0x2000 + 0x644),
                        (struct Peer *)self, data_ov091_020bc208, (char *)&cfg);
    *(void **)((char *)*(void **)(self + 0x2000 + 0x644) + 0x20) =
        (void *)&func_ov091_020bb868;

    cfg.field00 = 0x743;
    cfg.field04 = 0;
    cfg.field0c = 0x2000;
    cfg.field10 = 0xccd;
    cfg.field14 = 0x19000;
    cfg.field0a = 0;
    cfg.field1c = 0;
    cfg.field20 = 0x2000;
    cfg.field28 = 0;
    cfg.field18 = 0x1e000;
    cfg.field40 = 0x2ccd;
    cfg.field3c = 4;
    cfg.field48 = 0xd3;
    cfg.field4a = 5;
    cfg.field2c = 0x100;
    cfg.field30 = 0x300;
    cfg.field38 = 0x25;
    cfg.field4c = 2;
    cfg.field34 = 0x100;
    func_ov022_02091254((struct Group *)((char *)*(void **)(self + 0x2000 + 0x644) + 0x30),
                        (struct Peer *)self, data_ov091_020bc21c, (char *)&cfg);
    *(void **)((char *)*(void **)(self + 0x2000 + 0x644) + 0x50) =
        (void *)&func_ov091_020bb868;
}
