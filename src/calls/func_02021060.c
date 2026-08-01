/*
 * Camera_Init - initialise the camera/view block of a gameplay actor, called from
 * Ov023_VmTickActor and func_02020b64 when an actor is (re)spawned. param_1 is the actor object
 * (int-indexed). Steps: sub-init func_0202e3c4(actor+0x3c, ...); Projection_LoadDefaults(actor+4);
 * seed the state fields (0xdc=0x1800 distance, 0xa4=0x1554 angle, 0xe0=0xe38 radius, 0x10=0x19a,
 * 0x14=0x6a4000, 0x1c=0xccd height); zero the target vector (+0x18) from kVecZero (data_02041dc8);
 * derive the eye position (+0x28/+0x2c) from the radius and the angle's sin/cos (data_0203d210,
 * the shared 16-bit angle table); copy the eye (+0xc4) back into the working vector (+0x18) and the
 * target (+0x24) into +0xd0; clear the residual smoothing/velocity fields.
 *
 * THUMB. Two matching levers: (1) the kVecZero copy and the two +0xc4/+0x24 vector copies are
 * VecFx32 STRUCT COPIES addressed through the int* base with pointer arithmetic (`param_1 + 6`),
 * NOT a hand-computed byte offset - the byte-offset form makes mwcc hoist a second param_1 base
 * register for the ldm/stm and renumbers everything after it. (2) the angle table is read as a
 * flat short[] with `[idx*2]` (sin) and `[idx*2 + 1]` (cos); a {sin,cos} struct's `.cos` field
 * generates the wrong offset here (idx*4 instead of idx*4+2 - it reads the sin) once the two
 * accesses share the index.
 */

typedef struct {
    int nX, nY, nZ;
} VecFx32;

extern void func_0202e3c4(unsigned int *dst, unsigned int a, unsigned int b, unsigned int c);
extern void func_02023c60(unsigned int *proj);   /* Projection_LoadDefaults */
extern int  func_02005418(int a, int b);          /* FX_Mul */
extern VecFx32 data_02041dc8;                      /* kVecZero */
extern short   data_0203d210[];                    /* angle sin/cos table, 4 bytes/entry */

void func_02021060(int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int uVar2;

    func_0202e3c4((unsigned int *)(param_1 + 0xf), param_2, param_3, param_4);
    param_1[0x3e] = 0;
    param_1[0x3d] = 0;
    param_1[0x3c] = param_1[0x3d];
    param_1[0x40] = 0;
    param_1[0x3f] = 0x40;
    func_02023c60((unsigned int *)(param_1 + 1));
    param_1[0x37] = 0x1800;
    param_1[0x28] = 0;
    param_1[0x29] = 0x1554;
    param_1[0x2a] = 0;
    param_1[0x38] = 0xe38;
    *(VecFx32 *)(param_1 + 6) = data_02041dc8;
    param_1[7] = 0xccd;
    param_1[9] = param_1[6];
    uVar2 = func_02005418(param_1[0x37], data_0203d210[(param_1[0x29] >> 4) * 2]);
    param_1[0xa] = param_1[7] + uVar2;
    uVar2 = func_02005418(param_1[0x37], data_0203d210[(param_1[0x29] >> 4) * 2 + 1]);
    param_1[0xb] = param_1[8] + uVar2;
    *(VecFx32 *)(param_1 + 6) = *(VecFx32 *)(param_1 + 0x31);
    *(VecFx32 *)(param_1 + 0x34) = *(VecFx32 *)(param_1 + 9);
    param_1[0x2d] = 0;
    param_1[0x2c] = param_1[0x2d];
    param_1[0x2b] = param_1[0x2c];
    param_1[0x27] = 0;
    param_1[0x26] = param_1[0x27];
    param_1[0x25] = param_1[0x26];
    param_1[5] = 0x6a4000;
    param_1[4] = 0x19a;
}
