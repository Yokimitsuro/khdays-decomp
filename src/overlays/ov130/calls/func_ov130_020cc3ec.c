/* Picks how far down the actor's id list to walk with a d100 -- under 10 stops
   at the head, under 40 at the second entry, otherwise the third -- then fires
   the ov002 effect on whichever id it lands on. A list shorter than the chosen
   depth simply runs out and does nothing. */

struct State {
    char *pActor;
};

struct Node {
    void *pScene;
    struct State *pState;
};

extern int func_02023eb4();
extern int *func_01fffd70(void *list);
extern int *func_01fffd8c(void *list);
extern void func_ov002_02073094(char *actor, int nId, int a, int b);

void func_ov130_020cc3ec(struct Node *node)
{
    struct State *st;
    int *pEntry;
    int nRoll;
    int nDepth;
    long i;

    st = node->pState;
    nRoll = func_02023eb4(100);
    if (nRoll < 10) {
        nDepth = 0;
    } else if (nRoll < 0x28) {
        nDepth = 1;
    } else {
        nDepth = 2;
    }

    pEntry = func_01fffd70(st->pActor + 0x398);
    i = 0;
    if (pEntry == 0) {
        return;
    }
    do {
        if (i >= nDepth) {
            func_ov002_02073094(st->pActor, *pEntry, 0, 0x1000);
            return;
        }
        pEntry = func_01fffd8c(st->pActor + 0x398);
        i++;
    } while (pEntry != 0);
}
