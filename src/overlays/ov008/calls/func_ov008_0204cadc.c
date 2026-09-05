typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov008MessageHeader {
    u8 messageType : 4;
    u8 sessionState : 4;
    u8 playerIndex;
} Ov008MessageHeader;

typedef struct Ov008Message2 { Ov008MessageHeader header; } Ov008Message2;
typedef struct Ov008Message4 { Ov008MessageHeader header; u8 payload[2]; } Ov008Message4;
typedef struct Ov008Message6 { Ov008MessageHeader header; u8 payload[4]; } Ov008Message6;
typedef struct Ov008Message16 { Ov008MessageHeader header; u8 payload[14]; } Ov008Message16;
typedef struct Ov008Message28 { Ov008MessageHeader header; u8 payload[26]; } Ov008Message28;
typedef struct Ov008Message32 { Ov008MessageHeader header; u8 payload[30]; } Ov008Message32;
typedef struct Ov008Message68 { Ov008MessageHeader header; u8 payload[66]; } Ov008Message68;

typedef struct Ov008MenuContext {
    u8 pad_0000[0x18];
    u32 sessionState;
    Ov008Message2 message9;
    u8 pad_001e[8];
    Ov008Message32 message3;
    Ov008Message6 message2;
    Ov008Message68 message8;
    Ov008Message16 message5;
    u8 pad_00a0[0x70];
    Ov008Message28 message1;
    Ov008Message68 message6;
    Ov008Message4 message4;
    Ov008Message2 message7;
    u8 pad_0176[0x4ed6];
    u16 messageHandle;
} Ov008MenuContext;

extern Ov008MenuContext *data_ov008_02090f00;
extern u32 func_02030788(void);
extern int func_02031258(int type, u16 *payload, u16 size);
extern u16 func_02031384(int type, void *payload, u16 size);

void func_ov008_0204cadc(u8 mode)
{
    Ov008MessageHeader header;

    header.messageType = mode;
    header.sessionState = data_ov008_02090f00->sessionState & 0xf;
    header.playerIndex = func_02030788();

    switch (mode) {
    case 1:
        data_ov008_02090f00->message1.header = header;
        func_02031258(0xe, (u16 *)&data_ov008_02090f00->message1, sizeof(Ov008Message28));
        return;
    case 4:
        data_ov008_02090f00->message4.header = header;
        func_02031258(0xe, (u16 *)&data_ov008_02090f00->message4, sizeof(Ov008Message4));
        return;
    case 5:
        data_ov008_02090f00->message5.header = header;
        func_02031258(0xe, (u16 *)&data_ov008_02090f00->message5, sizeof(Ov008Message16));
        return;
    case 6:
        data_ov008_02090f00->message6.header = header;
        func_02031258(0xe, (u16 *)&data_ov008_02090f00->message6, sizeof(Ov008Message68));
        return;
    case 7:
        data_ov008_02090f00->message7.header = header;
        func_02031258(0xe, (u16 *)&data_ov008_02090f00->message7, sizeof(Ov008Message2));
        return;
    case 8:
        data_ov008_02090f00->message8.header = header;
        func_02031258(0xe, (u16 *)&data_ov008_02090f00->message8, sizeof(Ov008Message68));
        return;
    case 3:
        data_ov008_02090f00->message3.header = header;
        func_02031258(0xe, (u16 *)&data_ov008_02090f00->message3, sizeof(Ov008Message32));
        return;
    case 2:
        data_ov008_02090f00->message2.header = header;
        func_02031258(0xe, (u16 *)&data_ov008_02090f00->message2, sizeof(Ov008Message6));
        return;
    case 9:
        data_ov008_02090f00->message9.header = header;
        func_02031258(0xe, (u16 *)&data_ov008_02090f00->message9, sizeof(Ov008Message2));
        return;
    case 10:
        if (data_ov008_02090f00->messageHandle != 0xffff) {
            return;
        }
        data_ov008_02090f00->message9.header = header;
        data_ov008_02090f00->messageHandle = func_02031384(0xe, &data_ov008_02090f00->message9, sizeof(Ov008Message2));
        return;
    }
}
