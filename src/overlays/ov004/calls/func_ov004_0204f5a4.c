extern int func_ov004_0204f4b4(int value);

int func_ov004_0204f5a4(int value) {
    switch (value) {
    case 0x1c:
        return 0x31;

    case 0x0d:
    case 0x0e:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x31:
    case 0x32:
    case 0x47:
    case 0x48:
    case 0x49:
    case 0x4a:
    case 0x5e:
    case 0x5f:
    case 0x60:
    case 0x75:
    case 0x76:
    case 0x95:
    case 0x96:
    case 0x97:
    case 0xab:
    case 0xac:
    case 0xc1:
    case 0xe0:
    case 0xff:
    case 0x114:
    case 0x128:
    case 0x129:
    case 0x12a:
    case 0x12b:
    case 0x12c:
    case 0x141:
    case 0x160:
    case 0x161:
    case 0x162:
    case 0x163:
    case 0x164:
    case 0x165:
    case 0x166:
        return value + 1;

    default:
        if (value >= 7 && value <= 12) {
            return value + 1;
        }
        return func_ov004_0204f4b4(value);
    }
}
