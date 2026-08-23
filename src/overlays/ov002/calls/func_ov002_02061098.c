/*
 * Ov002_DrawHudNumber - draw a number with the panel's HUD widget.
 *
 * The palette says how urgent the number is: over ten takes the plain one,
 * three or under the warning one, and anything between the middle one. The
 * digits are drawn least significant first from the right-hand edge, stepping
 * left, so a zero still draws one digit.
 *
 * ARM.
 */

typedef struct {
    int x;
    int y;
    int z;
} Ov002Vec3;

typedef struct {
    char pad000[0x78];
    int nList;
    char pad07c[0x8c];
} Ov002Widget;

typedef struct {
    char pad000[0x1214];
    Ov002Widget hudWidget;
} Ov002HudScene;

extern int data_ov002_0207f628;

extern void func_02016cd0(int nList, int nValue);
extern void func_02016d10(int nList, int nValue);

extern void func_ov002_02060d0c(char *pWidget, const Ov002Vec3 *pPos, int nTag,
                                int nValue);

void func_ov002_02061098(int nX, int nY, int nValue)
{
    Ov002Vec3 v;
    int nTag;
    Ov002HudScene *s;

    s = *(Ov002HudScene **)&data_ov002_0207f628;
    func_02016cd0(s->hudWidget.nList, 0x36);
    func_02016d10(s->hudWidget.nList, 0x1f);

    if (nValue <= 10) {
        if (nValue <= 3) {
            nTag = 0x315f;
        } else {
            nTag = 0x3fdf;
        }
    } else {
        nTag = 0x7fff;
    }

    v.x = nX + 0x12000;
    v.y = nY;
    v.z = 0;
    do {
        v.x -= 0xa99a;
        func_ov002_02060d0c((char *)&s->hudWidget, &v, nTag,
                            (nValue % 10) << 12);
        nValue /= 10;
    } while (nValue > 0);
}
