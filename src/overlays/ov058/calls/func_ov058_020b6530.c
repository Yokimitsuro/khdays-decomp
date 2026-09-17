/* Set up this enemy's two sequence slots (0x10c each from +0x2cf0 of the shared object) and its
 * flight parameters: every slot is numbered and cleared, the flight timer at +0x2fe4 is zeroed
 * and its speed at +0x2fe8 set to 0x59a (scaled by 1.5 in hard mode), both slots register the
 * "lu" effect sequence with priority id+7, and the enemy's own emitter at +0x2648 is opened with
 * the 5-word parameter block before the first update. */
typedef unsigned char u8;

typedef struct { int w[5]; } Params;

extern int func_02023c40(void);                                                /* game mode: 1 = hard */
extern void func_0202a634(int a, void *b, int c, int d);                        /* RegisterSeqAndInit */
extern void func_ov022_02092384(int a, int b, int c, void *d);
extern void func_ov058_020b6ad4(char *self);
extern char *data_ov058_020b7e00;
extern char data_ov058_020b7dc8[];
extern Params data_ov058_020b7b9c;

void func_ov058_020b6530(char *self)
{
    Params p;
    char *base = data_ov058_020b7e00;
    char *rig = base + 0xd4 + 0x2c00;
    char *slot;
    int i;

    slot = rig;
    for (i = 0; i < 2; i++) {
        *(u8 *)(slot + 0x19) = 0;
        *(u8 *)(slot + 0x18) = i;
        slot += 0x10c;
    }
    *(int *)(rig + 0x310) = 0;
    *(int *)(rig + 0x314) = 0x59a;
    if (func_02023c40() == 1) {
        *(int *)(rig + 0x314) = (int)(((long long)*(int *)(rig + 0x314) * 0x1800 + 0x800) >> 12);
    }
    slot = rig + 0x1c;
    for (i = 0; i < 2; i++) {
        func_0202a634((int)slot, data_ov058_020b7dc8, 1, *(u8 *)(base + 9) + 7);
        slot += 0x10c;
    }
    p = data_ov058_020b7b9c;
    func_ov022_02092384((int)(self + 0x248 + 0x2400), *(u8 *)(self + 9), 5, &p);
    func_ov058_020b6ad4(self);
}
