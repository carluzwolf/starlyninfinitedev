'use strict';
/* Starlyn Studio · painel do robô Karlu (base: Starboy v12 BLE) */
const $ = (s, r = document) => r.querySelector(s), $$ = (s, r = document) => [...r.querySelectorAll(s)];
const clamp = (v, a, b) => Math.min(b, Math.max(a, v)), lerp = (a, b, t) => a + (b - a) * t;
const ease = t => { t = clamp(t, 0, 1); return t * t * (3 - 2 * t); };
const hex2 = h => [1, 3, 5].map(i => parseInt(h.substr(i, 2), 16));
const rgb2hex = (r, g, b) => '#' + [r, g, b].map(v => Math.round(clamp(v, 0, 255)).toString(16).padStart(2, '0')).join('');
const rgbs = (r, g, b) => `rgb(${r | 0},${g | 0},${b | 0})`;
const ic = n => `<svg class="ic"><use href="#i-${n}"/></svg>`;
const D2R = Math.PI / 180;
const SHAPES = ['Redonda', 'Fenda de gato', 'Coração', 'Estrela', 'Cifrão', 'Espiral', 'Mira', 'Raio', 'Flor'];

/* ---------- dados ---------- */
const newFace = (n = 'Novo olho') => ({ name: n, eL: '#ff42c4', pL: '#fadcb8', eR: '#ff42c4', pR: '#fadcb8', link: true, grad: false, gb: '#ff3282', rx: 1, ry: 1, ps: 1, tilt: 0, gap: 0, cutBot: 0, shape: 0 });
const KF0 = () => ({ t: 0, gx: 0, gy: 0, cT: 0, cB: 0, lid: 0, rot: 0, sq: 0, ps: 1, sc: 1, cheek: 0, arc: 0, tk: 0, tc: '#ff4060', odx: 0, ody: 0, orot: 0, oz: 0, shape: 0 });
const PRESETS = [
  ['Rosa original', '#ff42c4', '#fadcb8'], ['Azul elétrico', '#2e5cff', '#aaebff'], ['Verde neon', '#3cff78', '#fffa96'],
  ['Roxo', '#a050ff', '#ffaae6'], ['Laranja', '#ff8c28', '#ffeb78'], ['Starboy original', '#e53f17', '#dcc4e0'],
  ['Ciano', '#1ee6f0', '#142896'], ['Polly sol', '#ffd728', '#ff58a0'], ['Vampiro', '#cd0f2d', '#1c0008'], ['Matrix', '#00ff64', '#002d0f']
];
const TPL = [
  ['Feliz', 1800, [{ t: 0 }, { t: 350, arc: 1, ody: -3 }, { t: 900, arc: 1, ody: 3 }, { t: 1400, arc: 1, ody: -3 }, { t: 1800 }]],
  ['Susto', 1500, [{ t: 0 }, { t: 160, sc: 1.18, ps: .5, oz: .1, ody: -6 }, { t: 1000, sc: 1.12, ps: .55 }, { t: 1500 }]],
  ['Curioso', 2400, [{ t: 0 }, { t: 400, gx: 6, gy: -7, rot: 6, orot: 9, odx: 4 }, { t: 1500, gx: 6, gy: -7, rot: 6, orot: 9, odx: 4 }, { t: 2400 }]],
  ['Triste', 2800, [{ t: 0 }, { t: 700, cT: .25, lid: 12, gy: 7, ody: 5, tk: .4, tc: '#6e62ff' }, { t: 2100, cT: .25, lid: 12, gy: 7, ody: 5, tk: .4, tc: '#6e62ff' }, { t: 2800 }]],
  ['Bravo', 2200, [{ t: 0 }, { t: 300, cT: .45, lid: -24, tk: .5, tc: '#ff2828' }, { t: 1800, cT: .45, lid: -24, tk: .5, tc: '#ff2828', odx: 3 }, { t: 2200 }]]
];
const mkReact = i => { const [name, dur, ks] = TPL[i % TPL.length]; return { name, dur, w: 5, keys: ks.map(k => ({ ...KF0(), ...k })) }; };
const LS = 'starlyn-studio-v2';
let S = null;
try { S = JSON.parse(localStorage.getItem(LS)); } catch (e) { }
if (!S || !S.faces || !S.reacts) S = { faces: [newFace('Rosa original')], reacts: [mkReact(0)], fi: 0, ri: 0, ki: 0 };
const save = () => { try { localStorage.setItem(LS, JSON.stringify(S)); } catch (e) { } };
const curFace = () => S.faces[S.fi], curReact = () => S.reacts[S.ri], curKey = () => curReact().keys[S.ki];

/* ---------- parâmetros do simulador (mesmas medidas do firmware V12) ---------- */
function faceP(f) {
  const l = f.link, [a, b, c] = hex2(f.eL), [d, e, g] = hex2(f.pL), [a2, b2, c2] = hex2(l ? f.eL : f.eR), [d2, e2, g2] = hex2(l ? f.pL : f.pR), [x, y, z] = hex2(f.gb);
  return { er: a, eg: b, eb: c, pr: d, pg: e, pb: g, er2: a2, eg2: b2, eb2: c2, pr2: d2, pg2: e2, pb2: g2, gA: f.grad ? 1 : 0, gbr: x, gbg: y, gbb: z,
    rx: 42.24 * f.rx, ry: 56.32 * f.ry, rot: 7 + f.tilt, gap: 47.36 + f.gap, cy: 112.3, cutTop: 0, cutBot: f.cutBot, lid: 0,
    prx: 16.26 * f.ps, pry: 20.86 * f.ps, px: -11.78, py: 8.83, ps: 1, squint: 0, arc: 0, bend: -9, cheek: 0, scL: 1, scR: 1,
    odx: 0, ody: 0, orot: 0, oz: 1, gx: 0, gy: 0, conv: 1, shape: f.shape };
}
function sample(keys, t) {
  const ks = keys.slice().sort((a, b) => a.t - b.t); let i = 0;
  while (i + 1 < ks.length && t >= ks[i + 1].t) i++;
  const A = ks[i], B = ks[Math.min(i + 1, ks.length - 1)], u = B.t > A.t && B !== A ? ease((t - A.t) / (B.t - A.t)) : 0, o = {};
  for (const k in A) if (typeof A[k] === 'number') o[k] = lerp(A[k], B[k], u);
  const ca = hex2(A.tc), cb = hex2(B.tc); o.tr = lerp(ca[0], cb[0], u); o.tg = lerp(ca[1], cb[1], u); o.tb = lerp(ca[2], cb[2], u);
  o.arcV = lerp(A.arc ? 1 : 0, B.arc ? 1 : 0, u); o.bend = (A.arc === 2 || B.arc === 2) ? 9 : -9; o.shape = u > .5 ? B.shape : A.shape;
  return o;
}
function kfApply(P, k) {
  P.gx = k.gx * 1.2; P.gy = k.gy * 1.4;
  P.cutTop = clamp(P.cutTop + k.cT, 0, .7); P.cutBot = clamp(P.cutBot + k.cB, 0, .6);
  P.lid += k.lid; P.rot += k.rot; P.squint = clamp(k.sq, 0, .95); P.ps *= k.ps; P.rx *= k.sc; P.ry *= k.sc; P.cheek = k.cheek;
  const av = k.arcV !== undefined ? k.arcV : (k.arc ? 1 : 0); P.arc = av; P.bend = k.bend !== undefined ? k.bend : (k.arc === 2 ? 9 : -9);
  if (k.tk > .01) for (const [a, b, c] of [['er', 'eg', 'eb'], ['er2', 'eg2', 'eb2'], ['gbr', 'gbg', 'gbb']]) { P[a] = lerp(P[a], k.tr !== undefined ? k.tr : hex2(k.tc)[0], k.tk); P[b] = lerp(P[b], k.tg !== undefined ? k.tg : hex2(k.tc)[1], k.tk); P[c] = lerp(P[c], k.tb !== undefined ? k.tb : hex2(k.tc)[2], k.tk); }
  if (k.shape > 0) P.shape = k.shape;
  P.odx = k.odx; P.ody = k.ody; P.orot = k.orot; P.oz = 1 + k.oz;
}

/* ---------- desenho ---------- */
function hp(ctx, a, d, below) { ctx.rotate(a); ctx.beginPath(); below ? ctx.rect(-500, d, 1000, 1000) : ctx.rect(-500, d - 1000, 1000, 1000); ctx.rotate(-a); ctx.clip(); }
function drawShape(ctx, sh, rx, ry, col) {
  ctx.fillStyle = col; ctx.strokeStyle = col; const r = Math.max(rx, ry); ctx.beginPath();
  if (sh === 0) { ctx.ellipse(0, 0, rx, Math.max(ry, .1), 0, 0, 7); ctx.fill(); return; }
  if (sh === 1) { ctx.ellipse(0, 0, rx * .22, ry * 1.9, 0, 0, 7); ctx.fill(); return; }
  if (sh === 2) { const q = r * 1.15; ctx.moveTo(0, q * .9); ctx.bezierCurveTo(-q * 1.5, q * .1, -q * .9, -q * 1.1, 0, -q * .4); ctx.bezierCurveTo(q * .9, -q * 1.1, q * 1.5, q * .1, 0, q * .9); ctx.fill(); return; }
  if (sh === 3) { for (let i = 0; i < 10; i++) { const a = (-90 + 36 * i) * D2R, d = i % 2 ? r * .6 : r * 1.55; ctx.lineTo(Math.cos(a) * d, Math.sin(a) * d); } ctx.closePath(); ctx.fill(); return; }
  if (sh === 4) { ctx.font = `800 ${r * 2.3}px Manrope,sans-serif`; ctx.textAlign = 'center'; ctx.textBaseline = 'middle'; ctx.fillText('$', 0, 2); return; }
  if (sh === 5) { ctx.lineWidth = 2.4; for (let i = 0; i <= 60; i++) { const a = i / 60 * 18.85, d = i / 60 * r * 1.8; ctx.lineTo(Math.cos(a) * d, Math.sin(a) * d); } ctx.stroke(); return; }
  if (sh === 6) { ctx.lineWidth = 2; ctx.arc(0, 0, r * 1.1, 0, 7); ctx.moveTo(-r * 1.5, 0); ctx.lineTo(r * 1.5, 0); ctx.moveTo(0, -r * 1.5); ctx.lineTo(0, r * 1.5); ctx.stroke(); return; }
  if (sh === 7) { const p = [[.55, -1], [-.62, .1], [.0, .1], [-.42, 1], [.7, -.2], [.05, -.2]]; p.forEach(([a, b]) => ctx.lineTo(a * r * 1.2, b * r * 1.4)); ctx.closePath(); ctx.fill(); return; }
  for (let i = 0; i < 5; i++) { const a = (-90 + 72 * i) * D2R; ctx.moveTo(Math.cos(a) * r * .84 + r * .56, Math.sin(a) * r * .84); ctx.arc(Math.cos(a) * r * .84, Math.sin(a) * r * .84, r * .56, 0, 7); } ctx.fill();
}
function drawEye(ctx, P, side, bl) {
  const k = side < 0, sc = k ? P.scL : P.scR, cl = Math.max(bl, P.squint), arc = P.arc;
  const RX = P.rx * sc, RY0 = P.ry * sc, sy = Math.max((1 - cl * .96) * (1 - .94 * ease(arc / .55)), .03), RY = RY0 * sy;
  const cx = 120 + side * P.gap + side * (sc - 1) * P.rx * .35, cy = P.cy + RY0 * (3 * P.cutBot) * Math.max(cl, bl * .93) * .96;
  const rot = side * P.rot * (1 - .8 * Math.min(1, bl)) * (1 - .75 * arc);
  const ec = k ? [P.er, P.eg, P.eb] : [P.er2, P.eg2, P.eb2], pc = k ? [P.pr, P.pg, P.pb] : [P.pr2, P.pg2, P.pb2];
  const bodyA = 1 - ease((arc - .56) / .22);
  ctx.save(); ctx.translate(cx, cy); ctx.rotate(rot * D2R);
  ctx.beginPath(); ctx.ellipse(0, 0, RX * (1 + .05 * cl), RY, 0, 0, 7); ctx.clip();
  hp(ctx, side * P.lid * D2R, -RY + 2 * RY * P.cutTop, true);
  hp(ctx, (-side * 8 * (side > 0 ? 1.3 : .6) - rot) * D2R, RY - 2 * RY * P.cutBot, false);
  ctx.globalAlpha = bodyA;
  let fs = rgbs(...ec);
  if (P.gA) { const g = ctx.createLinearGradient(0, -RY, 0, RY); g.addColorStop(0, fs); g.addColorStop(1, rgbs(P.gbr, P.gbg, P.gbb)); fs = g; }
  ctx.fillStyle = fs; ctx.fillRect(-RX * 1.5, -RY0 * 1.5, RX * 3, RY0 * 3);
  const c0 = Math.cos(rot * D2R), s0 = Math.sin(rot * D2R), lgx = P.gx * c0 + P.gy * s0, lgy = -P.gx * s0 + P.gy * c0;
  const pf = ease((sy - .08) / .22);
  ctx.globalAlpha = bodyA * pf;
  ctx.save(); ctx.translate(side * P.px * P.conv * P.ps + lgx, P.py * sy + lgy * sy);
  drawShape(ctx, P.shape, P.prx * P.ps * sc, P.pry * P.ps * sc * sy, rgbs(...pc)); ctx.restore();
  if (P.cheek > .02) { ctx.globalAlpha = 1; ctx.fillStyle = '#000'; ctx.beginPath(); ctx.ellipse(0, RY * (1.66 - .78 * P.cheek), 1.5 * RX, .66 * RY, side * 4 * D2R, 0, 7); ctx.fill(); }
  ctx.restore();
  const la = Math.max(ease((arc - .5) / .05), bl > .8 ? ease((bl - .8) / .1) : 0);   // olho fechado = traço sólido
  if (la > .02) {
    ctx.save(); ctx.translate(cx, cy); ctx.rotate(rot * D2R); ctx.globalAlpha = la; ctx.strokeStyle = rgbs(...ec); ctx.lineCap = 'round';
    ctx.lineWidth = (arc > .5 ? 14 : 9) * (.4 + .6 * Math.max(arc, 1)); const bd = (arc > .5 ? P.bend : -4) * 1.28, hw = RX - 6;
    ctx.beginPath(); for (let i = 0; i <= 14; i++) { const u = -1 + i / 7; ctx[i ? 'lineTo' : 'moveTo'](u * hw, -.5 * bd + bd * (1 - u * u)); } ctx.stroke(); ctx.restore();
  }
}
function drawFace(ctx, P, bl) {
  ctx.setTransform(2, 0, 0, 2, 0, 0); ctx.globalAlpha = 1; ctx.fillStyle = '#000'; ctx.fillRect(0, 0, 240, 240);
  ctx.save(); ctx.translate(120 + P.odx, 118 + P.ody); ctx.rotate(P.orot * D2R); ctx.scale(P.oz, P.oz); ctx.translate(-120, -118);
  drawEye(ctx, P, -1, bl); drawEye(ctx, P, 1, bl); ctx.restore();
}

/* ---------- simulador ---------- */
class Sim {
  constructor(cv) {
    this.ctx = cv.getContext('2d'); this.mode = 'idle'; this.rest = 'idle'; this.cur = null; this.mid = null; this.last = performance.now();
    this.g = { x: 0, y: 0, sx: 0, sy: 0, tx: 0, ty: 0, t0: 0, d: 1, next: 0 }; this.b = { on: false, t0: 0, c: 80, h: 40, o: 200, next: 1500 };
    this.dome = 0; this.domeS = 0; this.moodNext = 3000; this.rx = null; this.t0 = 0; this.loop = false; this.pose = null; this.onEnd = null; requestAnimationFrame(t => this.frame(t));
  }
  play(r) { this.rx = r; this.t0 = performance.now(); this.mode = 'play'; }
  stop() { this.mode = this.rest; }
  gazeTo(x, y, now) { const g = this.g; g.sx = g.x; g.sy = g.y; g.tx = x; g.ty = y; g.t0 = now; g.d = 80 + 6.5 * Math.hypot(x - g.x, y - g.y); }
  blink(now) { const b = this.b, k = Math.random(); b.on = true; b.t0 = now; [b.c, b.h, b.o] = k < .22 ? [60, 10, 150] : k < .8 ? [90, 50, 230] : [130, 200, 350]; b.next = now + b.c + b.h + b.o + 2300 + Math.random() * 2000; }
  frame(ts) {
    const dt = clamp(ts - this.last, 1, 100); this.last = ts; const g = this.g, b = this.b;
    if (ts >= g.next && this.mode === 'idle') { const r = Math.random(); this.gazeTo(r < .5 ? (Math.random() - .5) * 12 : (Math.random() < .5 ? -1 : 1) * (8 + Math.random() * 4), (Math.random() - .5) * 14, ts); g.next = ts + 700 + Math.random() * 2200; }
    const gp = clamp((ts - g.t0) / g.d, 0, 1), gc = .45 * ease(gp) + .55 * (1 - Math.pow(1 - gp, 3)); g.x = g.sx + (g.tx - g.sx) * gc; g.y = g.sy + (g.ty - g.sy) * gc;
    if (!b.on && ts >= b.next && this.mode !== 'pose') this.blink(ts);
    let bl = 0;
    if (b.on) { const t = ts - b.t0; if (t < b.c) bl = ease(t / b.c); else if (t < b.c + b.h) bl = 1; else if (t < b.c + b.h + b.o) bl = Math.pow(1 - (t - b.c - b.h) / b.o, 3); else b.on = false; }
    const T = faceP(curFace()); let tau = 110;
    if (ts >= this.moodNext) { const q = Math.random(); this.dome = q < .55 ? .2 : 0; this.moodNext = ts + 5000 + Math.random() * 9000; }   // V13: cúpula ~50% do tempo
    this.domeS += (this.dome - this.domeS) * (1 - Math.exp(-dt / 650));
    if (this.mode === 'idle') { T.gx = g.x; T.gy = g.y; T.cutBot += this.domeS; }
    else if (this.mode === 'pose') { if (this.pose) kfApply(T, this.pose); }
    else if (this.mode === 'play') {
      let t = ts - this.t0; const r = this.rx;
      if (t >= r.dur) { if (this.loop) { this.t0 = ts; t = 0; } else { this.mode = this.rest; if (this.onEnd) this.onEnd(); } }
      if (this.mode === 'play') { kfApply(T, sample(r.keys, t)); tau = T.arc > .01 ? 150 : 90; this.ph = t / r.dur; }
    }
    if (!this.cur) { this.cur = { ...T }; this.mid = { ...T }; }
    const kk = 1 - Math.exp(-dt / (tau * .6));
    for (const k in T) { if (k === 'gx' || k === 'gy' || k === 'shape') this.cur[k] = T[k]; else { this.mid[k] += (T[k] - this.mid[k]) * kk; this.cur[k] += (this.mid[k] - this.cur[k]) * kk; } }
    if (this.mode === 'idle') { this.cur.gx += Math.sin(ts * .043) * .2; }
    drawFace(this.ctx, this.cur, bl);
    if (this.onFrame) this.onFrame(this);
    requestAnimationFrame(t => this.frame(t));
  }
}
const sim = new Sim($('#cv'));

/* ---------- utilidades de interface ---------- */
let toastT;
function toast(msg) { const t = $('#toast'); t.textContent = msg; t.classList.add('on'); clearTimeout(toastT); toastT = setTimeout(() => t.classList.remove('on'), 2600); }
function slider(host, obj, key, label, min, max, step, onInput, fmt) {
  const w = document.createElement('label'); w.className = 'rg';
  w.innerHTML = `<span>${label}</span><output></output><input type="range" min="${min}" max="${max}" step="${step}">`;
  const i = $('input', w), o = $('output', w), show = () => { o.textContent = fmt ? fmt(obj[key]) : (+obj[key]).toFixed(step < 1 ? 2 : 0); };
  i.value = obj[key]; show(); i.oninput = () => { obj[key] = +i.value; show(); onInput(); }; host.append(w);
}
function select(host, label, opts, obj, key, onInput) {
  const w = document.createElement('label'); w.className = 'rg';
  w.innerHTML = `<span>${label}</span><select>${opts.map((o, i) => `<option value="${i}">${o}</option>`).join('')}</select>`;
  const s = $('select', w); s.value = obj[key]; s.style.gridColumn = '1/-1'; s.onchange = () => { obj[key] = +s.value; onInput(); }; host.append(w);
}
function el(html, cls) { const d = document.createElement('div'); if (cls) d.className = cls; d.innerHTML = html; return d; }
function hsv2hex(h, s, v) { const f = n => { const k = (n + h / 60) % 6; return v - v * s * Math.max(0, Math.min(k, 4 - k, 1)); }; return rgb2hex(f(5) * 255, f(3) * 255, f(1) * 255); }
function hex2hsv(hex) { const [r, g, b] = hex2(hex).map(v => v / 255), m = Math.max(r, g, b), n = Math.min(r, g, b), d = m - n; let h = 0; if (d) h = m === r ? ((g - b) / d + 6) % 6 : m === g ? (b - r) / d + 2 : (r - g) / d + 4; return [h * 60, m ? d / m : 0, m]; }

/* ---------- aba OLHOS ---------- */
let slot = 'eL', wheel;
const SLOTS = [['eL', 'Olho esquerdo'], ['pL', 'Pupila esquerda'], ['eR', 'Olho direito'], ['pR', 'Pupila direita'], ['gb', 'Fundo do degradê']];
function onFace() { save(); renderChips(); paintSwatches(); }
function renderChips() {
  const h = $('#faceChips'); if (!h) return; h.innerHTML = '';
  S.faces.forEach((f, i) => {
    const b = document.createElement('button'); b.className = 'chip' + (i === S.fi ? ' on' : '');
    b.innerHTML = `<span class="dots"><i class="dot" style="background:${f.eL}"></i><i class="dot" style="background:${f.pL}"></i></span>${f.name}`;
    b.onclick = () => { S.fi = i; save(); renderEyes(); }; h.append(b);
  });
}
function paintSwatches() {
  const f = curFace(); $$('.sw').forEach(b => { const k = b.dataset.k; b.querySelector('i').style.background = f[k]; b.classList.toggle('on', k === slot); b.hidden = (f.link && (k === 'eR' || k === 'pR')) || (k === 'gb' && !f.grad); });
}
function renderEyes() {
  const P = $('#p-eyes'), f = curFace(); P.innerHTML = '<h2>Olhos</h2>';
  P.append(el('<div class="chips" id="faceChips"></div><div class="row"><button class="ghost sm" id="fNew">' + ic('plus') + 'Novo</button><button class="ghost sm" id="fDup">' + ic('copy') + 'Duplicar</button><button class="ghost sm" id="fDel">' + ic('trash') + 'Excluir</button></div><p class="ids">Os olhos salvos viram os rostos 77 a 92 do robô (até 16).</p>'));
  const c1 = el('<label class="rg"><span>Nome</span><input type="text" id="fName" maxlength="24"></label>', 'card'); P.append(c1);
  $('#fName').value = f.name; $('#fName').oninput = e => { f.name = e.target.value; onFace(); };
  P.append(el('<h3>Cores</h3>'));
  const col = el('', 'card'); col.innerHTML = '<div class="swatches">' + SLOTS.map(([k, n]) => `<button class="sw" data-k="${k}"><i></i>${n}</button>`).join('') + '</div><div class="wheelBox"><canvas id="wheel" width="400" height="400"></canvas><div class="wheelSide"><label class="rg"><span>Brilho</span><output id="vOut"></output><input id="vIn" type="range" min="0" max="1" step="0.01"></label><label class="rg"><span>Código da cor</span><input type="text" id="hexIn" maxlength="7"></label></div></div>';
  P.append(col);
  const tg = el('<label class="tog"><input type="checkbox" id="tLink"> Os dois olhos com a mesma cor</label><label class="tog"><input type="checkbox" id="tGrad"> Degradê de cima para baixo</label>');
  col.append(tg); $('#tLink').checked = f.link; $('#tGrad').checked = f.grad;
  $('#tLink').onchange = e => { f.link = e.target.checked; if (f.link && (slot === 'eR' || slot === 'pR')) slot = 'eL'; onFace(); setWheel(); };
  $('#tGrad').onchange = e => { f.grad = e.target.checked; if (!f.grad && slot === 'gb') slot = 'eL'; onFace(); setWheel(); };
  $$('.sw', col).forEach(b => b.onclick = () => { slot = b.dataset.k; paintSwatches(); setWheel(); });
  P.append(el('<h3>Cores prontas</h3>'));
  const pr = el('', 'chips'); PRESETS.forEach(([n, e, p]) => { const b = document.createElement('button'); b.className = 'chip'; b.innerHTML = `<span class="dots"><i class="dot" style="background:${e}"></i><i class="dot" style="background:${p}"></i></span>${n}`; b.onclick = () => { Object.assign(f, { eL: e, pL: p, eR: e, pR: p }); onFace(); setWheel(); }; pr.append(b); });
  P.append(pr);
  P.append(el('<h3>Formato</h3>'));
  const sh = el('', 'card grid2'); P.append(sh);
  slider(sh, f, 'rx', 'Largura do olho', .5, 1.5, .01, onFace); slider(sh, f, 'ry', 'Altura do olho', .5, 1.5, .01, onFace);
  slider(sh, f, 'ps', 'Tamanho da pupila', .3, 1.8, .01, onFace); slider(sh, f, 'cutBot', 'Base reta (cúpula)', 0, .5, .01, onFace);
  slider(sh, f, 'tilt', 'Inclinação dos olhos', -20, 20, 1, onFace); slider(sh, f, 'gap', 'Distância entre os olhos', -20, 20, 1, onFace);
  select(sh, 'Formato da pupila', SHAPES, f, 'shape', onFace);
  P.append(el('<h3>Testar no robô</h3><div class="row"><button class="solid" id="fTest">' + ic('send') + 'Enviar e mostrar este olho</button></div>'));
  $('#fNew').onclick = () => { if (S.faces.length >= 16) return toast('Limite de 16 olhos'); S.faces.push(newFace('Olho ' + (S.faces.length + 1))); S.fi = S.faces.length - 1; save(); renderEyes(); };
  $('#fDup').onclick = () => { if (S.faces.length >= 16) return toast('Limite de 16 olhos'); S.faces.push({ ...f, name: f.name + ' cópia' }); S.fi = S.faces.length - 1; save(); renderEyes(); };
  $('#fDel').onclick = () => { if (S.faces.length < 2) return toast('Mantenha pelo menos um olho'); S.faces.splice(S.fi, 1); S.fi = 0; save(); renderEyes(); };
  $('#fTest').onclick = async () => { if (!rxChar) return toast('Conecte o Bluetooth primeiro'); try { await ble.sendFace(S.fi); await ble.write([0x0A, 77 + S.fi, 1]); toast('Olho enviado'); } catch (e) { toast('Falha ao enviar: ' + e.message); } };
  wheel = wheelInit($('#wheel'), hex => { f[slot] = hex; if (f.link && slot === 'eL') f.eR = hex; if (f.link && slot === 'pL') f.pR = hex; $('#hexIn').value = hex; onFace(); });
  $('#vIn').oninput = e => wheel.setV(+e.target.value);
  $('#hexIn').oninput = e => { if (/^#[0-9a-f]{6}$/i.test(e.target.value)) { f[slot] = e.target.value.toLowerCase(); if (f.link && slot === 'eL') f.eR = f[slot]; if (f.link && slot === 'pL') f.pR = f[slot]; setWheel(); onFace(); } };
  renderChips(); paintSwatches(); setWheel();
}
function setWheel() { const h = curFace()[slot]; wheel.set(h); $('#hexIn').value = h; $('#vIn').value = hex2hsv(h)[2]; $('#vOut').textContent = Math.round(hex2hsv(h)[2] * 100) + '%'; }
function wheelInit(cv, onPick) {
  const c = cv.getContext('2d'), N = cv.width, r = N / 2; let h = 0, s = 0, v = 1;
  function paint() {
    c.clearRect(0, 0, N, N); const g = c.createConicGradient(-Math.PI / 2, r, r);
    for (let i = 0; i <= 360; i += 30) g.addColorStop(i / 360, `hsl(${i} 100% 50%)`);
    c.fillStyle = g; c.beginPath(); c.arc(r, r, r - 3, 0, 7); c.fill();
    const rg = c.createRadialGradient(r, r, 0, r, r, r - 3); rg.addColorStop(0, '#fff'); rg.addColorStop(1, 'rgba(255,255,255,0)'); c.fillStyle = rg; c.fill();
    c.fillStyle = `rgba(0,0,0,${1 - v})`; c.fill();
    const a = h * D2R - Math.PI / 2, d = s * (r - 3); c.beginPath(); c.arc(r + Math.cos(a) * d, r + Math.sin(a) * d, 14, 0, 7); c.lineWidth = 5; c.strokeStyle = '#fff'; c.stroke(); c.lineWidth = 2; c.strokeStyle = '#000'; c.stroke();
  }
  const emit = () => { paint(); onPick(hsv2hex(h, s, v)); };
  const mv = e => { const b = cv.getBoundingClientRect(), x = (e.clientX - b.left) / b.width * N - r, y = (e.clientY - b.top) / b.height * N - r; s = Math.min(1, Math.hypot(x, y) / (r - 3)); h = ((Math.atan2(y, x) + Math.PI / 2) / D2R + 360) % 360; emit(); };
  cv.onpointerdown = e => { cv.setPointerCapture(e.pointerId); mv(e); }; cv.onpointermove = e => { if (e.buttons) mv(e); };
  return { set(hex) { [h, s, v] = hex2hsv(hex); paint(); }, setV(x) { v = x; $('#vOut').textContent = Math.round(x * 100) + '%'; emit(); } };
}

/* ---------- aba REAÇÕES ---------- */
const KSCHEMA = [
  ['Olhar', [['gx', 'Olhar para os lados', -10, 10, 1], ['gy', 'Olhar para cima / baixo', -10, 10, 1]]],
  ['Pálpebras e rosto', [['cT', 'Pálpebra de cima', -.2, .6, .01], ['cB', 'Base do olho', -.2, .5, .01], ['lid', 'Inclinação da pálpebra', -30, 30, 1], ['sq', 'Meio fechado', 0, .95, .01], ['cheek', 'Bochecha (sorriso)', 0, 1, .01]]],
  ['Olho e pupila', [['rot', 'Giro dos olhos', -25, 25, 1], ['sc', 'Tamanho dos olhos', .5, 1.6, .01], ['ps', 'Tamanho da pupila', .2, 2.4, .01]]],
  ['Cabeça', [['odx', 'Deslocar para os lados', -30, 30, 1], ['ody', 'Deslocar para cima / baixo', -30, 30, 1], ['orot', 'Inclinar a cabeça', -30, 30, 1], ['oz', 'Aproximar / afastar', -.3, .3, .01]]]
];
const fmtS = v => (v / 1000).toFixed(2) + 's';
function poseKey() { if ($('#p-react').hidden) return; sim.rest = 'pose'; sim.pose = curKey(); if (sim.mode !== 'play') sim.mode = 'pose'; }
function renderReacts() {
  const P = $('#p-react'), r = curReact(); P.innerHTML = '<h2>Reações</h2>';
  const chips = el('', 'chips'); S.reacts.forEach((x, i) => { const b = document.createElement('button'); b.className = 'chip' + (i === S.ri ? ' on' : ''); b.textContent = x.name; b.onclick = () => { S.ri = i; S.ki = 0; save(); renderReacts(); }; chips.append(b); });
  P.append(chips);
  P.append(el('<div class="row"><button class="ghost sm" id="rNew">' + ic('plus') + 'Nova</button><button class="ghost sm" id="rDup">' + ic('copy') + 'Duplicar</button><button class="ghost sm" id="rDel">' + ic('trash') + 'Excluir</button></div><p class="ids">As reações salvas viram os ids 130 a 137 no robô (até 8).</p>'));
  P.append(el('<label class="rg"><span>Começar de um modelo</span><select id="rTpl"><option value="">Escolha…</option>' + TPL.map((t, i) => `<option value="${i}">${t[0]}</option>`).join('') + '</select></label>'));
  const c = el('', 'card grid2'); P.append(c);
  c.append(el('<label class="rg"><span>Nome</span><input type="text" id="rName" maxlength="24"></label>')); $('#rName').value = r.name; $('#rName').oninput = e => { r.name = e.target.value; save(); $$('#p-react .chip')[S.ri].textContent = r.name; };
  slider(c, r, 'dur', 'Duração', 500, 8000, 100, () => { r.keys.forEach(k => k.t = Math.min(k.t, r.dur)); save(); renderTrack(); }, fmtS);
  slider(c, r, 'w', 'Chance no sorteio automático (0 = nunca)', 0, 10, 1, save);
  P.append(el('<h3>Linha do tempo (quadros-chave)</h3><div class="track" id="track"><em id="ph"></em></div><div class="keys" id="keys"></div><div class="row"><button class="ghost sm" id="kNew">' + ic('plus') + 'Novo quadro</button><button class="ghost sm" id="kDup">' + ic('copy') + 'Duplicar</button><button class="ghost sm" id="kDel">' + ic('trash') + 'Excluir</button></div>'));
  const ed = el('', 'card'); ed.id = 'kEd'; P.append(ed);
  P.append(el('<div class="row" style="margin-top:6px"><button class="solid" id="rPlay">' + ic('play') + 'Reproduzir</button><button class="ghost" id="rLoop">' + ic('loop') + 'Repetir</button><button class="ghost" id="rSend">' + ic('send') + 'Enviar ao robô</button></div>'));
  $('#rNew').onclick = () => { if (S.reacts.length >= 8) return toast('Limite de 8 reações'); S.reacts.push(mkReact(S.reacts.length)); S.ri = S.reacts.length - 1; S.ki = 0; save(); renderReacts(); };
  $('#rDup').onclick = () => { if (S.reacts.length >= 8) return toast('Limite de 8 reações'); S.reacts.push(JSON.parse(JSON.stringify({ ...r, name: r.name + ' cópia' }))); S.ri = S.reacts.length - 1; save(); renderReacts(); };
  $('#rDel').onclick = () => { if (S.reacts.length < 2) return toast('Mantenha pelo menos uma reação'); S.reacts.splice(S.ri, 1); S.ri = 0; S.ki = 0; save(); renderReacts(); };
  $('#rTpl').onchange = e => { if (e.target.value === '') return; const n = mkReact(+e.target.value); r.dur = n.dur; r.keys = n.keys; r.name = n.name; S.ki = 0; save(); renderReacts(); };
  $('#kNew').onclick = () => { if (r.keys.length >= 12) return toast('Limite de 12 quadros'); const k = { ...curKey() }, n = r.keys.slice().sort((a, b) => a.t - b.t), i = n.indexOf(curKey()); k.t = Math.round(i + 1 < n.length ? (n[i].t + n[i + 1].t) / 2 : Math.min(r.dur, n[i].t + 400)); r.keys.push(k); S.ki = r.keys.length - 1; save(); renderKeys(); };
  $('#kDup').onclick = () => $('#kNew').onclick();
  $('#kDel').onclick = () => { if (r.keys.length < 3) return toast('Mantenha pelo menos 2 quadros'); r.keys.splice(S.ki, 1); S.ki = 0; r.keys.sort((a, b) => a.t - b.t); r.keys[0].t = 0; save(); renderKeys(); };
  $('#rPlay').onclick = () => { if (sim.mode === 'play') { sim.stop(); setPlayBtn(false); } else { sim.play(r); setPlayBtn(true); } };
  $('#rLoop').onclick = e => { sim.loop = !sim.loop; e.currentTarget.classList.toggle('solid', sim.loop); };
  $('#rSend').onclick = async () => { if (!rxChar) return toast('Conecte o Bluetooth primeiro'); try { await ble.sendReact(S.ri); await ble.write([0x01, 130 + S.ri]); toast('Reação enviada e disparada'); } catch (e) { toast('Falha ao enviar: ' + e.message); } };
  sim.onEnd = () => setPlayBtn(false);
  renderKeys();
}
function setPlayBtn(on) { const b = $('#rPlay'); if (b) b.innerHTML = (on ? ic('stop') + 'Parar' : ic('play') + 'Reproduzir'); }
function renderTrack() {
  const r = curReact(), t = $('#track'); if (!t) return; $$('b', t).forEach(b => b.remove());
  r.keys.forEach((k, i) => { const b = document.createElement('b'); b.style.left = (k.t / r.dur * 100) + '%'; if (i === S.ki) b.className = 'on'; t.append(b); });
}
function renderKeys() {
  const r = curReact(); r.keys.sort((a, b) => a.t - b.t); if (S.ki >= r.keys.length) S.ki = 0;
  const h = $('#keys'); h.innerHTML = '';
  r.keys.forEach((k, i) => { const b = document.createElement('button'); b.className = 'key' + (i === S.ki ? ' on' : ''); b.textContent = (k.t / 1000).toFixed(2) + 's'; b.onclick = () => { S.ki = i; renderKeys(); }; h.append(b); });
  renderTrack();
  const ed = $('#kEd'), k = curKey(); ed.innerHTML = '';
  const upd = () => { save(); poseKey(); };
  const tw = el('', 'grid2');
  if (S.ki === 0 && k.t === 0) tw.append(el('<p class="ids">Quadro inicial (0,00s): o ponto de partida da reação.</p>'));
  else slider(tw, k, 't', 'Momento deste quadro', 0, r.dur, 10, () => { save(); renderTrack(); poseKey(); }, fmtS);
  ed.append(tw);
  KSCHEMA.forEach(([title, items]) => { ed.append(el(`<h3>${title}</h3>`)); const g = el('', 'grid2'); items.forEach(([key, label, mn, mx, st]) => slider(g, k, key, label, mn, mx, st, upd)); ed.append(g); });
  ed.append(el('<h3>Aparência</h3>')); const g = el('', 'grid2'); ed.append(g);
  select(g, 'Olho fechado', ['Aberto', 'Fechado ^ ^', 'Fechado u u'], k, 'arc', upd);
  select(g, 'Formato da pupila', ['Do olho', ...SHAPES.slice(1)], k, 'shape', upd);
  slider(g, k, 'tk', 'Quantidade de cor passageira', 0, 1, .01, upd);
  const cw = el('<label class="rg"><span>Cor passageira</span><input type="color" id="kCol" style="width:100%;height:36px;border:0;background:none"></label>'); g.append(cw);
  $('#kCol').value = k.tc; $('#kCol').oninput = e => { k.tc = e.target.value; upd(); };
  poseKey();
}
sim.onFrame = s => { const ph = $('#ph'); if (!ph) return; if (s.mode === 'play') { ph.style.display = 'block'; ph.style.left = (s.ph * 100) + '%'; } else ph.style.display = 'none'; };

/* ---------- Bluetooth (Web Bluetooth) ---------- */
const SVC = '7a1c0001-5b1a-4c3e-9d7a-1f0e5a5e0001', RXU = '7a1c0002-5b1a-4c3e-9d7a-1f0e5a5e0001';
let btDev = null, rxChar = null;
const logEl = () => $('#log');
const log = m => { const l = logEl(); if (l) { l.textContent += m + '\n'; l.scrollTop = l.scrollHeight; } };
const sleep = ms => new Promise(r => setTimeout(r, ms));
const ble = {
  async write(a) { const u = a instanceof Uint8Array ? a : new Uint8Array(a); if (rxChar.writeValueWithResponse) await rxChar.writeValueWithResponse(u); else await rxChar.writeValue(u); await sleep(30); },
  async sendFace(i) { for (const p of StarboyExport.bleFace(i, S.faces[i])) await this.write(p); },
  async sendReact(i) { for (const p of StarboyExport.bleReact(i, S.reacts[i])) await this.write(p); },
  async sendAll() {
    const nf = Math.min(S.faces.length, 16), nr = Math.min(S.reacts.length, 8);
    for (let i = 0; i < nf; i++) { await this.sendFace(i); log('olho ' + (77 + i) + ' enviado'); }
    for (let i = 0; i < nr; i++) { await this.sendReact(i); log('reação ' + (130 + i) + ' enviada'); }
  }
};
function btUi(on) {
  $('#btTop').classList.toggle('live', on); $('#btTopTxt').textContent = on ? 'Conectado' : 'Conectar';
  $$('[data-needbt]').forEach(b => b.disabled = !on); const s = $('#btState'); if (s) s.textContent = on ? 'Conectado ao Starboy' : 'Desconectado';
}
async function btToggle() {
  if (rxChar) { try { btDev.gatt.disconnect(); } catch (e) { } return; }
  if (!navigator.bluetooth) return toast('Use o Google Chrome (Android ou computador) com HTTPS');
  try {
    btDev = await navigator.bluetooth.requestDevice({ filters: [{ name: 'Starboy' }], optionalServices: [SVC] });
    btDev.addEventListener('gattserverdisconnected', () => { rxChar = null; btUi(false); log('desconectado'); });
    const srv = await btDev.gatt.connect(), svc = await srv.getPrimaryService(SVC); rxChar = await svc.getCharacteristic(RXU);
    btUi(true); log('conectado'); toast('Starboy conectado');
  } catch (e) { toast(e.name === 'NotFoundError' ? 'Nenhum aparelho escolhido' : 'Não conectou: ' + e.message); log('erro: ' + e.message); }
}

/* ---------- aba EXPORTAR ---------- */
function dl(name, text, type) { const a = document.createElement('a'); a.href = URL.createObjectURL(new Blob([text], { type })); a.download = name; document.body.append(a); a.click(); a.remove(); setTimeout(() => URL.revokeObjectURL(a.href), 4000); }
function renderExport() {
  const P = $('#p-export'); P.innerHTML = '<h2>Exportar e conectar</h2>';
  P.append(el('<h3>Arquivo para o ESP32</h3><div class="card"><p style="margin-top:0">Gera o <b>.ino</b> da V12 já com os seus olhos e reações. Abra na Arduino IDE e grave na placa.</p><div class="btnrow"><button class="solid" id="xIno">' + ic('down') + 'Baixar .ino</button><button class="ghost" id="xJson">' + ic('down') + 'Salvar projeto (.json)</button><button class="ghost" id="xImp">' + ic('upload') + 'Abrir projeto</button></div><input type="file" id="xFile" accept=".json" hidden></div>'));
  P.append(el('<h3>Bluetooth</h3><div class="card"><p style="margin-top:0" id="btState">Desconectado</p><div class="btnrow"><button class="solid" id="xConn">' + ic('bt') + 'Conectar / desconectar</button><button class="ghost" id="xAll" data-needbt>' + ic('send') + 'Enviar tudo ao robô</button></div><div class="row" style="margin-top:12px"><button class="ghost sm" id="xBlink" data-needbt>Piscar</button><button class="ghost sm" id="xChg" data-needbt>Simular carregando</button><button class="ghost sm" id="xRand" data-needbt>Rosto aleatório</button></div></div><div class="log" id="log"></div>'));
  P.append(el('<p class="ids">O envio pelo Bluetooth grava na memória temporária do robô (some ao desligar). Para deixar permanente, baixe o .ino e grave na placa. O robô precisa estar com o .ino gerado por este site.</p>'));
  $('#xIno').onclick = async () => {
    try { const t = await (await fetch('starboy_v13_ble.ino')).text(); dl('starboy_v12_studio.ino', StarboyExport.patch(t, S), 'text/plain'); toast('.ino gerado'); }
    catch (e) { toast('Não deu para gerar: ' + e.message); log('erro: ' + e.message); }
  };
  $('#xJson').onclick = () => dl('starlyn-projeto.json', JSON.stringify(S, null, 1), 'application/json');
  $('#xImp').onclick = () => $('#xFile').click();
  $('#xFile').onchange = async e => { try { const j = JSON.parse(await e.target.files[0].text()); if (!j.faces || !j.reacts) throw new Error('arquivo inválido'); S = { fi: 0, ri: 0, ki: 0, ...j }; save(); renderAll(); toast('Projeto aberto'); } catch (er) { toast('Erro: ' + er.message); } };
  $('#xConn').onclick = btToggle;
  $('#xAll').onclick = async () => { try { await ble.sendAll(); toast('Tudo enviado'); } catch (e) { toast('Falha: ' + e.message); log('erro: ' + e.message); } };
  $('#xBlink').onclick = () => ble.write([0x09]);
  $('#xChg').onclick = () => ble.write([0x0B, 1]);
  $('#xRand').onclick = () => ble.write([0x0A, Math.floor(Math.random() * 77), 0]);
  btUi(!!rxChar);
}

/* ---------- abas ---------- */
function renderAll() { renderEyes(); renderReacts(); renderExport(); }
$('#btTop').onclick = btToggle;
$$('#tabs button').forEach(b => b.onclick = () => {
  const t = b.dataset.tab; $$('#tabs button').forEach(x => x.classList.toggle('on', x === b));
  ['eyes', 'react', 'export'].forEach(n => $('#p-' + n).hidden = n !== t);
  if (t === 'react') poseKey(); else { sim.rest = 'idle'; if (sim.mode !== 'play') sim.mode = 'idle'; else sim.stop(); }
  window.scrollTo({ top: 0 });
});
$('#bBlink').onclick = () => sim.blink(performance.now());
$('#bGaze').onclick = () => { const n = performance.now(); sim.gazeTo((Math.random() < .5 ? -1 : 1) * 12, (Math.random() - .5) * 14, n); sim.g.next = n + 2500; };
renderAll();
