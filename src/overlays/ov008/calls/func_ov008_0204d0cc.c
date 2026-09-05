typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct GameplayThresholds {
    u8 pad_00[4];
    u16 optionFlags;
    u8 value6;
    u8 value7;
    u16 pad_08;
    u16 valueA;
    u16 valueC;
} GameplayThresholds;

typedef struct GameplayRules {
    u8 value0;
    u8 value1;
    u8 value2;
    u8 value3;
    u8 value4;
    u8 value5;
    u8 value6;
    u8 value7;
    u8 value8;
    u8 value9;
    u8 valueA;
    u8 valueB;
} GameplayRules;

extern GameplayRules data_0204c248;
extern GameplayThresholds data_0204c254;
extern u32 func_020235d0(int fieldId, int width);

void func_ov008_0204d0cc(void)
{
    u32 value;

    value = func_020235d0(0x3c15, 1);
    switch (value) {
    case 0:
        data_0204c254.optionFlags |= 1;
        break;
    case 1:
        data_0204c254.optionFlags &= ~1;
        break;
    }

    value = func_020235d0(0x3c16, 1);
    switch (value) {
    case 0:
        data_0204c254.optionFlags |= 6;
        break;
    case 1:
        data_0204c254.optionFlags &= ~6;
        break;
    }

    value = func_020235d0(0x3c17, 2);
    switch (value) {
    case 0:
        data_0204c248.value7 = 0;
        data_0204c254.value6 = 0;
        break;
    case 1:
        data_0204c248.value7 = 1;
        data_0204c254.value6 = 0x14;
        break;
    case 2:
        data_0204c248.value7 = 2;
        data_0204c254.value6 = 0x32;
        break;
    }

    value = func_020235d0(0x3c19, 2);
    switch (value) {
    case 0:
        data_0204c254.value7 = 0;
        break;
    case 1:
        data_0204c254.value7 = 0x1e;
        break;
    case 2:
        data_0204c254.value7 = 0x3c;
        break;
    }

    value = func_020235d0(0x3c1b, 2);
    switch (value) {
    case 2:
        data_0204c254.valueA = 0;
        data_0204c254.valueC = 0;
        break;
    case 0:
        data_0204c254.valueA = 0x1e;
        data_0204c254.valueC = 0;
        break;
    case 1:
        data_0204c254.valueA = 0;
        data_0204c254.valueC = 0xc;
        break;
    }

    value = func_020235d0(0x3c1d, 2);
    switch (value) {
    case 2:
        data_0204c248.value0 = 0;
        break;
    case 1:
        data_0204c248.value0 = 1;
        break;
    case 0:
        data_0204c248.value0 = 2;
        break;
    }

    value = func_020235d0(0x3c26, 1);
    switch (value) {
    case 0:
        data_0204c248.valueB = 1;
        break;
    case 1:
        data_0204c248.valueB = 0;
        break;
    }

    value = func_020235d0(0x3c1f, 1);
    switch (value) {
    case 0:
        data_0204c248.value1 = 1;
        break;
    case 1:
        data_0204c248.value1 = 0;
        break;
    }

    value = func_020235d0(0x3c20, 1);
    switch (value) {
    case 0:
        data_0204c248.value2 = 1;
        break;
    case 1:
        data_0204c248.value2 = 0;
        break;
    }

    value = func_020235d0(0x35c1, 2);
    switch (value) {
    case 0:
        data_0204c248.value9 = 2;
        break;
    case 1:
        data_0204c248.value9 = 1;
        break;
    case 2:
        data_0204c248.value9 = 0;
        break;
    }

    value = func_020235d0(0x3c23, 2);
    switch (value) {
    case 0:
        data_0204c248.value4 = 0x1e;
        break;
    case 1:
        data_0204c248.value4 = 0x78;
        break;
    case 2:
        data_0204c248.value4 = 0xff;
        break;
    }

    value = func_020235d0(0x3c21, 2);
    switch (value) {
    case 0:
        data_0204c248.value3 = 4;
        break;
    case 1:
        data_0204c248.value3 = 2;
        break;
    case 2:
        data_0204c248.value3 = 0;
        break;
    }

    value = func_020235d0(0x3c25, 1);
    switch (value) {
    case 0:
        data_0204c248.value5 = 1;
        break;
    case 1:
        data_0204c248.value5 = 0;
        break;
    }

    value = func_020235d0(0x3c27, 2);
    switch (value) {
    case 0:
        data_0204c248.valueA = 2;
        break;
    case 1:
        data_0204c248.valueA = 1;
        break;
    case 2:
        data_0204c248.valueA = 0;
        break;
    }

    value = func_020235d0(0x3c29, 2);
    switch (value) {
    case 2:
        data_0204c248.value8 = 0;
        return;
    case 1:
        data_0204c248.value8 = 1;
        return;
    case 0:
        data_0204c248.value8 = 2;
        return;
    }
}
