/* Update of the ov259 actor (+0xc): the +0x414 partner updates (020c9ec8), then the base update
 * (020c6980), the move hook for the current move (020cc134) and both placements (the +0x404 slot's
 * shape and the +0x408 shape) take the +0xa0 transform. */
typedef struct { int m[11]; } Srt;
struct Piece { char pad[0x10]; Srt srt; };

extern void func_ov107_020c9ec8(int part);
extern void func_ov107_020c6980(char *self, int arg);
extern void func_ov259_020cc134(char *self, int move);

void func_ov259_020cc590(char *self, int arg)
{
    func_ov107_020c9ec8(*(int *)(self + 0x414));
    func_ov107_020c6980(self, arg);
    func_ov259_020cc134(self, *(signed char *)(self + 0x100 + 0xc6));
    ((struct Piece *)**(int **)(self + 0x404))->srt = *(Srt *)(self + 0xa0);
    ((struct Piece *)*(int *)(self + 0x408))->srt = *(Srt *)(self + 0xa0);
}
