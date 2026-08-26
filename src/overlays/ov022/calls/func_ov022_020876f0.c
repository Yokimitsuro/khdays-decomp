typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct Ov022Node {
    unsigned long long flags;
    char padding008[0x10];
    unsigned short flags018;
    unsigned short flags01a;
    char padding01c[0x4a];
    short field066;
    char padding068[0x410];
    short facing478;
    signed char mode47a;
    signed char modeData47b;
    char padding47c[0x10];
    VecFx32 position48c;
    char padding498[0x58];
    unsigned char packedLow2_4f0;
    unsigned char packedHigh_4f1;
    unsigned char packedLowShift3_4f2;
    unsigned char padding4f3;
    int packedBit2_4f4;
} Ov022Node;

typedef struct Ov022NodeOwner {
    char padding000[0x20];
    Ov022Node *node;
} Ov022NodeOwner;

typedef struct Ov022Root {
    unsigned int flags;
    char padding004[0xc];
    Ov022NodeOwner *primaryOwner;
    char padding014[0x34];
    unsigned short savedMask0;
    unsigned short savedMask1;
} Ov022Root;

extern char data_ov022_020b2e78[];
extern unsigned short data_0204c190;
extern unsigned short data_0204c18c;

extern int func_ov002_0206aaa0(void);
extern int func_ov022_02083f0c(void);
extern int func_ov002_0204cb18(void);
extern int func_ov022_0208a278(void);
extern void func_ov022_020acfa4(Ov022Node *node, int value);
extern VecFx32 *func_ov002_0204cde8(int actor);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern short FX_Atan2(int x, int y);
extern void func_ov022_020a0678(Ov022Node *node, int isPrimary);
extern void func_ov022_020ad474(Ov022Node *node);
extern void func_ov022_020a06bc(Ov022Node *node);
extern void func_ov022_020a0008(Ov022Node *node);
extern void func_ov022_020a0710(Ov022Node *node);
extern void func_ov022_02087630(int index);

void func_ov022_020876f0(int unused)
{
    VecFx32 target;
    VecFx32 delta;
    Ov022Node *node;
    Ov022Root *root = *(Ov022Root **)(data_ov022_020b2e78 + 4);
    int actor;
    int resource;

    if (root->primaryOwner == 0) {
        return;
    }
    if (func_ov002_0206aaa0() == 0) {
        return;
    }
    node = root->primaryOwner->node;
    if (node->field066 == -1) {
        return;
    }
    actor = func_ov022_02083f0c();
    if (func_ov002_0204cb18() == 0) {
        return;
    }

    resource = func_ov022_0208a278();
    node->packedLow2_4f0 =
        (unsigned int)(*(unsigned short *)(resource + 0x28) << 30) >> 30;
    node->packedHigh_4f1 = ((unsigned int)*(unsigned short *)(resource + 0x28) << 16) >> 24;
    node->packedLowShift3_4f2 =
        ((unsigned int)*(unsigned short *)(resource + 0x28) << 24) >> 27;
    node->packedBit2_4f4 = ((unsigned int)*(unsigned short *)(resource + 0x28) << 29) >> 31;
    func_ov022_020acfa4(node, node->packedBit2_4f4);

    target = *func_ov002_0204cde8(actor);
    VEC_Subtract(&target, &node->position48c, &delta);
    node->facing478 = FX_Atan2(delta.x, delta.z);

    if ((node->flags & 0x1000000ULL) != 0) {
        node->flags018 &= ~0xc02;
        node->flags01a &= ~0xc02;
    }
    func_ov022_020a0678(node, 1);
    if ((root->flags & 4) == 0) {
        func_ov022_020ad474(node);
    }
    func_ov022_020a06bc(node);
    if ((root->flags & 4) == 0) {
        func_ov022_020a0008(node);
    }
    func_ov022_020a0710(node);
    func_ov022_02087630(1);
    root->savedMask0 = data_0204c190;
    root->savedMask1 = data_0204c18c;
}


