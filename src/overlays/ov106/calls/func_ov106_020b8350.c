/* func_ov106_020b8350 -- Ov106_CmdSaveGame: script command that walks the ov002 save sequence,
 * keeping its step in data_ov106_020b8b64: 0 waits for 0206d324, 1 for 0206d350, 2 requests
 * the write (02071de4 1), 3 waits for it (02071e08) and then finishes (02073ffc 1 / 1), resets
 * the step and returns 1; until then 0. *
 * PROVENANCE: byte-identical twin of ov023's Ov023_CmdSaveGame (func_ov023_020870a0), same code and
 * callees, verified byte-exact in this overlay. */
extern int  func_ov002_0206d324(void);
extern int  func_ov002_0206d350(void);
extern void func_ov002_02071de4(int nArg);
extern int  func_ov002_02071e08(void);
extern void func_ov002_02073ffc(int nA, int nB);
extern int  data_ov106_020b8b64;                                    /* the save step */

int func_ov106_020b8350(void)
{
    switch (data_ov106_020b8b64) {
    case 0:
        if (func_ov002_0206d324() != 0) {
            data_ov106_020b8b64++;
        }
        break;
    case 1:
        if (func_ov002_0206d350() != 0) {
            data_ov106_020b8b64++;
        }
        break;
    case 2:
        func_ov002_02071de4(1);
        data_ov106_020b8b64++;
        break;
    case 3:
        if (func_ov002_02071e08() != 0) {
            func_ov002_02073ffc(1, 1);
            data_ov106_020b8b64 = 0;
            return 1;
        }
        break;
    }
    return 0;
}
