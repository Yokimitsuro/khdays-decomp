typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u16 id;
    u8 flag_2;
    u8 flag_3;
    s8 icon;
    s8 sprite;
    u8 field_6;
    u8 pad_7;
} MissionMenuRow;

typedef struct {
    u8 pad_00[0x28];
    int single_row_mode;
    u8 pad_2c[4];
    u8 option_mask;
    u8 pad_31;
    u16 message_id;
    u16 field_34;
    u8 pad_36[0x0a];
    MissionMenuRow rows[4];
    u8 pad_60[0x0d];
    u8 parameters_ready;
} MissionMenuContext;

typedef struct {
    u8 pad_0000[0x9d8];
    u8 feature_a;
    u8 feature_b;
} MissionSystemContext;

extern MissionMenuContext *data_ov006_02056660;
extern MissionSystemContext *data_0204be18;

extern int func_ov006_02050090(void);
extern void func_ov006_0204fef4(void);
extern int func_ov006_0204fa58(void);
extern int func_ov006_02055b0c(int selection);
extern int func_ov006_0204fb50(void);
extern int func_ov006_02055950(void);
extern int func_020235d0(int id, int field);
extern void func_ov006_02055af4(int mask);
extern void func_ov006_0204fbd0(int row, MissionMenuRow *out);
extern int func_ov006_0204fa88(void);
extern int func_ov006_02055b30(unsigned mode);
extern void func_ov006_02056030(void);
extern void func_ov006_02056098(void);
extern int func_02030788(void);
extern void func_ov006_02056018(int row);
extern int func_ov006_02055a54(unsigned state, int arg1, int arg2);
extern int func_ov006_02055c38(int pose);
extern void func_ov006_02051884(void);
extern void func_ov006_02050fc8(void);

int func_ov006_02050e1c(void) {
    int input;
    int result = 0;
    u8 option_mask = result;
    u8 level;

    if (func_ov006_02050090() != 0) {
        func_ov006_0204fef4();
        data_ov006_02056660->parameters_ready = 0;
        return (int)func_ov006_02051884;
    }

    func_ov006_02055b0c(func_ov006_0204fa58());
    if (func_ov006_0204fb50() != 2) {
        goto return_result;
    }
    if (func_ov006_02055950() != 14) {
        return result;
    }

    func_020235d0(0, 9);
    level = func_020235d0(0x44e, 3);
    if (level >= 2) {
        option_mask |= 1;
    }
    if (level >= 3) {
        option_mask |= 8;
    }
    if (level >= 4) {
        option_mask |= 0x10;
    }
    if (level >= 5) {
        option_mask |= 0x20;
    }
    if (data_0204be18->feature_a != 0) {
        option_mask |= 4;
    }
    if (data_0204be18->feature_b != 0) {
        option_mask |= 2;
    }

    data_ov006_02056660->option_mask = option_mask;
    func_ov006_02055af4(option_mask);

    if (data_ov006_02056660->single_row_mode != 0) {
        func_ov006_0204fbd0(0, &data_ov006_02056660->rows[0]);
    } else {
        u8 i;

        input = func_ov006_0204fa88();
        for (i = 0; i < 4; i++) {
            func_ov006_0204fbd0(i, &data_ov006_02056660->rows[i]);
        }
    }

    func_ov006_02055b30(input);
    func_ov006_02056030();
    func_ov006_02056098();
    func_ov006_02056018(func_02030788());
    func_ov006_02055a54(4, 1, 1);
    func_ov006_02055c38(
        data_ov006_02056660->rows[func_02030788()].icon);

    data_ov006_02056660->message_id = 0x35;
    data_ov006_02056660->field_34 = 0;
    result = (int)func_ov006_02050fc8;

return_result:
    return result;
}
