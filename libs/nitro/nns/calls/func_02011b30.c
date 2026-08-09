typedef unsigned long u32;
typedef unsigned short u16;
typedef signed long fx32;
typedef int BOOL;

#define TRUE 1
#define FALSE 0

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

extern void func_02011ecc(NNSG2dAnimController *pAnimCtrl);

static inline const NNSG2dAnimFrame *
GetFrameBegin_(const NNSG2dAnimSequence *pSequence)
{
    (void)0;
    return pSequence->pAnmFrameArray;
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

static inline NNSG2dAnimationPlayMode
GetAnimationPlayMode_(const NNSG2dAnimController *pAnimCtrl)
{
    (void)0;
    (void)0;
    if (pAnimCtrl->overriddenPlayMode != NNS_G2D_ANIMATIONPLAYMODE_INVALID) {
        return pAnimCtrl->overriddenPlayMode;
    } else {
        return pAnimCtrl->pAnimSequence->playMode;
    }
}

static inline BOOL IsLoopAnimSequence_(const NNSG2dAnimController *pAnimCtrl)
{
    (void)0;
    (void)0;
    {
        const NNSG2dAnimationPlayMode playMode =
            GetAnimationPlayMode_(pAnimCtrl);
        return (playMode == NNS_G2D_ANIMATIONPLAYMODE_FORWARD_LOOP ||
                playMode == NNS_G2D_ANIMATIONPLAYMODE_REVERSE_LOOP)
                   ? TRUE
                   : FALSE;
    }
}

static inline BOOL IsReversePlayAnim_(const NNSG2dAnimController *pAnimCtrl)
{
    (void)0;
    (void)0;
    {
        const NNSG2dAnimationPlayMode playMode =
            GetAnimationPlayMode_(pAnimCtrl);
        return (playMode == NNS_G2D_ANIMATIONPLAYMODE_REVERSE ||
                playMode == NNS_G2D_ANIMATIONPLAYMODE_REVERSE_LOOP)
                   ? TRUE
                   : FALSE;
    }
}

static inline void NNS_G2dStopAnimCtrl(NNSG2dAnimController *pAnimCtrl)
{
    (void)0;
    pAnimCtrl->bActive = FALSE;
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

static inline void SequenceEdgeHandleCommon_(NNSG2dAnimController *pAnimCtrl)
{
    (void)0;
    if (pAnimCtrl->callbackFunctor.type ==
        NNS_G2D_ANMCALLBACKTYPE_LAST_FRM) {
        (void)0;
        (*pAnimCtrl->callbackFunctor.pFunc)(pAnimCtrl->callbackFunctor.param,
                                            pAnimCtrl->currentTime);
    }

    if (!IsLoopAnimSequence_(pAnimCtrl)) {
        NNS_G2dStopAnimCtrl(pAnimCtrl);
    } else {
        func_02011ecc(pAnimCtrl);
    }
}

static inline void SequenceEdgeHandleReverse_(NNSG2dAnimController *pAnimCtrl)
{
    (void)0;
    pAnimCtrl->bReverse = pAnimCtrl->bReverse ^ TRUE;
    if (IsReachStartEdge_(pAnimCtrl, pAnimCtrl->pCurrent)) {
        SequenceEdgeHandleCommon_(pAnimCtrl);
    }
}

static inline void SequenceEdgeHandleNormal_(NNSG2dAnimController *pAnimCtrl)
{
    (void)0;
    SequenceEdgeHandleCommon_(pAnimCtrl);
}

static inline void ValidateAnimFrame_(NNSG2dAnimController *pAnimCtrl,
                                      const NNSG2dAnimFrame **pFrame)
{
    if (*pFrame > GetFrameEnd_(pAnimCtrl->pAnimSequence) - 1) {
        *pFrame = GetFrameEnd_(pAnimCtrl->pAnimSequence) - 1;
    } else if (*pFrame < GetFrameBegin_(pAnimCtrl->pAnimSequence)) {
        *pFrame = GetFrameBegin_(pAnimCtrl->pAnimSequence);
    }
}

void func_02011b30(NNSG2dAnimController *pAnimCtrl)
{
    (void)0;
    if (IsReversePlayAnim_(pAnimCtrl)) {
        SequenceEdgeHandleReverse_(pAnimCtrl);
    } else {
        SequenceEdgeHandleNormal_(pAnimCtrl);
    }
    ValidateAnimFrame_(pAnimCtrl, &pAnimCtrl->pCurrent);
}
