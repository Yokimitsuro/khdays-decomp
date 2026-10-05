/* Script command: formats a message with the player names and two counters from the game state, and
 * shows it in the panel. */

extern char *ByteCode_ResolveOperand(int a, unsigned short *b);
extern int ScriptVm_ReadOperandInt(int a, unsigned short *b);
extern void MIi_CpuClear16(int val, void *buf, int n);
extern void Utf8_ToUcs2(void *src, unsigned short *dst);
extern void MI_CpuFill8(void *buf, int val, int n);
extern int GameState_GetField(int key, int kind);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void Ov002_SetSeatFlag(int a, int b);
extern void Ov002_TryBeginPanelRequest(void *s, int nValue);

extern unsigned char data_ov019_0207fd40[];
extern char gOv019IntFmt[];

struct namelist {
    unsigned short *names;
    int a;
    int b;
    int c;
    int id;
    int m1;
    int e;
    int pad7;
    int pad8;
};

int Ov019_ShowMessageWithCounters(int param_1, unsigned short *param_2, int param_3,
                        unsigned short *param_4)
{
    unsigned char header[6];
    unsigned int fmtbuf[4];
    unsigned short scratch[16];
    unsigned short found[16];
    struct namelist out;
    unsigned short names[256];

    char *s;
    int id1;
    int id2;
    int mode;
    int pos;
    int i;
    unsigned short *q;

    s = ByteCode_ResolveOperand(param_1, param_2);

    id1 = ScriptVm_ReadOperandInt(param_1, param_2 + 4);
    id2 = ScriptVm_ReadOperandInt(param_1, param_2 + 8);
    mode = ScriptVm_ReadOperandInt(param_1, param_2 + 0xc);

    header[4] = data_ov019_0207fd40[2];
    header[5] = data_ov019_0207fd40[3];
    header[2] = data_ov019_0207fd40[4];
    header[3] = data_ov019_0207fd40[5];
    header[0] = data_ov019_0207fd40[0];
    header[1] = data_ov019_0207fd40[1];

    pos = 0;

    MIi_CpuClear16(0, names, 0x200);
    Utf8_ToUcs2(s, names);

    if (mode != 3) {
        int iter = 0;

        do {
            int val;

            MIi_CpuClear16(0, scratch, 0x20);
            MIi_CpuClear16(0, found, 0x20);
            MI_CpuFill8(fmtbuf, 0, 0x10);

            if (iter == 0) {
                val = GameState_GetField(0x140b, 10);
                Utf8_ToUcs2(&header[4], scratch);
            } else if (iter == 1) {
                val = GameState_GetField(0x1415, 10);
                Utf8_ToUcs2(&header[2], scratch);
            } else {
                val = GameState_GetField(0x141f, 10);
                Utf8_ToUcs2(&header[0], scratch);
            }

            OS_SPrintf((char *)fmtbuf, gOv019IntFmt, val);
            Utf8_ToUcs2(fmtbuf, found);

            i = pos;

            if (pos < 0x100) {
                q = names + pos;

                do {
                    if (scratch[0] == *q) {
                        pos = i;
                        break;
                    }

                    i++;
                    q++;
                } while (i < 0x100);
            }

            {
                unsigned short *src;
                int count;
                unsigned short *dst;

                count = 0;
                src = found;
                dst = names + pos;

                do {
                    if (*src == 0) {
                        break;
                    }

                    count++;
                    *dst = *src;
                    dst++;
                    pos++;
                    src++;
                } while (count < 0x10);
            }
        } while (iter != mode && (++iter < 3));
    } else {
        int val;

        MIi_CpuClear16(0, scratch, 0x20);
        MIi_CpuClear16(0, found, 0x20);
        MI_CpuFill8(fmtbuf, 0, 0x10);

        val = GameState_GetField(0x1400, 10);
        Utf8_ToUcs2(&header[4], scratch);

        OS_SPrintf((char *)fmtbuf, gOv019IntFmt, val);
        Utf8_ToUcs2(fmtbuf, found);

        {
            unsigned short *scan;
            unsigned short needle;
            int idx;

            idx = pos;
            scan = names;
            needle = scratch[0];

            do {
                if (needle == *scan) {
                    pos = idx;
                    break;
                }

                idx++;
                scan++;
            } while (idx < 0x100);
        }

        {
            unsigned short *src;
            int count;
            unsigned short *dst;

            count = 0;
            src = found;
            dst = names + pos;

            do {
                if (*src == 0) {
                    break;
                }

                count++;
                *dst = *src;
                dst++;
                pos++;
                src++;
            } while (count < 0x18);
        }
    }

    Ov002_SetSeatFlag(0, id1);

    out.names = names;
    out.c = 0;
    out.id = id2;
    out.m1 = -1;
    out.b = 0;
    out.a = 0;
    out.e = 0;

    Ov002_TryBeginPanelRequest(&out, 0);

    return 0;
}
