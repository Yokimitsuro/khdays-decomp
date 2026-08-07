/*
 * Ov128_ChaserInit -- class initialiser for the ov128 chaser.
 *
 * Same function as ov130's initialiser; only the tuning constants differ:
 * speed pair 0x900 (ov130: 0x1400), channel range 0x2000 (0x4000),
 * spawn radius 0x1800 (0x3000), spawn height 0x900 (0x1400),
 * resource id 0x118 (0x15c).
 *
 * Installs the seven handlers the framework calls into, sets the two speed
 * pairs, builds the sub-objects (the model instance kept at +0x384, the effect
 * at +0x390 and the boxed instance at +0x394), opens three subscriber channels,
 * takes a sorted slot for the id list and finally requests the spawn volume:
 * a zero position, an up axis, a 0x3000 radius and a 0x1400 height. The request
 * returns a 64-bit id pair -- the low half is stored, the high half is handed
 * straight to the resource request.
 *
 * The object is addressed as an array of words; the indices below are the byte
 * offsets divided by four:
 *
 *   [2]=+0x08 [3]=+0x0c [7]=+0x1c [0xc]=+0x30 [0xe]=+0x38   handler slots
 *   [0x74]=+0x1d0 [0x77]=+0x1dc                             handler slots
 *   [0x19]=+0x64 .. [0x1c]=+0x70                            speed pairs
 *   [0x27]=+0x9c   owner list      [0x51]=+0x144  id list
 *   [0x8b]=+0x22c  sorted slots    [0xe1]=+0x384  model instance
 *   [0xe2]=+0x388  list slot       [0xe3]=+0x38c  spawn id
 *   [0xe4]=+0x390  effect          [0xe5]=+0x394  boxed instance
 *   [0xe6]=+0x398  child list
 *
 * aOwnerTag is a zeroed word whose low nine bits are or'ed into the subitem id
 * together with the tag derived from the current thread's stack bottom.
 */

typedef struct { int nX, nY, nZ; } VecFx32;

struct SpawnVolume {
    VecFx32 vPos;
    VecFx32 vUp;
    int nRadius;
    int nHeight;
};

extern void func_ov128_020d3a50(void);
extern void func_ov128_020d3a90(void);
extern void func_ov128_020d3b34(void);
extern void func_ov128_020d3c10(void);
extern void func_ov128_020d3bb0(void);
extern void func_ov128_020d3fdc(void);
extern void func_ov128_020d3b04(void);

extern int func_ov107_020c9440(int *self, int nKind);
extern int func_0203b898(unsigned int uId);
extern void func_0203bfb4(int a, int b);
extern int func_ov107_020c9e50(int a, const void *b);
extern void func_01fffc24(void *pList);
extern int func_0203d15c(int nSize);
extern int OS_IsThreadAvailable_0x020c9848(void);
extern void func_ov107_020c9074(int *self, int a);
extern void func_ov107_020c92b0(int *self, int nChannel, int b, int c, int nRange);
extern int func_01fffca8(void *a, int b, int c);
extern int func_ov107_020c319c(void *a);
extern long long func_ov107_020c3210(VecFx32 *pReq);
extern void func_0203355c(int nId, int nHigh);

extern const char data_ov128_020d4fec[];
extern const VecFx32 data_02041dc8;
extern const VecFx32 data_02042264;

void func_ov128_020cbfc4(int *self)
{
    struct SpawnVolume req;
    int aOwnerTag[1] = { 0 };
    int nInst;
    int nThread;
    int *pSlot;
    long long idPair;

    ((void **)self)[2] = (void *)func_ov128_020d3a50;
    ((void **)self)[3] = (void *)func_ov128_020d3a90;
    ((void **)self)[7] = (void *)func_ov128_020d3b34;
    ((void **)self)[0xc] = (void *)func_ov128_020d3c10;
    ((void **)self)[0xe] = (void *)func_ov128_020d3bb0;
    ((void **)self)[0x74] = (void *)func_ov128_020d3fdc;
    ((void **)self)[0x77] = (void *)func_ov128_020d3b04;

    self[0x1c] = 0x900;
    self[0x19] = 0;
    self[0x1a] = 0x900;
    self[0x1b] = 0;

    nInst = func_0203b898(func_ov107_020c9440(self, 0));
    self[0xe1] = nInst;
    func_0203bfb4(self[0x27], self[0xe1]);

    self[0xe4] = func_ov107_020c9e50(func_ov107_020c9440(self, 1), data_ov128_020d4fec);
    func_01fffc24((void *)&self[0xe6]);
    self[0xe5] = func_0203d15c(8);

    nThread = OS_IsThreadAvailable_0x020c9848();
    *(int *)self[0xe5] =
        func_0203b898((aOwnerTag[0] & 0x1ff) |
                      (((*(int *)(nThread + 0x88) + 0x8000) & 0xfffffc) << 7 |
                       0x80000000));
    func_ov107_020c9074(self, *(int *)self[0xe5]);
    *(unsigned int *)(*(int *)self[0xe5] + 0x5c) |= 2;

    func_ov107_020c92b0(self, 0, 1, 0, 0x2000);
    func_ov107_020c92b0(self, 2, 1, 0, 0x2000);
    func_ov107_020c92b0(self, 1, 1, 0, 0x2000);

    self[0xe2] = func_01fffca8((void *)&self[0x8b], 0x10, 100);
    *(int *)self[0xe2] = func_ov107_020c319c((void *)&self[0x19]);

    req.nRadius = 0x1800;
    req.vPos = data_02041dc8;
    req.vUp = data_02042264;
    req.nHeight = 0x900;
    pSlot = (int *)func_01fffca8((void *)&self[0x51], 4, 100);
    idPair = func_ov107_020c3210(&req.vPos);
    *pSlot = (int)idPair;
    self[0xe3] = (int)idPair;
    func_0203355c(0x118, (int)(idPair >> 32));
}
