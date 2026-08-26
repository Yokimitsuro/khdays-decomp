typedef struct Ov022BitByte {
    unsigned char bit0 : 1;
    unsigned char bit1 : 1;
    unsigned char bit2 : 1;
    unsigned char bit3 : 1;
    unsigned char bit4 : 1;
    unsigned char rest : 3;
} Ov022BitByte;

typedef struct Ov022Node {
    unsigned int flagsLow;
    unsigned int flagsHigh;
    char padding008[0xa];
    unsigned short field012;
    char padding014[0x52];
    short field066;
    char padding068[0x412];
    signed char mode47a;
    signed char modeData47b;
    char padding47c[0x38];
    int field4b4;
    char padding4b8[0x1dc];
    Ov022BitByte stateBits;
} Ov022Node;

typedef struct Ov022FlagsView {
    unsigned long long flags;
} Ov022FlagsView;

typedef struct Ov022NodeOwner {
    char padding000[0x20];
    Ov022Node *node;
} Ov022NodeOwner;

typedef struct Ov022Root {
    unsigned int flags;
    Ov022NodeOwner *firstOwner;
    char padding008[0x2c];
    unsigned char count;
    char padding035[7];
    Ov022BitByte stateBits;
    char padding03d[0xb];
    unsigned short savedMask0;
    unsigned short savedMask1;
} Ov022Root;

typedef struct Ov022RootCursor {
    char padding000[4];
    Ov022NodeOwner *owner;
    char padding008[6];
    unsigned char rowIndex;
} Ov022RootCursor;

typedef struct Ov022SlotRow {
    int x;
    int y;
    int z;
    unsigned short packedField66;
    unsigned short biasedField80;
} Ov022SlotRow;

extern Ov022Root *NNSi_FndGetCurrentRootHeap(void);
extern int func_02030788(void);
extern int func_ov022_02087344(void);
extern void func_02030de4(int index);
extern int func_ov022_02083f0c(void);
extern void func_ov022_0208a1fc(void);
extern int func_02020a9c(void);
extern void func_ov022_02087a70(void);
extern int func_ov022_0208a278(void);
extern void func_ov002_0204cb70(int actor, int mode, int modeData);
extern void func_ov022_02087890(Ov022Node *node, int rowIndex);
extern void func_ov022_020ad9b0(
    Ov022Node *node, Ov022Node *primaryNode, unsigned int flags);
extern void func_ov022_020ad474(Ov022Node *node);
extern int func_01fffe14(void);
extern void func_ov022_02087298(int index);
extern void func_ov022_02088428(int index, int field66);
extern void func_ov002_0206d798(int field66);
extern void func_ov022_02088218(int index, Ov022SlotRow *row);
extern void func_ov022_02088280(int index, unsigned short value);
extern void func_ov022_020a0678(Ov022Node *node, int isPrimary);
extern void func_ov022_020a06bc(Ov022Node *node);
extern void func_ov022_020a0008(Ov022Node *node);
extern void func_ov022_020a0710(Ov022Node *node);
extern void func_ov022_02087630(int index);
extern void func_ov022_0208a1a4(void);

extern unsigned short data_0204c190;
extern unsigned short data_0204c18c;

void func_ov022_0208739c(int unused)
{
    Ov022Root *root = NNSi_FndGetCurrentRootHeap();
    Ov022SlotRow *rowBase;
    Ov022Node *primaryNode;
    int primaryField66;
    int actor;
    int resourceBase;
    int index;
    int changed;
    Ov022SlotRow *row;
    Ov022RootCursor *cursor;
    Ov022Node *node;
    int count;

    if (func_02030788() != 0) {
        return;
    }
    if (func_ov022_02087344() == 0) {
        return;
    }
    func_02030de4(0);
    actor = func_ov022_02083f0c();
    func_ov022_0208a1fc();
    if (func_02020a9c() == 0x2a) {
        data_0204c190 |= root->savedMask0;
        data_0204c18c |= root->savedMask1;
        func_ov022_02087a70();
    }
    primaryNode = root->firstOwner->node;
    primaryField66 = primaryNode->field066;
    resourceBase = func_ov022_0208a278();
    if (primaryNode->mode47a > 0) {
        func_ov002_0204cb70(actor, primaryNode->mode47a, primaryNode->modeData47b);
    }
    count = root->count;
    index = 0;
    if (count > 0) {
        rowBase = (Ov022SlotRow *)(resourceBase + 0x44);
        cursor = (Ov022RootCursor *)root;
        int zero = index;
        int minusOne = -1;

        do {
            node = cursor->owner->node;
            short oldField66 = node->field066;
            unsigned int flags = node->flagsLow;
            row = &rowBase[cursor->rowIndex];
            changed = 0;

            if ((int)(*(long long *)node & 0x10000LL) == 0) {
                func_ov022_02087890(node, cursor->rowIndex);
            } else {
                func_ov022_020ad9b0(node, primaryNode, flags);
            }
            if ((root->flags & 4) == 0) {
                func_ov022_020ad474(node);
            }
            if (index == func_01fffe14()) {
                root->stateBits.bit4 = node->stateBits.bit3;
            } else {
                unsigned int newField66 =
                    ((unsigned int)row->packedField66 << 16) >> 19;
                if (newField66 != 0x1000) {
                    flags = node->flagsLow;
                    if ((int)(*(long long *)node & 0x10000LL) == 0) {
                        if (oldField66 != (int)newField66) {
                            func_ov022_02087298(index);
                            func_ov022_02088428(
                                index,
                                ((unsigned int)row->packedField66 << 16) >> 19);
                            func_ov002_0206d798(oldField66);
                        } else {
                            if (node->field012 == 0 &&
                                ((((Ov022FlagsView *)node)->flags & 0x100ULL) != 0)) {
                                func_ov022_02088428(index, newField66);
                            }
                        }
                        func_ov022_02088218(index, row);
                        func_ov022_02088280(index, row->biasedField80);
                        node->field4b4 = 0x6000;
                        changed = 1;
                    }
                }
            }
            if (node->field066 != minusOne) {
                func_ov022_020a0678(node, primaryField66 == node->field066);
                if (changed == 0) {
                    func_ov022_020a06bc(node);
                }
                if ((root->flags & 4) == 0) {
                    func_ov022_020a0008(node);
                }
                if (changed == 0) {
                    func_ov022_020a0710(node);
                }
                func_ov022_02087630(index);
            }
            cursor = (Ov022RootCursor *)((char *)cursor + 0xc);
            index++;
        } while (index < root->count);
    }
    func_ov022_0208a1a4();
}


