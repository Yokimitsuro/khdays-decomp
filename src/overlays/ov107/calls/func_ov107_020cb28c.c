typedef unsigned int u32;

extern void func_ov107_020cb578(int obj);
extern void func_ov107_020cb2dc(void);
extern void func_ov107_020cb400(void);
extern void func_02039824(int *dst, int *src);

typedef struct { u32 w[3]; } Blk3;
typedef struct { u32 w[4]; } Blk4;

void func_ov107_020cb28c(int a, int b)
{
    func_ov107_020cb578(a);
    *(void (**)(void))(a + 4) = func_ov107_020cb2dc;
    *(void (**)(void))(a + 8) = func_ov107_020cb400;
    *(Blk3 *)(a + 0x10) = *(Blk3 *)b;
    *(Blk4 *)(a + 0x1c) = *(Blk4 *)b;
    func_02039824((int *)(a + 0x2c), (int *)b);
}
