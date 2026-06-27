extern void SND_SetPlayerVolume(int playerNo, int volume);
extern void SND_StopSeq(int playerNo);
extern void func_0201a80c(void *p);

typedef struct {
    char _0[0x2c];
    unsigned char state;
    char _2d[0xf];
    unsigned char player_id;
} X;

void func_0201a76c(X *p)
{
    if (p->state == 2)
        SND_SetPlayerVolume(p->player_id, -723);
    SND_StopSeq(p->player_id);
    func_0201a80c(p);
}
