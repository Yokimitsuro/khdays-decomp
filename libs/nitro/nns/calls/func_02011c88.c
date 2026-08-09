typedef unsigned long u32;
typedef unsigned short u16;
typedef signed long fx32;
typedef signed long long s64;
typedef int BOOL;

#define TRUE 1
#define FALSE 0
#define FX32_ONE 0x1000

typedef enum NNSG2dAnimationPlayMode {
    NNS_G2D_ANIMATIONPLAYMODE_INVALID = 0,
    NNS_G2D_ANIMATIONPLAYMODE_FORWARD,
    NNS_G2D_ANIMATIONPLAYMODE_FORWARD_LOOP,
    NNS_G2D_ANIMATIONPLAYMODE_REVERSE,
    NNS_G2D_ANIMATIONPLAYMODE_REVERSE_LOOP
} NNSG2dAnimationPlayMode;

typedef enum NNSG2dAnmCallbackType {
    NNS_G2D_ANMCALLBACKTYPE_NONE = 0,
    NNS_G2D_ANMCALLBACKTYPE_LAST_FRM,
    NNS_G2D_ANMCALLBACKTYPE_SPEC_FRM,
    NNS_G2D_ANMCALLBACKTYPE_EVER_FRM
} NNSG2dAnmCallbackType;

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

typedef void (*NNSG2dAnmCallBackPtr)(u32 data, fx32 currentFrame);

typedef struct NNSG2dCallBackFunctor {
    NNSG2dAnmCallbackType type;
    u32 param;
    NNSG2dAnmCallBackPtr pFunc;
    u16 frameIdx;
    u16 pad16_;
} NNSG2dCallBackFunctor;

typedef struct NNSG2dAnimController {
    const NNSG2dAnimFrame *pCurrent;
    const NNSG2dAnimFrame *pActiveCurrent;
    BOOL bReverse;
    BOOL bActive;
    fx32 currentTime;
    fx32 speed;
    NNSG2dAnimationPlayMode overriddenPlayMode;
    const NNSG2dAnimSequence *pAnimSequence;
    NNSG2dCallBackFunctor callbackFunctor;
} NNSG2dAnimController;

extern int abs(int value);
extern void func_02011b30(NNSG2dAnimController *pAnimCtrl);

static inline fx32 FX_Mul(fx32 v1, fx32 v2)
{
    return (fx32)(((s64)v1 * v2 + 0x800) >> 12);
}

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

static inline u16 GetCurrentFrameIdx_(const NNSG2dAnimController *pAnimCtrl)
{
    (void)0;
    return (u16)(((u32)pAnimCtrl->pCurrent -
                  (u32)pAnimCtrl->pAnimSequence->pAnmFrameArray) /
                 sizeof(NNSG2dAnimFrame));
}

static inline BOOL IsAnimCtrlMovingForward_(
    const NNSG2dAnimController *pAnimCtrl)
{
    (void)0;
    return (pAnimCtrl->speed > 0) ^ pAnimCtrl->bReverse ? TRUE : FALSE;
}

static inline BOOL ShouldAnmCtrlMoveNext_(NNSG2dAnimController *pAnimCtrl)
{
    (void)0;
    (void)0;
    if (pAnimCtrl->bActive &&
        pAnimCtrl->currentTime >=
            FX32_ONE * (int)pAnimCtrl->pCurrent->frames) {
        return TRUE;
    }
    return FALSE;
}

static inline void CallbackFuncHandling_(const NNSG2dCallBackFunctor *pFunctor,
                                         u16 currentFrameIdx)
{
    (void)0;
    switch (pFunctor->type) {
    case NNS_G2D_ANMCALLBACKTYPE_SPEC_FRM:
        if (currentFrameIdx == pFunctor->frameIdx) {
            (*pFunctor->pFunc)(pFunctor->param, currentFrameIdx);
        }
        break;
    case NNS_G2D_ANMCALLBACKTYPE_EVER_FRM:
        (*pFunctor->pFunc)(pFunctor->param, currentFrameIdx);
        break;
    }
}

static inline BOOL IsReachStartEdge_(const NNSG2dAnimController *pAnimCtrl,
                                     const NNSG2dAnimFrame *pFrame)
{
    (void)0;
    (void)0;
    return pFrame <= GetFrameLoopBegin_(pAnimCtrl->pAnimSequence) - 1
               ? TRUE
               : FALSE;
}

static inline BOOL IsReachEdge_(const NNSG2dAnimController *pAnimCtrl,
                                const NNSG2dAnimFrame *pFrame)
{
    (void)0;
    (void)0;
    if (IsAnimCtrlMovingForward_(pAnimCtrl)) {
        return pFrame >= GetFrameEnd_(pAnimCtrl->pAnimSequence) ? TRUE : FALSE;
    } else {
        return IsReachStartEdge_(pAnimCtrl, pFrame);
    }
}

static inline void MoveNext_(NNSG2dAnimController *pAnimCtrl)
{
    (void)0;
    if (IsAnimCtrlMovingForward_(pAnimCtrl)) {
        pAnimCtrl->pCurrent++;
    } else {
        pAnimCtrl->pCurrent--;
    }
}

BOOL func_02011c88(NNSG2dAnimController *pAnimCtrl, fx32 frames)
{
    BOOL bChangeFrame = FALSE;

    (void)0;
    (void)0;
    (void)0;

    if (pAnimCtrl->bActive != TRUE) {
        return FALSE;
    }

    pAnimCtrl->currentTime += abs(FX_Mul(pAnimCtrl->speed, frames));

    while (ShouldAnmCtrlMoveNext_(pAnimCtrl)) {
        bChangeFrame = TRUE;
        pAnimCtrl->currentTime -=
            FX32_ONE * (int)pAnimCtrl->pCurrent->frames;
        MoveNext_(pAnimCtrl);

        if (IsReachEdge_(pAnimCtrl, pAnimCtrl->pCurrent)) {
            func_02011b30(pAnimCtrl);
        }

        if (pAnimCtrl->pCurrent->frames != 0) {
            pAnimCtrl->pActiveCurrent = pAnimCtrl->pCurrent;
        }

        if (pAnimCtrl->callbackFunctor.type !=
            NNS_G2D_ANMCALLBACKTYPE_NONE) {
            CallbackFuncHandling_(&pAnimCtrl->callbackFunctor,
                                  GetCurrentFrameIdx_(pAnimCtrl));
        }
    }
    return bChangeFrame;
}
