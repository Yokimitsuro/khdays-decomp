extern int OS_DisableIrqMask();
extern int OS_EnableIrqMask();
extern int func_0201f9ec();

extern int data_027e0088[];
extern char data_027e0090[];

void func_02000f48(int a, int b, int c, int d) {
    int *node;
    char *slot;
    int i;

    node = (int *)data_027e0088[1];
    if (node != 0 && node[6] != 0) {
        do {
            node = (int *)node[6];
        } while (node[6] != 0);
    }

    slot = data_027e0090;
    for (i = 0; i < 4; i++) {
        if (*(int *)slot == 0) break;
        slot += 0x20;
    }

    func_0201f9ec(slot + 4, b, 0x10);
    *(int *)slot = 1;
    *(int *)(slot + 0x14) = c;
    *(int *)(slot + 0x18) = 0;

    OS_DisableIrqMask(1);
    if (node != 0) {
        *(int *)(slot + 0x1c) = (int)node;
        node[6] = (int)slot;
    } else {
        *(int *)(slot + 0x1c) = 0;
    }

    if (data_027e0088[1] == 0) {
        data_027e0088[1] = (int)slot;
    }
    OS_EnableIrqMask(1);
}
