/* func_ov023_020870a0 -- Ov023_CmdSaveGame: script command that walks the ov002 save sequence,
 * keeping its step in data_ov023_0208a78c: 0 waits for 0206d324, 1 for 0206d350, 2 requests
 * the write (02071de4 1), 3 waits for it (02071e08) and then finishes (02073ffc 1 / 1), resets
 * the step and returns 1; until then 0. */
extern int  func_ov002_0206d324(void);
extern int  func_ov002_0206d350(void);
extern void func_ov002_02071de4(int nArg);
extern int  func_ov002_02071e08(void);
extern void func_ov002_02073ffc(int nA, int nB);
extern int  data_ov023_0208a78c;                                    /* the save step */

int func_ov023_020870a0(void)
{
    switch (data_ov023_0208a78c) {
    case 0:
        if (func_ov002_0206d324() != 0) {
            data_ov023_0208a78c++;
        }
        break;
    case 1:
        if (func_ov002_0206d350() != 0) {
            data_ov023_0208a78c++;
        }
        break;
    case 2:
        func_ov002_02071de4(1);
        data_ov023_0208a78c++;
        break;
    case 3:
        if (func_ov002_02071e08() != 0) {
            func_ov002_02073ffc(1, 1);
            data_ov023_0208a78c = 0;
            return 1;
        }
        break;
    }
    return 0;
}
