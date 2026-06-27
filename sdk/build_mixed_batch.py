"""Build a mixed batch: all contextual candidates plus enough any-SDK extras."""
import json, sys, os, re
from collections import Counter, defaultdict

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from prep_contextual_batch import (
    sym_to_delink, sym_meta, disasm_func, format_disasm,
    INDEX, CALLS, NAMES, DONE, display,
)
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
N = int(sys.argv[1]) if len(sys.argv) > 1 else 16
ctx_path = sys.argv[2] if len(sys.argv) > 2 else os.path.join(ROOT, 'sdk', 'build', 'ctx_batch.json')
out_path = sys.argv[3] if len(sys.argv) > 3 else os.path.join(ROOT, 'sdk', 'build', 'ctx_batch_full.json')

counts = Counter(NAMES.values())
by_name = defaultdict(list)
for k, v in NAMES.items():
    m = re.match(r'^func_(ov\d+_)?([0-9a-f]{8})$', k)
    if not m: continue
    addr = int(m.group(2), 16)
    info = INDEX.get(k, {})
    sz = info.get('size', 0); rl = info.get('relocs', [])
    if counts[v] > 1 and sz <= 16 and not rl: continue
    by_name[v].append((addr, k))
sf = {}
for sdk, lst in by_name.items():
    lst.sort()
    sf[lst[0][1]] = sdk
    for addr, k in lst[1:]:
        sf['%s_0x%08x' % (sdk, addr)] = k
sdk_known = set(sf.keys()) | set(sf.values()) | DONE

ctx = json.load(open(ctx_path))
ctx_names = {e['name'] for e in ctx}
extras = []
for c in CALLS:
    fn = c['name']
    if display(fn) in DONE or fn in ctx_names: continue
    callees = set(c['callees'])
    if not (callees & sdk_known): continue
    if c['ninstr'] < 6 or c['ninstr'] > 30: continue
    if fn not in sym_to_delink: continue
    extras.append(c)
extras.sort(key=lambda c: (c['ninstr'], c['size']))

combined = list(ctx)
needed = max(0, N - len(combined))
for c in extras[:needed]:
    fn = c['name']
    info = INDEX[fn]
    mode, hexb, items, rel = disasm_func(fn)
    if mode != c['mode']:
        md = Cs(CS_ARCH_ARM, CS_MODE_THUMB if c['mode'] == 'thumb' else CS_MODE_ARM)
        items = [(i.address, i.mnemonic, i.op_str, rel.get(i.address)) for i in md.disasm(bytes.fromhex(hexb), 0)]
        mode = c['mode']
    combined.append({
        'name': fn, 'size': info['size'], 'mode': mode, 'hex': hexb,
        'n_callers': 0, 'callers': [],
        'delink': sym_to_delink[fn].replace('\\', '/'),
        'disasm': format_disasm(items),
    })

with open(out_path, 'w') as f: json.dump(combined, f, indent=2)
print('combined batch:', len(combined))
for i, e in enumerate(combined):
    print('[%2d] %-30s size=%-3d mode=%-5s callers=%d' % (i, e['name'], e['size'], e['mode'], e.get('n_callers', 0)))
