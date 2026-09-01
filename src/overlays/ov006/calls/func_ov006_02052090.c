typedef unsigned char u8;

typedef struct {
    u8 pad_0000[0x94f4];
    int state;
} Ov006MissionRootContext;

extern Ov006MissionRootContext *data_ov006_02056664;

int func_ov006_02052090(int color, int alternate)
{
    int palette = 0;

    switch (data_ov006_02056664->state) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 10:
    case 11:
    case 13:
    case 14:
        switch (color) {
        case 0: palette = 0; break;
        case 1: palette = 1; break;
        case 2: palette = 5; break;
        case 3: palette = 3; break;
        case 4:
        case 5:
        case 6:
            palette = 0;
            break;
        }
        break;
    case 4:
    case 5:
    case 6:
    case 7:
        switch (color) {
        case 0:
            palette = 0;
            break;
        case 1:
            palette = alternate != 0 ? 1 : 0xf2;
            break;
        case 2:
            palette = alternate != 0 ? 6 : 0xf3;
            break;
        case 3:
            if (alternate != 0) {
                palette = 0xf;
            }
            break;
        case 4:
        case 5:
            palette = 0;
            break;
        case 6:
            palette = alternate != 0 ? 3 : 0xf4;
            break;
        }
        break;
    }
    return palette;
}
