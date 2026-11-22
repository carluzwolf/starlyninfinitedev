/* Starlyn Studio - gerador do .ino e pacotes Bluetooth. Roda no navegador e no Node (teste). */
(function (g) {
'use strict';
const cl = (v, a, b) => Math.max(a, Math.min(b, v)), R = Math.round;
const hx = h => [1, 3, 5].map(i => parseInt((h || '#000000').substr(i, 2), 16) || 0);
const KF_SLOTS = 8, KF_MAXK = 12, CF_SLOTS = 16;

function pk(k) {
  const c = hx(k.tc);
  return { t: cl(R(k.t), 0, 65535), gx: cl(R(k.gx), -127, 127), gy: cl(R(k.gy), -127, 127), cT: cl(R(k.cT * 100), -127, 127),
    cB: cl(R(k.cB * 100), -127, 127), lid: cl(R(k.lid), -127, 127), rot: cl(R(k.rot), -127, 127), sq: cl(R(k.sq * 100), 0, 127),
    ps: cl(R(k.ps * 100), 0, 255), sc: cl(R(k.sc * 100), 0, 255), cheek: cl(R(k.cheek * 100), 0, 255), arc: cl(k.arc | 0, 0, 2),
    tk: cl(R(k.tk * 100), 0, 255), tr: c[0], tg: c[1], tb: c[2], odx: cl(R(k.odx), -127, 127), ody: cl(R(k.ody), -127, 127),
    orot: cl(R(k.orot), -127, 127), oz: cl(R(k.oz * 100), -127, 127), shape: cl(k.shape | 0, 0, 8) };
}
function pf(f) {
  const l = f.link;
  return { c: [...hx(f.eL), ...hx(f.pL), ...hx(l ? f.eL : f.eR), ...hx(l ? f.pL : f.pR)], gA: f.grad ? 1 : 0, gb: hx(f.gb),
    rxS: cl(R(f.rx * 100), 20, 255), ryS: cl(R(f.ry * 100), 20, 255), psS: cl(R(f.ps * 100), 10, 255),
    tilt: cl(R(f.tilt), -127, 127), gap: cl(R(f.gap), -127, 127), cutBot: cl(R(f.cutBot * 100), 0, 100), shape: cl(f.shape | 0, 0, 8) };
}
const sortKeys = r => r.keys.slice(0, KF_MAXK).sort((a, b) => a.t - b.t);

/* ---------- pacotes Bluetooth (<= 20 bytes cada) ---------- */
function bleFace(s, f) {
  const p = pf(f);
  return [new Uint8Array([0x20, s, ...p.c, p.gA, ...p.gb]),
          new Uint8Array([0x21, s, p.rxS, p.ryS, p.psS, p.tilt & 255, p.gap & 255, p.cutBot, p.shape])];
}
function bleReact(s, r) {
  const keys = sortKeys(r).map(pk), out = [];
  out.push(new Uint8Array([0x22, s, keys.length, r.dur & 255, (r.dur >> 8) & 255, cl(r.w | 0, 0, 255)]));
  keys.forEach((k, i) => {
    out.push(new Uint8Array([0x23, s, i, k.t & 255, k.t >> 8, k.gx & 255, k.gy & 255, k.cT & 255, k.cB & 255, k.lid & 255, k.rot & 255, k.sq & 255, k.ps, k.sc, k.cheek, k.arc & 255]));
    out.push(new Uint8Array([0x24, s, i, k.tk, k.tr, k.tg, k.tb, k.odx & 255, k.ody & 255, k.orot & 255, k.oz & 255, k.shape]));
  });
  return out;
}

/* ---------- bloco C++ que entra no .ino ---------- */
const FIXED = `
// ======================= STARLYN STUDIO (gerado pelo site) =======================
// Rostos novos = ids 77..92 (CF_SLOTS) | Reacoes novas = ids 130..137 (KF_SLOTS). Tambem podem ser reescritos ao vivo pelo Bluetooth (0x20..0x24).
#define KF_SLOTS 8
#define KF_MAXK  12
#define CF_SLOTS 16
#define CF_BASE  77
struct KFr { uint16_t t; int8_t gx, gy, cT, cB, lid, rot, sq; uint8_t ps, sc, cheek; int8_t arc; uint8_t tk, tr, tg, tb; int8_t odx, ody, orot, oz; uint8_t shape; };
struct CFace { uint8_t used, c[12], gA, gb0, gb1, gb2, rxS, ryS, psS; int8_t tilt, gap; uint8_t cutBot, shape; };
@@DATA@@
static void cfApply(int s) {
  Style &S = STY[CF_BASE + s]; const CFace &c = cfD[s];
  S = STY[0];
  if (!c.used) return;
  S.er = c.c[0]; S.eg = c.c[1]; S.eb = c.c[2]; S.pr = c.c[3]; S.pg = c.c[4]; S.pb = c.c[5];
  S.er2 = c.c[6]; S.eg2 = c.c[7]; S.eb2 = c.c[8]; S.pr2 = c.c[9]; S.pg2 = c.c[10]; S.pb2 = c.c[11];
  S.gA = c.gA ? 1.0f : 0.0f; S.gbr = c.gb0; S.gbg = c.gb1; S.gbb = c.gb2;
  S.rx = 33 * KS * c.rxS * 0.01f; S.ry = 44 * KS * c.ryS * 0.01f;
  S.prx = 12.7f * KS * c.psS * 0.01f; S.pry = 16.3f * KS * c.psS * 0.01f;
  S.rot = 7.0f + c.tilt; S.gap = 37 * KS + c.gap; S.cutBot = c.cutBot * 0.01f;
  S.pSlit = (c.shape == 1); S.pHeart = (c.shape == 2); S.pStar = (c.shape == 3); S.pDollar = (c.shape == 4);
  S.pSpiral = (c.shape == 5); S.pCross = (c.shape == 6); S.pBolt = (c.shape == 7); S.pFlower = (c.shape == 8);
}
static void applyCustomFaces() { for (int s = 0; s < CF_SLOTS; s++) cfApply(s); }
static void kfApplyAll() { for (int s = 0; s < KF_SLOTS; s++) { RXT[113 + s].dur = kfDur[s]; RXT[113 + s].w = kfW[s]; } }

// linha do tempo de uma reacao criada no site (interpola quadro-chave a quadro-chave)
static void kfPlay(int s, float t, Style &T, Ov &O, const Style &H) {
  if (s < 0 || s >= KF_SLOTS) return;
  int n = kfN[s]; if (n < 1) return;
  int i = 0; while (i + 1 < n && t >= (float)kfK[s][i + 1].t) i++;
  int j = (i + 1 < n) ? i + 1 : i;
  const KFr &a = kfK[s][i], &b = kfK[s][j];
  float u = (j != i && b.t > a.t) ? ease((t - a.t) / (float)(b.t - a.t)) : 0.0f;
  #define KL(f) lerpf((float)a.f, (float)b.f, u)
  goX = KL(gx) * 0.1f * LOOK_X; goY = KL(gy) * 0.1f * LOOK_Y;
  T.cutTop = clampf(H.cutTop + KL(cT) * 0.01f, 0, 0.7f);
  T.cutBot = clampf(H.cutBot + KL(cB) * 0.01f, 0, 0.6f);
  T.lid = H.lid + KL(lid); T.rot = H.rot + KL(rot);
  T.squint = clampf(KL(sq) * 0.01f, 0, 0.95f);
  T.ps = H.ps * KL(ps) * 0.01f;
  float sc = KL(sc) * 0.01f; T.rx = H.rx * sc; T.ry = H.ry * sc;
  T.cheek = KL(cheek) * 0.01f;
  float ar = lerpf(a.arc ? 1.0f : 0.0f, b.arc ? 1.0f : 0.0f, u);
  if (ar > 0.01f) { T.arc = ar; T.bend = (a.arc == 2 || b.arc == 2) ? 9.0f : -9.0f; morphTau = 150; } else morphTau = 90;
  float tkk = KL(tk) * 0.01f;
  if (tkk > 0.01f) tintStyle(T, KL(tr), KL(tg), KL(tb), tkk);
  int sh = (u > 0.5f) ? b.shape : a.shape;
  if (sh > 0) {
    T.pSlit = (sh == 1); T.pHeart = (sh == 2); T.pStar = (sh == 3); T.pDollar = (sh == 4);
    T.pSpiral = (sh == 5); T.pCross = (sh == 6); T.pBolt = (sh == 7); T.pFlower = (sh == 8);
  } else { T.pSlit = H.pSlit; T.pHeart = H.pHeart; T.pStar = H.pStar; T.pDollar = H.pDollar; }
  O.dx += KL(odx); O.dy += KL(ody); O.rot += KL(orot); O.zoom *= 1.0f + KL(oz) * 0.01f;
  #undef KL
}

// comandos Bluetooth novos do site: 0x20/0x21 = rosto | 0x22 = cabecalho da reacao | 0x23/0x24 = quadro-chave
static void studioBle(const uint8_t *d, size_t n) {
  switch (d[0]) {
    case 0x20: if (n >= 18 && d[1] < CF_SLOTS) { CFace &c = cfD[d[1]]; c.used = 1; memcpy(c.c, d + 2, 12); c.gA = d[14]; c.gb0 = d[15]; c.gb1 = d[16]; c.gb2 = d[17]; cfApply(d[1]); } break;
    case 0x21: if (n >= 9 && d[1] < CF_SLOTS) { CFace &c = cfD[d[1]]; c.rxS = d[2]; c.ryS = d[3]; c.psS = d[4]; c.tilt = (int8_t)d[5]; c.gap = (int8_t)d[6]; c.cutBot = d[7]; c.shape = d[8]; cfApply(d[1]); } break;
    case 0x22: if (n >= 6 && d[1] < KF_SLOTS) { int s = d[1]; kfN[s] = 0; kfDur[s] = d[3] | (d[4] << 8); kfW[s] = d[5]; RXT[113 + s].dur = kfDur[s]; RXT[113 + s].w = kfW[s]; } break;
    case 0x23: if (n >= 16 && d[1] < KF_SLOTS && d[2] < KF_MAXK) { KFr &k = kfK[d[1]][d[2]];
        k.t = d[3] | (d[4] << 8); k.gx = (int8_t)d[5]; k.gy = (int8_t)d[6]; k.cT = (int8_t)d[7]; k.cB = (int8_t)d[8]; k.lid = (int8_t)d[9];
        k.rot = (int8_t)d[10]; k.sq = (int8_t)d[11]; k.ps = d[12]; k.sc = d[13]; k.cheek = d[14]; k.arc = (int8_t)d[15]; } break;
    case 0x24: if (n >= 12 && d[1] < KF_SLOTS && d[2] < KF_MAXK) { KFr &k = kfK[d[1]][d[2]];
        k.tk = d[3]; k.tr = d[4]; k.tg = d[5]; k.tb = d[6]; k.odx = (int8_t)d[7]; k.ody = (int8_t)d[8]; k.orot = (int8_t)d[9]; k.oz = (int8_t)d[10]; k.shape = d[11];
        if (kfN[d[1]] < d[2] + 1) kfN[d[1]] = d[2] + 1; } break;
    default: break;
  }
}
`;

function dataBlock(S) {
  const rs = S.reacts.slice(0, KF_SLOTS), fs = S.faces.slice(0, CF_SLOTS);
  const kfLine = k => '{' + [k.t, k.gx, k.gy, k.cT, k.cB, k.lid, k.rot, k.sq, k.ps, k.sc, k.cheek, k.arc, k.tk, k.tr, k.tg, k.tb, k.odx, k.ody, k.orot, k.oz, k.shape].join(',') + '}';
  const slots = [], N = [], D = [], W = [];
  for (let s = 0; s < KF_SLOTS; s++) {
    const r = rs[s];
    if (!r) { slots.push('  {}'); N.push(0); D.push(2000); W.push(0); continue; }
    const ks = sortKeys(r).map(pk);
    slots.push('  { ' + ks.map(kfLine).join(', ') + ' }'); N.push(ks.length); D.push(cl(R(r.dur), 300, 20000)); W.push(cl(R(r.w), 0, 10));
  }
  const cf = [];
  for (let s = 0; s < CF_SLOTS; s++) {
    const f = fs[s];
    if (!f) { cf.push('  {0,{0},0,0,0,0,100,100,100,0,0,20,0}'); continue; }
    const p = pf(f);
    cf.push('  {1,{' + p.c.join(',') + '},' + p.gA + ',' + p.gb.join(',') + ',' + [p.rxS, p.ryS, p.psS, p.tilt, p.gap, p.cutBot, p.shape].join(',') + '}');
  }
  const names = (a, pre) => a.map((x, i) => '//   ' + pre + i + ' = ' + String(x.name || '').replace(/[^\x20-\x7E]/g, '?').replace(/\*\//g, '')).join('\n');
  return names(fs, 'rosto id ' + 77 + '+') + '\n' + names(rs, 'reacao id ' + 130 + '+') + '\n' +
    'static KFr kfK[KF_SLOTS][KF_MAXK] = {\n' + slots.join(',\n') + '\n};\n' +
    'static uint8_t kfN[KF_SLOTS] = {' + N.join(',') + '};\n' +
    'static uint16_t kfDur[KF_SLOTS] = {' + D.join(',') + '};\n' +
    'static uint8_t kfW[KF_SLOTS] = {' + W.join(',') + '};\n' +
    'static CFace cfD[CF_SLOTS] = {\n' + cf.join(',\n') + '\n};';
}

function patch(src, S) {
  let t = src.replace(/\r\n/g, '\n');
  const sig = 'static void customRx(uint8_t cu, float t, float d, float e, float sd, uint32_t now, Style &T, Ov &O, const Style &H) {';
  const rules = [
    ['#define NFACES 77', '#define NFACES 93'],
    ['A_COUNT = A_CU0 + 27 + 4 };', 'A_COUNT = A_CU0 + 27 + 4 + 8 };'],
    ['#define NRX 113', '#define NRX 121'],
    ['  // n tem que ser 113 (NRX)', '  for (int k = 0; k < 8; k++) RXT[n++].D(2000).Gz(0, 0).Wt(0).Cu(100 + k);   // Studio: reacoes criadas no site (ids 130..137)\n  // n tem que ser 121 (NRX)'],
    [sig, FIXED.replace('@@DATA@@', dataBlock(S)) + '\n' + sig + '\n  if (cu >= 100) { kfPlay(cu - 100, t, T, O, H); return; }'],
    ['if (i >= 82 && i < 109) {', 'if (i >= 113) return false;\n    if (i >= 82 && i < 109) {'],
    ['case 0x0A: if (n >= 2 && d[1] < NFACES)', 'case 0x20: case 0x21: case 0x22: case 0x23: case 0x24: studioBle(d, n); break;\n    case 0x0A: if (n >= 2 && d[1] < NFACES)'],
    ['void setup() {\n  initStyles();', 'void setup() {\n  initStyles();\n  applyCustomFaces();'],
    ['  initReacts();\n  cur = STY[0];', '  initReacts();\n  kfApplyAll();\n  cur = STY[0];']
  ];
  for (const [a, b] of rules) {
    const n = t.split(a).length - 1;
    if (n !== 1) throw new Error('Ponto de edicao nao encontrado no .ino (' + n + 'x): ' + a.slice(0, 50));
    t = t.replace(a, () => b);
  }
  return '/* STARLYN STUDIO: arquivo gerado a partir do starboy_v13_ble.ino pelo site (rostos 77..92, reacoes 130..137). */\n' + t;
}

g.StarboyExport = { patch, bleFace, bleReact, KF_SLOTS, KF_MAXK, CF_SLOTS };
if (typeof module !== 'undefined') module.exports = g.StarboyExport;
})(typeof window !== 'undefined' ? window : globalThis);
