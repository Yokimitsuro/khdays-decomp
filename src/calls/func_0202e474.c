/* Per-frame update of a camera/actor rig workspace: publishes the shared matrix pointer
 * (data_02042510) to the render state (+0xe8), samples the +8 source's two frames (func_020172a0
 * 0 and 1) into the down-direction (func_0202e1cc) and anchor (func_0202e2b0) stages, refreshes the
 * +0x10 block (func_02023cc0) and finishes with func_0202e400. */
typedef struct {
    char data[0x58];
} Frame;

extern int data_02042510;
extern char *data_020475d0;
extern void func_020172a0(Frame *out, int src, int which);
extern void func_0202e1cc(char *self, Frame *src);
extern void func_0202e2b0(char *self, Frame *src);
extern void func_02023cc0(void *block);
extern void func_0202e400(char *self, int arg);

void func_0202e474(char *self, int arg)
{
    Frame second;
    Frame first;

    *(int *)(data_020475d0 + 0xe8) = data_02042510;
    func_020172a0(&first, *(int *)(self + 8), 0);
    func_020172a0(&second, *(int *)(self + 8), 1);
    func_0202e1cc(self, &first);
    func_0202e2b0(self, &second);
    func_02023cc0(self + 0x10);
    func_0202e400(self, arg);
}
