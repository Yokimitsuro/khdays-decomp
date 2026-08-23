/*
 * Ov002_SceneDrawPanelTotal - draw the panel's running total.
 *
 * Nothing is drawn while the number has no digits. Otherwise the shared digit
 * widget is placed and drawn once per digit, most significant first, each one
 * a fixed step further left so the number always ends on the same right edge.
 *
 * ARM.
 */

typedef struct {
    int x;
    int y;
    int z;
} Ov002Vec3;

typedef struct {
    char pad000[0x970];
    Ov002Vec3 vDigitPos;
    char pad97c[0x3e4];
    int nTotalShown;
} Ov002CounterScene;

extern int data_ov002_0207f628;

extern int func_ov002_020618d8(int nValue);
extern int func_ov002_02061908(int nIndex, int nValue);
extern void func_ov002_020617f8(void *pWidget, int nDigit);
extern void func_ov002_0205f810(void *pWidget);

void func_ov002_02060254(void)
{
    Ov002Vec3 v;
    int i;
    int nValue;
    Ov002CounterScene *s;

    s = *(Ov002CounterScene **)&data_ov002_0207f628;
    nValue = s->nTotalShown;
    for (i = 0; i < func_ov002_020618d8(nValue); i++) {
        v.x = (func_ov002_020618d8(nValue) - i) * 0x6a4 - 0x4394;
        v.y = 0x348a;
        v.z = 0;
        s->vDigitPos = v;
        func_ov002_020617f8((char *)s + 0x8cc,
                            func_ov002_02061908(i, nValue));
        func_ov002_0205f810((char *)s + 0x8cc);
    }
}
