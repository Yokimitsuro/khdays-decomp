extern void func_ov107_020c9ec8(int node);
extern void func_0202a818(unsigned short *anim, int frame);
extern void func_ov107_020c6980(int obj, int frame);
/* Per-frame tick: refresh the child node (+0x3d8), advance the animation held by the model
 * (*(obj+0x3e4))+0x88, then run the shared transform update. */
void func_ov237_020cc80c(int obj, int frame) {
    func_ov107_020c9ec8(*(int *)(obj + 0x3d8));
    func_0202a818(*(unsigned short **)(*(int *)(obj + 0x3e4) + 0x88), frame);
    func_ov107_020c6980(obj, frame);
}
