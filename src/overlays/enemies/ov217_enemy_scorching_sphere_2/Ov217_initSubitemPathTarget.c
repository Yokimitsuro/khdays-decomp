/* Renders the sub-item and tracks its path: samples the joint to get its movement since the last
 * frame and its speed; when its animation ends, chains to the next phase or resets the tracked
 * vectors. */

struct v3 { int x, y, z; };

extern void Obj_RenderModel(int a, int b, int c, int d);
extern int NNS_G3dGetResultMtx(int a, void *buf, void *c, unsigned d);
extern void VEC_Subtract(void *a, void *b, void *out);
extern int VEC_Mag(void *v);
extern void SetSubitemState(int a, int b, int c, int d);
extern const struct v3 data_02041dc8;

void Ov217_initSubitemPathTarget(int param_1, int param_2, int param_3, int param_4) {
    int obj = *(int *)(param_1 + 0x84);
    int buf[12];
    struct v3 tmp;
    int t;
    Obj_RenderModel(param_1, param_2, param_3, param_4);
    if (NNS_G3dGetResultMtx(*(int *)(param_1 + 0x88) + 0x20, buf, 0, *(unsigned *)(obj + 0x434)) != 0) {
        tmp = *(struct v3 *)&buf[9];
        VEC_Subtract(&tmp, (void *)(obj + 0x3b4), (void *)(obj + 0x424));
        *(struct v3 *)(obj + 0x3b4) = tmp;
        *(int *)(obj + 0x430) = VEC_Mag((void *)(obj + 0x424));
    }
    if (*(unsigned char *)(param_1 + 0xad) != 0) return;
    t = *(short *)(*(int *)(param_1 + 0x88) + 2);
    switch (t) {
    case 1:
    case 2:
        SetSubitemState(param_1, 0, (short)(t + 1), 0);
        return;
    case 3:
        {
            struct v3 stage = data_02041dc8;
            *(int *)(obj + 0x430) = 0;
            *(struct v3 *)(obj + 0x3b4) = stage;
            *(struct v3 *)(obj + 0x424) = stage;
        }
        return;
    default:
        if (t >= 0) SetSubitemState(param_1, 0, t, 0);
        {
            struct v3 stage = data_02041dc8;
            *(int *)(obj + 0x430) = 0;
            *(struct v3 *)(obj + 0x3b4) = stage;
            *(struct v3 *)(obj + 0x424) = stage;
        }
    }
}
