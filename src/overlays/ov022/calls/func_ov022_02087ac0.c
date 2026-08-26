typedef struct Ov022RootBits {
    unsigned char bit0 : 1;
    unsigned char bit1 : 1;
    unsigned char bit2 : 1;
    unsigned char bit3 : 1;
    unsigned char rest : 4;
} Ov022RootBits;

typedef struct Ov022Root {
    unsigned int flags;
    char padding004[0x30];
    unsigned char entryCount34;
    char padding035[7];
    Ov022RootBits stateBits3c;
} Ov022Root;

extern char data_ov022_020b2e78[];

extern int func_ov022_02087344(void);
extern int func_ov022_02087b7c(void);
extern int func_ov022_02088474(int index);
extern void func_ov022_020a06bc(int node);
extern void func_ov022_020a0008(int node);
extern void func_ov022_020a0710(int node);
extern int func_ov022_0208a28c(void);

void func_ov022_02087ac0(int unused)
{
    Ov022Root *root;
    char *entryCursor;
    int node;
    int index;

    entryCursor = *(char **)(data_ov022_020b2e78 + 4);
    root = (Ov022Root *)entryCursor;

    if ((*(unsigned int *)entryCursor & 2) == 0 ||
        func_ov022_02087344() == 0) {
        ((Ov022Root *)entryCursor)->stateBits3c.bit3 = 0;
        return;
    }

    ((Ov022Root *)entryCursor)->stateBits3c.bit3 = func_ov022_02087b7c();
    index = 0;
    if (index < ((Ov022Root *)entryCursor)->entryCount34) {
        do {
            if (func_ov022_02088474(index) >= 0) {
                node = *(int *)(*(int *)(entryCursor + 4) + 0x20);

                func_ov022_020a06bc(node);
                func_ov022_020a0008(node);
                func_ov022_020a0710(node);
            }
            index++;
            entryCursor += 0xc;
        } while (index < root->entryCount34);
    }
    *(unsigned char *)(func_ov022_0208a28c() + 0xc0) = 0;
}

