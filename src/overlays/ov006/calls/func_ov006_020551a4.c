typedef unsigned char u8;

typedef struct {
    u8 bytes[0x1c];
} MissionTween;

typedef struct {
    u8 pad_0000[0x94f4];
    int current_state;
    int next_state;
    int field_94fc;
    int start_value;
    int end_value;
    u8 pad_9508[0x3c];
    MissionTween transition;
    int payload;
    u8 pad_9564[8];
    int transition_pending;
} Ov006RootContext;

extern Ov006RootContext *data_ov006_02056664;
extern void func_02035fb0(MissionTween *tween, int mode, int start,
                          int end, int duration);
extern void func_02035ffc(MissionTween *tween);

void func_ov006_020551a4(int state, int duration, int start, int end,
                         int payload) {
    if (state <= -1) {
        return;
    }
    if (state >= 15) {
        return;
    }

    if (start < -16) {
        start = -16;
    } else if (start > 16) {
        start = 16;
    }

    if (end < -16) {
        end = -16;
    } else if (end > 16) {
        end = 16;
    }

    data_ov006_02056664->start_value = start;
    data_ov006_02056664->end_value = end;

    if (duration != 0) {
        func_02035fb0(&data_ov006_02056664->transition, 0,
                      data_ov006_02056664->start_value << 12,
                      data_ov006_02056664->end_value << 12, duration);
        func_02035ffc(&data_ov006_02056664->transition);
        data_ov006_02056664->payload = payload;
        data_ov006_02056664->next_state = state;
        data_ov006_02056664->transition_pending = 1;
    } else {
        data_ov006_02056664->current_state = state;
    }
}
