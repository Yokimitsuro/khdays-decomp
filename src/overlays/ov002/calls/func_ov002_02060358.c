/*
 * Ov002_SceneStartPanelBlink - start one blink of the panel's alert widget.
 *
 * The tint tween swings between the two shades and back, and the level tween
 * takes the widget from full down to nothing over a second.
 *
 * ARM.
 */

typedef struct {
    int nMode;
    int nDuration;
    int nFrom;
    int nTo;
    int aStart[2];
    unsigned int dwFlags;
} Ov002Tween;

typedef struct {
    char pad000[0xff0];
    Ov002Tween tweenLevel;
    Ov002Tween tweenTint;
} Ov002BlinkScene;

extern int data_ov002_0207f628;

extern void func_02035fb0(Ov002Tween *pTween, int nMode, int nFrom, int nTo,
                          int nDuration);
extern void func_02035ffc(Ov002Tween *pTween);

void func_ov002_02060358(void)
{
    Ov002BlinkScene *s;

    s = *(Ov002BlinkScene **)&data_ov002_0207f628;
    func_02035fb0(&s->tweenTint, 2, 0x2e1, 0x5ec, 200);
    func_02035ffc(&s->tweenTint);
    func_02035fb0(&s->tweenLevel, 1, 0x1f000, 0, 1000);
    func_02035ffc(&s->tweenLevel);
}
