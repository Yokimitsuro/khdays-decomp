/*
 * Ov002_RefreshSlotOccupancy - refresh the per-slot occupancy GameState flags (ids
 * 0x2001..0x2004) and the cached slot count. Called from the ov002 gameplay constructor
 * (func_ov002_020679d4).
 *
 * First clears all four slot flags (0x2001+i, i=0..3). If the multiplayer bit (data_0204c240 &
 * 4) is not set, it marks slot 0 occupied (count byte at data_02042a1d = 1, data_02042a1c = 0,
 * GameState flag 0x2001 = 1). Otherwise it reads the slot count from the ROM accessor
 * (*(rom+4)), then for each slot polls Slot4_GetIfOccupied: sets flag 0x2001+j to 1 and counts
 * it when occupied, else clears it; the occupied count is written back to data_02042a1d.
 *
 * THUMB. `count` is int (a plain add increment; only the final store truncates to the byte),
 * and the occupancy loop is a for so the signed `j < count` entry test yields the ble guard.
 */

typedef unsigned char u8;

extern void func_020235e8(int field, int a, int val);
extern int  CARDi_GetRomAccessor_0x020315f4(void);
extern int  func_020315c0(int index);
extern u8   data_0204c240;
extern u8   data_02042a1c;
extern u8   data_02042a1d;

void func_ov002_02069b70(void)
{
    int base = 0x2001;
    int i = 0;
    int rom;
    int count;
    int j;

    do {
        func_020235e8(i + base, 1, 0);
        i++;
    } while (i < 4);

    if ((data_0204c240 & 4) == 0) {
        data_02042a1d = 1;
        data_02042a1c = 0;
        func_020235e8(0x2001, 1, 1);
        return;
    }

    rom = CARDi_GetRomAccessor_0x020315f4();
    data_02042a1d = (u8)*(int *)(rom + 4);
    base = 0x2001;
    for (j = 0, count = 0; j < data_02042a1d; j++) {
        if (func_020315c0(j) == 0) {
            func_020235e8(j + base, 1, 0);
        } else {
            func_020235e8(j + base, 1, 1);
            count++;
        }
    }
    data_02042a1d = count;
}
