/* Tick handler of the ov153 enemy (x3: ov153/154/155). If flagged (+0x1c4 & 0xa) and idle
 * (+0x1c7 == -1) and the current sub-state (+0x1c6) is not 0, 1, 3 or 5, force sub-state 5.
 * Unless in sub-state 6 the two attachments of the +0x394 set (+0xc, +4) are released; then
 * the actor's own +0xa0 placement is copied into the +0x388 pool's first node and into the
 * +0x390 frame, and the base tick runs (cf. func_ov191_020d0270). */
typedef struct { int w[11]; } Placement;
typedef struct { char pad[0x10]; Placement placement; } Frame;      /* frames and pool nodes */
typedef struct { char pad[0xa0]; Placement placement; } Actor;      /* the actor's own placement */

extern void func_0203c650(int list, int node);
extern void func_ov107_020c7ca4(int obj);

void func_ov155_020d3c9c(int self)
{
    int list = *(int *)(self + 0x3c);
    if ((*(unsigned char *)(self + 0x1c4) & 0xa) != 0 &&
        *(signed char *)(self + 0x1c7) == -1) {
        signed char cur = *(signed char *)(self + 0x1c6);
        if (cur != 0 && cur != 1 && cur != 3 && cur != 5) {
            ((signed char *)self)[0x1c7] = 5;
        }
    }
    if (*(signed char *)(self + 0x1c6) != 6) {
        if (*(int *)(*(int *)(self + 0x394) + 0xc) != 0) {
            func_0203c650(list, *(int *)(*(int *)(self + 0x394) + 0xc));
            *(int *)(*(int *)(self + 0x394) + 0xc) = 0;
        }
        if (*(int *)(*(int *)(self + 0x394) + 4) != 0) {
            func_0203c650(list, *(int *)(*(int *)(self + 0x394) + 4));
            *(int *)(*(int *)(self + 0x394) + 4) = 0;
        }
    }
    {
        Frame *node = *(Frame **)*(int *)(self + 0x388);
        node->placement = ((Actor *)self)->placement;
    }
    {
        Frame *frame = *(Frame **)(self + 0x390);
        frame->placement = ((Actor *)self)->placement;
    }
    func_ov107_020c7ca4(self);
}
