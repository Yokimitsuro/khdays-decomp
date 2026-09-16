/* func_ov023_02085174 -- Ov023_CmdStopCamera: script command that stops a camera's motion.
 * Operand 0 names the camera (-1: the current one, +0x488 of the event block); the cameras
 * are the 0x104-byte blocks from +0x30.  A camera whose target mode (+0xf8) is 1 only has its
 * word at +0xec cleared.  Otherwise the mode becomes -1 in a client session (bit 1 of the
 * global mode 02020a9c) or 0; a tracked actor (+0xfc, 0x40 for none) has its entity position
 * (0202bfcc, +0xa8) folded into the camera position (+0x94, VEC_Add) and is dropped; then the
 * angles, position, distance and roll are rewound to their "from" copies (+0xb8 -> +0xa0,
 * +0xac -> +0x94, +0xe4 -> +0xdc, the angles once more, +0xe8 -> +0xe0) and the duration
 * (+0xf0) cleared.  Returns 1. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
    int  z;                   /* 0x08 */
} VecFx32;

typedef struct Ov023Camera {
    u8   pad_000[0x94];
    VecFx32 vPos;             /* 0x94 */
    VecFx32 vAngle;           /* 0xa0 */
    VecFx32 vPosFrom;         /* 0xac */
    VecFx32 vAngleFrom;       /* 0xb8 */
    u8   pad_0c4[0xdc - 0xc4];
    int  nDistance;           /* 0xdc */
    int  nRoll;               /* 0xe0 */
    int  nDistanceFrom;       /* 0xe4 */
    int  nRollFrom;           /* 0xe8 */
    int  nFieldec;            /* 0xec */
    int  nDuration;           /* 0xf0 */
    int  nRemaining;          /* 0xf4 */
    int  nTargetMode;         /* 0xf8 */
    int  nTargetActor;        /* 0xfc */
    int  nField100;           /* 0x100 */
} Ov023Camera;                /* 0x104 */

typedef struct Ov023EventBlock {
    u8   pad_000[0x30];
    Ov023Camera aCamera[4];   /* 0x030 */
    u8   pad_440[0x488 - 0x440];
    int  nCamera;             /* 0x488 */
} Ov023EventBlock;

typedef struct Ov023ScriptCtx {
    u8   pad_000[0x128];
    Ov023EventBlock *pEvent;  /* 0x128 */
} Ov023ScriptCtx;

typedef struct Ov023Entity {
    u8   pad_00[0xa8];
    VecFx32 vPos;             /* 0xa8 */
} Ov023Entity;

extern int   func_02021980(Ov023ScriptCtx *pCtx, void *pOperand);  /* ScriptVm_ReadOperandInt */
extern int   func_02020a9c(void);                                   /* the global mode halfword */
extern Ov023Entity *func_0202bfcc(u16 nEntity);                     /* Entity_Get */
extern void  VEC_Add(const VecFx32 *pA, const VecFx32 *pB, VecFx32 *pOut);

int func_ov023_02085174(Ov023ScriptCtx *pCtx, void *pOperand)
{
    VecFx32 vActor;
    int nCamera;
    Ov023Camera *pCamera;

    nCamera = func_02021980(pCtx, pOperand);
    if (nCamera == -1) {
        nCamera = pCtx->pEvent->nCamera;
    }
    pCamera = &pCtx->pEvent->aCamera[nCamera];
    if (pCamera->nTargetMode == 1) {
        pCamera->nFieldec = 0;
    } else {
        if (func_02020a9c() & 2) {
            pCamera->nTargetMode = -1;
        } else {
            pCamera->nTargetMode = 0;
        }
        if (pCamera->nTargetActor != 0x40) {
            vActor = func_0202bfcc((u16)pCamera->nTargetActor)->vPos;
            VEC_Add(&pCamera->vPos, &vActor, &pCamera->vPos);
            pCamera->nTargetActor = 0x40;
        }
        pCamera->vAngle = pCamera->vAngleFrom;
        pCamera->vPos = pCamera->vPosFrom;
        pCamera->nDistance = pCamera->nDistanceFrom;
        pCamera->vAngle = pCamera->vAngleFrom;
        pCamera->nRoll = pCamera->nRollFrom;
        pCamera->nDuration = 0;
    }
    return 1;
}
