/* Per-frame update of the ov208 enemy (x3 with ov209/ov268): copies the 44-byte collision
 * shapes of the +0x3d0/+0x3d4/+0x3d8/+0x3cc parts (from +4) into the +0x3c0/+0x3c4/+0x3c8/+0x3bc
 * parts and the first +0x3b8/+0x3b4 bodies (at +0x10); a +0x1c4 bit 1/3 enemy with no pending
 * request outside sub-states 0-3 asks for sub-state 2; outside sub-states 6/8 the +0x40c part's
 * +0x14 effect is released on the +0x3c list and cleared; then the base update (ov107 7ca4) runs. */
typedef struct { int w[11]; } Shape;
struct Dst { char pad[0x10]; Shape shape; };
struct Src { int pad; Shape shape; };

extern void func_0203c650(int list, int handle);
extern void func_ov107_020c7ca4(char *self);

void func_ov209_020d252c(char *self)
{
    int s;

    ((struct Dst *)*(int *)(self + 0x3c0))->shape = ((struct Src *)*(int *)(self + 0x3d0))->shape;
    ((struct Dst *)*(int *)(self + 0x3c4))->shape = ((struct Src *)*(int *)(self + 0x3d4))->shape;
    ((struct Dst *)*(int *)(self + 0x3c8))->shape = ((struct Src *)*(int *)(self + 0x3d8))->shape;
    ((struct Dst *)*(int *)(self + 0x3bc))->shape = ((struct Src *)*(int *)(self + 0x3cc))->shape;
    ((struct Dst *)**(int **)(self + 0x3b8))->shape = ((struct Src *)*(int *)(self + 0x3d0))->shape;
    ((struct Dst *)**(int **)(self + 0x3b4))->shape = ((struct Src *)*(int *)(self + 0x3cc))->shape;
    if ((*(unsigned char *)(self + 0x1c4) & 0xa) != 0 && *(signed char *)(self + 0x1c7) == -1) {
        s = *(signed char *)(self + 0x1c6);
        if (s != 0 && s != 1 && s != 3 && s != 2) {
            *(signed char *)(self + 0x1c7) = 2;
        }
    }
    if (*(signed char *)(self + 0x1c6) != 8 && *(signed char *)(self + 0x1c6) != 6
        && *(int *)(*(int *)(self + 0x40c) + 0x14) != 0) {
        func_0203c650(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x40c) + 0x14));
        *(int *)(*(int *)(self + 0x40c) + 0x14) = 0;
    }
    func_ov107_020c7ca4(self);
}
