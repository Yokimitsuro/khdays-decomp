/* Tick handler of the ov156 enemy (and its byte-identical twin). If flagged (+0x1c4 & 0xa) and
 * idle (+0x1c7 == -1) and the current sub-state (+0x1c6) is not 0, 1, 3 or 5, force sub-state 5.
 * Then the placements are shuffled: the +0x398 source's (+4) goes into the +0x390 frame and into
 * the +0x38c pool's first node, the actor's own +0xa0 placement into the +0x394 frame and into
 * the +0x388 pool's first node. Unless in sub-state 4 the two
 * effects of the +0x3a0 set (+0xc, +4) are released; finally the base tick runs.
 * Destinations are struct fields through typed pointers (cf. func_ov178_020cc6b8); the actor's
 * own placement is read as a typed field too, which keeps the two `self + 0xa0` reads as two
 * separate address temps (a cast source is CSE'd into one). */
typedef struct { int w[11]; } Placement;
typedef struct { int pad; Placement placement; } Source;            /* +0x398 */
typedef struct { char pad[0x10]; Placement placement; } Frame;      /* frames and pool nodes */
typedef struct { char pad[0xa0]; Placement placement; } Actor;      /* the actor's own placement */

extern void func_0203c650(int list, int node);
extern void func_ov107_020c7ca4(int obj);

void func_ov157_020ce444(int self)
{
    int list = *(int *)(self + 0x3c);
    if ((*(unsigned char *)(self + 0x1c4) & 0xa) != 0 &&
        *(signed char *)(self + 0x1c7) == -1) {
        signed char cur = *(signed char *)(self + 0x1c6);
        if (cur != 0 && cur != 1 && cur != 3 && cur != 5) {
            ((signed char *)self)[0x1c7] = 5;
        }
    }
    {
        Frame *frame = *(Frame **)(self + 0x390);
        Source *src = *(Source **)(self + 0x398);
        frame->placement = src->placement;
    }
    {
        Frame *node = *(Frame **)*(int *)(self + 0x38c);
        Source *src = *(Source **)(self + 0x398);
        node->placement = src->placement;
    }
    {
        Frame *frame = *(Frame **)(self + 0x394);
        frame->placement = ((Actor *)self)->placement;
    }
    {
        Frame *node = *(Frame **)*(int *)(self + 0x388);
        node->placement = ((Actor *)self)->placement;
    }
    if (*(signed char *)(self + 0x1c6) != 4) {
        if (*(int *)(*(int *)(self + 0x3a0) + 0xc) != 0) {
            func_0203c650(list, *(int *)(*(int *)(self + 0x3a0) + 0xc));
            *(int *)(*(int *)(self + 0x3a0) + 0xc) = 0;
        }
        if (*(int *)(*(int *)(self + 0x3a0) + 4) != 0) {
            func_0203c650(list, *(int *)(*(int *)(self + 0x3a0) + 4));
            *(int *)(*(int *)(self + 0x3a0) + 4) = 0;
        }
    }
    func_ov107_020c7ca4(self);
}
