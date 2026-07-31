/*
 * Ov002_BuildSessionCommand - map a command kind (0..0x1a) to its payload length and, when the
 * session state permits, submit it via func_02031384(7, buf, len). Shared helper used across the
 * ov002 gameplay/session code (Ov002_PollSessionReady, Ov002_UpdatePendingRequest, ...).
 *
 * Writes the kind byte into buf[0], then dispatches on the kind. Most kinds only submit when
 * Session_IsReady() reports the expected state (kinds 3/9/0xf submit when NOT ready; the rest
 * when ready); kinds 0xb/0x12/0x13/0x14/0x15/0x16/0x17/0x18/0x1a submit unconditionally; kinds
 * 0/0xa/0x19 do nothing. On submit it returns func_02031384's handle; otherwise it returns
 * 0xffff (no command sent).
 *
 * ARM. func_02031384's length argument is an unsigned short (zero-extended at the call). The
 * case bodies are emitted in the original source order (NOT numeric) - notably kind 0x12 sits
 * right after kind 9, and kind 0xb sits with the tail unconditional kinds after 0x18 - which is
 * what reproduces the jump-table targets and body layout.
 */

typedef unsigned short u16;
typedef unsigned int   uint;

extern int  func_02030694(void);
extern uint func_02031384(int a, void *b, u16 c);

uint func_ov002_0206fb84(int param_1, u16 *param_2)
{
    uint len;

    *(char *)param_2 = (char)param_1;
    switch (param_1) {
    case 0:
    case 10:
    case 0x19: break;
    case 1:  if (func_02030694()) { len = 8; goto submit; } break;
    case 2:  if (func_02030694()) { len = 8; goto submit; } break;
    case 3:  if (!func_02030694()) { len = 2; goto submit; } break;
    case 4:  if (func_02030694()) { len = 1; goto submit; } break;
    case 5:  if (func_02030694()) { len = 3; goto submit; } break;
    case 6:  if (func_02030694()) { len = 0x24; goto submit; } break;
    case 7:  if (func_02030694()) { len = 8; goto submit; } break;
    case 8:  if (func_02030694()) { len = 0x22; goto submit; } break;
    case 9:  if (!func_02030694()) { len = 10; goto submit; } break;
    case 0x12: len = 4; goto submit;
    case 0xc: if (func_02030694()) { len = 3; goto submit; } break;
    case 0xd: if (func_02030694()) { len = 2; goto submit; } break;
    case 0xe: if (func_02030694()) { len = 2; goto submit; } break;
    case 0xf: if (!func_02030694()) { len = 2; goto submit; } break;
    case 0x10: if (func_02030694()) { len = 0x14; goto submit; } break;
    case 0x11: if (func_02030694()) { len = 0x10; goto submit; } break;
    case 0x14:
    case 0x15: len = 8; goto submit;
    case 0x16: len = 2; goto submit;
    case 0x17:
    case 0x18: len = 0xc; goto submit;
    case 0xb: len = 0x14; goto submit;
    case 0x13: len = 2; goto submit;
    case 0x1a: len = 1; goto submit;
    }
    return 0xffff;
submit:
    return func_02031384(7, param_2, len);
}
