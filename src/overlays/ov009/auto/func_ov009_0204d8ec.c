int func_ov009_0204d8ec(int pos, int stride, int width, int height) {
    int w = width;
    if (w > 0x20) w = 0x20;
    if (height > 0x20) height = 0x20;
    int base;
    if (pos >= w) {
        base = w * height;
        pos = pos - w;
        w = width - w;
    } else {
        base = 0;
    }
    return base + (stride * w + pos);
}
