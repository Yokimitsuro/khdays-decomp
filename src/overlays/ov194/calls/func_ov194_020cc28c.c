/* Draw hook of the ov194 enemy (x3: ov194/195/196): refreshes the +0x3d0 sub-node, runs the
 * ov107 base draw, copies the +0x394 item's +4 placement into the actor's +0x3a4 slot and
 * scales that copy to 0x2199 (the func_ov120_020cc280 shape with a placement mirror). */
typedef struct { int w[11]; } Placement;

extern void func_ov107_020c9ec8(int node);
extern void func_ov107_020c6980(int *self, int arg);
extern void func_0203ca9c(Placement *placement, int scale);

void func_ov194_020cc28c(int *self, int arg)
{
    func_ov107_020c9ec8(self[0xf4]);
    func_ov107_020c6980(self, arg);
    *(Placement *)(self + 0xe9) = *(Placement *)(self[0xe5] + 4);
    func_0203ca9c((Placement *)(self + 0xe9), 0x2199);
}
