typedef unsigned char u8;
typedef unsigned short u16;

extern int data_0204be18;

void func_ov004_0204f7e8(int id, int count) {
    int removed;
    int i;
    int j;

    removed = 0;
    for (i = 2; i >= 0; i--) {
        for (j = 39; j >= 0; j--) {
            if (((u16 *)((u8 *)(i * 0x50) + data_0204be18 + 0xee0))[j] == id) {
                if (count <= 0) {
                    goto done;
                }
                ((u16 *)((u8 *)(i * 0x50) + data_0204be18 + 0xee0))[j] = 0;
                removed++;
                count--;
            }
        }
    }

done:
    {
        u8 *counterBase = (u8 *)data_0204be18 + 0x810;
        if (counterBase[id] > removed) {
            counterBase[id] -= removed;
        } else {
            counterBase[id] = 0;
        }
    }
}
