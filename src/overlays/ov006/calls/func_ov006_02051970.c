typedef unsigned char u8;

typedef struct {
    u8 pad_00[0x38];
    int cursorIndex;
    int repeatFrames;
} MissionMenuContext;

extern MissionMenuContext *data_ov006_02056660;
extern unsigned short data_0204c190;
extern unsigned short data_0204c18c;
extern void func_02033b78(unsigned int soundId, unsigned int variant);

void func_ov006_02051970(int count)
{
    MissionMenuContext *context = data_ov006_02056660;
    int moveLeft;
    int moveRight;

    if (count == 0) {
        context->cursorIndex = 0;
        return;
    }

    if (count <= context->cursorIndex) {
        context->cursorIndex = count - 1;
    }

    moveRight = 0;
    moveLeft = moveRight;
    if (data_0204c190 == 0x40) {
        context->repeatFrames = 0;
        moveLeft = 1;
    } else if (data_0204c190 == 0x80) {
        context->repeatFrames = 0;
        moveRight = 1;
    } else if (data_0204c18c == 0x40) {
        context->repeatFrames++;
        if (context->repeatFrames >= 6 &&
            (context->repeatFrames - 6) % 2 == 0) {
            moveLeft = 1;
        }
    } else if (data_0204c18c == 0x80) {
        context->repeatFrames++;
        if (context->repeatFrames >= 6 &&
            (context->repeatFrames - 6) % 2 == 0) {
            moveRight = 1;
        }
    }

    if (moveLeft != 0) {
        if (context->cursorIndex > 0) {
            context->cursorIndex--;
        } else {
            context->cursorIndex = count - 1;
        }
        if (count > 1) {
            func_02033b78(0, 0);
        }
    } else if (moveRight != 0) {
        if (context->cursorIndex < count - 1) {
            context->cursorIndex++;
        } else {
            context->cursorIndex = 0;
        }
        if (count > 1) {
            func_02033b78(0, 0);
        }
    }
}