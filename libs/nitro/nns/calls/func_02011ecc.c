typedef unsigned long u32;
typedef unsigned short u16;
typedef signed long fx32;
typedef int BOOL;

typedef enum NNSG2dAnimationPlayMode {
    NNS_G2D_ANIMATIONPLAYMODE_INVALID = 0
} NNSG2dAnimationPlayMode;

typedef struct NNSG2dAnimFrameData {
    void *pContent;
    u16 frames;
    u16 pad16;
} NNSG2dAnimFrame;

typedef struct NNSG2dAnimSequenceData {
    u16 numFrames;
    u16 loopStartFrameIdx;
    u32 animType;
    NNSG2dAnimationPlayMode playMode;
    NNSG2dAnimFrame *pAnmFrameArray;
} NNSG2dAnimSequence;

typedef struct NNSG2dAnimController {
    const NNSG2dAnimFrame *pCurrent;
    const NNSG2dAnimFrame *pActiveCurrent;
    BOOL bReverse;
    BOOL bActive;
    fx32 currentTime;
    fx32 speed;
    NNSG2dAnimationPlayMode overriddenPlayMode;
    const NNSG2dAnimSequence *pAnimSequence;
    u32 callbackFunctor[4];
} NNSG2dAnimController;

extern BOOL func_02011c88(NNSG2dAnimController *pAnimCtrl, fx32 frames);

static inline const NNSG2dAnimFrame *
GetFrameEnd_(const NNSG2dAnimSequence *pSequence)
{
    (void)0;
    return pSequence->pAnmFrameArray + pSequence->numFrames;
}

static inline const NNSG2dAnimFrame *
GetFrameLoopBegin_(const NNSG2dAnimSequence *pSequence)
{
    (void)0;
    return pSequence->pAnmFrameArray + pSequence->loopStartFrameIdx;
}

static inline BOOL IsAnimCtrlMovingForward_(
    const NNSG2dAnimController *pAnimCtrl)
{
    (void)0;
    return (pAnimCtrl->speed > 0) ^ pAnimCtrl->bReverse ? 1 : 0;
}

void func_02011ecc(NNSG2dAnimController *pAnimCtrl)
{
    (void)0;
    if (IsAnimCtrlMovingForward_(pAnimCtrl)) {
        pAnimCtrl->pCurrent = GetFrameLoopBegin_(pAnimCtrl->pAnimSequence);
    } else {
        pAnimCtrl->pCurrent = GetFrameEnd_(pAnimCtrl->pAnimSequence) - 1;
    }
    pAnimCtrl->pActiveCurrent = pAnimCtrl->pCurrent;
    pAnimCtrl->currentTime = 0;
    (void)func_02011c88(pAnimCtrl, 0);
}
