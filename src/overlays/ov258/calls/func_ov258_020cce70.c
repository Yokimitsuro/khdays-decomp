/* Play move `move` on both rigs of the ov258 actor: the +0x384 rig takes its pose from the first
 * 16-entry table (data_ov258_020d16f4) and the +0x3ac rig from the second (data_ov258_020d1734),
 * each through 020ccf40 with its +0x388 / +0x3b0 work list; a negative id skips that rig. */
typedef struct { int id[16]; } MovePoses;

extern void *func_ov107_020c9440(char *self, int index);
extern void func_ov258_020ccf40(int rig, void *pose, int loop, void *work);
extern const MovePoses data_ov258_020d16f4;
extern const MovePoses data_ov258_020d1734;

void func_ov258_020cce70(char *self, int move, int loop)
{
    MovePoses body = data_ov258_020d16f4;
    MovePoses tail = data_ov258_020d1734;

    if (body.id[move] >= 0) {
        func_ov258_020ccf40(*(int *)(self + 0x384), func_ov107_020c9440(self, body.id[move]), loop, self + 0x388);
    }
    if (tail.id[move] < 0) {
        return;
    }
    func_ov258_020ccf40(*(int *)(self + 0x3ac), func_ov107_020c9440(self, tail.id[move]), loop, self + 0x3b0);
}
