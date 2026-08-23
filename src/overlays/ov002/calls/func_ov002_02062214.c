/*
 * Ov002_StepProgressBar - advance the progress bar towards where the run
 * actually is.
 *
 * On the first pass the bar is armed: the two reward icons are taken if the
 * run has already earned them, the tick is stamped and the bar jumps straight
 * to its true length, which is the done count scaled to the width of the
 * screen.
 *
 * After that the bar creeps: one step per interval, catching up however many
 * intervals have gone by since the last pass. When it reaches the target the
 * chime plays once and the bar stops exactly on it.
 *
 * Either way, once the run has any steps at all, the two icons are taken as
 * soon as they are earned.
 *
 * ARM.
 */

typedef unsigned long long u64;

typedef struct {
    char pad000[0xa0];
    void *pGoalIcon;
    void *pFullIcon;
} Ov002TextScene;

typedef struct {
    int nTotal;
    int nDone;
    int nGoal;
} Ov002Progress;

typedef struct {
    int nCurrent;
    int nTarget;
    int bSound;
    int bDirty;
    u64 llStamp;
    u64 llInterval;
} Ov002BarAnim;

extern int data_ov002_0207f62c;

extern u64 func_020031d4(void);
extern int func_02020400(int nNumer, int nDenom);
extern void func_02033bb4(int a, int b, int c);

extern Ov002Progress *func_ov002_02063698(void);
extern Ov002BarAnim *func_ov002_020636ac(void);
extern void *func_ov002_0206ce78(void);
extern void *func_ov002_0206ced8(void);

void func_ov002_02062214(void)
{
    Ov002TextScene *s;
    Ov002Progress *p;
    u64 llNow;
    Ov002BarAnim *a;

    s = *(Ov002TextScene **)((char *)&data_ov002_0207f62c + 4);
    p = func_ov002_02063698();
    a = func_ov002_020636ac();

    if (a->llStamp == 0) {
        if (p->nDone >= p->nGoal) {
            s->pGoalIcon = func_ov002_0206ce78();
        }
        if (p->nDone == p->nTotal) {
            s->pFullIcon = func_ov002_0206ced8();
        }
        if (p->nTotal > 0) {
            a->llStamp = func_020031d4();
            a->nTarget = a->nCurrent =
                func_02020400(p->nDone * 0xe0, p->nTotal);
            a->bDirty = 1;
        }
    } else if (a->nTarget > a->nCurrent) {
        llNow = func_020031d4();
        while (a->llStamp + a->llInterval <= llNow) {
            a->llStamp += a->llInterval;
            a->nCurrent++;
            if (a->nCurrent >= a->nTarget) {
                if (a->bSound != 0) {
                    func_02033bb4(0, 0x32, 0);
                    a->bSound = 0;
                }
                a->nCurrent = a->nTarget;
                break;
            }
        }
        a->bDirty = 1;
    }

    if (p->nTotal <= 0) {
        return;
    }
    if (s->pGoalIcon == 0 && p->nDone >= p->nGoal) {
        s->pGoalIcon = func_ov002_0206ce78();
    }
    if (s->pFullIcon == 0 && p->nDone == p->nTotal) {
        s->pFullIcon = func_ov002_0206ced8();
    }
}
