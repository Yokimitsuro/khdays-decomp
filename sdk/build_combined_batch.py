import json, sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from prep_contextual_batch import sym_to_delink, sym_meta, disasm_func, format_disasm, INDEX

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ctx = json.load(open(os.path.join(ROOT,'sdk','build','ctx_batch7.json')))
extras_names = [
    'func_02030a2c','func_02024ae0','func_02024b04','func_0203d194',
    'func_0202f818','func_0202f9f8','func_02035c28','func_0202429c',
    'func_0202c06c','func_02024264',
]
combined = list(ctx)
for n in extras_names:
    if n not in sym_to_delink: continue
    info = INDEX[n]
    mode, hexb, items, rel = disasm_func(n)
    combined.append({
        'name': n, 'size': info['size'], 'mode': mode,
        'hex': hexb, 'n_callers': 0, 'callers': [],
        'delink': sym_to_delink[n].replace('\\', '/'),
        'disasm': format_disasm(items),
    })
print('combined batch:', len(combined))
with open(os.path.join(ROOT,'sdk','build','ctx_batch7_full.json'),'w') as f:
    json.dump(combined,f,indent=2)
for i,e in enumerate(combined):
    print('[%2d] %-25s size=%-3d mode=%-5s callers=%d' % (i,e['name'],e['size'],e['mode'],e.get('n_callers',0)))
