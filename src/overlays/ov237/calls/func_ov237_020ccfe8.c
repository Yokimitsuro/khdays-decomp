/* Play move `move` on both rigs of the ov237 actor: the +0x384 rig takes its pose from the first
 * 25-entry table (data_ov237_020d1a6c) and the +0x3ac rig from the second (data_ov237_020d1ad0),
 * each through 020cd0b0 with its +0x388 / +0x3b0 work list; a negative id skips that rig. */
typedef struct { int id[25]; } MovePoses;

extern void *func_ov107_020c9440(char *self, int index);
extern void func_ov237_020cd0b0(int rig, void *pose, int loop, void *work);
extern const MovePoses data_ov237_020d1a6c;
extern const MovePoses data_ov237_020d1ad0;

void func_ov237_020ccfe8(char *self, int move, int loop)
{
    MovePoses body = data_ov237_020d1a6c;
    MovePoses tail = data_ov237_020d1ad0;

    if (body.id[move] >= 0) {
        func_ov237_020cd0b0(*(int *)(self + 0x384), func_ov107_020c9440(self, body.id[move]), loop, self + 0x388);
    }
    if (tail.id[move] < 0) {
        return;
    }
    func_ov237_020cd0b0(*(int *)(self + 0x3ac), func_ov107_020c9440(self, tail.id[move]), loop, self + 0x3b0);
}
