typedef struct {
    int nX;
    int nY;
    int nZ;
} VecFx32;

typedef struct {
    int x;
    int y;
    int z;
    int w;
} Quat;

struct State {
    char *pActor;
    int nAngle04;
    int nAngleTarget08;
    char pad0c[8];
    int nAngleStep14;
    char pad18[4];
    VecFx32 vPending1c;
};

struct Node {
    void *pScene;
    struct State *pState;
};

extern int func_0203d040(int cur, int target, int step, int *pDone);
extern void func_0202f188(Quat *out, const VecFx32 *axis, int angle);
extern void func_0202ed60(Quat *out, const VecFx32 *a, VecFx32 *b);
extern void func_0202ef54(Quat *out, Quat *a, Quat *b);
extern void func_0203c9d0(void *srt, Quat *q);

extern const VecFx32 data_02042264;
extern const VecFx32 data_02041dc8;

void func_ov285_020d1ef8(struct Node *node)
{
    struct State *st;
    Quat qDelta;
    Quat qFacing;

    st = node->pState;
    st->nAngle04 = func_0203d040(st->nAngle04, st->nAngleTarget08,
                                 st->nAngleStep14, 0);
    func_0202f188(&qDelta, &data_02042264, st->nAngle04);
    func_0202ed60(&qFacing, &data_02042264, (VecFx32 *)(st->pActor + 0x124));
    func_0202ef54(&qFacing, &qFacing, &qDelta);
    func_0203c9d0(st->pActor + 0xa0, &qFacing);
    *(VecFx32 *)(st->pActor + 0xf0) = st->vPending1c;
    st->vPending1c = data_02041dc8;
}
