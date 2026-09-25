/* main 0x0203d1bc-0x0203d210: the CodeWarrior exception-table index of the seven functions built
 * with exception tables.  Each entry names the function, its code size with bit 0 set (the
 * unwind descriptor is stored inline, not through a pointer) and that inline descriptor. */

typedef unsigned int u32;

typedef struct ExceptionTableIndex {
    void (*function)(void);   /* 0x00: function start */
    u32 sizeAndFlags;         /* 0x04: code size | 1 (descriptor stored inline) */
    u32 descriptor;           /* 0x08: inline unwind descriptor */
} ExceptionTableIndex;

extern void func_0201f79c(void);
extern void func_0201fc04(void);
extern void func_0201ffec(void);
extern void func_020200b4(void);
extern void OSi_FreeStackAlloc(void);
extern void func_020207f4(void);
extern void func_02020808(void);

const ExceptionTableIndex data_0203d1bc[7] = {
    { func_0201f79c, 0x14 | 1, 0x00100000 },
    { func_0201fc04, 0x3e8 | 1, 0x0060ff00 },
    { func_0201ffec, 0xc8 | 1, 0x00600300 },
    { func_020200b4, 0x14 | 1, 0x00000000 },
    { OSi_FreeStackAlloc, 0x18 | 1, 0x00000000 },
    { func_020207f4, 0x14 | 1, 0x00100000 },
    { func_02020808, 0x2c | 1, 0x00100100 },
};
