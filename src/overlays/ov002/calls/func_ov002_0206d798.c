typedef unsigned short u16;

/* Only the leading flag word of a player record matters here: bit 16 takes the
   player out of the walk. */
typedef struct Ov002PlayerRecord {
    unsigned long long nFlags;
} Ov002PlayerRecord;

/* Index of the local player; zero for the one running the session. */
extern int func_02030788(void);
/* Number of players the session currently holds. */
extern int func_ov022_020882f8(void);
extern Ov002PlayerRecord *func_01fffde0(int nPlayer);
extern int func_ov022_02088474(int nPlayer);
extern int func_ov002_02072754(int nWorld);
extern void func_ov002_0207669c(int nTrack);

/* Drop the music a world was holding, once nobody is left in it.
 *
 * Only the player running the session decides this, and only for a real world.
 * Every player still in play is checked, and finding one of them in that world
 * leaves the music alone; otherwise the world's track is looked up and stopped.
 */
void func_ov002_0206d798(int nWorld)
{
    int i;
    int nPlayerWorld;

    if (nWorld < 0) {
        return;
    }
    if (func_02030788() != 0) {
        return;
    }

    for (i = 0; i < func_ov022_020882f8(); i++) {
        if ((func_01fffde0(i)->nFlags & 0x10000) == 0) {
            nPlayerWorld = func_ov022_02088474(i);
            if (nPlayerWorld >= 0) {
                if (nWorld == nPlayerWorld) {
                    return;
                }
            }
        }
    }

    func_ov002_0207669c((u16)func_ov002_02072754(nWorld));
}
