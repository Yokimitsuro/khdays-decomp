/* Draws one sub-object slot in its visible states: loads its matrix for the entry, sets the polygon
 * id from the slot index, sends its scale and matrix to the geometry FIFO and runs its animation
 * channels. */

extern void MI_Copy48B(int a, int b);
extern void NNS_G3dMdlSetMdlPolygonID(int a, int b, int c);
extern void GX_SendFifoWords(int tag, int *buf, int count);
extern void NNS_G3dGlbFlush(void);
extern void NNS_G3dDraw(int p);

void Ov031_configureSubObjectSlot(int this, int entry, int p3) {
    int buf[3];
    int val;
    switch (*(int *)(entry + 4)) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 6:
        switch (*(int *)entry) {
        case 0:
            MI_Copy48B(this + 0x528, entry + 0x88);
            break;
        case 1:
            MI_Copy48B(this + 0x558, entry + 0x88);
            break;
        }
        NNS_G3dMdlSetMdlPolygonID(*(int *)(entry + 0x80), 2, p3 + 5);
        val = *(int *)(*(int *)(entry + 0x2c) + 0x1c);
        buf[0] = val;
        buf[1] = val;
        buf[2] = val;
        GX_SendFifoWords(0x1b, buf, 3);
        NNS_G3dGlbFlush();
        GX_SendFifoWords(0x17, (int *)(entry + 0x88), 0xc);
        NNS_G3dDraw(entry + 0x28);
        break;
    default:
        break;
    }
}
