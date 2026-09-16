/* func_ov023_02083700 -- Ov023_ApplyFades: step the active screen's fade tween (+0x104 plus
 * 0x14 * the active screen +0x87590) while its elapsed counter (+8) is short of its duration
 * (+0xc; Ov023_StepTween 020836c0) and push both brightness values: the active screen's to
 * the main engine (0201e374) and the other screen's to the sub engine (0201e3cc). */
typedef unsigned char  u8;

typedef struct Ov023Tween {
    int  nStart;              /* 0x00 */
    int  nTarget;             /* 0x04 */
    int  nElapsed;            /* 0x08 */
    int  nDuration;           /* 0x0c */
    int  nValue;              /* 0x10 */
} Ov023Tween;

typedef struct Ov023Scene {
    u8   pad_00000[0x104];
    Ov023Tween aFade[2];      /* 0x00104 */
    u8   pad_0012c[0x87590 - 0x12c];
    int  nActiveScreen;       /* 0x87590 */
} Ov023Scene;

typedef struct Ov023SceneRoot {
    int  nField00;            /* 0x00 */
    Ov023Scene *pScene;       /* 0x04 */
} Ov023SceneRoot;

extern void func_ov023_020836c0(Ov023Tween *pTween);                /* Ov023_StepTween */
extern void func_0201e374(int nLevel);                              /* set the main fade */
extern void func_0201e3cc(int nLevel);                              /* set the sub fade */
extern Ov023SceneRoot data_ov023_0208a784;

void func_ov023_02083700(void)
{
    Ov023Tween *pTween;

    pTween = &data_ov023_0208a784.pScene->aFade[data_ov023_0208a784.pScene->nActiveScreen];
    if (pTween->nElapsed < pTween->nDuration) {
        func_ov023_020836c0(pTween);
    }
    func_0201e374(pTween->nValue);
    func_0201e3cc(data_ov023_0208a784.pScene->aFade[data_ov023_0208a784.pScene->nActiveScreen == 0 ? 1 : 0].nValue);
}
