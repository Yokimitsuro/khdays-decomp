/* func_ov023_020885fc -- Ov023_DrawJointRotations: the joint hook of the event's models.  The
 * hook value kept at +0x2c of data_ov023_0208a790 is applied to the node when set (0202afe8).
 * Then each of the seven rotation tweens of data_ov023_0208a7a0 whose joint (+0x18) is the
 * node's joint (byte +0xae, only for nodes with bit 4 of +8; -1 otherwise) is applied: the
 * current position and vector matrices are read (02016294), the tween's rotation built
 * (Ov023_RotTweenStep 02088454) and concatenated onto the position matrix (MTX_Concat43,
 * keeping its translation), and both matrices are re-sent to the geometry engine
 * (GX_SendFifoWords: matrix mode 2, the vector matrix, mode 1, the position matrix,
 * mode 2). */
typedef unsigned char  u8;
typedef unsigned int   u32;

typedef struct VecFx32 {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
    int  z;                   /* 0x08 */
} VecFx32;

typedef struct MtxFx33 {
    int  a[9];                /* 0x00 */
} MtxFx33;

typedef struct MtxFx43 {
    int  a[9];                /* 0x00 */
    VecFx32 vTrans;           /* 0x24 */
} MtxFx43;

typedef struct Ov023RotTween {
    VecFx32 vTarget;          /* 0x00 */
    VecFx32 vFrom;            /* 0x0c */
    int  nJoint;              /* 0x18 */
    unsigned int nDuration;   /* 0x1c */
    int  nRemaining;          /* 0x20 */
    int  nMode;               /* 0x24 */
} Ov023RotTween;

typedef struct Ov023Node {
    u8   pad_00[8];
    u32  nFlags;              /* 0x08 */
    u8   pad_0c[0xae - 0x0c];
    u8   nJoint;              /* 0xae */
} Ov023Node;

typedef struct Ov023JointHook {
    u8   pad_00[0x2c];
    int  nValue;              /* 0x2c */
} Ov023JointHook;

extern void WM_EndKeySharing_0x0202afe8(Ov023Node *pNode, int nValue); /* apply the joint hook value (0202afe8) */
extern void func_02016294(MtxFx43 *pPosition, MtxFx33 *pVector);  /* G3_ReadClipAndVectorMtx */
extern MtxFx33 *func_ov023_02088454(Ov023RotTween *pTween, MtxFx33 *pOut); /* Ov023_RotTweenStep */
extern void MTX_Concat43(const MtxFx43 *pA, const MtxFx43 *pB, MtxFx43 *pOut);
extern void func_01ff9f00(u32 nCommand, const void *pWords, u32 nCount); /* GX_SendFifoWords */
extern Ov023JointHook data_ov023_0208a790;
extern Ov023RotTween *data_ov023_0208a7a0[7];                       /* the joint rotation tweens */

void func_ov023_020885fc(Ov023Node *pNode)
{
    MtxFx33 mtxVector;
    MtxFx43 mtxPosition;
    MtxFx33 mtxRot;
    int nModeVector;
    int nModePosition;
    int nModeBoth;
    int i;
    int nJoint;
    int nTransX;
    int nTransY;
    int nTransZ;

    if (data_ov023_0208a790.nValue != 0) {
        WM_EndKeySharing_0x0202afe8(pNode, data_ov023_0208a790.nValue);
    }
    for (i = 0; i < 7; i++) {
        Ov023RotTween *pTween = data_ov023_0208a7a0[i];

        if (pNode->nFlags & 0x10) {
            nJoint = pNode->nJoint;
        } else {
            nJoint = -1;
        }
        if (pTween->nJoint == nJoint) {
            func_02016294(&mtxPosition, &mtxVector);
            nTransZ = mtxPosition.vTrans.z;
            nTransY = mtxPosition.vTrans.y;
            nTransX = mtxPosition.vTrans.x;
            func_ov023_02088454(pTween, &mtxRot);
            MTX_Concat43((MtxFx43 *)&mtxRot, &mtxPosition, &mtxPosition);
            nModeVector = 2;
            mtxPosition.vTrans.x = nTransX;
            mtxPosition.vTrans.y = nTransY;
            mtxPosition.vTrans.z = nTransZ;
            func_01ff9f00(0x10, &nModeVector, 1);
            func_01ff9f00(0x17, &mtxVector, 0xc);
            nModePosition = 1;
            func_01ff9f00(0x10, &nModePosition, 1);
            func_01ff9f00(0x17, &mtxPosition, 0xc);
            nModeBoth = 2;
            func_01ff9f00(0x10, &nModeBoth, 1);
        }
    }
}
