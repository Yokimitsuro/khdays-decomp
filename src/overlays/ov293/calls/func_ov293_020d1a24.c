/* Constructor of the ov293 enemy: installs the handlers (+8 tick, +0xc draw, +0x1c message,
 * +0x30/+0x34 hit callbacks, +0x1d0 on-hit, +0x1dc finish), seeds the +0x64 pose (scale 0x800,
 * y 0x800), builds the primary item from pool entry 0 (subscribed), resolves three named joints
 * into +0x390/+0x394/+0x398 (the first's +0x14 block kept at +0x2cc), keeps the named motion
 * handle (+0x39c), the two sub-items of the overlay's kind pair in a fresh 16-byte slot table
 * (+0x3a0, attached, bit 1 on their +0x5c), configures actions 0/1/2/4 (rate 0x1800) and
 * creates two placements from the zero pose at scale 0x800: +0x388 on the +0x22c list and
 * +0x38c on the +0x144 list; sound 0x11a is loaded. */
struct v2 { int w[2]; };
struct v3 { int a, b, c; };
struct slot { void *ptr; int pad; };

extern struct v2 data_ov293_020d35fc;
extern struct v3 data_02041dc8;
extern unsigned short data_ov293_020d362c[];
extern unsigned short data_ov293_020d3634[];
extern unsigned short data_ov293_020d3644[];
extern int data_ov293_020d3654;
extern void func_ov293_020d1c74(void), func_ov293_020d1cbc(void), func_ov293_020d1ce0(void);
extern void func_ov293_020d1e3c(void), func_ov293_020d1ea4(void), func_ov293_020d1ef0(void);
extern void func_ov293_020d1e1c(void);
extern void *func_ov107_020c9440();
extern void *func_0203b898();
extern void func_0203bfb4();
extern char *func_0203bee8();
extern void *func_ov107_020c9e50();
extern void *func_0203d15c();
extern void func_ov107_020c9074();
extern void func_ov107_020c92b0();
extern void *func_01fffca8();
extern int func_ov107_020c319c();
extern void func_0203355c();

void func_ov293_020d1a24(int param_1)
{
    struct v2 tbl;
    struct { struct v3 t; int scale; } g;
    int i;
    int r;

    tbl = data_ov293_020d35fc;
    *(void **)(param_1 + 8) = func_ov293_020d1c74;
    *(void **)(param_1 + 0xc) = func_ov293_020d1cbc;
    *(void **)(param_1 + 0x1c) = func_ov293_020d1ce0;
    *(void **)(param_1 + 0x34) = func_ov293_020d1e3c;
    *(void **)(param_1 + 0x30) = func_ov293_020d1ea4;
    *(void **)(param_1 + 0x1d0) = func_ov293_020d1ef0;
    *(void **)(param_1 + 0x1dc) = func_ov293_020d1e1c;
    *(int *)(param_1 + 0x70) = 0x800;
    *(int *)(param_1 + 0x64) = 0;
    *(int *)(param_1 + 0x68) = 0x800;
    *(int *)(param_1 + 0x6c) = 0;
    *(void **)(param_1 + 0x384) = func_0203b898(func_ov107_020c9440(param_1, 0));
    func_0203bfb4(*(int *)(param_1 + 0x9c), *(void **)(param_1 + 0x384));
    *(char **)(param_1 + 0x390) = func_0203bee8(*(int *)(param_1 + 0x384), 1, data_ov293_020d362c);
    *(char **)(param_1 + 0x394) = func_0203bee8(*(int *)(param_1 + 0x384), 1, data_ov293_020d3634);
    *(char **)(param_1 + 0x398) = func_0203bee8(*(int *)(param_1 + 0x384), 1, data_ov293_020d3644);
    *(char **)(param_1 + 0x2cc) = *(char **)(param_1 + 0x390) + 0x14;
    *(void **)(param_1 + 0x39c) = func_ov107_020c9e50(func_ov107_020c9440(param_1, 1), &data_ov293_020d3654);
    *(void **)(param_1 + 0x3a0) = func_0203d15c(0x10);
    for (i = 0; i < 2; i++) {
        ((struct slot *)*(int *)(param_1 + 0x3a0))[i].ptr = func_0203b898(func_ov107_020c9440(param_1, tbl.w[i]));
        func_ov107_020c9074(param_1, ((struct slot *)*(int *)(param_1 + 0x3a0))[i].ptr);
        *(int *)((char *)((struct slot *)*(int *)(param_1 + 0x3a0))[i].ptr + 0x5c) |= 2;
    }
    func_ov107_020c92b0(param_1, 0, 1, 0, 0x1800);
    func_ov107_020c92b0(param_1, 1, 1, 0, 0x1800);
    func_ov107_020c92b0(param_1, 2, 1, 0, 0x1800);
    func_ov107_020c92b0(param_1, 4, 1, 0, 0x1800);
    g.t = data_02041dc8;
    g.scale = 0x800;
    *(void **)(param_1 + 0x388) = func_01fffca8(param_1 + 0x22c, 0x10, 100);
    **(int **)(param_1 + 0x388) = func_ov107_020c319c(&g);
    {
        int *p = func_01fffca8(param_1 + 0x144, 4, 100);
        r = func_ov107_020c319c(&g);
        *p = r;
        *(int *)(param_1 + 0x38c) = r;
    }
    func_0203355c(0x11a);
}
