/* Play move `move` on both rigs of the ov256 actor: the +0x384 rig takes its pose from the first
 * 34-entry table (data_ov256_020d2484) and the +0x3ac rig from the second (data_ov256_020d250c),
 * each through 020ccc6c with its +0x388 / +0x3b0 work list; a negative id skips that rig. */
typedef struct { int id[34]; } MovePoses;

extern void *func_ov107_020c9440(char *self, int index);
extern void func_ov256_020ccc6c(int rig, void *pose, int loop, void *work);
extern const MovePoses data_ov256_020d2484;
extern const MovePoses data_ov256_020d250c;

void func_ov256_020ccba4(char *self, int move, int loop)
{
    MovePoses body = data_ov256_020d2484;
    MovePoses tail = data_ov256_020d250c;

    if (body.id[move] >= 0) {
        func_ov256_020ccc6c(*(int *)(self + 0x384), func_ov107_020c9440(self, body.id[move]), loop, self + 0x388);
    }
    if (tail.id[move] < 0) {
        return;
    }
    func_ov256_020ccc6c(*(int *)(self + 0x3ac), func_ov107_020c9440(self, tail.id[move]), loop, self + 0x3b0);
}
