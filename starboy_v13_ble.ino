/*
 * STARBOY v13 + BLUETOOTH  (= v12 com o olho CHEIO como padrao)
 *   - Padrao: oval completo com pupila oval (como o rosto "parado" de referencia). A CUPULA (base reta) virou um humor
 *     que aparece ~48% do tempo (olho cheio ~40%, outros humores o resto). Para mudar a proporcao veja pickMood().
 *   - Piscada do olho cheio achata no proprio lugar; a da cupula continua ancorada na base.
 */
/*
 * STARBOY v12 + BLUETOOTH  (= v11 com o CORACAO DAS ANIMACOES refeito a partir do video e das cartelas de quadros-chave)
 * Cores, rostos (76 + 1 novo), reacoes (1..129), Bluetooth, microfone, logo e abertura: IGUAIS ao v11. O que mudou:
 *   - OLHO NOVO EM "CUPULA": topo redondo, base reta e inclinada (ponta mais baixa no canto de dentro), pupila REDONDA grande
 *     embaixo/dentro - igual ao Starboy do video. Vale para TODOS os rostos (so a forma mudou; as cores continuam as mesmas).
 *   - PISCADA NOVA (como no video): a palpebra de cima DESCE ate a base reta (a base nao se mexe), a pupila achata junto e o
 *     olho vira um traco fino e curvado "arco" (nao e mais um "u" grosso). Abre devagar, freando.
 *   - VIRADA DE CABECA (falso 3D): ao olhar pro lado o rosto inteiro desliza e o olho mais perto cresce enquanto o mais longe
 *     encolhe (quadros 195-221 do video). Variavel: HEAD_TURN (0 = desliga).
 *   - HUMORES NOVOS do olhar: "atento" (olho alto e esticado) e "largo" (olho baixo e aberto) - quadros 221 e 281 do video.
 *   - ROSTO NOVO 76 "Starboy Original": laranja + pupila lilas-clara (as cores do video). O rosto principal continua o ROSA (0)
 *     (BOOT_FINAL_FACE; -1 = sorteia como na v11).
 *   - ANIMACAO DE CARREGAR / CONECTAR (id 129, R-48): olho verde em cupula com pupila laranja -> pisca em linha -> viram ovais
 *     verdes inclinados com um RAIO laranja no lugar da pupila, balancando -> volta pra cupula -> verde -> ambar -> laranja.
 *       * dispara sozinha quando o celular CONECTA no Bluetooth (BT_CHARGE_ANIM = 1);
 *       * se voce ligar um pino de "carregando" (CHARGE_PIN), o Starboy fica VERDE enquanto carrega e repete o raio a cada
 *         CHARGE_REPEAT_MS; ao tirar da tomada ele volta ao laranja passando por ambar (quadros 582-591 do video).
 *   - O comando Bluetooth 0x01 agora aceita 1..129.
 */
/*
 * STARBOY v11 + BLUETOOTH  (= v10.2 com VISUAL APRIMORADO e ANIMACAO MAIS FLUIDA)
 * Cores, rostos (76), reacoes (1..125), Bluetooth, microfone, logo e abertura: IGUAIS ao v10.2. O que mudou:
 *   - PISCADA NOVA: o olho achata, gira ate ficar na horizontal e, no fim, vira um arco 'u' solido de pontas redondas
 *     (antes virava um 'V' fino e feio). Vale para a piscada normal, dupla, sonolenta, troca de rosto e abertura.
 *   - BOCHECHA CURVA ("montanhinha"): nos olhos sorrindo (sorrisao, sorriso de canto, sim, emocionado) a bochecha sobe
 *     em ARCO por baixo de cada olho (antes era um corte reto). Campo novo no Style: cheek (0..1).
 *   - OLHAR PRA CIMA mais realista: ao olhar reto pra cima a pupila sobe mais no olho (nas diagonais fica como antes).
 *   - A palpebra de cima acompanha o olhar: olhando pra baixo ela desce um tiquinho.
 *   - ANIMACAO MAIS FLUIDA: a troca de expressao agora e suavizada em 2 estagios (comeca devagar, acelera e freia, sem
 *     "tranco" no inicio) e a pupila tem uma pulsacao bem sutil (como olho de verdade).
 *   - 3 REACOES NOVAS (ids 126..128): R-45 Feliz de bochecha, R-46 Sorrisao, R-47 Olhos brilhantes felizes.
 *     O comando Bluetooth 0x01 agora aceita 1..128. Entram no sorteio automatico.
 */
/*
 * STARBOY v10.2 = v10.1 com: bolinha rebatendo nas paredes por ~6 s (cresce ate encher a tela) e abertura SEM PAUSAS
 *   (manchas -> diagonal -> roleta pra direita direto, uma na outra).
 *
 * STARBOY v10.1 + BLUETOOTH  (= v10 com a ABERTURA NOVA: bolinha quicando, manchas cinza, 2 roletas, brilhos novos)
 *   - Os OLHOS, as reacoes, o piscar, o Bluetooth e o loop sao IDENTICOS ao v10. So mudou o que acontece ao ligar:
 *       1) tela branca -> bolinha preta quica de verdade (gravidade realista, amassa no impacto, cresce a cada quique)
 *          e infla ate preencher a tela;
 *       2) aparecem MANCHAS CINZA no escuro, elas se juntam, a massa se PARTE EM DOIS e vira os dois olhos (ganham cor);
 *       3) ANIMACAO A: os olhos olham pra baixo na diagonal e os rostos SOBEM rapido (na diagonal), trocando varias
 *          vezes, e param com um tranquinho;
 *       4) ANIMACAO B: ROLETA rapidissima pra DIREITA; desacelera e o ultimo rosto fica.
 *   - BRILHO novo: o simbolo de estrela (4 pontas) agora tem halo, pontas finas, diagonais e miolo claro. Vale pra
 *     abertura e tambem para as reacoes que usam brilhinhos (se_spark).
 *   - Ajustes: BOOT_TIME_SCALE (velocidade geral da abertura) e SLOT_DIAG_DEG (inclinacao da animacao A; 0 = reto pra cima).
 *   - Correcao: se_G agora tem espaco para todos os olhos do quadro (SE_MAXEYES) - antes eram 4.
 */
/*
 * STARBOY v10 + BLUETOOTH  (= v9.3 com ANIMACOES FLUIDAS: piscar, olhar, troca de rosto e abertura - ver o bloco V10 acima)
 * ---- (historico) STARBOY v9.3 + BLUETOOTH  (= v9.2 + 4 OLHOS NOVOS DA POLLY: P-01..P-04)
 *   - Rostos 72..75 = P-01..P-04 (homenagem a Pollyana: amarelo + rosa). Total: 76 rostos. O comando Bluetooth 0x0A agora
 *     aceita rostos 0..75. Entram na roleta e na troca automatica. O resto e IDENTICO ao v9.2.
 *       72 P-01 Polly Sol            amarelo + pupila rosa
 *       73 P-02 Sakura da Polly      rosa + FLOR amarela na pupila (miolo rosa)
 *       74 P-03 Polly | Ana (hetero) olho esquerdo amarelo/pupila rosa | olho direito rosa/pupila amarela
 *       75 P-04 Pollyana Radiante    degrade amarelo -> rosa (cima -> baixo) + pupila vinho
 *   - Novidade do motor de desenho: pupila em formato de FLOR (se_flower), usada pelo P-02.
 *
 * ---- (historico) STARBOY v9.2 + BLUETOOTH  (= v9.1 + 24 ROSTOS DE COR NOVOS + 12 ROSTOS COM DEGRADE)
 *   - Rostos 36..59 = F-36..F-59 (cores novas, varios com heterocromia). Rostos 60..71 = D-01..D-12 (olhos com DEGRADE
 *     de cima para baixo: Por do sol, Oceano fundo, Aurora, Algodao doce, Fogo, Floresta, Galaxia, Vampiro, Nuvem, Gelo,
 *     Neon, Ouro). Total: 72 rostos. O comando Bluetooth 0x0A agora aceita rostos 0..71. Entram na roleta e na troca automatica.
 *
 * ---- (historico) STARBOY v9.1 + BLUETOOTH  (= v9 + OLHOS NOVOS + ENFEITES NOVOS + 24 REACOES NOVAS + 3 ESTADOS DO BLUETOOTH)
 *
 * NOVIDADES DO v9.1 (o resto e IDENTICO ao v9: logo, roleta, 36 rostos, microfone, Bluetooth, loop):
 *   - MOTOR DE OLHOS NOVO (addEyes): degrade (cima->baixo), escurecer (dim), tamanho de cada olho (zoom), olho marejado,
 *     brilho na pupila, olho congelado (gelo + rachaduras), galaxia, loading (anel de pontinhos), pupila ESPIRAL e MIRA.
 *   - ENFEITES NOVOS (addDeco): veia, vapor, interrogacao, notas musicais, raios, fogo, neve, chuva, nuvem, lua, sol,
 *     cantoneiras de camera, aviso, linhas de glitch, sonar, radar, estrelinhas girando, confete, codigo (hacker),
 *     equalizador, simbolo do Bluetooth e bateria. Quando um "olho" de enfeites enche, abre outro automaticamente.
 *   - REACOES: de 98 para 125. Novas = ids 99..125:
 *       99 R-21 Raiva com veia        108 R-30 Dia de chuva          117 R-39 Hipnose espiral
 *      100 R-22 Ha?                   109 R-31 Boa noite             118 R-40 Tontura
 *      101 R-23 Ouvindo musica        110 R-32 Bom dia               119 R-41 Gelatina
 *      102 R-24 Emocionado            111 R-33 Alvo travado          120 R-42 Zoom
 *      103 R-25 Plano maligno         112 R-34 Carregando            121 R-43 Galaxia nos olhos
 *      104 R-26 Boom!                 113 R-35 Modo hacker           122 R-44 Parabens!
 *      105 R-27 Pegando fogo          114 R-36 Erro de sistema       123 S-01 Bluetooth conectou
 *      106 R-28 Congelando            115 R-37 Foto!                 124 S-02 Bluetooth caiu
 *      107 R-29 Eletrizado            116 R-38 Radar                 125 S-03 Procurando Bluetooth
 *   - As R-21..R-44 entram no sorteio automatico. Os estados S-01..S-03 NAO sao sorteados: o S-01 dispara sozinho quando
 *     o celular conecta e o S-02 quando desconecta (BT_REACTIONS = 0 desliga isso). Todos tambem podem ser
 *     disparados pelo site: comando 0x01 agora aceita 1..125.
 *   - Foto! (R-37) faz um flash branco na tela toda (gFlash).
 *
 * ---- (historico) STARBOY v9 + BLUETOOTH  (= v8.1 + 12 ROSTOS NOVOS + 20 REACOES NOVAS)
 *
 * NOVIDADES DO v9 (o resto e IDENTICO ao v8.1: logo da Starlyn Infinite, microfone, Bluetooth, loop, tudo):
 *   - ROSTOS: de 24 para 36. Os novos (rostos 24..35) so mudam as cores (mesma forma do rosa):
 *       24 Sakura | 25 Galaxia | 26 Fogo & Gelo | 27 Matrix | 28 Chiclete | 29 Ouro branco | 30 Oceano
 *       31 Por do sol | 32 Menta & rosa | 33 Lava | 34 Alienigena | 35 Sakura | Oceano (heterocromia)
 *   - REACOES: de 78 para 98. As novas sao os ids 79..98 (R-01..R-20 das folhas de previa):
 *       79 R-01 Olhos de estrela      89 R-11 Reiniciando
 *       80 R-02 Olhos de coracao      90 R-12 Escondendo e espiando
 *       81 R-03 Ideia!                91 R-13 Determinado
 *       82 R-04 Escaneando            92 R-14 Deslumbrado (uau)
 *       83 R-05 Maquinando            93 R-15 Olhar de gato
 *       84 R-06 Dor de gelo           94 R-16 Dormindo Zzz
 *       85 R-07 Com calor             95 R-17 Rindo ate chorar
 *       86 R-08 Enjoado               96 R-18 Modo festa (cores)
 *       87 R-09 Piscadela charmosa    97 R-19 Olhos de cifrao $
 *       88 R-10 Soluco                98 R-20 Desmaiou (X X)
 *   - Coisas novas que o motor de desenho aprendeu: pupila em formato de ESTRELA, CORACAO, CIFRAO e FENDA (gato),
 *     olhos em X, e enfeites ao redor do rosto (brilhinhos, coracoes, lagrimas, Zzz, gota de suor, raios da ideia,
 *     linha de varredura, reticencias e exclamacao). Tudo desenhado por codigo, sem imagem.
 *   - Bluetooth: o comando 0x01 agora aceita reacoes 1..98 e o 0x0A aceita rostos 0..35.
 *   - As reacoes novas entram no sorteio automatico junto com as antigas.
 *
 * ---- (historico) STARBOY v8.1 + BLUETOOTH  (= v8 com a NOVA LOGO: STARLYN INFINITE)
 *
 * NOVIDADE DO v8 (o resto e IDENTICO ao v7.1: rostos, reacoes, microfone, Bluetooth, tudo):
 *   - Ao ligar, a PRIMEIRA coisa e a NOVA logomarca STARLYN INFINITE (olhos rosa + nome) em fundo branco:
 *     fade-in (~1,3 s) -> fica parada 5 s -> fade-out (~1,3 s) -> so entao comeca a bolinha quicando e a roleta.
 *   - A logo e desenhada 100% POR CODIGO (ovais + contornos vetoriais das letras). Nao precisa subir imagem
 *     nenhuma e nao pesa: ~4 KB de pontos no codigo; a memoria temporaria (57,6 KB) e liberada depois da abertura.
 *   - Para ajustar: LOGO_INTRO (liga/desliga), LOGO_HOLD_MS (tempo parada), LOGO_FADE_IN_MS / LOGO_FADE_OUT_MS,
 *     LOGO_SCALE (tamanho; se a borda redonda do display cortar o texto, diminua um pouco, ex.: 0.170).
 *
 * ---- (historico) STARBOY v7.1 + BLUETOOTH - so OLHOS, um unico modelo (o rosto ROSA do v5) em varias combinacoes de cor
 * ESP32-C3 + display redondo GC9A01 (1.28", 240x240) + microfone MAX4466
 * Nao precisa de NENHUMA biblioteca extra: so SPI.h (ja vem com o ESP32). Tudo e DESENHADO pelo codigo.
 * A ESTRUTURA (pinos, driver do display, Bluetooth, microfone, loop) e a mesma do v5/v6.
 *
 * NOVIDADES DO v7.1 (o resto e IDENTICO ao v7):
 *   - O olhar NORMAL nao e mais triste: ao ligar ele vem com o olho bem aberto (sem palpebra caida).
 *     Tristeza agora e so uma emocao (reacao 'Triste', 'Chorando'...) e um humor raro e passageiro.
 *   - Os humores aleatorios (meio fechado, caido, cansado...) ficam raros: ~65% do tempo ele fica no olhar normal aberto.
 *
 * NOVIDADES DO v7 (ja incluidas):
 *   - OLHO FECHADO (^ ^ , u u): agora e um traco SOLIDO, sem brilho em volta e sem miolo claro. Tem exatamente a cor
 *     principal que o olho tinha naquele momento, a mesma largura do olho normal, pontas redondas.
 *   - Reacoes felizes (risada, contente, dancando, cantarolando): sem balancar de lado. Fica de olho fechado
 *     fazendo um "sim" leve e devagar com a cabeca (pra cima e pra baixo).
 *   - Transicao de fechar/abrir mais detalhada: o olho primeiro ACHATA ate virar uma linha reta, depois a linha CURVA
 *     ate virar ^ ou u (e o contrario ao abrir). Ao fechar, o olho desce um tiquinho e alarga; a pupila some suave.
 *   - Reacoes calmas "pestanejam" ao comecar e ao terminar, para a troca de expressao nao dar tranco.
 *   - Bug corrigido: a curva do olho fechado nao vira mais de "u" para "^" (ou ao contrario) enquanto o traco aparece/some.
 *   - Bug corrigido: a pupila nao some mais "de uma vez" quando o olho fecha (agora esmaece junto com o olho).
 *
 * LIGACAO (ESP32-C3 SuperMini)          DISPLAY GC9A01
 *   3V3  ............................... VCC
 *   GND  ............................... GND
 *   GPIO4  ............................. SCL (clock)
 *   GPIO6  ............................. SDA (MOSI / dados)
 *   GPIO7  ............................. CS
 *   GPIO1  ............................. DC
 *   GPIO0  ............................. RST
 *
 * MICROFONE MAX4466
 *   3V3  ............................... VCC
 *   GND  ............................... GND
 *   GPIO3  ............................. OUT
 *
 * Placa na IDE: "ESP32C3 Dev Module"  |  USB CDC On Boot: Enabled
 * Se der erro de "sketch too big": Ferramentas > Partition Scheme > "Huge APP (3MB No OTA)".
 *
 * AO LIGAR (~15 s) - IGUAL AO v5:  tela branca -> cai uma bolinha preta que rebate nas paredes e vai crescendo
 *   ate tomar a tela toda -> tela preta -> ROLETA de rostos passando rapido para a direita ->
 *   para num rosto sorteado. O rosto que cair na roleta FICA no display (nao volta mais pro rosa).
 *
 * OS ROSTOS: so existe UM modelo (o rosa do v5: mesmo tamanho, mesma inclinacao, mesma pupila). O que muda e a COR:
 *   cor do olho grande + cor da pupila pequena. Sao 24 combinacoes (lista FACES, la embaixo):
 *   0 = ROSA/bege (o original) ... 16 a 23 = cada olho de uma cor (heterocromia).
 *   O FUNDO E SEMPRE 100% PRETO (0,0,0) em todos os rostos.
 *
 * (v7.1) Todos os rostos tem o olhar NORMAL de base (olho bem aberto) e, de vez em quando, o humor muda sozinho:
 *   olho meio fechado / curvado / tracado / mais caido. Pisca a cada ~3 s (piscada realista, as vezes dupla).
 *
 * REACOES (sorteadas): ficam 40-60 s so no modo normal (piscando e olhando), depois fazem UMA reacao, e voltam.
 *   Sao 15 reacoes do v5 (ids 1..15, o site continua funcionando) + 1 troca de rosto + 62 novas = 78 no total.
 *
 * TROCA DE ROSTO AUTOMATICA: a cada 1 a 3 minutos ele treme, faz PUFF de fumaca e aparece com outra combinacao de cor.
 *
 * Microfone: ao ouvir voz ele inclina a cabeca e arregala. Barulho forte = susto. DUAS palmas = cambalhota!
 *
 * BLUETOOTH: igual ao v5 (aparece como "Starboy"). Comando 0x0A: [0x0A, rosto 0..35, fixo 0/1].
 *   fixo=0: esse vira o rosto "de casa" (e a troca automatica continua). fixo=1: trava nesse rosto.
 *   Comando 0x01: [0x01, reacao 1..98]  (16 = troca de rosto com fumaca).
 */

/*
 * ============================ V10 - ANIMACOES FLUIDAS ============================
 * Base: v9.3. Os OLHOS (formas, cores, reacoes) estao IDENTICOS ao v9.3. O que mudou foram so as ANIMACOES,
 * medidas quadro a quadro nos dois videos de referencia:
 *   - PISCAR: 3 tipos (normal / rapida / sonolenta). Fecha rapido, segura fechado, abre devagar (curva que freia).
 *             O olhar desce um tico ao fechar. Piscada dupla ficou rapida.
 *   - OLHAR: pulo do olhar com curva suave (acelera e freia), um pouco mais demorado e mais natural.
 *   - TROCA DE ROSTO (A_MORPH): como no video - o olho fecha numa linha, troca de cor/forma fechado, e abre
 *             devagar no rosto novo, com brilhinhos. (A fumaca da v9 volta com MORPH_SMOKE 1.)
 *   - ABERTURA: tela branca -> bolinha pequena passeando devagar (estica na velocidade, achata na parede) ->
 *             encolhe num pontinho no centro -> estoura e vira preto -> nuvem clara cresce no escuro ->
 *             a nuvem se parte em dois olhos -> fecham em linha -> roleta de rostos (troca seca com
 *             piscadinha e brilhinhos, desacelerando) -> o ultimo fica.
 *   Tudo da abertura pode ser acelerado com BOOT_TIME_SCALE (1.0 = mesmo tempo do video).
 * ================================================================================
 */
#include <SPI.h>
#include <math.h>
#include <initializer_list>
#include <string.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#ifdef sq
#undef sq   // v8.1: o Arduino.h do ESP32 core 3.x define sq(x); aqui 'sq' e o nome de um campo
#endif

// ---------------- PINOS (mude aqui se ligar diferente) ----------------
#define PIN_SCK   4
#define PIN_MOSI  6
#define PIN_CS    7
#define PIN_DC    1
#define PIN_RST   0
#define PIN_MIC   3   // saida (OUT) do microfone MAX4466 (entrada analogica)

// ---------------- AJUSTES DO DISPLAY ----------------
#define MADCTL_VAL      0x08   // se azul aparecer VERMELHO, troque para 0x00
#define INVERT_DISPLAY  1      // se cores aparecerem invertidas (fundo branco), troque para 0
#define SPI_HZ          40000000

// ---------------- PERSONALIDADE (mude a vontade) ----------------

// ---------------- PERSONALIDADE (mude a vontade) ----------------
const uint32_t BLINK_MIN = 2300, BLINK_MAX = 4300;   // piscar: sorteia entre esses tempos (ms) => media ~3 s
const uint32_t ACT_MIN   = 40000, ACT_MAX  = 60000;  // pausa NORMAL entre uma reacao e outra (ms): 40 a 60 s
const uint32_t FIRST_ACT_MIN = 12000, FIRST_ACT_MAX = 20000;   // 1a reacao depois de ligar (so para voce ver logo)
const uint32_t MORPH_MIN = 60000, MORPH_MAX = 180000;          // troca de rosto (cor) com fumaca: de 1 a 3 minutos
const uint32_t MOOD_MIN  = 5000,  MOOD_MAX  = 14000;           // muda o "humor" triste (olho caido/curvado/fechado)
const uint32_t SPIN_COOLDOWN = 25000;                // minimo entre duas cambalhotas sorteadas (ms)
#define DOUBLE_CLAP_SPIN 1                           // 1 = duas palmas fortes seguidas => cambalhota
#define BOOT_INTRO       1                           // 1 = animacao de ligar (bolinha + roleta). 0 = pula
#define LOGO_INTRO       1                           // v8: 1 = mostra a logo da Starlyn Infinite ao ligar (fade-in, parada, fade-out). 0 = pula
#define LOGO_FADE_IN_MS  1300                        // v8: tempo do fade-in da logo (ms)
#define LOGO_HOLD_MS     5000                        // v8: tempo da logo parada, 100% visivel (ms)
#define LOGO_FADE_OUT_MS 1300                        // v8: tempo do fade-out da logo (ms)
#define LOGO_SCALE       0.178f                      // v8: tamanho da logo (1.0 = imagem original 1254 px; 0.178 cabe na tela redonda)
// ---------------- v10: ANIMACOES FLUIDAS (medidas nos videos de referencia) ----------------
#define BOOT_TIME_SCALE  1.0f   // v10.1: 1.0 = abertura no tempo normal (~17 s depois da logo). 0.5 = metade do tempo
#define SLOT_DIAG_DEG    16.0f  // v10.1: inclinacao da animacao A (rostos subindo). 0 = reto pra cima, 30 = bem na diagonal
#define MORPH_SMOKE      0      // 0 = troca de rosto como no video (fecha, troca, abre). 1 = fumaca da v9
#define BLINK_DIP        1.3f   // quanto o olhar desce (px) quando pisca (0 = nao desce)
#define HEAD_TURN        1      // v12: 1 = virada de cabeca em falso 3D (olho de perto cresce, o de longe encolhe)
#define BOOT_FINAL_FACE  0      // v12: rosto que fica depois da abertura (0 = ROSA principal como na v11; 76 = Starboy Original laranja do video; -1 = sorteia)
#define BT_CHARGE_ANIM   1      // v12: 1 = ao conectar o Bluetooth toca a animacao verde do raio (id 129)
#define CHARGE_PIN       -1     // v12: pino que le "esta carregando" (ex.: CHRG do TP4056, ativo em LOW). -1 = sem deteccao
#define CHARGE_ACTIVE    LOW    // v12: nivel do pino quando esta carregando
#define CHARGE_REPEAT_MS 14000  // v12: de quanto em quanto tempo o raio toca enquanto carrega
#define SE_SS            3                           // qualidade da borda (2 = mais rapido, 4 = mais suave)


// ---------------- FORMA DO ROSTO ----------------
const float PIV_X = 120, PIV_Y = 118;   // centro do rosto (e o ponto em volta do qual ele gira)
const float LOOK_X = 12, LOOK_Y = 14;   // quanto a pupila anda ao olhar p/ os lados / cima-baixo

// ---------------- MICROFONE ----------------
const int TALK_DELTA = 60;    // acima do silencio = "alguem falando"
const int LOUD_DELTA = 450;   // acima do silencio = "barulho forte"

#define SE_W        240
#define SE_MAXP     72         // v9.1: camadas por olho (era 40)
#define SE_MAXSEG   72
#define SE_MAXEYES  6          // v9.1: olhos por quadro (2 olhos + ate 3 de enfeites + fumaca)
#define BT_REACTIONS 1         // v9.1: 1 = reacao S-01 ao conectar e S-02 ao desconectar o Bluetooth. 0 = desliga

// ---- TIPOS (ficam aqui no comeco para a IDE nao reclamar) ----
enum { PK_ELL = 0, PK_SEG = 1 };
enum { F_LID = 1, F_CLIP = 2 };   // F_LID: obedece as palpebras | F_CLIP: so aparece dentro do olho-base

struct Prim {
  uint8_t kind, flags, alpha, col[3];
  float a, b, c, d, e;   // OVAL: a,b = deslocamento | c,d = raio x,y | e = giro extra (graus)
                         // TRACO: (a,b)->(c,d) | e = raio do traco
};
struct Eye {
  float cx, cy, rot;                 // centro (pixels) e inclinacao (graus, + = topo para a direita)
  float lidAngB;                     // v12: inclinacao da BASE reta (cupula), separada da palpebra de cima
  float cutTop, cutBot, lidAng;      // palpebras: fracao cortada em cima/embaixo (0..1) e inclinacao do corte
  int base;                          // indice da camada que e o "olho" (-1 = nenhuma)
  int n;
  int grad; float gb[3];             // v9.1: degrade vertical da camada-base (cor do olho = topo, gb = base)
  Prim p[SE_MAXP];
};
struct Face { uint8_t bg[3]; int nEyes; Eye eye[SE_MAXEYES]; };


// "Estilo" = tudo que define a cara do olho. Todos os numeros mudam suavemente de um estilo para outro.
// (v6: nao tem mais fundo no estilo - o fundo e SEMPRE preto. Cada olho pode ter a sua cor.)
struct Style {
  float rx, ry, rot, gap, cy, cutTop, cutBot, lid;   // oval do olho, inclinacao, distancia ao centro, altura, palpebras
  float er, eg, eb;                                  // cor do olho ESQUERDO
  float prx, pry, px, py, prot, pr, pg, pb, pa;      // pupila: tamanho, posicao, giro, cor (esquerda), opacidade
  float band, bOy, bRx, bRy;                         // brilho claro embaixo (olhos bravos)
  float arc, bend;                                   // olho fechado em barrinha: quanto, curva
  float squint, conv, winkL, winkR, ps;              // meio-fechado, vesgo, piscadinha de cada olho, tamanho pupila
  float er2, eg2, eb2, pr2, pg2, pb2;                // cor do olho DIREITO e da pupila direita
  float pHeart, pStar, pSlit, pDollar, xEye;         // v9: pupila de coracao / estrela / fenda (gato) / cifrao | olho em X (0..1)
  float hl, wet, ice, gal, dim, ld;                  // v9.1: brilho na pupila, marejado, gelo, galaxia, escurecer, loading (0..1)
  float gA, gbr, gbg, gbb;                           // v9.1: degrade (quanto, cor de baixo)
  float scL, scR;                                    // v9.1: tamanho do olho esquerdo / direito (1 = normal)
  float pSpiral, pCross;                             // v9.1: pupila espiral / mira (0..1)
  float pFlower;                                     // v9.3: pupila em formato de flor (0..1)
  float cheek;                                       // v11: bochecha curva subindo por baixo do olho (0..1)
  float cbAng, pBolt;                                // v12: inclinacao da base da cupula (graus) | pupila em RAIO (0..1)
};
#define NFACES 77
enum Act { A_NONE = 0, A_GRIN, A_SMIRK, A_THINK, A_YAWN, A_LAUGH, A_SAD, A_SURPRISE, A_SPIN,
           A_NO, A_YES, A_CURIOUS, A_WINK, A_CROSS, A_MUMBLE, A_SLEEPY,    // 1..15 = iguais ao v5
           A_MORPH,                                                        // 16 = troca de rosto (treme + fumaca)
           A_RX0,                                                          // 17.. = reacoes novas (tabela RXT)
           A_CU0 = A_RX0 + 82,                                             // v9.1: 99.. = R-21..R-44 e S-01..S-03 (receitas no fim da tabela RXT)
           A_COUNT = A_CU0 + 27 + 4 };            // v11: +3 reacoes (ids 126..128) | v12: +1 (id 129 = R-48 carregando/conectado)
#define ACT_CHARGE   (A_RX0 + 112)   // v12: R-48 verde com raio: carregando / Bluetooth conectou (id 129)
#define ACT_BT_ON    (A_CU0 + 24)   // S-01 Bluetooth conectou (id 123)
#define ACT_BT_OFF   (A_CU0 + 25)   // S-02 Bluetooth caiu (id 124)
#define ACT_BT_SEEK  (A_CU0 + 26)   // S-03 Procurando Bluetooth (id 125)
struct Ov { float rot, dx, dy, zoom; };       // giro, deslocamento e tamanho do rosto inteiro
// v9: enfeites ao redor do rosto (brilhinhos, coracoes, lagrimas...). As reacoes ligam cada um (0..1) a cada quadro.
enum { D_SPARK = 1, D_HEART = 2, D_TEAR = 4, D_Z = 8, D_SWEAT = 16, D_BULB = 32, D_SCAN = 64, D_DOTS = 128, D_BANG = 256 };
// v9.1: as 35 primeiras variaveis sao as INTENSIDADES (0..1) de cada enfeite; depois vem os parametros de cada um.
struct Deco {
  float spark, heart, tear, z, sweat, bulb, scan, dots, bang,
        vein, steam, quest, quest2, notes, burst, fire, snow, bolt, rain, cloud, moon, sun, brk, focus, warn, glitchL,
        sonar, blip, orbit, confetti, code, bars, bt, btWaves, bat;
  float scanY, questS, burstR, fireH, sunP, brkK, sonarM, btDim, btSlash, batPct;
  uint8_t cr, cg, cb, br, bg, bb, sr, sg, sb;
};
#define DECO_NI 35
static_assert(offsetof(Deco, scanY) == DECO_NI * sizeof(float), "DECO_NI tem que bater com as intensidades da struct Deco");
static Deco gDeco;
static float gFlash = 0;      // v9.1: flash branco da tela inteira (R-37 Foto!)

typedef void (*RowSink)(const uint16_t *rgb565, int y);

// v10.1: configuracao de uma "fila de rostos" da abertura (fica aqui no comeco por causa dos prototipos do Arduino)
struct SpinCfg {
  float L, cull, ux, uy;                      // distancia entre rostos, corte de tela, direcao do movimento
  float tWind, tScroll, tSettle, tHold;       // preparo | corrida | freada | parada (ms)
  float ramp, pw, ovs;                        // curva da velocidade e "tranquinho" no freio (px)
  float stX, stY;                             // esticada dos olhos na velocidade
  float lkX, lkY, wGX, wGY, wDX, wDY;         // olhar na corrida | olhar no preparo | deslocamento no preparo
  float lean;                                 // inclinacao da cabeca na velocidade
};

// v8.1: estes tipos ficam aqui no comeco porque o Arduino cria 'prototipos' das funcoes ANTES do resto do codigo
struct SeGeo {
  float ell[SE_MAXP][5];
  float ylo[SE_MAXP], yhi[SE_MAXP];
  float sax[SE_MAXSEG], say[SE_MAXSEG], sdx[SE_MAXSEG], sdy[SE_MAXSEG], sil2[SE_MAXSEG], slim2[SE_MAXSEG];
  float sx0[SE_MAXSEG], sx1[SE_MAXSEG], sy0[SE_MAXSEG], sy1[SE_MAXSEG];
  int segPrim[SE_MAXSEG]; int nSeg;
  float hn[2][3]; int nHalf;          // meio-planos: nx*x + ny*y >= K
};

#define UNSET (-99.0f)
enum { G_TARGET = 0, G_FREE, G_CIRCLE, G_SCAN, G_VSCAN, G_DART, G_SPIRAL };
enum { M_NONE = 0, M_SHAKE, M_NOD, M_TILT, M_WOBBLE, M_BOUNCE, M_ZOOMP, M_AWAY, M_CLOSE, M_TURN, M_FLIP,
       M_DROP, M_TREMBLE, M_SWAY, M_HEART, M_FLUTTER, M_PUPIL, M_SNEEZE, M_NODOFF, M_GLITCH, M_FALL, M_POP, M_SINK,
       M_HIC, M_PEEK };   // v9: soluco, espiando
struct Rx {
  uint16_t dur; uint8_t w, gm, band, wink; int8_t gx, gy; bool arc;
  float ga, gf, cT, cB, lid, sq, rot, ps, sc, cv, pa, py, px, bend, tr, tg, tb, tk;
  uint8_t m1, m2; float a1, f1, a2, f2;
  uint8_t sh = 0;                                     // v9: 1 pupila de gato | 2 coracao | 3 estrela | 4 cifrao | 5 olhos em X
  float ptr = 0, ptg = 0, ptb = 0, ptk = 0;           // v9: cor passageira da PUPILA
  float rb = 0;                                       // v9: > 0 = os olhos mudam de cor sem parar (velocidade)
  bool boot = false;                                  // v9: "reiniciando"
  uint16_t deco = 0; uint8_t dr = 255, dg = 255, db = 255;   // v9: enfeites (D_...) e a cor deles
  uint8_t cu = 0;                                     // v9.1: > 0 = tem uma linha do tempo propria em customRx()
  float chv = 0, hlv = 0;                             // v11: bochecha curva / brilho na pupila
  Rx() : dur(2400), w(5), gm(G_FREE), band(0), wink(0), gx(0), gy(0), arc(false), ga(0), gf(0),
         cT(UNSET), cB(UNSET), lid(UNSET), sq(0), rot(UNSET), ps(1), sc(1), cv(1), pa(1), py(0), px(0), bend(9),
         tr(0), tg(0), tb(0), tk(0), m1(0), m2(0), a1(0), f1(0), a2(0), f2(0) {}
  Rx &D(int v)  { dur = v; return *this; }
  Rx &Wt(int v) { w = v; return *this; }
  Rx &Gz(int x, int y) { gm = G_TARGET; gx = x; gy = y; return *this; }          // olha para (x,y) em -10..10
  Rx &Gm(int m, float a, float f) { gm = m; ga = a; gf = f; return *this; }      // movimento dos olhos
  Rx &Ct(float v) { cT = v; return *this; }   // palpebra de cima
  Rx &Cb(float v) { cB = v; return *this; }   // palpebra de baixo
  Rx &Ld(float v) { lid = v; return *this; }  // inclinacao da palpebra
  Rx &Sq(float v) { sq = v; return *this; }   // meio fechado
  Rx &Rt(float v) { rot = v; return *this; }  // inclinacao dos olhos
  Rx &Ps(float v) { ps = v; return *this; }   // tamanho da pupila
  Rx &Sc(float v) { sc = v; return *this; }   // tamanho do olho
  Rx &Cv(float v) { cv = v; return *this; }   // vesgo
  Rx &Pa(float v) { pa = v; return *this; }   // opacidade da pupila (0 = some)
  Rx &Py(float v) { py = v; return *this; }   // pupila mais pra baixo
  Rx &Bd() { band = 1; return *this; }        // brilho de olho bravo
  Rx &Ar(float b) { arc = true; bend = b; return *this; }   // olho fechado em barrinha (b<0 = ^ ^, b>0 = u u)
  Rx &Wk(int m) { wink = m; return *this; }   // 1 = piscadinha de um lado, 2 = alterna
  Rx &Tn(float r, float g, float b, float k) { tr = r; tg = g; tb = b; tk = k; return *this; }   // cor passageira
  Rx &Sh(int s) { sh = s; return *this; }
  Rx &Pt(float r, float g, float b, float k) { ptr = r; ptg = g; ptb = b; ptk = k; return *this; }
  Rx &Rb(float v) { rb = v; return *this; }
  Rx &Bt() { boot = true; return *this; }
  Rx &Ch(float v) { chv = v; return *this; }              // v11: bochecha curva (olho sorrindo)
  Rx &Hl(float v) { hlv = v; return *this; }              // v11: brilho branco na pupila
  Rx &Cu(int v) { cu = v; return *this; }                // v9.1: liga a reacao a linha do tempo n de customRx()
  Rx &Dc(int bits, int r, int g, int b) { deco = bits; dr = r; dg = g; db = b; return *this; }
  Rx &M(int m, float a, float f) { if (!m1) { m1 = m; a1 = a; f1 = f; } else { m2 = m; a2 = a; f2 = f; } return *this; }
};

// ============================ DRIVER GC9A01 ============================
static inline void csLow()  { digitalWrite(PIN_CS, LOW); }
static void cmd(uint8_t c) { digitalWrite(PIN_DC, LOW); SPI.transfer(c); digitalWrite(PIN_DC, HIGH); }
static void dat(uint8_t d) { SPI.transfer(d); }
static void cmdd(uint8_t c, std::initializer_list<uint8_t> d) { cmd(c); for (auto v : d) dat(v); }

static void gc9a01Init() {
  pinMode(PIN_CS, OUTPUT); pinMode(PIN_DC, OUTPUT); pinMode(PIN_RST, OUTPUT);
  digitalWrite(PIN_CS, HIGH);
  digitalWrite(PIN_RST, HIGH); delay(10);
  digitalWrite(PIN_RST, LOW);  delay(20);
  digitalWrite(PIN_RST, HIGH); delay(150);
  SPI.begin(PIN_SCK, -1, PIN_MOSI, -1);
  SPI.beginTransaction(SPISettings(SPI_HZ, MSBFIRST, SPI_MODE0));
  csLow();
  cmd(0xEF);
  cmdd(0xEB, {0x14});
  cmd(0xFE); cmd(0xEF);
  cmdd(0xEB, {0x14}); cmdd(0x84, {0x40}); cmdd(0x85, {0xFF}); cmdd(0x86, {0xFF}); cmdd(0x87, {0xFF});
  cmdd(0x88, {0x0A}); cmdd(0x89, {0x21}); cmdd(0x8A, {0x00}); cmdd(0x8B, {0x80}); cmdd(0x8C, {0x01});
  cmdd(0x8D, {0x01}); cmdd(0x8E, {0xFF}); cmdd(0x8F, {0xFF});
  cmdd(0xB6, {0x00, 0x00});
  cmdd(0x36, {MADCTL_VAL});
  cmdd(0x3A, {0x05});                       // 16 bits por pixel
  cmdd(0x90, {0x08, 0x08, 0x08, 0x08});
  cmdd(0xBD, {0x06}); cmdd(0xBC, {0x00});
  cmdd(0xFF, {0x60, 0x01, 0x04});
  cmdd(0xC3, {0x13}); cmdd(0xC4, {0x13}); cmdd(0xC9, {0x22}); cmdd(0xBE, {0x11});
  cmdd(0xE1, {0x10, 0x0E}); cmdd(0xDF, {0x21, 0x0C, 0x02});
  cmdd(0xF0, {0x45, 0x09, 0x08, 0x08, 0x26, 0x2A});
  cmdd(0xF1, {0x43, 0x70, 0x72, 0x36, 0x37, 0x6F});
  cmdd(0xF2, {0x45, 0x09, 0x08, 0x08, 0x26, 0x2A});
  cmdd(0xF3, {0x43, 0x70, 0x72, 0x36, 0x37, 0x6F});
  cmdd(0xED, {0x1B, 0x0B}); cmdd(0xAE, {0x77}); cmdd(0xCD, {0x63});
  cmdd(0x70, {0x07, 0x07, 0x04, 0x0E, 0x0F, 0x09, 0x07, 0x08, 0x03});
  cmdd(0xE8, {0x34});
  cmdd(0x62, {0x18, 0x0D, 0x71, 0xED, 0x70, 0x70, 0x18, 0x0F, 0x71, 0xEF, 0x70, 0x70});
  cmdd(0x63, {0x18, 0x11, 0x71, 0xF1, 0x70, 0x70, 0x18, 0x13, 0x71, 0xF3, 0x70, 0x70});
  cmdd(0x64, {0x28, 0x29, 0xF1, 0x01, 0xF1, 0x00, 0x07});
  cmdd(0x66, {0x3C, 0x00, 0xCD, 0x67, 0x45, 0x45, 0x10, 0x00, 0x00, 0x00});
  cmdd(0x67, {0x00, 0x3C, 0x00, 0x00, 0x00, 0x01, 0x54, 0x10, 0x32, 0x98});
  cmdd(0x74, {0x10, 0x85, 0x80, 0x00, 0x00, 0x4E, 0x00});
  cmdd(0x98, {0x3E, 0x07});
  cmd(0x35);
  cmd(INVERT_DISPLAY ? 0x21 : 0x20);
  cmd(0x11); delay(120);
  cmd(0x29); delay(20);
}

static void setWindow(int x0, int y0, int x1, int y1) {
  cmdd(0x2A, {(uint8_t)(x0 >> 8), (uint8_t)x0, (uint8_t)(x1 >> 8), (uint8_t)x1});
  cmdd(0x2B, {(uint8_t)(y0 >> 8), (uint8_t)y0, (uint8_t)(y1 >> 8), (uint8_t)y1});
  cmd(0x2C);
}

static void clearScreen() {
  static uint8_t z[480];
  memset(z, 0, sizeof(z));
  setWindow(0, 0, 239, 239);
  for (int y = 0; y < 240; y++) SPI.writeBytes(z, 480);
}

// ============================ UTILIDADES ============================
static inline float clampf(float v, float a, float b) { return v < a ? a : (v > b ? b : v); }
static inline float lerpf(float a, float b, float t) { return a + (b - a) * t; }
static float ease(float t) { t = clampf(t, 0, 1); return t * t * (3 - 2 * t); }
static float rf(float a, float b) { return a + (b - a) * (random(1001) / 1000.0f); }   // float aleatorio
static inline int rsign() { return random(2) ? 1 : -1; }
// envelope 0..1: sobe em 'rin' ms e desce nos ultimos 'rout' ms
static float env(float t, float d, float rin, float rout) { return fminf(ease(t / rin), ease((d - t) / rout)); }
static void hsv2rgb(float h, float &r, float &g, float &b) {   // arco-iris (h em graus)
  h = fmodf(h, 360.0f); float x = h / 60.0f; int i = (int)x; float f = x - i, q = 1.0f - f;
  switch (i) { case 0: r = 1; g = f; b = 0; break; case 1: r = q; g = 1; b = 0; break; case 2: r = 0; g = 1; b = f; break;
               case 3: r = 0; g = q; b = 1; break; case 4: r = f; g = 0; b = 1; break; default: r = 1; g = 0; b = q; break; }
  r *= 255; g *= 255; b *= 255;
}

// ============================ MOTOR DE OLHOS (desenha tudo linha por linha) ============================
// Cada olho = lista de camadas: ovais inclinadas (olho, pupila, brilho, petalas) e tracos (olho fechado).
// "Palpebra" = corte reto no olho (meio-plano). Borda suave: horizontal (cobertura) + vertical (SE_SS sub-linhas).
static inline void se_ell(Eye &e, float ox, float oy, float rx, float ry, float rot,
                          uint8_t r, uint8_t g, uint8_t b, uint8_t alpha, uint8_t fl) {
  if (e.n >= SE_MAXP) return;
  Prim &p = e.p[e.n++];
  p.kind = PK_ELL; p.flags = fl; p.alpha = alpha; p.col[0] = r; p.col[1] = g; p.col[2] = b;
  p.a = ox; p.b = oy; p.c = rx; p.d = ry; p.e = rot;
}
static inline void se_seg(Eye &e, float x0, float y0, float x1, float y1, float rad,
                          uint8_t r, uint8_t g, uint8_t b, uint8_t alpha, uint8_t fl) {
  if (e.n >= SE_MAXP) return;
  Prim &p = e.p[e.n++];
  p.kind = PK_SEG; p.flags = fl; p.alpha = alpha; p.col[0] = r; p.col[1] = g; p.col[2] = b;
  p.a = x0; p.b = y0; p.c = x1; p.d = y1; p.e = rad;
}


static void se_mk(float *e, float cx, float cy, float a, float b, float c, float s) {
  float ia = 1.0f / (a * a), ib = 1.0f / (b * b);
  e[0] = cx; e[1] = cy;
  e[2] = c * c * ia + s * s * ib;
  e[3] = 2 * c * s * (ia - ib);
  e[4] = s * s * ia + c * c * ib;
}
static bool se_span(const float *e, float y, float &x0, float &x1) {
  float dy = y - e[1];
  float disc = e[3] * e[3] * dy * dy - 4 * e[2] * (e[4] * dy * dy - 1);
  if (disc <= 0) return false;
  float sq = sqrtf(disc), inv = 0.5f / e[2];
  x0 = e[0] + (-e[3] * dy - sq) * inv;
  x1 = e[0] + (-e[3] * dy + sq) * inv;
  return true;
}
static bool se_half(const SeGeo &g, float fy, float &a, float &b) {
  for (int h = 0; h < g.nHalf; h++) {
    float nx = g.hn[h][0], ny = g.hn[h][1], K = g.hn[h][2];
    float rhs = K - ny * fy;
    if (fabsf(nx) < 1e-4f) { if (rhs > 0) return false; }
    else if (nx > 0) { float v = rhs / nx; if (v > a) a = v; }
    else             { float v = rhs / nx; if (v < b) b = v; }
  }
  return b > a;
}

static uint8_t se_row[SE_W][3];
static uint8_t se_cov[SE_W];
static uint16_t se_acc[SE_W][3];
static uint16_t se_out[SE_W];
static SeGeo se_G[SE_MAXEYES];   // v10.1: era [4] - mas um quadro pode ter ate SE_MAXEYES olhos

static inline void se_blend(int i, const uint8_t *col, int k) {   // k = 0..256
  int ik = 256 - k;
  for (int c = 0; c < 3; c++) se_row[i][c] = (uint8_t)((se_row[i][c] * ik + col[c] * k) >> 8);
}
static void se_paint(float l, float r, const uint8_t *col, int alpha) {
  if (l < 0) l = 0;
  if (r > SE_W) r = SE_W;
  int i0 = (int)floorf(l), i1 = (int)ceilf(r) - 1;
  for (int i = i0; i <= i1; i++) {
    float cov = 1;
    if (i == i0 || i == i1) cov = fminf((float)i + 1, r) - fmaxf((float)i, l);
    if (cov <= 0.004f) continue;
    int k = (int)(cov * alpha + 0.5f);
    if (k <= 0) continue;
    if (k >= 256) { se_row[i][0] = col[0]; se_row[i][1] = col[1]; se_row[i][2] = col[2]; }
    else se_blend(i, col, k);
  }
}
static inline uint16_t se_565(int r, int g, int b) { return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3); }

static void se_render(const Face &f, RowSink sink) {
  const float D2R = 0.0174533f;
  float yMin = 1e9f, yMax = -1e9f;
  for (int k = 0; k < f.nEyes; k++) {
    const Eye &E = f.eye[k]; SeGeo &g = se_G[k];
    float rr = E.rot * D2R, cR = cosf(rr), sR = sinf(rr);
    g.nSeg = 0; g.nHalf = 0;
    for (int i = 0; i < E.n; i++) {
      const Prim &p = E.p[i];
      if (p.kind == PK_ELL) {
        float wx = E.cx + p.a * cR - p.b * sR, wy = E.cy + p.a * sR + p.b * cR;
        float th = (E.rot + p.e) * D2R, c = cosf(th), s = sinf(th);
        se_mk(g.ell[i], wx, wy, p.c, p.d, c, s);
        float hh = sqrtf(p.c * p.c * s * s + p.d * p.d * c * c) + 2;
        g.ylo[i] = wy - hh; g.yhi[i] = wy + hh;
        if (p.alpha > 0) { yMin = fminf(yMin, g.ylo[i]); yMax = fmaxf(yMax, g.yhi[i]); }
      } else if (g.nSeg < SE_MAXSEG) {
        int n = g.nSeg++;
        float ax = E.cx + p.a * cR - p.b * sR, ay = E.cy + p.a * sR + p.b * cR;
        float bx = E.cx + p.c * cR - p.d * sR, by = E.cy + p.c * sR + p.d * cR;
        g.segPrim[n] = i; g.sax[n] = ax; g.say[n] = ay; g.sdx[n] = bx - ax; g.sdy[n] = by - ay;
        float l2 = g.sdx[n] * g.sdx[n] + g.sdy[n] * g.sdy[n]; g.sil2[n] = l2 > 1e-6f ? 1.0f / l2 : 0;
        float rd = p.e + 0.5f; g.slim2[n] = rd * rd;
        g.sx0[n] = fminf(ax, bx) - rd; g.sx1[n] = fmaxf(ax, bx) + rd; g.sy0[n] = fminf(ay, by) - rd; g.sy1[n] = fmaxf(ay, by) + rd;
        if (p.alpha > 0) { yMin = fminf(yMin, g.sy0[n]); yMax = fmaxf(yMax, g.sy1[n]); }
      }
    }
    if (E.base >= 0) {                       // palpebras (cortes retos)
      float ry = E.p[E.base].d, ph = (E.lidAng + E.rot) * D2R;
      float nx = -sinf(ph), ny = cosf(ph);
      if (E.cutTop > 0.001f) {
        float d = -ry + 2 * ry * E.cutTop;
        g.hn[g.nHalf][0] = nx; g.hn[g.nHalf][1] = ny; g.hn[g.nHalf][2] = d + nx * E.cx + ny * E.cy; g.nHalf++;
      }
      if (E.cutBot > 0.001f) {
        float d = ry - 2 * ry * E.cutBot;
        float pb = (E.lidAngB + E.rot) * D2R, nbx = -sinf(pb), nby = cosf(pb);   // v12: a base tem o proprio angulo
        g.hn[g.nHalf][0] = -nbx; g.hn[g.nHalf][1] = -nby; g.hn[g.nHalf][2] = -d - nbx * E.cx - nby * E.cy; g.nHalf++;
      }
    }
  }
  int ry0 = (int)floorf(yMin) - 1, ry1 = (int)ceilf(yMax) + 1;
  uint16_t bgPx = se_565(f.bg[0], f.bg[1], f.bg[2]);

  for (int y = 0; y < 240; y++) {
    if (y < ry0 || y > ry1) {                // linha sem olhos: so o fundo
      for (int i = 0; i < SE_W; i++) se_out[i] = bgPx;
      sink(se_out, y);
      continue;
    }
    memset(se_acc, 0, sizeof(se_acc));
    for (int ss = 0; ss < SE_SS; ss++) {
      float fy = y + (ss + 0.5f) / SE_SS;
      for (int i = 0; i < SE_W; i++) { se_row[i][0] = f.bg[0]; se_row[i][1] = f.bg[1]; se_row[i][2] = f.bg[2]; }
      for (int k = 0; k < f.nEyes; k++) {
        const Eye &E = f.eye[k]; const SeGeo &g = se_G[k];
        float ba = 0, bb = 0; bool baseOK = false;
        if (E.base >= 0 && fy >= g.ylo[E.base] && fy <= g.yhi[E.base] && se_span(g.ell[E.base], fy, ba, bb) && se_half(g, fy, ba, bb)) baseOK = true;
        int sc = 0;
        for (int i = 0; i < E.n; i++) {
          const Prim &p = E.p[i];
          if (p.kind == PK_ELL) {
            if (p.alpha == 0 || fy < g.ylo[i] || fy > g.yhi[i]) continue;
            float a, b;
            if (!se_span(g.ell[i], fy, a, b)) continue;
            if (p.flags & F_LID) { if (!se_half(g, fy, a, b)) continue; }
            if (p.flags & F_CLIP) {
              if (!baseOK) continue;
              if (ba > a) a = ba;
              if (bb < b) b = bb;
              if (b <= a) continue;
            }
            const uint8_t *pcol = p.col; uint8_t gcol[3];
            if (E.grad && i == E.base) {                         // v9.1: degrade vertical (cor do olho no topo -> gb embaixo)
              float top = g.ylo[i] + 2.0f, bot = g.yhi[i] - 2.0f;
              float u = (bot > top) ? (fy - top) / (bot - top) : 0.0f; u = u < 0 ? 0 : (u > 1 ? 1 : u);
              for (int c = 0; c < 3; c++) gcol[c] = (uint8_t)(p.col[c] + (E.gb[c] - p.col[c]) * u);
              pcol = gcol;
            }
            se_paint(a, b, pcol, p.alpha + (p.alpha == 255 ? 1 : 0));
          } else {
            int iend = i;                       // sequencia de segmentos iguais = um traco so
            while (iend + 1 < E.n && E.p[iend + 1].kind == PK_SEG && E.p[iend + 1].alpha == p.alpha &&
                   E.p[iend + 1].flags == p.flags && E.p[iend + 1].col[0] == p.col[0] &&
                   E.p[iend + 1].col[1] == p.col[1] && E.p[iend + 1].col[2] == p.col[2] && E.p[iend + 1].e == p.e) iend++;
            int i0 = SE_W, i1 = -1;
            if (p.alpha > 0) {
              for (int s = sc; s < g.nSeg && g.segPrim[s] <= iend; s++) {
                if (fy < g.sy0[s] || fy > g.sy1[s]) continue;
                int xa = (int)fmaxf(g.sx0[s], 0), xb = (int)fminf(g.sx1[s], SE_W - 1);
                for (int x = xa; x <= xb; x++) {
                  float qx = x + 0.5f - g.sax[s], qy = fy - g.say[s];
                  float t = (qx * g.sdx[s] + qy * g.sdy[s]) * g.sil2[s]; t = t < 0 ? 0 : (t > 1 ? 1 : t);
                  float ex = qx - t * g.sdx[s], ey = qy - t * g.sdy[s];
                  float d2 = ex * ex + ey * ey;
                  if (d2 >= g.slim2[s]) continue;
                  float cv = p.e + 0.5f - sqrtf(d2);
                  int c8 = cv >= 1.0f ? 255 : (int)(cv * 255.0f);
                  if (c8 > se_cov[x]) se_cov[x] = (uint8_t)c8;
                  if (x < i0) i0 = x;
                  if (x > i1) i1 = x;
                }
              }
            }
            while (sc < g.nSeg && g.segPrim[sc] <= iend) sc++;
            for (int x = i0; x <= i1; x++) {
              if (!se_cov[x]) continue;
              int k256 = se_cov[x] * (p.alpha + 1) >> 8;
              se_cov[x] = 0;
              if (p.flags & F_CLIP) {
                if (!baseOK) k256 = 0;
                else {
                  float ov = fminf((float)x + 1, bb) - fmaxf((float)x, ba);
                  ov = ov < 0 ? 0 : (ov > 1 ? 1 : ov);
                  k256 = (int)(k256 * ov);
                }
              }
              if (k256 <= 0) continue;
              if (k256 >= 255) { se_row[x][0] = p.col[0]; se_row[x][1] = p.col[1]; se_row[x][2] = p.col[2]; }
              else se_blend(x, p.col, k256);
            }
            i = iend;
          }
        }
      }
      for (int i = 0; i < SE_W; i++) { se_acc[i][0] += se_row[i][0]; se_acc[i][1] += se_row[i][1]; se_acc[i][2] += se_row[i][2]; }
    }
    for (int i = 0; i < SE_W; i++) se_out[i] = se_565(se_acc[i][0] / SE_SS, se_acc[i][1] / SE_SS, se_acc[i][2] / SE_SS);
    sink(se_out, y);
  }
}

// ============================ OS ROSTOS (um modelo so, varias cores) ============================
// Medidas ja em pixels da tela 240x240. O MODELO e o ROSA do v5: ovais grandes e tortinhos, pupila menor olhando
// para baixo/dentro. Todos os 24 rostos usam EXATAMENTE a mesma forma - muda so a cor do olho e a cor da pupila.
// O olhar de base e meio TRISTE (palpebra de cima um pouco caida). O fundo e sempre preto.
static const float KS = 1.28f;                    // tamanho geral dos olhos
static inline float cyv(float c) { return 120 + (c - 120) * KS; }
static const float SAD_CUT = 0.0f, SAD_LID = 0;   // v7.1: sem tristeza de base (olho bem aberto). Quer um tico de triste? use 0.06 e 9
static Style STY[NFACES];

// cor do olho esquerdo, pupila esquerda, olho direito, pupila direita (R,G,B cada)
static const uint8_t FACES[NFACES][12] = {
  // ---- uma cor so (os dois olhos iguais) ----
  {255, 66,196, 250,220,184, 255, 66,196, 250,220,184},   //  0 ROSA + bege (o original)
  { 46, 92,255, 170,235,255,  46, 92,255, 170,235,255},   //  1 azul eletrico + celeste
  { 60,255,120, 255,250,150,  60,255,120, 255,250,150},   //  2 verde neon + amarelo claro
  {160, 80,255, 255,170,230, 160, 80,255, 255,170,230},   //  3 roxo + rosa claro
  {255,140, 40, 255,235,120, 255,140, 40, 255,235,120},   //  4 laranja + amarelo
  {255, 45, 60, 255,225,225, 255, 45, 60, 255,225,225},   //  5 vermelho + branco rosado
  { 30,230,240,  20, 40,150,  30,230,240,  20, 40,150},   //  6 ciano + azul marinho
  {255,226, 72, 255,120, 40, 255,226, 72, 255,120, 40},   //  7 amarelo + laranja
  {235,240,255,  70,110,255, 235,240,255,  70,110,255},   //  8 branco gelo + azul
  {190,255, 60,  30,140, 70, 190,255, 60,  30,140, 70},   //  9 lima + verde escuro
  { 40,220,170, 255,150,200,  40,220,170, 255,150,200},   // 10 turquesa + rosa
  {220, 60,255, 120,240,255, 220, 60,255, 120,240,255},   // 11 magenta + ciano claro
  {255,110,100, 255,225,190, 255,110,100, 255,225,190},   // 12 coral + bege
  {140,200,255, 150, 80,255, 140,200,255, 150, 80,255},   // 13 azul gelo + violeta
  {255,190, 40, 230, 50, 50, 255,190, 40, 230, 50, 50},   // 14 dourado + vermelho
  { 30,170, 90, 190,255,215,  30,170, 90, 190,255,215},   // 15 verde floresta + menta
  // ---- cada olho de uma cor (heterocromia) ----
  {255, 66,196, 250,220,184,  46, 92,255, 170,235,255},   // 16 rosa | azul
  { 60,255,120, 255,250,150, 160, 80,255, 255,170,230},   // 17 verde | roxo
  {255,140, 40,  40, 70,200,  30,230,240, 255,120, 40},   // 18 laranja | ciano
  {255,226, 72, 230, 60, 40, 255, 45, 60, 255,235,120},   // 19 amarelo | vermelho
  {255, 66,196, 120,240,255,  30,230,240, 255,150,210},   // 20 rosa | ciano (pupilas trocadas)
  { 46, 92,255, 255,235,120, 255,140, 40, 170,235,255},   // 21 azul | laranja
  { 60,255,120, 255,120,190, 255, 66,196, 190,255,200},   // 22 verde | rosa
  {160, 80,255, 255,230, 90, 255,226, 72, 160, 80,255},   // 23 roxo | amarelo
  // ---- v9: 12 rostos novos (mesma forma, so cores) ----
  {255,170,205, 150, 30, 85, 255,170,205, 150, 30, 85},   // 24 Sakura (rosa claro + vinho)
  {100, 50,215, 255,240,150, 100, 50,215, 255,240,150},   // 25 Galaxia (roxo escuro + amarelo claro)
  {150,215,255, 255,255,255, 255,120, 40, 255,230,100},   // 26 Fogo & Gelo (gelo | fogo)
  {  0,255,100,   0, 45, 15,   0,255,100,   0, 45, 15},   // 27 Matrix (verde neon + preto esverdeado)
  {255, 50,170, 130,225,255, 255, 50,170, 130,225,255},   // 28 Chiclete (rosa choque + azul bebe)
  {255,245,220, 225,165, 35, 255,245,220, 225,165, 35},   // 29 Ouro branco (branco quente + dourado)
  {  0,115,225, 130,255,235,   0,115,225, 130,255,235},   // 30 Oceano (azul profundo + turquesa)
  {255,115, 70, 145, 40,165, 255,115, 70, 145, 40,165},   // 31 Por do sol (laranja rosado + roxo)
  {150,255,210, 255,140,170, 150,255,210, 255,140,170},   // 32 Menta & rosa
  {225, 30, 30, 255,220, 60, 225, 30, 30, 255,220, 60},   // 33 Lava (vermelho escuro + amarelo)
  {175,255, 60, 255, 40,200, 175,255, 60, 255, 40,200},   // 34 Alienigena (lima + magenta)
  {255,170,205, 150, 30, 85,   0,115,225, 130,255,235},   // 35 Sakura | Oceano (heterocromia)
  // ---- v9.2: F-36..F-59 (rostos 36..59) ----
  {205, 15, 45,  28,  0,  8, 205, 15, 45,  28,  0,  8},   // 36 Vampiro (vermelho sangue + preto)
  { 70,120,255, 255, 80,200,  70,120,255, 255, 80,200},   // 37 Neon azul e rosa
  {215,115, 60,  70,215,200, 215,115, 60,  70,215,200},   // 38 Cobre e turquesa
  {195,165,255, 255,240,160, 195,165,255, 255,240,160},   // 39 Lavanda e manteiga
  { 20,200,115, 255,205, 70,  20,200,115, 255,205, 70},   // 40 Esmeralda e ouro
  { 35, 65,205, 225,230,255,  35, 65,205, 225,230,255},   // 41 Safira e prata
  {225, 25, 90, 255,200,220, 225, 25, 90, 255,200,220},   // 42 Rubi e rose
  {150, 55,220, 232,205,255, 150, 55,220, 232,205,255},   // 43 Ametista
  {255,178, 60, 110, 55, 20, 255,178, 60, 110, 55, 20},   // 44 Mel e chocolate
  {200,245,255,  10, 90,115, 200,245,255,  10, 90,115},   // 45 Gelo seco
  {255,185,155, 230, 80, 90, 255,185,155, 230, 80, 90},   // 46 Pessego e coral
  {240,255, 80, 110, 40,200, 240,255, 80, 110, 40,200},   // 47 Limao e roxo
  {205,212,228,  30, 40,110, 205,212,228,  30, 40,110},   // 48 Lua prata
  {232, 40,115, 160,255,215, 232, 40,115, 160,255,215},   // 49 Framboesa e menta
  { 80,255,205, 170, 85,250,  80,255,205, 170, 85,250},   // 50 Aurora (verde agua + violeta)
  {245,246,255,  30, 28, 70, 245,246,255,  30, 28, 70},   // 51 Fantasma
  {205,212,228,  30, 40,110, 255,195, 50, 230, 90, 20},   // 52 Lua | Sol (hetero)
  {255, 66,196, 250,220,184, 185,255, 50,  30,145, 75},   // 53 Rosa | Limao (hetero)
  { 30,230,240,  20, 40,150, 230, 50,200, 255,215,250},   // 54 Ciano | Magenta (hetero)
  {235, 40, 60, 255,220,220,  50,100,255, 160,235,255},   // 55 Vermelho | Azul (hetero)
  {155, 80,255, 255,160,225,  35,215,165, 255,140,190},   // 56 Roxo | Turquesa (hetero)
  {255,195, 60, 150, 60, 10, 205,212,228,  55, 70,120},   // 57 Ouro | Prata (hetero)
  { 20,200,115, 255,210, 70, 255,120,180, 120, 20, 70},   // 58 Esmeralda | Rosa (hetero)
  { 75, 40,150, 255,240,170, 255,215,115, 120, 35, 20},   // 59 Eclipse | Sol (hetero)
  // ---- v9.2: D-01..D-12 (rostos 60..71): cor do TOPO + pupila (a cor de BAIXO esta na tabela GRADB) ----
  {255,200, 60, 110, 20,100, 255,200, 60, 110, 20,100},   // 60 D-01 Por do sol
  {110,235,255,  10, 25,100, 110,235,255,  10, 25,100},   // 61 D-02 Oceano fundo
  {110,255,190,  20, 20, 90, 110,255,190,  20, 20, 90},   // 62 D-03 Aurora
  {255,170,215, 255,255,255, 255,170,215, 255,255,255},   // 63 D-04 Algodao doce
  {255,235, 70, 120, 10, 10, 255,235, 70, 120, 10, 10},   // 64 D-05 Fogo
  {200,255,110, 255,240,140, 200,255,110, 255,240,140},   // 65 D-06 Floresta
  {195,100,255, 255,240,150, 195,100,255, 255,240,150},   // 66 D-07 Galaxia
  {255, 95, 95,  25,  0,  5, 255, 95, 95,  25,  0,  5},   // 67 D-08 Vampiro
  {255,255,255, 110,150,255, 255,255,255, 110,150,255},   // 68 D-09 Nuvem
  {255,255,255,  20, 60,160, 255,255,255,  20, 60,160},   // 69 D-10 Gelo
  {255, 50,200,  20, 10, 60, 255, 50,200,  20, 10, 60},   // 70 D-11 Neon
  {255,240,190, 120, 50,  0, 255,240,190, 120, 50,  0},   // 71 D-12 Ouro
  // ---- v9.3: P-01..P-04 (rostos 72..75) - olhos da Polly (amarelo e rosa) ----
  {255,215, 40, 255, 88,160, 255,215, 40, 255, 88,160},   // 72 P-01 Polly Sol (amarelo + pupila rosa)
  {253,149,198, 254,232,110, 253,149,198, 254,232,110},   // 73 P-02 Sakura da Polly (rosa + flor amarela; miolo da flor rosa = POLLY_FLOWER_C)
  {255,215, 40, 255, 88,160, 254, 98,179, 255,230,101},   // 74 P-03 Polly | Ana (amarelo/rosa | rosa/amarelo)
  {255,235,115, 127, 22, 88, 255,235,115, 127, 22, 88},   // 75 P-04 Pollyana Radiante (topo amarelo; baixo rosa esta na GRADB; pupila vinho)
  // ---- v12: rosto 76 = Starboy Original (cores medidas no video) ----
  {229, 63, 23, 220,196,224, 229, 63, 23, 220,196,224},   // 76 Starboy Original (laranja + pupila lilas-clara)
};
static const uint8_t POLLY_FLOWER_C[3] = {255, 112, 177};   // v9.3: miolo rosa da flor do P-02
// v9.2: cor de BAIXO do degrade dos rostos 60..71 e 75 (R,G,B)
static const uint8_t GRADB[13][3] = {
  {255, 50,130}, { 20, 70,200}, {150, 70,255}, {110,200,255}, {255, 50, 20}, { 10,115, 85},
  { 25, 15,125}, {110,  0, 35}, {255,140,200}, { 60,160,255}, { 40,255,255}, {230,145, 15},
  {250,100,165} };                                   // v9.3: indice 12 = cor de BAIXO do P-04 (rosto 75)

static void initStyles() {
  for (int i = 0; i < NFACES; i++) {
    Style &s = STY[i];
    memset(&s, 0, sizeof(s));
    // forma do rosa do v5 (rx ry rot gap cy) | pupila (prx pry px py prot)
    // v12: olho em CUPULA (medido nas cartelas): oval alto com a base cortada reta e inclinada; pupila redonda grande
    s.rx = 33 * KS; s.ry = 44 * KS; s.rot = 7; s.gap = 37 * KS; s.cy = cyv(114);
    s.cutTop = SAD_CUT; s.cutBot = 0.0f; s.lid = SAD_LID; s.cbAng = 8;
    s.prx = 12.7f * KS; s.pry = 16.3f * KS; s.px = -9.2f * KS; s.py = 6.9f * KS; s.prot = 0; s.pa = 255;
    s.bOy = 15; s.bRx = 36; s.bRy = 16;
    s.bend = 9; s.conv = 1; s.ps = 1;
    s.scL = 1; s.scR = 1;                                // v9.1: tamanho de cada olho
    const uint8_t *c = FACES[i];
    s.er = c[0]; s.eg = c[1]; s.eb = c[2]; s.pr = c[3]; s.pg = c[4]; s.pb = c[5];
    s.er2 = c[6]; s.eg2 = c[7]; s.eb2 = c[8]; s.pr2 = c[9]; s.pg2 = c[10]; s.pb2 = c[11];
    if ((i >= 60 && i < 72) || i == 75) {                                            // v9.2: degrade (v9.3: tambem o P-04)
      int gi = (i == 75) ? 12 : i - 60;
      s.gA = 1; s.gbr = GRADB[gi][0]; s.gbg = GRADB[gi][1]; s.gbb = GRADB[gi][2];
    }
    if (i == 73) s.pFlower = 1;                                                      // v9.3: P-02 tem flor na pupila
  }
}
// puxa as cores dos DOIS olhos na direcao de uma cor (k 0..1) - usado nas reacoes (corar, frio, raiva...)
static void tintStyle(Style &T, float r, float g, float b, float k) {
  k = clampf(k, 0, 1);
  T.er = lerpf(T.er, r, k); T.eg = lerpf(T.eg, g, k); T.eb = lerpf(T.eb, b, k);
  T.er2 = lerpf(T.er2, r, k); T.eg2 = lerpf(T.eg2, g, k); T.eb2 = lerpf(T.eb2, b, k);
  T.gbr = lerpf(T.gbr, r, k); T.gbg = lerpf(T.gbg, g, k); T.gbb = lerpf(T.gbb, b, k);   // v9.2: o degrade tambem
}


// ---- v9: formas desenhadas so com ovais e tracos (coracao, estrela, cifrao, brilhinho) ----
static void se_heart(Eye &e, float cx, float cy, float W, uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint8_t fl) {
  se_ell(e, cx - 0.50f * W, cy - 0.30f * W, 0.54f * W, 0.54f * W, 0, r, g, b, a, fl);
  se_ell(e, cx + 0.50f * W, cy - 0.30f * W, 0.54f * W, 0.54f * W, 0, r, g, b, a, fl);
  se_ell(e, cx, cy - 0.02f * W, 0.60f * W, 0.42f * W, 0, r, g, b, a, fl);
  se_seg(e, cx - 0.42f * W, cy + 0.06f * W, cx, cy + 0.76f * W, 0.30f * W, r, g, b, a, fl);
  se_seg(e, cx + 0.42f * W, cy + 0.06f * W, cx, cy + 0.76f * W, 0.30f * W, r, g, b, a, fl);
}
static void se_star(Eye &e, float cx, float cy, float R, uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint8_t fl) {
  se_ell(e, cx, cy, 0.36f * R, 0.36f * R, 0, r, g, b, a, fl);
  for (int i = 0; i < 5; i++) {                       // 5 pontas: cada uma = 2 tracos (grosso perto do centro, fino na ponta)
    float an = (-90.0f + 72.0f * i) * 0.0174533f, c = cosf(an), s = sinf(an);
    se_seg(e, cx + 0.20f * R * c, cy + 0.20f * R * s, cx + 0.55f * R * c, cy + 0.55f * R * s, 0.20f * R, r, g, b, a, fl);
    se_seg(e, cx + 0.55f * R * c, cy + 0.55f * R * s, cx + 0.97f * R * c, cy + 0.97f * R * s, 0.06f * R, r, g, b, a, fl);
  }
}
static void se_dollar(Eye &e, float cx, float cy, float u, uint8_t r, uint8_t g, uint8_t b, uint8_t a, uint8_t fl) {
  static const float P[10][2] = { {0.55f, -0.55f}, {0.30f, -0.85f}, {-0.30f, -0.85f}, {-0.60f, -0.50f}, {-0.30f, -0.10f},
                                  {0.30f, 0.10f}, {0.60f, 0.50f}, {0.30f, 0.85f}, {-0.30f, 0.85f}, {-0.55f, 0.55f} };
  for (int i = 0; i < 9; i++)
    se_seg(e, cx + P[i][0] * u, cy + P[i][1] * u, cx + P[i + 1][0] * u, cy + P[i + 1][1] * u, 0.17f * u, r, g, b, a, fl);
  se_seg(e, cx, cy - 1.20f * u, cx, cy + 1.20f * u, 0.12f * u, r, g, b, a, fl);
}
// v10.1: brilhinho de 4 pontas bem mais bonito: halo suave + 2 pontas longas e finas + 2 diagonais curtas + corpo + miolo claro (7 pecas)
static void se_glint(Eye &e, float cx, float cy, float s, float ang, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  if (s < 0.6f) return;
  uint8_t wr = (uint8_t)(r + (255 - r) * 0.65f), wg = (uint8_t)(g + (255 - g) * 0.65f), wb = (uint8_t)(b + (255 - b) * 0.65f);
  float th = fmaxf(s * 0.12f, 0.8f);
  se_ell(e, cx, cy, s * 0.95f, s * 0.95f, 0, r, g, b, (uint8_t)(a * 0.12f), 0);
  se_ell(e, cx, cy, s, th, ang, r, g, b, a, 0);
  se_ell(e, cx, cy, th, s, ang, r, g, b, a, 0);
  se_ell(e, cx, cy, s * 0.52f, fmaxf(s * 0.10f, 0.7f), ang + 45.0f, r, g, b, (uint8_t)(a * 0.85f), 0);
  se_ell(e, cx, cy, s * 0.52f, fmaxf(s * 0.10f, 0.7f), ang - 45.0f, r, g, b, (uint8_t)(a * 0.85f), 0);
  se_ell(e, cx, cy, s * 0.30f, s * 0.30f, 0, r, g, b, a, 0);
  se_ell(e, cx, cy, s * 0.16f, s * 0.16f, 0, wr, wg, wb, a, 0);
}
static void se_spark(Eye &e, float cx, float cy, float s, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {   // brilhinho de 4 pontas
  se_glint(e, cx, cy, s, 0, r, g, b, a);
}

// v9.3: flor de 5 petais (cada petala = circulo) com miolo de outra cor. R = raio total da flor.
static void se_flower(Eye &e, float cx, float cy, float R, uint8_t r, uint8_t g, uint8_t b,
                      uint8_t cr, uint8_t cg, uint8_t cb, uint8_t a, uint8_t fl) {
  for (int i = 0; i < 5; i++) {
    float an = (-90.0f + 72.0f * i) * 0.0174533f;
    se_ell(e, cx + 0.60f * R * cosf(an), cy + 0.60f * R * sinf(an), 0.40f * R, 0.40f * R, 0, r, g, b, a, fl);
  }
  se_ell(e, cx, cy, 0.26f * R, 0.26f * R, 0, cr, cg, cb, a, fl);
}

// ---- v10: mais formas desenhadas so com ovais e tracos (anel, bluetooth, interrogacao, nota, espiral, mira) ----
static float gAnimT = 0;   // v10: tempo em segundos (para o que gira/cintila dentro do olho)
static float gTurn = 0;    // v12: virada de cabeca (-1 esquerda .. +1 direita): o olho de perto cresce, o de longe encolhe
static void se_bolt(Eye &e, float cx, float cy, float hh, float ww, float r, uint8_t R, uint8_t G, uint8_t B, uint8_t a, uint8_t fl) {   // v12: RAIO (3 tracos grossos)
  const float x0 = cx + 0.55f * ww, y0 = cy - hh;           // ponta de cima (direita)
  const float x1 = cx - 0.62f * ww, y1 = cy + 0.10f * hh;   // dobra da esquerda
  const float x2 = cx + 0.70f * ww, y2 = cy - 0.06f * hh;   // dobra da direita (o "degrau" do raio)
  const float x3 = cx - 0.42f * ww, y3 = cy + hh;           // ponta de baixo (afina)
  se_seg(e, x0, y0, x1, y1, r, R, G, B, a, fl);
  se_seg(e, x1, y1, x2, y2, r * 0.85f, R, G, B, a, fl);
  se_seg(e, x2, y2, x3, y3, r * 0.60f, R, G, B, a, fl);
}
static void se_ring(Eye &e, float cx, float cy, float r, float th, int N, uint8_t R, uint8_t G, uint8_t B, uint8_t a, uint8_t fl) {
  for (int i = 0; i < N; i++) {
    float a0 = 6.2831853f * i / N, a1 = 6.2831853f * (i + 1) / N;
    se_seg(e, cx + r * cosf(a0), cy + r * sinf(a0), cx + r * cosf(a1), cy + r * sinf(a1), th, R, G, B, a, fl);
  }
}
static void se_arcs(Eye &e, float cx, float cy, float r, float an0, float an1, float th, int N, uint8_t R, uint8_t G, uint8_t B, uint8_t a) {
  for (int i = 0; i < N; i++) {
    float a0 = an0 + (an1 - an0) * i / N, a1 = an0 + (an1 - an0) * (i + 1) / N;
    se_seg(e, cx + r * cosf(a0), cy + r * sinf(a0), cx + r * cosf(a1), cy + r * sinf(a1), th, R, G, B, a, 0);
  }
}
static void se_bt(Eye &e, float cx, float cy, float s, uint8_t R, uint8_t G, uint8_t B, uint8_t a) {   // simbolo do Bluetooth
  float w = 0.62f * s, th = 0.17f * s;
  se_seg(e, cx, cy - s, cx, cy + s, th, R, G, B, a, 0);
  se_seg(e, cx, cy - s, cx + w, cy - 0.40f * s, th, R, G, B, a, 0);
  se_seg(e, cx + w, cy - 0.40f * s, cx - w, cy + 0.40f * s, th, R, G, B, a, 0);
  se_seg(e, cx, cy + s, cx + w, cy + 0.40f * s, th, R, G, B, a, 0);
  se_seg(e, cx + w, cy + 0.40f * s, cx - w, cy - 0.40f * s, th, R, G, B, a, 0);
}
static void se_quest(Eye &e, float cx, float cy, float s, uint8_t R, uint8_t G, uint8_t B, uint8_t a) {   // ponto de interrogacao
  static const float Q[8][2] = { {-0.55f, -0.45f}, {-0.32f, -0.82f}, {0.08f, -1.0f}, {0.50f, -0.78f},
                                 {0.58f, -0.38f}, {0.32f, -0.02f}, {0.02f, 0.18f}, {0.02f, 0.48f} };
  for (int i = 0; i < 7; i++)
    se_seg(e, cx + Q[i][0] * s, cy + Q[i][1] * s, cx + Q[i + 1][0] * s, cy + Q[i + 1][1] * s, 0.19f * s, R, G, B, a, 0);
  se_ell(e, cx + 0.02f * s, cy + 0.98f * s, 0.22f * s, 0.22f * s, 0, R, G, B, a, 0);
}
static void se_note(Eye &e, float x, float y, float s, uint8_t R, uint8_t G, uint8_t B, uint8_t a) {      // nota musical
  se_ell(e, x, y, 0.62f * s, 0.44f * s, -20, R, G, B, a, 0);
  se_seg(e, x + 0.52f * s, y - 0.10f * s, x + 0.52f * s, y - 1.70f * s, 0.14f * s, R, G, B, a, 0);
  se_seg(e, x + 0.52f * s, y - 1.70f * s, x + 1.15f * s, y - 1.05f * s, 0.14f * s, R, G, B, a, 0);
}
static void se_spiral(Eye &e, float cx, float cy, float Rr, float ph, float th, uint8_t R, uint8_t G, uint8_t B, uint8_t a, uint8_t fl) {
  const int N = 26; const float TH = 18.85f;      // 3 voltas
  float px = cx, py = cy;
  for (int i = 1; i <= N; i++) {
    float u = (float)i / N, an = u * TH + ph, r = Rr * u;
    float x = cx + r * cosf(an), y = cy + r * sinf(an);
    se_seg(e, px, py, x, y, th, R, G, B, a, fl);
    px = x; py = y;
  }
}
static void se_cross(Eye &e, float cx, float cy, float Rr, float th, uint8_t R, uint8_t G, uint8_t B, uint8_t a, uint8_t fl) {   // mira
  se_ring(e, cx, cy, Rr, th, 14, R, G, B, a, fl);
  se_seg(e, cx - Rr - 5, cy, cx + Rr + 5, cy, th, R, G, B, a, fl);
  se_seg(e, cx, cy - Rr - 5, cx, cy + Rr + 5, th, R, G, B, a, fl);
}

// ============================ MONTA OS DOIS OLHOS DE UM ESTILO ============================
// bl = piscar (0..1) | (gx,gy) = olhar em pixels | convEff = pupilas viradas p/ dentro | O = movimento do rosto
// offX = deslocamento horizontal (usado so pela roleta, para mostrar varios rostos lado a lado)
// v10: degrade (cima->baixo), escurecer (dim), tamanho de cada olho (scL/scR), marejado, brilho na pupila, gelo,
//      galaxia, loading, pupila espiral e pupila de mira.
static void addEyes(Face &F, const Style &S, float bl, float gx, float gy, float convEff, const Ov &O, float offX) {
  const float D2R = 0.0174533f;
  float rr = O.rot * D2R, cR = cosf(rr), sR = sinf(rr);
  if (gy < 0) gy *= 1.0f + 0.6f * (1.0f - clampf(fabsf(gx) / (LOOK_X * 0.8f), 0, 1));   // v11: olhando reto pra cima a pupila sobe mais
  // v11: PISCADA NOVA. bl 0..0.8 = o olho achata e gira pro horizontal; 0.8..1 = vira um arco 'u' solido (olho fechado)
  float blB = clampf(bl, 0, 1), blEff = 0, blArc = 0, blRot = 0;
  if (blB < 0.8f) { float k = blB / 0.8f; blEff = blB * 0.93f; blRot = k * k; }
  else { float u = (blB - 0.8f) / 0.2f; blEff = 0.74f * (1.0f - u); blArc = 0.35f + 0.65f * ease(u); blRot = 1.0f; }
  float arcA = clampf(fmaxf(S.arc, blArc), 0, 1);
  bool blinkArc = (blArc > S.arc);
  float bendUse = blinkArc ? -4.0f : S.bend;      // v12: fechado da piscada = arco fino curvado pra cima
  // v7: olho fechado em 2 tempos. (1) o olho achata ate virar uma linha reta; (2) a linha curva ate virar ^ ou u.
  float sqA   = ease(arcA / 0.55f);                        // achatamento do olho
  float aBody = 1.0f - ease((arcA - 0.56f) / 0.22f);       // o olho some quando ja e so uma linha fina (por baixo do traco)
  float aArc  = ease((arcA - 0.50f) / 0.05f);              // e o traco solido aparece (antes do olho sumir: sem 'fantasma' translucido)
  float arcP  = ease((arcA - 0.50f) / 0.50f);              // quanto o traco ja curvou (0 = reto, 1 = ^ ou u)
  float dk  = 1.0f - clampf(S.dim, 0, 0.92f);              // v10: escurece os olhos (modo noite, bateria fraca, sono)
  float ldA = clampf(S.ld, 0, 1);                          // v10: olho vira "loading"
  float galA = clampf(S.gal, 0, 1);                        // v10: galaxia
  for (int k = 0; k < 2; k++) {
    if (F.nEyes >= SE_MAXEYES) return;
    float side = (k == 0) ? -1.0f : 1.0f;
    float sc = k ? S.scR : S.scL;                          // v10: tamanho proprio de cada olho (zoom)
    float RX = S.rx * sc, RY = S.ry * sc;
    float tn = HEAD_TURN ? gTurn : 0.0f;                   // v12: falso 3D - olho de perto maior, de longe menor
    RX *= 1.0f - side * 0.15f * tn; RY *= 1.0f - side * 0.05f * tn;
    float wink = (k == 0) ? S.winkL : S.winkR;
    float cl = fmaxf(blEff, fmaxf(S.squint, wink));
    float sy = (1.0f - cl * 0.96f) * (1.0f - 0.94f * sqA);                               // v7: 1o o olho achata...
    Eye &e = F.eye[F.nEyes++];
    // v7: ao fechar, o olho desce um pouquinho e alarga (a palpebra de cima desce mais que a de baixo sobe)
    e.cx = 120 + side * S.gap + side * (sc - 1.0f) * S.rx * 0.35f;
    // v12: ao piscar a palpebra de cima DESCE ate a base reta (a base fica parada) - como no video
    float anchor = fmaxf(cl, blB * 0.93f);
    e.cy = S.cy + RY * (3.0f * S.cutBot) * anchor * 0.96f; e.rot = side * lerpf(S.rot, S.rot * 0.2f, blRot) * (1.0f - 0.75f * arcP);
    e.cutTop = S.cutTop; e.cutBot = S.cutBot; e.lidAng = side * S.lid; e.base = 0; e.n = 0; e.grad = 0;
    e.lidAngB = -side * S.cbAng * (side > 0 ? 1.3f : 0.6f) - e.rot;   // v12: base reta inclinada (ponta de dentro mais baixa)
    float fr = (k ? S.er2 : S.er) * dk, fg = (k ? S.eg2 : S.eg) * dk, fb = (k ? S.eb2 : S.eb) * dk;   // cor deste olho
    float qr = (k ? S.pr2 : S.pr) * dk, qg = (k ? S.pg2 : S.pg) * dk, qb = (k ? S.pb2 : S.pb) * dk;   // cor da pupila deste olho
    uint8_t er = (uint8_t)clampf(fr, 0, 255), eg = (uint8_t)clampf(fg, 0, 255), eb = (uint8_t)clampf(fb, 0, 255);
    float xA = clampf(S.xEye, 0, 1), aBe = aBody * (1.0f - xA) * (1.0f - ldA);             // v9: olho em X | v10: loading
    uint8_t aB = (uint8_t)(255 * aBe);
    se_ell(e, 0, 0, RX * (1.0f + 0.05f * cl), RY * sy, 0, er, eg, eb, aB, F_LID);   // o olho
    if (S.gA > 0.01f) {                                                                  // v10: degrade (cor do olho = TOPO, gb = BAIXO)
      float ga = clampf(S.gA, 0, 1);
      e.grad = 1;
      e.gb[0] = clampf(lerpf(fr, S.gbr * dk, ga), 0, 255);
      e.gb[1] = clampf(lerpf(fg, S.gbg * dk, ga), 0, 255);
      e.gb[2] = clampf(lerpf(fb, S.gbb * dk, ga), 0, 255);
    }
    if (S.band > 1) {                                                                    // brilho claro embaixo
      uint8_t lr = (uint8_t)(er + (255 - er) * 0.45f), lg = (uint8_t)(eg + (255 - eg) * 0.45f), lb = (uint8_t)(eb + (255 - eb) * 0.45f);
      se_ell(e, 0, S.bOy * sy, S.bRx, S.bRy * sy, 0, lr, lg, lb, (uint8_t)(clampf(S.band, 0, 255) * aBe), F_CLIP);
    }
    if (galA > 0.02f) {                                                                  // v10: galaxia (nebulosas + estrelinhas que cintilam)
      float ga = galA * aBe, RYs = RY * sy;
      se_ell(e, -0.30f * RX, -0.22f * RYs, 0.66f * RX, 0.52f * RYs, -20, 150, 64, 200, (uint8_t)(200 * ga), F_CLIP);
      se_ell(e,  0.20f * RX,  0.42f * RYs, 0.80f * RX, 0.46f * RYs,  15,  54, 96, 220, (uint8_t)(190 * ga), F_CLIP);
      se_ell(e, -0.05f * RX,  0.10f * RYs, 0.36f * RX, 0.26f * RYs,   0, 110, 120, 235, (uint8_t)(110 * ga), F_CLIP);
      static const float GS[9][3] = { {-0.55f, -0.55f, 1.7f}, {0.12f, -0.72f, 1.4f}, {0.52f, -0.28f, 2.0f}, {-0.22f, -0.08f, 1.5f},
                                      {0.30f, 0.22f, 1.6f}, {-0.48f, 0.28f, 1.4f}, {0.04f, 0.58f, 1.8f}, {0.50f, 0.62f, 1.3f}, {-0.10f, -0.38f, 2.4f} };
      for (int q = 0; q < 9; q++) {
        float tw = 0.30f + 0.70f * (0.5f + 0.5f * sinf(gAnimT * 3.6f + q * 2.3f + k * 1.1f));
        se_ell(e, GS[q][0] * RX, GS[q][1] * RYs, GS[q][2], GS[q][2], 0, 255, 250, 235, (uint8_t)(255 * ga * tw), F_CLIP);
      }
    }
    float c0 = cosf(e.rot * D2R), s0 = sinf(e.rot * D2R);
    float lgx = gx * c0 + gy * s0, lgy = -gx * s0 + gy * c0;                             // olhar -> eixos do olho
    float pf = ease((sy - 0.08f) / 0.22f);                                               // v7: pupila some suave ao fechar (antes sumia de uma vez)
    if (S.pa > 1 && pf > 0.01f) {                                                        // pupila
      float ppx = side * S.px * convEff * S.ps + lgx, ppy = (S.py + 0) * sy + lgy * sy;
      float pA = clampf(S.pa, 0, 255) * aBe * pf * (1.0f - galA);
      uint8_t qR = (uint8_t)clampf(qr, 0, 255), qG = (uint8_t)clampf(qg, 0, 255), qB = (uint8_t)clampf(qb, 0, 255);
      float shOth = clampf(fmaxf(fmaxf(fmaxf(fmaxf(S.pHeart, S.pStar), fmaxf(S.pSlit, S.pDollar)), fmaxf(S.pSpiral, S.pCross)), S.pBolt), 0, 1);   // v9/v10: pupilas especiais
      float flA = clampf(S.pFlower, 0, 1) * (1.0f - shOth);                                // v9.3: a flor some quando outra forma assume a pupila
      float shMax = fmaxf(shOth, flA);
      float dotA = 1.0f - shMax;
      float prxE = S.prx * S.ps * sc, pryE = S.pry * S.ps * sc;
      if (dotA > 0.02f)
        se_ell(e, ppx, ppy, prxE, pryE * sy, side * S.prot, qR, qG, qB, (uint8_t)(pA * dotA), F_CLIP);
      float big = fmaxf(S.prx, S.pry) * S.ps * sc;
      if (S.pHeart > 0.02f)  se_heart(e, ppx, ppy, 1.15f * big, qR, qG, qB, (uint8_t)(pA * clampf(S.pHeart, 0, 1)), F_CLIP);
      if (S.pStar > 0.02f)   se_star(e, ppx, ppy, 1.55f * big, qR, qG, qB, (uint8_t)(pA * clampf(S.pStar, 0, 1)), F_CLIP);
      if (flA > 0.02f) se_flower(e, ppx, ppy, 1.40f * big, qR, qG, qB,
                                 (uint8_t)(POLLY_FLOWER_C[0] * dk), (uint8_t)(POLLY_FLOWER_C[1] * dk), (uint8_t)(POLLY_FLOWER_C[2] * dk),
                                 (uint8_t)(pA * flA), F_CLIP);                              // v9.3: pupila em flor (P-02)
      if (S.pDollar > 0.02f) se_dollar(e, ppx, ppy, 1.10f * big, qR, qG, qB, (uint8_t)(pA * clampf(S.pDollar, 0, 1)), F_CLIP);
      if (S.pSlit > 0.02f)   se_ell(e, ppx, ppy, prxE * 0.22f, pryE * 1.9f * sy, 0, qR, qG, qB, (uint8_t)(pA * clampf(S.pSlit, 0, 1)), F_CLIP);
      if (S.pSpiral > 0.02f) se_spiral(e, ppx * 0.5f, ppy * 0.4f, 0.46f * RX, gAnimT * 4.4f, 2.0f, qR, qG, qB, (uint8_t)(pA * clampf(S.pSpiral, 0, 1)), F_CLIP);
      if (S.pCross > 0.02f)  se_cross(e, ppx * 0.6f, ppy * 0.6f, 0.44f * RX, 1.7f, qR, qG, qB, (uint8_t)(pA * clampf(S.pCross, 0, 1)), F_CLIP);
      if (S.pBolt > 0.02f) {                                                             // v12: RAIO no lugar da pupila
        float RYs = RY * sy;
        se_bolt(e, ppx * 0.2f, ppy * 0.2f, 0.58f * RYs, 0.50f * RX, 0.25f * RX, qR, qG, qB, (uint8_t)(pA * clampf(S.pBolt, 0, 1)), F_CLIP);
      }
      if (S.hl > 0.02f) {                                                                // v10: brilhinho branco na pupila (olhao brilhante)
        uint8_t ha = (uint8_t)(235 * clampf(S.hl, 0, 1) * aBe * pf);
        se_ell(e, ppx - 0.34f * prxE, ppy - 0.36f * pryE * sy, 0.30f * prxE, 0.28f * pryE * sy, 0, 255, 255, 255, ha, F_CLIP);
        se_ell(e, ppx + 0.30f * prxE, ppy + 0.34f * pryE * sy, 0.15f * prxE, 0.14f * pryE * sy, 0, 255, 255, 255, ha, F_CLIP);
      }
    }
    if (S.wet > 0.02f) {                                                                 // v10: olho marejado (agua sobe de baixo)
      float wt = clampf(S.wet, 0, 1), w = wt * aBe, RYs = RY * sy;
      float ytop = RYs * (0.78f - 0.74f * wt), ryw = RYs * 0.62f;
      se_ell(e, 0, ytop + ryw, RX * 1.35f, ryw, 0, 150, 205, 255, (uint8_t)(150 * w), F_CLIP);
      se_ell(e, 0, ytop + 1.2f, RX * 0.70f, 1.8f, 0, 225, 242, 255, (uint8_t)(170 * w), F_CLIP);
    }
    if (S.ice > 0.02f) {                                                                 // v10: olho congelado (casca de gelo + rachaduras)
      float ic = clampf(S.ice, 0, 1) * aBe, RYs = RY * sy;
      se_ell(e, 0, 0, RX * 1.10f, RYs * 1.08f, 0, 205, 228, 255, (uint8_t)(120 * ic), 0);
      uint8_t ca = (uint8_t)(235 * ic);
      se_seg(e, -0.35f * RX, -0.60f * RYs, -0.08f * RX, -0.10f * RYs, 1.6f, 240, 250, 255, ca, F_CLIP);
      se_seg(e, -0.08f * RX, -0.10f * RYs, -0.30f * RX, 0.22f * RYs, 1.6f, 240, 250, 255, ca, F_CLIP);
      se_seg(e, 0.30f * RX, -0.62f * RYs, 0.12f * RX, -0.05f * RYs, 1.6f, 240, 250, 255, ca, F_CLIP);
      se_seg(e, 0.12f * RX, -0.05f * RYs, 0.36f * RX, 0.26f * RYs, 1.6f, 240, 250, 255, ca, F_CLIP);
    }
    if (ldA > 0.02f) {                                                                   // v10: loading (anel de pontinhos girando)
      for (int q = 0; q < 8; q++) {
        float an = q * 0.785398f, ph = fmodf(gAnimT * 1.3f - q / 8.0f, 1.0f); if (ph < 0) ph += 1.0f;
        float al = 0.15f + 0.85f * (1.0f - ph);
        se_ell(e, 15.0f * cosf(an), 15.0f * sinf(an), 3.3f, 3.3f, 0, er, eg, eb, (uint8_t)(255 * ldA * al), 0);
      }
    }
    if (S.cheek > 0.02f) {                                                               // v11: bochecha curva (a "montanhinha" subindo por baixo do olho)
      float ch = clampf(S.cheek, 0, 1), RYs = RY * sy;
      se_ell(e, 0, RYs * (1.66f - 0.78f * ch), 1.5f * RX, 0.66f * RYs, side * 4.0f, 0, 0, 0, 255, 0);
    }
    if (aArc > 0.02f) {                                                                  // olho fechado: UM traco solido, sem brilho
      // v7: sem halo e sem miolo claro. Cor = cor atual do olho (er,eg,eb), mesma largura do olho, bordas redondas.
      const int N = blinkArc ? 12 : 14;
      float rad = (blinkArc ? 4.4f : 5.6f) * KS * (0.30f + 0.70f * arcP);                                    // comeca fino (igual ao olho achatado) e engrossa
      float half = RX * (1.0f + 0.05f * cl) - rad * 0.75f;                               // largura total = largura do olho
      float bd = bendUse * KS * arcP, yc = -0.5f * bd;                                         // curva cresce de reto ate ^/u; centrado no olho
      uint8_t ca = (uint8_t)(255 * aArc);
      for (int i = 0; i < N; i++) {
        float u0 = -1 + 2.0f * i / N, u1 = -1 + 2.0f * (i + 1) / N;
        float um = 0.5f * (u0 + u1), rr2 = rad;
        if (blinkArc) rr2 = rad * (0.38f + 0.62f * sqrtf(fmaxf(0.0f, 1.0f - um * um)));   // v12: traco afilado nas pontas
        se_seg(e, u0 * half, yc + bd * (1 - u0 * u0), u1 * half, yc + bd * (1 - u1 * u1), rr2, er, eg, eb, ca, 0);
      }
    }
    if (xA > 0.02f) {                                                                    // v9: olho em X (x_x)
      float xa = RX * 0.78f, xb = RY * 0.52f, xr = 5.4f * KS;
      se_seg(e, -xa, -xb, xa, xb, xr, er, eg, eb, (uint8_t)(255 * xA), 0);
      se_seg(e, -xa, xb, xa, -xb, xr, er, eg, eb, (uint8_t)(255 * xA), 0);
    }
    // movimento do rosto inteiro (giro em volta do centro, deslocamento, zoom)
    float relx = e.cx - PIV_X, rely = e.cy - PIV_Y;
    e.cx = PIV_X + offX + O.dx + O.zoom * (relx * cR - rely * sR);
    e.cy = PIV_Y + O.dy + O.zoom * (relx * sR + rely * cR);
    e.rot += O.rot;
    for (int i = 0; i < e.n; i++) {
      Prim &p = e.p[i];
      p.a *= O.zoom; p.b *= O.zoom; p.c *= O.zoom; p.d *= O.zoom;
      if (p.kind == PK_SEG) p.e *= O.zoom;
    }
  }
}

// ============================ ENFEITES (v9 + v10) ============================
// Brilhinhos, coracoes, lagrimas, Zzz, fogo, chuva, confete, radar... viram "olhos" extras da tela (coordenadas da tela, sem giro).
// v10: quando um "olho" de enfeites enche (72 pecas), o proximo enfeite abre outro automaticamente.
static Eye gDummyEye;
static float gBarsV[10];        // v10: altura das barras do equalizador (S-04)
static void addDeco(Face &F, uint32_t now) {
  const Deco &D = gDeco;
  const float *dv = &D.spark; float tot = 0;
  for (int i = 0; i < DECO_NI; i++) tot += dv[i];
  if (tot < 0.01f) return;
  float t = now * 0.001f;
  Eye *cd = NULL;
  auto E = [&](int need) -> Eye & {
    if (cd && cd->n + need <= SE_MAXP) return *cd;
    if (F.nEyes >= SE_MAXEYES) { gDummyEye.n = SE_MAXP; return gDummyEye; }
    Eye &ne = F.eye[F.nEyes++];
    ne.cx = 0; ne.cy = 0; ne.rot = 0; ne.cutTop = 0; ne.cutBot = 0; ne.lidAng = 0; ne.lidAngB = 0; ne.base = -1; ne.n = 0; ne.grad = 0;
    cd = &ne; return ne;
  };
  if (D.spark > 0.01f) {
    Eye &e = E(28);
    static const float SX[4] = {36, 204, 56, 196}, SY[4] = {64, 72, 190, 186}, SS[4] = {10, 8, 7, 9};
    for (int i = 0; i < 4; i++) {
      float tw = 0.45f + 0.55f * (0.5f + 0.5f * sinf(t * 5.0f + i * 1.7f));
      se_spark(e, SX[i], SY[i], SS[i] * tw, D.cr, D.cg, D.cb, (uint8_t)(255 * D.spark));
    }
  }
  if (D.heart > 0.01f) {
    Eye &e = E(10);
    se_heart(e, 200, 54 + 2.5f * sinf(t * 3.0f), 10, 255, 90, 150, (uint8_t)(255 * D.heart), 0);
    se_heart(e, 36, 72 + 2.5f * sinf(t * 3.0f + 1.5f), 7, 255, 90, 150, (uint8_t)(255 * D.heart), 0);
  }
  if (D.tear > 0.01f) {
    Eye &e = E(4);
    for (int k = 0; k < 2; k++) {
      float ph = fmodf(t * 0.9f + k * 0.5f, 1.0f);
      float x = k ? 188 : 52, y = 134 + 44 * ph, a = D.tear * (1.0f - ph * ph);
      se_ell(e, x, y, 4.6f, 6.0f, 0, 120, 200, 255, (uint8_t)(255 * a), 0);
      se_ell(e, x, y - 6.5f, 2.6f, 5.0f, 0, 120, 200, 255, (uint8_t)(255 * a), 0);
    }
  }
  if (D.z > 0.01f) {
    Eye &e = E(9);
    for (int i = 0; i < 3; i++) {
      float ph = fmodf(t * 0.5f + i * 0.33f, 1.0f);
      float x = 164 + 13 * i + 6 * ph, y = 74 - 17 * i - 12 * ph, s = 6.0f + 3.0f * i;
      uint8_t a = (uint8_t)(255 * D.z * sinf(3.14159f * ph));
      se_seg(e, x - s, y - s, x + s, y - s, 1.8f, 180, 190, 255, a, 0);
      se_seg(e, x + s, y - s, x - s, y + s, 1.8f, 180, 190, 255, a, 0);
      se_seg(e, x - s, y + s, x + s, y + s, 1.8f, 180, 190, 255, a, 0);
    }
  }
  if (D.sweat > 0.01f) {
    Eye &e = E(2);
    float ph = fmodf(t * 0.35f, 1.0f), y = 52 + 34 * ph, a = D.sweat * (1.0f - ph * ph);
    se_ell(e, 196, y, 4.8f, 6.2f, 0, 120, 200, 255, (uint8_t)(255 * a), 0);
    se_ell(e, 196, y - 6.8f, 2.7f, 5.2f, 0, 120, 200, 255, (uint8_t)(255 * a), 0);
  }
  if (D.bulb > 0.01f) {
    Eye &e = E(3);
    float fl = 0.65f + 0.35f * sinf(t * 14.0f);
    uint8_t a = (uint8_t)(255 * D.bulb * fl);
    se_seg(e, 120, 24, 120, 11, 2.6f, 255, 235, 120, a, 0);
    se_seg(e, 84, 32, 74, 21, 2.6f, 255, 235, 120, a, 0);
    se_seg(e, 156, 32, 166, 21, 2.6f, 255, 235, 120, a, 0);
  }
  if (D.scan > 0.01f) { Eye &e = E(1); se_seg(e, 28, D.scanY, 212, D.scanY, 1.5f, D.cr, D.cg, D.cb, (uint8_t)(170 * D.scan), 0); }
  if (D.dots > 0.01f) {
    Eye &e = E(3);
    for (int i = 0; i < 3; i++) {
      float on = 0.35f + 0.65f * (0.5f + 0.5f * sinf(t * 7.0f - i * 1.2f));
      se_ell(e, 104 + 16 * i, 206, 3.6f, 3.6f, 0, D.cr, D.cg, D.cb, (uint8_t)(255 * D.dots * on), 0);
    }
  }
  if (D.bang > 0.01f) {
    Eye &e = E(2);
    uint8_t a = (uint8_t)(255 * D.bang);
    se_seg(e, 200, 36, 200, 51, 3.6f, D.cr, D.cg, D.cb, a, 0);
    se_ell(e, 200, 62, 3.8f, 3.8f, 0, D.cr, D.cg, D.cb, a, 0);
  }
  // ------------------------------ v10 ------------------------------
  if (D.vein > 0.01f) {                       // veia de raiva (cruz que pulsa)
    Eye &e = E(3);
    float pu = 1.0f + 0.16f * sinf(t * 11.0f), s = (6.0f + 4.0f * D.vein) * pu;
    uint8_t a = (uint8_t)(255 * D.vein);
    se_seg(e, 196 - s, 54, 196 + s, 54, 3.0f, 255, 70, 82, a, 0);
    se_seg(e, 196, 54 - s, 196, 54 + s, 3.0f, 255, 70, 82, a, 0);
    se_ell(e, 196, 54, 3.4f, 3.4f, 0, 255, 140, 140, a, 0);
  }
  if (D.steam > 0.01f) {                      // vapor saindo dos lados
    Eye &e = E(6);
    for (int s = 0; s < 2; s++)
      for (int i = 0; i < 3; i++) {
        float ph = fmodf(t * 0.8f + i * 0.34f + s * 0.17f, 1.0f);
        float x = (s ? 204 : 36) + (s ? 1 : -1) * 7 * ph + 3 * sinf(t * 4 + i);
        float y = 96 - 52 * ph, r = 4.5f + 6.0f * ph;
        uint8_t g = (uint8_t)(170 - 70 * ph);
        se_ell(e, x, y, r, r * 0.9f, 0, g, g, (uint8_t)(g + 6), (uint8_t)(210 * D.steam * (1.0f - ph * ph)), 0);
      }
  }
  if (D.quest > 0.01f) {                      // ponto de interrogacao que flutua e cresce
    Eye &e = E(9);
    float s = 7.0f + 9.0f * D.questS;
    se_quest(e, 192 + 3 * sinf(t * 3.0f), 56 - 3 * D.questS + 2.0f * sinf(t * 4.5f), s, 255, 230, 90, (uint8_t)(255 * D.quest));
  }
  if (D.quest2 > 0.01f) { Eye &e = E(9); se_quest(e, 46, 66 + 2 * sinf(t * 4 + 1), 6.0f, 200, 170, 70, (uint8_t)(230 * D.quest2)); }
  if (D.notes > 0.01f) {                      // notas musicais coloridas subindo
    Eye &e = E(12);
    static const uint8_t NC[4][3] = { {90, 220, 255}, {255, 225, 90}, {255, 110, 200}, {170, 130, 255} };
    static const float NX[4] = {44, 196, 66, 178};
    for (int i = 0; i < 4; i++) {
      float ph = fmodf(t * 0.38f + i * 0.25f, 1.0f);
      float x = NX[i] + 7 * sinf(t * 2.2f + i * 1.7f), y = 168 - 118 * ph;
      se_note(e, x, y, 7.0f, NC[i][0], NC[i][1], NC[i][2], (uint8_t)(255 * D.notes * sinf(3.14159f * ph)));
    }
  }
  if (D.burst > 0.01f) {                      // explosao de raios em volta do rosto
    Eye &e = E(18);
    float r0 = 58.0f + 44.0f * D.burstR, len = 14.0f + 16.0f * (1.0f - D.burstR * 0.4f);
    for (int i = 0; i < 18; i++) {
      float an = (i * 20.0f + 7.0f) * 0.0174533f, c = cosf(an), s = sinf(an), L = (i & 1) ? len * 0.65f : len;
      se_seg(e, 120 + r0 * c, 118 + r0 * s, 120 + (r0 + L) * c, 118 + (r0 + L) * s, 2.3f, D.cr, D.cg, D.cb, (uint8_t)(255 * D.burst), 0);
    }
  }
  if (D.fire > 0.01f) {                       // chamas crescendo embaixo
    Eye &e = E(21);
    static const float FX[7] = {44, 70, 96, 120, 144, 170, 196};
    static const float FH[7] = {10, 16, 12, 18, 12, 16, 10};
    for (int i = 0; i < 7; i++) {
      float fl = 0.78f + 0.22f * sinf(t * 13.0f + i * 1.9f), h = FH[i] * D.fireH * fl * 1.5f;
      float x = FX[i] + 1.6f * sinf(t * 9.0f + i), yb = 178.0f - 3.0f * fabsf(i - 3.0f);
      uint8_t a = (uint8_t)(255 * D.fire);
      se_ell(e, x, yb - h * 0.50f, 0.26f * h + 1.4f, 0.55f * h + 1.0f, 0, 255, 120, 20, a, 0);
      se_ell(e, x, yb - h * 0.32f, 0.14f * h + 0.8f, 0.30f * h + 0.8f, 0, 255, 228, 80, a, 0);
      se_ell(e, x, yb - h * 1.02f, 0.10f * h + 0.6f, 0.20f * h + 0.6f, 0, 255, 90, 20, (uint8_t)(a * 0.8f), 0);
    }
  }
  if (D.snow > 0.01f) {                       // flocos de neve
    Eye &e = E(12);
    static const float SX2[4] = {38, 204, 54, 190}, SY2[4] = {72, 60, 172, 178}, SZ2[4] = {6.5f, 5.5f, 5.0f, 6.0f};
    for (int i = 0; i < 4; i++) {
      float ph = fmodf(t * 0.22f + i * 0.27f, 1.0f);
      float x = SX2[i] + 4 * sinf(t * 1.6f + i * 2), y = SY2[i] - 16 + 32 * ph, s = SZ2[i];
      uint8_t a = (uint8_t)(255 * D.snow * sinf(3.14159f * ph));
      for (int k = 0; k < 3; k++) {
        float an = k * 1.0472f + t * 0.8f * ((i & 1) ? 1.0f : -1.0f), c = cosf(an), sn = sinf(an);
        se_seg(e, x - s * c, y - s * sn, x + s * c, y + s * sn, 1.3f, 190, 235, 255, a, 0);
      }
    }
  }
  if (D.bolt > 0.01f) {                       // raios piscando em volta
    Eye &e = E(34);
    static const float BX[4] = {46, 196, 82, 160}, BY[4] = {58, 54, 164, 168}, BD[4] = {-1, 1, -1, 1};
    uint32_t sdd = (uint32_t)(t * 13.0f);
    for (int k = 0; k < 4; k++) {
      uint32_t h = (sdd * 2654435761u) ^ (uint32_t)(k * 40503u + 977u); h ^= h >> 13; h *= 1274126177u; h ^= h >> 16;
      if (((h >> 7) & 3) == 0) continue;
      float px[5], py[5]; px[0] = BX[k]; py[0] = BY[k];
      for (int s = 0; s < 4; s++) {
        px[s + 1] = px[s] + BD[k] * ((s & 1) ? -5.0f : 9.0f) + (float)((h >> (s * 4)) & 3) - 1.0f;
        py[s + 1] = py[s] + 9.0f + (float)((h >> (s * 4 + 2)) & 3);
      }
      for (int s = 0; s < 4; s++) se_seg(e, px[s], py[s], px[s + 1], py[s + 1], 4.2f, 255, 200, 40, (uint8_t)(90 * D.bolt), 0);
      for (int s = 0; s < 4; s++) se_seg(e, px[s], py[s], px[s + 1], py[s + 1], 1.8f, 255, 246, 110, (uint8_t)(255 * D.bolt), 0);
    }
  }
  if (D.rain > 0.01f) {                       // chuva
    Eye &e = E(16);
    for (int i = 0; i < 15; i++) {
      float ph = fmodf(t * (1.5f + 0.09f * (i % 5)) + i * 0.377f, 1.0f);
      float x = 18 + 14.0f * i + 3.0f * sinf(i * 2.3f), y = 24 + 200.0f * ph;
      se_seg(e, x, y, x - 3.5f, y + 10.0f, 1.2f, 120, 175, 255, (uint8_t)(190 * D.rain), 0);
    }
  }
  if (D.cloud > 0.01f) {                      // nuvem no topo
    Eye &e = E(4);
    uint8_t a = (uint8_t)(235 * D.cloud);
    float bob = 1.5f * sinf(t * 1.6f);
    se_ell(e, 96, 31 + bob, 21, 11, 0, 118, 132, 172, a, 0);
    se_ell(e, 144, 31 + bob, 21, 11, 0, 118, 132, 172, a, 0);
    se_ell(e, 120, 25 + bob, 26, 14, 0, 142, 156, 196, a, 0);
    se_ell(e, 120, 33 + bob, 40, 9, 0, 128, 142, 182, a, 0);
  }
  if (D.moon > 0.01f) {                       // lua crescente
    Eye &e = E(2);
    uint8_t a = (uint8_t)(255 * D.moon);
    se_ell(e, 200, 46, 11, 11, 0, 240, 212, 100, a, 0);
    se_ell(e, 205.5f, 42, 9.6f, 9.6f, 0, 0, 0, 0, a, 0);
  }
  if (D.sun > 0.01f) {                        // sol nascendo no topo
    Eye &e = E(13);
    float cy = -6.0f + 30.0f * D.sunP, sp = clampf(D.sunP * 1.6f, 0, 1);
    uint8_t sr = (uint8_t)lerpf(150, 255, sp), sg = (uint8_t)lerpf(112, 208, sp), sb = (uint8_t)lerpf(36, 62, sp);
    uint8_t a = (uint8_t)(255 * D.sun);
    se_ell(e, 120, cy, 15, 15, 0, sr, sg, sb, a, 0);
    for (int i = 0; i < 12; i++) {
      float an = i * 0.5236f, c = cosf(an), s = sinf(an), L = 8.0f + 6.0f * D.sunP;
      se_seg(e, 120 + 21 * c, cy + 21 * s, 120 + (21 + L) * c, cy + (21 + L) * s, 2.0f, sr, sg, sb, (uint8_t)(a * (0.35f + 0.65f * sp)), 0);
    }
  }
  if (D.brk > 0.01f) {                        // cantoneiras de camera / mira (fecham em volta dos olhos)
    Eye &e = E(8);
    float W = 94.0f - 6.0f * D.brkK, H2 = lerpf(86.0f, 64.0f, D.brkK), L = 15.0f; uint8_t a = (uint8_t)(255 * D.brk);
    for (int sx = -1; sx <= 1; sx += 2)
      for (int sy2 = -1; sy2 <= 1; sy2 += 2) {
        float cx = 120 + sx * W, cy = 112 + sy2 * H2;
        se_seg(e, cx, cy, cx - sx * L, cy, 2.0f, D.br, D.bg, D.bb, a, 0);
        se_seg(e, cx, cy, cx, cy - sy2 * L, 2.0f, D.br, D.bg, D.bb, a, 0);
      }
  }
  if (D.focus > 0.01f) {                      // marquinha verde de foco
    Eye &e = E(2); uint8_t a = (uint8_t)(255 * D.focus);
    se_seg(e, 114, 198, 126, 198, 1.6f, 110, 255, 140, a, 0);
    se_seg(e, 120, 192, 120, 204, 1.6f, 110, 255, 140, a, 0);
  }
  if (D.warn > 0.01f) {                       // triangulo de aviso
    Eye &e = E(5);
    float bl = 0.65f + 0.35f * sinf(t * 12.0f); uint8_t a = (uint8_t)(255 * D.warn * bl);
    se_seg(e, 120, 22, 108, 44, 2.4f, 255, 70, 82, a, 0);
    se_seg(e, 108, 44, 132, 44, 2.4f, 255, 70, 82, a, 0);
    se_seg(e, 132, 44, 120, 22, 2.4f, 255, 70, 82, a, 0);
    se_seg(e, 120, 30, 120, 37, 1.7f, 255, 70, 82, a, 0);
    se_ell(e, 120, 41, 1.8f, 1.8f, 0, 255, 70, 82, a, 0);
  }
  if (D.glitchL > 0.01f) {                    // linhas de glitch
    Eye &e = E(3);
    uint32_t h = (uint32_t)(t * 11.0f) * 2654435761u;
    for (int i = 0; i < 3; i++) {
      uint32_t q = h ^ (uint32_t)(i * 40503u + 977u); q ^= q >> 15; q *= 2246822519u; q ^= q >> 13;
      float y = 74.0f + (float)(q & 63) + i * 30.0f, x0 = 28.0f + (float)((q >> 6) & 31), x1 = x0 + 70.0f + (float)((q >> 11) & 63);
      se_seg(e, x0, y, x1, y, 1.3f, 255, 60, 100, (uint8_t)(220 * D.glitchL), 0);
    }
  }
  if (D.sonar > 0.01f) {                      // ondas de sonar saindo do centro
    Eye &e = E(48);
    for (int k = 0; k < 2; k++) {
      float ph = fmodf(t * 0.55f + k * 0.5f, 1.0f), r = 8.0f + (D.sonarM - 8.0f) * ph;
      se_ring(e, 120, 114, r, 1.7f, 24, D.sr, D.sg, D.sb, (uint8_t)(215 * D.sonar * (1.0f - ph)), 0);
    }
  }
  if (D.blip > 0.01f) {                       // alvo encontrado no radar
    Eye &e = E(3);
    float pu = 0.7f + 0.3f * sinf(t * 10.0f); uint8_t a = (uint8_t)(255 * D.blip);
    se_ell(e, 176, 72, 4.2f, 4.2f, 0, 255, 70, 80, a, 0);
    se_seg(e, 166, 72, 186, 72, 1.3f, 255, 120, 120, (uint8_t)(a * pu), 0);
    se_seg(e, 176, 62, 176, 82, 1.3f, 255, 120, 120, (uint8_t)(a * pu), 0);
  }
  if (D.orbit > 0.01f) {                      // estrelinhas rodando em volta da cabeca
    Eye &e = E(21);
    for (int i = 0; i < 3; i++) {
      float an = t * 3.4f + i * 2.0944f, s2 = sinf(an);
      se_spark(e, 120 + 66 * cosf(an), 40 + 13 * s2, 6.0f + 3.0f * (0.5f + 0.5f * s2), 255, 232, 100, (uint8_t)(255 * D.orbit));
    }
  }
  if (D.confetti > 0.01f) {                   // confete colorido caindo
    Eye &e = E(22);
    static const uint8_t CC[7][3] = { {255, 90, 160}, {90, 230, 255}, {255, 225, 80}, {150, 255, 130}, {190, 130, 255}, {255, 150, 60}, {255, 255, 255} };
    for (int i = 0; i < 22; i++) {
      float ph = fmodf(t * (0.30f + 0.045f * (i % 4)) + i * 0.173f, 1.0f);
      float x = 12.0f + fmodf(i * 37.0f, 214.0f) + 8 * sinf(t * 2.0f + i), y = -8.0f + 256.0f * ph, an = t * 6.0f + i * 1.7f;
      const uint8_t *c = CC[i % 7];
      se_seg(e, x - 3.2f * cosf(an), y - 3.2f * sinf(an), x + 3.2f * cosf(an), y + 3.2f * sinf(an), 1.7f, c[0], c[1], c[2], (uint8_t)(255 * D.confetti), 0);
    }
  }
  if (D.code > 0.01f) {                       // chuva de codigo (hacker)
    Eye &e = E(48);
    for (int j = 0; j < 3; j++)
      for (int i = 0; i < 16; i++) {
        float spd = 0.45f + 0.11f * (i % 5);
        float head = fmodf(t * spd + i * 0.317f, 1.0f) * 280.0f - 24.0f;
        float y = head - j * 12.0f, x = 26.0f + 13.0f * i, len = 3.0f + (float)((i * 7 + j * 3) % 4);
        uint8_t cr = (j == 0) ? 205 : (j == 1 ? 50 : 20), cg = (j == 0) ? 255 : (j == 1 ? 225 : 150), cb = (j == 0) ? 215 : (j == 1 ? 100 : 60);
        se_seg(e, x, y, x, y + len, 1.2f, cr, cg, cb, (uint8_t)(255 * D.code * ((j == 0) ? 1.0f : (j == 1 ? 0.7f : 0.4f))), 0);
      }
  }
  if (D.bars > 0.01f) {                       // S-04: barrinhas do equalizador (sobem e descem com o volume)
    Eye &e = E(10);
    for (int i = 0; i < 10; i++) {
      float u = i / 9.0f, x = 51.0f + 15.2f * i, h = 3.0f + 52.0f * clampf(gBarsV[i], 0, 1);
      float r2, g2, b2;
      if (u < 0.5f) { float k = u * 2; r2 = lerpf(255, 170, k); g2 = lerpf(66, 130, k); b2 = lerpf(196, 255, k); }
      else { float k = (u - 0.5f) * 2; r2 = lerpf(170, 40, k); g2 = lerpf(130, 220, k); b2 = lerpf(255, 240, k); }
      se_seg(e, x, 210, x, 210 - h, 2.8f, (uint8_t)r2, (uint8_t)g2, (uint8_t)b2, (uint8_t)(255 * D.bars), 0);
    }
  }
  if (D.bt > 0.01f) {                         // simbolo do Bluetooth (azul; cinza e riscado de vermelho quando cai)
    Eye &e = E(10);
    float dm = clampf(D.btDim, 0, 1);
    uint8_t r2 = (uint8_t)lerpf(60, 120, dm), g2 = (uint8_t)lerpf(130, 128, dm), b2 = (uint8_t)lerpf(255, 160, dm);
    uint8_t a = (uint8_t)(255 * D.bt * (1.0f - 0.45f * dm));
    se_bt(e, 120, 44, 11.0f, r2, g2, b2, a);
    if (D.btSlash > 0.01f) {
      float k = clampf(D.btSlash, 0, 1);
      se_seg(e, 106, 31, 106 + 28 * k, 31 + 26 * k, 2.0f, 255, 60, 70, (uint8_t)(255 * D.bt), 0);
    }
  }
  if (D.btWaves > 0.01f) {                    // S-03: ondinhas saindo do simbolo (convidando a parear)
    Eye &e = E(24);
    for (int k = 0; k < 2; k++) {
      float ph = fmodf(t * 0.8f + k * 0.5f, 1.0f), r = 14.0f + 16.0f * ph;
      uint8_t a = (uint8_t)(255 * D.btWaves * (1.0f - ph));
      se_arcs(e, 120, 44, r, -0.7f, 0.7f, 1.6f, 5, 70, 140, 255, a);
      se_arcs(e, 120, 44, r, 3.1416f - 0.7f, 3.1416f + 0.7f, 1.6f, 5, 70, 140, 255, a);
    }
  }
  if (D.bat > 0.01f) {                        // S-05: icone de bateria embaixo (verde / amarelo / vermelho)
    Eye &e = E(10);
    float pc = clampf(D.batPct, 0, 1);
    uint8_t fr, fg, fb;
    if (pc > 0.6f) { fr = 90; fg = 230; fb = 110; } else if (pc > 0.3f) { fr = 255; fg = 200; fb = 60; } else { fr = 255; fg = 60; fb = 60; }
    float blk = (pc < 0.1f) ? (0.55f + 0.45f * sinf(t * 7.0f)) : 1.0f;
    uint8_t a = (uint8_t)(255 * D.bat), af = (uint8_t)(255 * D.bat * blk);
    se_seg(e, 98, 190, 140, 190, 1.6f, 235, 235, 242, a, 0);
    se_seg(e, 140, 190, 140, 210, 1.6f, 235, 235, 242, a, 0);
    se_seg(e, 140, 210, 98, 210, 1.6f, 235, 235, 242, a, 0);
    se_seg(e, 98, 210, 98, 190, 1.6f, 235, 235, 242, a, 0);
    se_seg(e, 143, 196, 143, 204, 2.2f, 235, 235, 242, a, 0);
    se_seg(e, 105.5f, 200, 105.5f + 27.5f * pc, 200, 5.2f, fr, fg, fb, af, 0);
  }
}

// ============================ FUMACA (puff da troca de rosto) ============================
// p = 0..1: a nuvem cresce rapido, cobre o rosto (~p 0.4) e depois vai sumindo subindo. Vira um "olho" extra so de ovais cinza.
static void addSmoke(Face &F, float p) {
  if (F.nEyes >= SE_MAXEYES || p <= 0.0f || p >= 1.0f) return;
  static const float OX[12] = {-42, 42, 0, -52, 52, -50, 50, 0, 0, -22, 24, 0};
  static const float OY[12] = {  6,  6, 0, -38, -38, 36, 36, -52, 50, -22, 22, 4};
  static const float SR[12] = { 62, 62, 66, 48, 48, 46, 46, 44, 44, 46, 46, 50};
  static const uint8_t GR[12] = {214, 206, 222, 196, 202, 190, 198, 208, 186, 218, 200, 226};
  Eye &e = F.eye[F.nEyes++];
  e.cx = PIV_X; e.cy = PIV_Y; e.rot = 0; e.cutTop = 0; e.cutBot = 0; e.lidAng = 0; e.lidAngB = 0; e.base = -1; e.n = 0; e.grad = 0;
  float g = ease(p / 0.35f);                              // tamanho
  float fade = 1.0f - ease((p - 0.50f) / 0.50f);          // some no fim
  float a = ease(p / 0.20f) * fade;                       // opacidade
  float rise = -26.0f * ease(p);                          // a nuvem sobe um pouco
  for (int i = 0; i < 12; i++) {
    float r = SR[i] * (0.35f + 0.65f * g) * (1.0f + 0.10f * sinf(p * 9 + i));
    float x = OX[i] * (0.25f + 0.75f * g), y = OY[i] * (0.25f + 0.75f * g) + rise * (0.5f + 0.5f * (i % 3) / 2.0f);
    se_ell(e, x, y, r, r * 0.92f, 0, GR[i], GR[i], (uint8_t)(GR[i] + 12 > 255 ? 255 : GR[i] + 12), (uint8_t)(a * 232), 0);
  }
}

// ============================ SAIDA PARA O DISPLAY ============================
static uint16_t sendBuf[SE_W];
static void sinkSPI(const uint16_t *p, int y) {
  (void)y;
  if (gFlash > 0.01f) {                               // v9.1: flash branco (R-37 Foto!): mistura cada pixel com branco
    int k = (int)(clampf(gFlash, 0, 1) * 256.0f);
    for (int i = 0; i < SE_W; i++) {
      int c = p[i], r = (c >> 11) & 31, g = (c >> 5) & 63, b = c & 31;
      r += ((31 - r) * k) >> 8; g += ((63 - g) * k) >> 8; b += ((31 - b) * k) >> 8;
      uint16_t v = (uint16_t)((r << 11) | (g << 5) | b);
      sendBuf[i] = (v >> 8) | (v << 8);
    }
  } else
  for (int i = 0; i < SE_W; i++) sendBuf[i] = (p[i] >> 8) | (p[i] << 8);
  SPI.writeBytes((uint8_t *)sendBuf, SE_W * 2);
}
static Face gFace;
static void showFace() {
  setWindow(0, 0, 239, 239);
  se_render(gFace, sinkSPI);
}

// ============================ OLHAR (natural) ============================
// Sacada = pulo rapido do olhar de um ponto para outro. Microssacada = tremidinha minuscula
// dos dois olhos juntos. Tudo sorteado, sem horario certinho.
static float gX = 0, gY = 0, gSX = 0, gSY = 0, gTX = 0, gTY = 0;   // olhar atual / inicio / alvo
static uint32_t gT0 = 0, gDur = 100, nextSacc = 0;
static bool gazeLock = false;                    // uma animacao esta controlando o olhar
static float goX = 0, goY = 0;                   // deslocamento extra do olhar (animacoes)
static float mcX = 0, mcY = 0, mtX = 0, mtY = 0; // microssacada atual / alvo
static uint32_t nextMicro = 0, nextFlick = 0;
static int flickN = 0, flickSign = 1;
static float hx = 0, hy = 0;                     // a cabeca acompanha um pouquinho o olhar

static float gazeCurve(float p) {                // v10: mistura de "suave" com "freia no fim" (como o olho do video)
  p = clampf(p, 0, 1);
  float a = p * p * (3.0f - 2.0f * p), b = 1.0f - (1.0f - p) * (1.0f - p) * (1.0f - p);
  return 0.45f * a + 0.55f * b;
}
static void gazeTo(float x, float y, uint32_t now) {
  gSX = gX; gSY = gY; gTX = x; gTY = y; gT0 = now;
  float amp = hypotf(x - gX, y - gY);
  gDur = (uint32_t)(78.0f + amp * 6.5f);         // v10: pulo um pouco mais demorado e suave
}

// ============================ PISCAR ============================
static bool blinkOn = false, blinkDouble = false;
static uint32_t blinkT0 = 0, blClose = 80, blHold = 40, blOpen = 110, nextBlink = 0;
static float gLidX = 0;   // v10: as animacoes (ex.: troca de rosto) fecham as palpebras por aqui (0 aberto .. 1 fechado)
static void startBlink(uint32_t now) {
  blinkOn = true; blinkT0 = now;
  bool dbl2 = blinkDouble;                                   // esta e a 2a piscada de uma dupla?
  int k = random(100);
  if (dbl2 || k < 22)  { blClose = random(50, 80);   blHold = random(0, 25);    blOpen = random(120, 175); }   // rapida (v12: ~0,25 s no total)
  else if (k < 80)     { blClose = random(70, 110);  blHold = random(20, 80);   blOpen = random(170, 300); }   // normal (v12: ~0,3-0,45 s)
  else                 { blClose = random(110, 150); blHold = random(140, 260); blOpen = random(280, 420); }   // sonolenta
  uint32_t total = blClose + blHold + blOpen;
  if (!dbl2 && random(100) < 16) { blinkDouble = true; blClose = random(50, 80); blHold = random(0, 25); blOpen = random(130, 180); total = blClose + blHold + blOpen; nextBlink = now + total + random(40, 110); }   // piscada dupla
  else { blinkDouble = false; nextBlink = now + total + random(BLINK_MIN, BLINK_MAX); }
}
// v10: FECHA rapido (acelera), SEGURA fechado, ABRE mais devagar (freia) - curva medida no video
static float blinkFactor(uint32_t now) {
  if (!blinkOn) return 0;
  uint32_t t = now - blinkT0;
  if (t < blClose) return ease((float)t / blClose);
  if (t < blClose + blHold) return 1;
  if (t < blClose + blHold + blOpen) { float u = (float)(t - blClose - blHold) / blOpen; float v = 1.0f - u; return v * v * v; }
  blinkOn = false; return 0;
}

static void pickGaze(uint32_t now) {
  float tx, ty;
  bool awayBefore = hypotf(gTX / LOOK_X, gTY / LOOK_Y) > 0.7f;
  int r = random(100);
  if (awayBefore && r < 70) { tx = rf(-0.25f, 0.25f) * LOOK_X; ty = rf(-0.2f, 0.2f) * LOOK_Y; }          // volta pro centro
  else if (r < 55)          { tx = rf(-0.5f, 0.5f) * LOOK_X;   ty = rf(-0.35f, 0.35f) * LOOK_Y; }        // mexida pequena
  else if (r < 82)          { tx = rsign() * rf(0.65f, 1.0f) * LOOK_X; ty = rf(-0.3f, 0.3f) * LOOK_Y; }  // olha pro lado
  else                      { ty = rsign() * rf(0.7f, 1.0f) * LOOK_Y;  tx = rf(-0.4f, 0.4f) * LOOK_X; }  // cima ou baixo
  float amp = hypotf(tx - gX, ty - gY);
  gazeTo(tx, ty, now);
  float farN = hypotf(tx / LOOK_X, ty / LOOK_Y);                  // quanto mais longe, mais tempo ele fica la
  nextSacc = now + random(500, 1800) + (uint32_t)(farN * random(300, 1500));
  if (amp > 12 && !blinkOn && random(100) < 35) nextBlink = now + random(20, 70);   // olhar longe => pisca junto
}

// ============================ ANIMACOES ============================
static const float TILT_PINK = 15;
static int baseSt = 0;                           // rosto "de casa" (muda sozinho a cada 1-3 min; o da roleta fica aqui)
static int permSt = -1;                          // rosto travado pelo Bluetooth (-1 = nenhum)
static int styleNow(uint32_t now) { (void)now; return permSt >= 0 ? permSt : baseSt; }

static Act act = A_NONE, lastAct = A_NONE;
static uint32_t actT0 = 0, actDur = 0, nextAct = 0, lastSpin = 0, nextMorph = 0;
static int actSide = 1, spinDir = 1, spinTurns = 1;
static float morphTau = 110;                  // rapidez da troca de expressao (ms)
static float mumT = 0; static uint32_t nextMum = 0;
static int morphTo = 0; static bool morphSwapped = false, snapCur = false;
static float smokeP = -1;                     // >= 0 enquanto a fumaca esta na tela

// ---- HUMOR (olhar triste que muda sozinho: mais caido, meio fechado, curvado, tracado...) ----
static float mdCT = 0, mdCB = 0, mdLid = 0, mdSq = 0, mdRot = 0;   // alvo
static float msCT = 0, msCB = 0, msLid = 0, msSq = 0, msRot = 0;   // atual (suavizado)
static float mdSX = 1, mdSY = 1, msSX = 1, msSY = 1;                 // v12: tamanho do olho (largura/altura) - humores atento e largo
static uint32_t nextMood = 0;
static void pickMood(uint32_t now) {
  static int last = -1; int m;
  int rr = random(100);
  if (rr < 40) m = 0;                                                // v13: olho CHEIO (oval completo) = padrao
  else if (rr < 88) m = 10;                                          // v13: CUPULA (base reta)                                       // na maior parte do tempo, olhar normal aberto
  else if (random(100) < 45) m = 8 + random(2);                      // v12: atento (alto) ou largo (baixo e aberto) - quadros 221/281 do video
  else { do { m = 1 + random(7); } while (m == last); }
  last = m;
  mdCT = mdCB = mdLid = mdSq = mdRot = 0; mdSX = mdSY = 1;
  switch (m) {
    case 0: break;                                                     // normal (triste de base)
    case 1: mdCT = 0.12f; mdLid = 4; mdRot = -2; break;                // mais caido
    case 2: mdSq = 0.30f; mdCT = 0.04f; break;                         // meio fechado
    case 3: mdCB = 0.18f; mdCT = 0.04f; mdRot = -3; break;             // curvado (meia-lua)
    case 4: mdSq = 0.42f; mdCT = 0.08f; mdLid = 3; break;              // cansado
    case 5: mdCT = -SAD_CUT; mdLid = -SAD_LID; break;                  // olho aberto (esperanca)
    case 6: mdCT = 0.06f; mdCB = 0.10f; mdLid = -6; mdSq = 0.12f; break;   // tracado / estreito
    case 10: mdCB = 0.20f; break;                                      // v13: cupula
    case 8: mdSY = 1.20f; mdSX = 0.97f; mdCB = -0.04f; break;          // v12: atento - olho alto e esticado
    case 9: mdSX = 1.17f; mdSY = 0.82f; mdSq = 0.10f; break;           // v12: largo - olho aberto e mais baixo
    default: mdCT = 0.16f; mdLid = 8; mdSq = 0.18f; mdRot = -5; break; // bem triste
  }
  nextMood = now + random(MOOD_MIN, MOOD_MAX);
}

// ---- TABELA DAS 109 REACOES NOVAS (62 do v8 + 20 do v9 + 27 do v9.1) ----
// Cada reacao e uma "receita": duracao, para onde olha, expressao (palpebras, pupila, tamanho...) e ate 2 movimentos do rosto.
#define NRX 113
static_assert(A_COUNT == A_RX0 + NRX, "A_COUNT e NRX precisam bater");
static Rx RXT[NRX];
static void initReacts() {
  int n = 0;
  RXT[n++].D(3400).Gm(G_SCAN, 12, 0.0042f).M(M_TURN, 0.5f, 0.0042f).Wt(6);                     //  0 olhando em volta
  RXT[n++].D(2000).Gm(G_CIRCLE, 12, 0.0065f).Ct(0.12f).Wt(4);                                   //  1 rolando os olhos
  RXT[n++].D(2800).Gz(0, 0).M(M_TILT, 10, 0).Ps(1.15f).Sc(1.05f).Ct(0).Wt(6);                   //  2 ouvindo atento
  RXT[n++].D(2800).Gz(5, 8).Ct(0.14f).Py(2).M(M_TILT, 7, 0).M(M_SWAY, 2, 0.005f).Tn(255, 120, 150, 0.3f);   //  3 envergonhado
  RXT[n++].D(3000).Gz(7, 9).Sq(0.15f).Sc(0.94f).M(M_SWAY, 3, 0.003f);                           //  4 timido
  RXT[n++].D(3400).Gz(0, 8).Ct(0.2f).Ld(13).Rt(-6).Ps(1.25f).Py(2).M(M_TREMBLE, 1.1f, 0.045f).M(M_SINK, 3, 0).Tn(120, 170, 255, 0.25f);   //  5 chorando
  RXT[n++].D(2600).Gz(0, 6).Ct(0.15f).Ld(12).Sq(0.2f).M(M_BOUNCE, 2.6f, 0.0125f).Wt(4);         //  6 solucando
  RXT[n++].D(3400).Gz(0, 5).Sq(0.55f).M(M_SINK, 4, 0).M(M_TILT, 5, 0);                          //  7 com sono
  RXT[n++].D(1300).Sq(0.95f).Wt(6);                                                             //  8 piscada lenta
  RXT[n++].D(2600).Gz(10, -1).Ct(0.33f).Cb(0.2f).Ld(-8).M(M_TILT, 5, 0);                        //  9 desconfiado
  RXT[n++].D(2600).Bd().Ct(0.5f).Ld(-26).Rt(0).Pa(0).M(M_TREMBLE, 0.9f, 0.05f).Tn(255, 70, 70, 0.25f);   // 10 bravo
  RXT[n++].D(3000).Gz(7, 9).Ct(0.3f).Ld(14).Rt(-6).M(M_SINK, 3, 0);                             // 11 emburrado
  RXT[n++].D(3200).Gm(G_SCAN, 6, 0.0022f).Ct(0.35f).Ld(0).Sq(0.2f);                             // 12 entediado
  RXT[n++].D(2200).Gz(0, 0).Ps(0.62f).Sc(1.1f).Ct(0).Ld(0).M(M_TREMBLE, 1.8f, 0.06f);           // 13 assustado
  RXT[n++].D(2600).Gz(0, 2).Ps(0.7f).Ct(0).M(M_AWAY, 0.3f, 0).M(M_TREMBLE, 1.2f, 0.07f).Wt(4);  // 14 encolhido de medo
  RXT[n++].D(3200).Gz(0, 0).M(M_AWAY, 0.55f, 0).Wt(6);                                          // 15 indo pra longe (3D)
  RXT[n++].D(3000).Gz(0, 0).M(M_CLOSE, 0.35f, 0).Wt(6);                                         // 16 chegando perto (3D)
  RXT[n++].D(3000).Gm(G_SCAN, 8, 0.0030f).M(M_TURN, 0.95f, 0.0030f);                            // 17 virando a cabeca (3D)
  RXT[n++].D(2400).Gz(10, 0).M(M_TILT, 6, 0).Wt(6);                                             // 18 olhar de lado
  RXT[n++].D(2600).Gz(0, -10).Ct(0).Ld(0);                                                      // 19 olhando pra cima
  RXT[n++].D(2800).Gz(0, 10).Ct(0.25f).Ld(12).M(M_SINK, 3, 0);                                  // 20 olhando pra baixo
  RXT[n++].D(2600).Sc(1.14f).Ps(1.35f).Py(-2).Ct(0).Ld(0).M(M_BOUNCE, 2, 0.008f).M(M_PUPIL, 0.15f, 0.012f);   // 21 fofura (olhao brilhante)
  RXT[n++].D(2000).Wk(2).Ct(0).M(M_TILT, 5, 0);                                                 // 22 piscadinhas alternadas
  RXT[n++].D(3400).Sq(0.48f).Ct(0.1f).Ld(8).Wt(6);                                              // 23 meio fechado
  RXT[n++].D(3000).Ar(-9).Ct(0).M(M_NOD, 3.2f, 0.0036f);                                        // 24 contente ^ ^ (v7: "sim" leve e devagar, sem balancar de lado)
  RXT[n++].D(3400).Ar(9).M(M_TILT, 6, 0).M(M_SINK, 3, 0).Wt(4);                                 // 25 sonhando u u
  RXT[n++].D(3200).Gm(G_SPIRAL, 11, 0.012f).Sq(0.15f).M(M_WOBBLE, 8, 0.008f);                   // 26 tonto
  RXT[n++].D(2800).Gm(G_CIRCLE, 7, 0.0032f).Ps(0.7f).Sc(1.05f).Ct(0).Wt(4);                     // 27 hipnotizado
  RXT[n++].D(3000).Ps(1.4f).Sc(1.1f).Ct(0).Ld(0).Py(-1).M(M_HEART, 0.1f, 0.0013f).Tn(255, 90, 170, 0.45f);   // 28 apaixonado
  RXT[n++].D(3400).Gz(0, 8).Ct(0.3f).Sq(0.3f).M(M_NOD, 4, 0.0028f);                             // 29 cansado suspirando
  RXT[n++].D(2800).Gm(G_DART, 4, 0).Ct(0.12f).Ld(-10).M(M_TILT, 12, 0);                         // 30 confuso
  RXT[n++].D(1500).Gz(0, -2).Ps(0.8f).Sc(1.08f).Ct(0).Ld(0).M(M_POP, 0.07f, 320);               // 31 surpresa leve
  RXT[n++].D(1800).Sc(1.18f).Ps(0.55f).Ct(0).Ld(0).M(M_POP, 0.12f, 260).M(M_TREMBLE, 1.2f, 0.07f).Wt(4);   // 32 choque
  RXT[n++].D(2800).Sq(0.1f).M(M_TREMBLE, 1.6f, 0.09f).Tn(150, 190, 255, 0.35f).Wt(4);           // 33 calafrio
  RXT[n++].D(2800).Gm(G_DART, 9, 0).Ps(0.8f).Ct(0).M(M_TREMBLE, 0.7f, 0.05f);                   // 34 nervoso
  RXT[n++].D(3400).Gz(8, -6).Ct(0.15f).M(M_TILT, 6, 0);                                         // 35 pensativo
  RXT[n++].D(2800).Ct(0).Ld(0).Sc(1.04f).Wk(1).M(M_TILT, 8, 0).M(M_BOUNCE, 3, 0.01f);           // 36 brincalhao
  RXT[n++].D(2600).Ct(0).Ld(0).Sc(1.1f).Ps(1.2f).M(M_BOUNCE, 5, 0.013f);                        // 37 empolgado
  RXT[n++].D(2600).Gz(0, -4).Ct(0).Cb(0.12f).Ld(0).M(M_SINK, -3, 0).Wt(4);                      // 38 orgulhoso
  RXT[n++].D(2600).Gz(6, -3).Ct(0.35f).Cb(0).Ld(0).M(M_SINK, -2, 0).Wt(4);                      // 39 metido
  RXT[n++].D(1500).M(M_FLUTTER, 1, 0.022f);                                                     // 40 borboleta (piscadas rapidas)
  RXT[n++].D(2800).Sc(1.08f).Ps(1.1f).Ct(0).M(M_PUPIL, 0.3f, 0.009f);                           // 41 olhos brilhando
  RXT[n++].D(2600).Cv(2.2f).Py(4).M(M_WOBBLE, 2.5f, 0.007f).Wt(4);                              // 42 vesgo pesado
  RXT[n++].D(1800).Gz(0, 0).M(M_SNEEZE, 9, 0).Wt(4);                                            // 43 espirro
  RXT[n++].D(3000).Gz(0, -2).Sc(1.15f).Ps(1.35f).Ct(0.2f).Ld(14).M(M_TILT, 8, 0);               // 44 cachorrinho pidao
  RXT[n++].D(3200).Gz(-4, 9).Ct(0.25f).Ld(14).Rt(-10).Sc(0.94f).M(M_SINK, 5, 0);                // 45 desapontado
  RXT[n++].D(3200).Gm(G_SCAN, 13, 0.0072f).M(M_TURN, 0.6f, 0.0072f).Ct(0).Wt(4);                // 46 procurando
  RXT[n++].D(2200).Ar(-9).Ct(0).M(M_NOD, 2.2f, 0.022f);                                         // 47 risinho
  RXT[n++].D(3200).M(M_NODOFF, 10, 0).Wt(4);                                                    // 48 cabeceando de sono
  RXT[n++].D(1500).M(M_GLITCH, 9, 0).Wt(3);                                                     // 49 glitch
  RXT[n++].D(3400).Gz(0, 0).M(M_FLIP, 180, 0).Wt(4);                                            // 50 de cabeca pra baixo
  RXT[n++].D(3400).Ar(-9).Ct(0).M(M_NOD, 4.0f, 0.0042f);                                        // 51 dancando (v7: olho fechado ^ ^ + "sim" leve, sem balanco)
  RXT[n++].D(2600).Ct(0).M(M_DROP, 16, 0.009f).Wt(4);                                           // 52 bola quicando
  RXT[n++].D(2600).Ps(0.8f).M(M_FALL, 0, 0).Wt(3);                                              // 53 caindo da tela e voltando
  RXT[n++].D(2600).Bd().Ct(0.46f).Ld(-22).Rt(0).Pa(0).M(M_TREMBLE, 2, 0.06f).M(M_SHAKE, 3, 0.05f).Tn(255, 40, 40, 0.4f).Wt(3);   // 54 furioso
  RXT[n++].D(2400).Sq(0.85f).Ct(0).Ld(0).M(M_SINK, 3, 0).Wt(4);                                 // 55 aliviado
  RXT[n++].D(2800).Gz(-8, -6).Ct(0.2f).M(M_TILT, -8, 0).Wt(4);                                  // 56 duvidando
  RXT[n++].D(3000).Ct(0.4f).Cb(0.15f).Ps(0.85f).Gz(0, 0).Wt(4);                                 // 57 concentrado
  RXT[n++].D(3200).Gz(0, 0).Ps(0.9f).Sc(1.04f).Ct(0).Ld(0).M(M_CLOSE, 0.12f, 0).Wt(4);          // 58 encarando
  RXT[n++].D(3000).Ar(-8).M(M_NOD, 3.6f, 0.0034f).Wt(4);                                        // 59 cantarolando (v7: sem balanco de lado)
  RXT[n++].D(1800).Ps(0.5f).Sc(1.15f).Ct(0).Ld(0).M(M_POP, 0.22f, 380).Wt(3);                   // 60 susto de pulo
  RXT[n++].D(3200).Gm(G_CIRCLE, 6, 0.003f).M(M_SWAY, 9, 0.0022f).Sq(0.3f).Wt(3);                // 61 tontinho (bamboleando)
  // ---- v9: 20 reacoes novas (ids 79..98 = R-01..R-20) ----
  RXT[n++].D(3000).Gz(0, -1).Sh(3).Pt(255, 225, 90, 1).Sc(1.08f).Ps(1.25f).Ct(0).Ld(0).M(M_PUPIL, 0.12f, 0.008f).M(M_TILT, 4, 0).Dc(D_SPARK, 255, 225, 90);   // 62 R-01 olhos de estrela
  RXT[n++].D(3000).Gz(0, 0).Sh(2).Pt(255, 60, 110, 1).Tn(255, 120, 190, 0.35f).Sc(1.06f).Ps(1.2f).Ct(0).Ld(0).M(M_HEART, 0.07f, 0.0013f).Dc(D_HEART, 255, 90, 150);   // 63 R-02 olhos de coracao
  RXT[n++].D(2600).Gz(0, -9).Ps(0.9f).Sc(1.1f).Ct(0).Ld(0).Tn(255, 240, 120, 0.2f).M(M_POP, 0.07f, 320).Dc(D_BULB, 255, 235, 120);   // 64 R-03 ideia!
  RXT[n++].D(3200).Gm(G_VSCAN, 13, 0.0040f).Ct(0.08f).Tn(60, 230, 255, 0.22f).Dc(D_SCAN, 60, 230, 255);                    // 65 R-04 escaneando
  RXT[n++].D(3000).Bd().Ct(0.42f).Ld(-20).Rt(0).Ps(0.8f).Tn(170, 60, 255, 0.22f).M(M_CLOSE, 0.10f, 0).M(M_TREMBLE, 0.5f, 0.04f).Wt(4);   // 66 R-05 maquinando
  RXT[n++].D(2800).Cv(2.3f).Py(5).Sq(0.12f).Tn(150, 215, 255, 0.3f).M(M_TREMBLE, 1.4f, 0.07f).Dc(D_SPARK, 190, 235, 255).Wt(4);   // 67 R-06 dor de gelo
  RXT[n++].D(3200).Gz(0, 5).Tn(255, 100, 55, 0.35f).Sq(0.32f).Py(3).M(M_SINK, 3, 0).M(M_TILT, 5, 0).Dc(D_SWEAT, 120, 200, 255);   // 68 R-07 com calor
  RXT[n++].D(3200).Gm(G_SPIRAL, 5, 0.006f).Tn(120, 220, 100, 0.32f).Sq(0.22f).Ct(0.12f).M(M_TILT, 8, 0).M(M_SINK, 3, 0);   // 69 R-08 enjoado
  RXT[n++].D(2400).Wk(1).Ct(0).Ld(0).Tn(255, 120, 190, 0.22f).M(M_TILT, 6, 0).Dc(D_HEART, 255, 90, 150);                  // 70 R-09 piscadela charmosa
  RXT[n++].D(2800).Gz(0, 0).Ct(0).M(M_HIC, 8, 0.0014f).Dc(D_BANG, 235, 235, 240).Wt(4);                                    // 71 R-10 soluco
  RXT[n++].D(2800).Bt().Wt(3).Dc(D_DOTS, 190, 200, 220);                                                                  // 72 R-11 reiniciando
  RXT[n++].D(3200).Gz(9, 0).M(M_PEEK, 40, 0).Wt(4);                                                                        // 73 R-12 escondendo e espiando
  RXT[n++].D(3000).Ct(0.34f).Ld(-12).Sc(1.05f).Tn(80, 150, 255, 0.28f).M(M_CLOSE, 0.12f, 0).M(M_WOBBLE, 2, 0.004f);        // 74 R-13 determinado
  RXT[n++].D(3000).Gz(3, -6).Sc(1.2f).Ps(1.55f).Py(-2).Ct(0).Ld(0).M(M_PUPIL, 0.12f, 0.01f).Dc(D_SPARK, 255, 255, 255);    // 75 R-14 deslumbrado (uau)
  RXT[n++].D(3000).Sh(1).Tn(190, 255, 60, 0.95f).Pt(15, 25, 5, 1).Ct(0.2f).Ld(-10).Gm(G_SCAN, 6, 0.003f).M(M_TILT, 4, 0);  // 76 R-15 olhar de gato
  RXT[n++].D(3600).Ar(9).Ct(0).M(M_SINK, 4, 0).M(M_TILT, 4, 0).Dc(D_Z, 180, 190, 255);                                     // 77 R-16 dormindo Zzz
  RXT[n++].D(3000).Ar(-9).M(M_WOBBLE, 4, 0.012f).M(M_NOD, 3, 0.012f).Dc(D_TEAR, 120, 200, 255);                           // 78 R-17 rindo ate chorar
  RXT[n++].D(3200).Rb(0.35f).Sc(1.04f).M(M_BOUNCE, 5, 0.012f).M(M_WOBBLE, 5, 0.006f).Dc(D_SPARK, 255, 225, 70);           // 79 R-18 modo festa (cores)
  RXT[n++].D(3000).Gz(0, 0).Sh(4).Tn(150, 255, 170, 0.92f).Pt(30, 160, 70, 1).Sc(1.1f).Ps(1.2f).Ct(0).Ld(0).M(M_BOUNCE, 2, 0.008f).Dc(D_SPARK, 150, 255, 170);   // 80 R-19 olhos de cifrao
  RXT[n++].D(3200).Sh(5).M(M_TILT, 10, 0).M(M_SINK, 6, 0).Wt(3);                                                          // 81 R-20 desmaiou (X X)
  // ---- v9.1: 24 reacoes novas (ids 99..122 = R-21..R-44) + 3 estados do Bluetooth (ids 123..125 = S-01..S-03) ----
  // Aqui fica so a "receita" base (duracao, olhar, palpebras, movimento do rosto). A linha do tempo de cada uma
  // (cores, enfeites, pupilas especiais...) esta em customRx(), ligada pelo .Cu(n). Wt(0) = nunca e sorteada.
  RXT[n++].D(3200).Gz(0, 1).Bd().Ct(0.46f).Ld(-24).Rt(0).Pa(0).M(M_TREMBLE, 1.0f, 0.05f).Cu(1);                    // 82  R-21 raiva com veia
  RXT[n++].D(2800).Gz(4, -9).Ct(0).Ld(0).Ps(0.95f).M(M_TILT, 11, 0).Cu(2);                                         // 83  R-22 ha?
  RXT[n++].D(3600).Gz(0, 0).Ct(0).Ld(0).Cu(3);                                                                     // 84  R-23 ouvindo musica
  RXT[n++].D(3600).Gz(0, -2).Sc(1.06f).Ps(1.3f).Ct(0).Ld(0).M(M_PUPIL, 0.1f, 0.01f).Cu(4);                         // 85  R-24 emocionado
  RXT[n++].D(3400).Gz(0, 0).Ct(0.24f).Ld(-14).M(M_CLOSE, 0.08f, 0).M(M_TILT, 4, 0).Cu(5);                          // 86  R-25 plano maligno
  RXT[n++].D(2400).Gz(0, -1).Ct(0).Ld(0).Wt(4).Cu(6);                                                              // 87  R-26 boom!
  RXT[n++].D(3600).Gz(0, 2).Ct(0).Ld(0).Cu(7);                                                                     // 88  R-27 pegando fogo
  RXT[n++].D(3600).Gz(0, 0).Ps(0.9f).Cu(8);                                                                        // 89  R-28 congelando
  RXT[n++].D(3000).Gz(0, 0).Sc(1.04f).Ct(0).Ld(0).Cu(9);                                                           // 90  R-29 eletrizado
  RXT[n++].D(3800).Gz(0, 8).Ct(0.22f).Ld(12).M(M_SINK, 3, 0).Cu(10);                                               // 91  R-30 dia de chuva
  RXT[n++].D(4200).Gz(0, 3).M(M_SINK, 4, 0).M(M_TILT, 4, 0).Cu(11);                                                // 92  R-31 boa noite
  RXT[n++].D(4200).Gz(0, 0).M(M_TILT, 3, 0).Cu(12);                                                                // 93  R-32 bom dia
  RXT[n++].D(3600).Gz(0, 0).Ct(0).Ld(0).Cu(13);                                                                    // 94  R-33 alvo travado
  RXT[n++].D(3600).Gz(0, 0).Ct(0).Ld(0).Wt(4).Cu(14);                                                              // 95  R-34 carregando
  RXT[n++].D(4200).Gz(0, 0).Ct(0.1f).Cu(15);                                                                       // 96  R-35 modo hacker
  RXT[n++].D(3400).Gz(0, 0).Wt(4).Cu(16);                                                                          // 97  R-36 erro de sistema
  RXT[n++].D(3000).Gz(0, 0).Ct(0).Ld(0).Sc(1.04f).Cu(17);                                                          // 98  R-37 foto!
  RXT[n++].D(4000).Gz(0, 0).Ct(0.08f).Ps(0.9f).Cu(18);                                                             // 99  R-38 radar
  RXT[n++].D(3600).Gz(0, 0).Ct(0).Ld(0).Sc(1.06f).Cu(19);                                                          // 100 R-39 hipnose espiral
  RXT[n++].D(3200).Gz(0, 0).Cu(20);                                                                                // 101 R-40 tontura
  RXT[n++].D(2400).Gz(0, 0).Ct(0).Ld(0).Cu(21);                                                                    // 102 R-41 gelatina
  RXT[n++].D(3600).Gz(0, 0).Ct(0).Ld(0).Cu(22);                                                                    // 103 R-42 zoom
  RXT[n++].D(3600).Gz(0, -2).Sc(1.08f).Ct(0).Ld(0).Cu(23);                                                         // 104 R-43 galaxia nos olhos
  RXT[n++].D(3400).Gz(0, 0).Ct(0).Ld(0).Cu(24);                                                                    // 105 R-44 parabens!
  RXT[n++].D(3600).Gz(0, 0).Wt(0).Cu(25);                                                                          // 106 S-01 bluetooth conectou
  RXT[n++].D(3800).Gz(0, 0).Wt(0).Cu(26);                                                                          // 107 S-02 bluetooth caiu
  RXT[n++].D(4000).Gz(0, 0).Wt(0).Cu(27);                                                                          // 108 S-03 procurando bluetooth
  // ---- v11: 3 reacoes novas (ids 126..128 = R-45..R-47): olhos sorrindo com bochecha curva ----
  RXT[n++].D(3000).Gz(0, 0).Ct(0).Ld(0).Rt(11).Ch(0.55f).M(M_NOD, 1.6f, 0.0040f);                                        // 109 R-45 feliz de bochecha
  RXT[n++].D(3200).Gz(0, -1).Ct(0).Ld(0).Rt(9).Ch(0.85f).M(M_BOUNCE, 3, 0.010f).Dc(D_SPARK, 255, 225, 250);              // 110 R-46 sorrisao
  RXT[n++].D(3000).Gz(0, 0).Ct(0).Ld(0).Rt(12).Ch(0.40f).Hl(1.0f).Sc(1.06f).Ps(1.3f).M(M_PUPIL, 0.12f, 0.009f).Dc(D_SPARK, 255, 230, 245);   // 111 R-47 olhos brilhantes felizes
  // ---- v12: R-48 (id 129) olho verde em cupula -> pisca -> ovais com RAIO balancando -> cupula -> volta pra laranja ----
  RXT[n++].D(7600).Gz(0, 0).Wt(0).Cu(28);                                                                          // 112 R-48 carregando / conectado
  // n tem que ser 113 (NRX)
}

// ---- movimentos do rosto inteiro usados pelas reacoes ----
static void motion(uint8_t m, float a, float f, float t, float d, float e, float sd, uint32_t now, Style &T, Ov &O) {
  float p = clampf(t / d, 0, 1);
  float bump = env(t, d, 0.33f * d, 0.33f * d);
  switch (m) {
    case M_SHAKE:   O.dx += a * e * sinf(t * f); O.rot += 0.5f * a * e * sinf(t * f + 0.5f); break;
    case M_NOD:     O.dy += a * e * sinf(t * f); break;
    case M_TILT:    O.rot += a * sd * e; O.dx += 0.3f * a * sd * e; break;
    case M_WOBBLE:  O.rot += a * e * sinf(t * f); break;
    case M_BOUNCE:  O.dy -= a * e * fabsf(sinf(t * f)); break;
    case M_ZOOMP:   O.zoom *= 1 + a * e * sinf(t * f); break;
    case M_AWAY:    O.zoom *= 1 - a * bump; O.dy -= 8 * bump; break;                       // "indo pra longe"
    case M_CLOSE:   O.zoom *= 1 + a * bump; O.dy += 4 * bump; break;                       // "chegando perto"
    case M_TURN: {                                                                         // cabeca virando (falso 3D)
      float y = a * e * sinf(t * f);
      T.gap *= fmaxf(cosf(y), 0.3f); T.rx *= 0.7f + 0.3f * cosf(y); O.dx += sinf(y) * 22;
      break;
    }
    case M_FLIP:    O.rot += a * sd * fminf(ease(p / 0.25f), ease((1 - p) / 0.25f)); break;   // vira de cabeca pra baixo e volta
    case M_DROP:    O.dy -= a * expf(-t * 0.0011f) * fabsf(sinf(t * f)); break;            // quicando como bola
    case M_TREMBLE: {
      O.dx += a * e * (sinf(t * f) + 0.6f * sinf(t * f * 2.3f + 1.0f));
      O.dy += a * e * 0.7f * sinf(t * f * 1.7f + 2.0f);
      O.rot += a * 0.6f * e * sinf(t * f * 1.3f);
      break;
    }
    case M_SWAY:    O.dx += a * e * sinf(t * f); O.rot += 0.8f * a * e * sinf(t * f); O.dy -= 2 * e * fabsf(sinf(t * f)); break;
    case M_HEART: {
      float q = fmodf(t * f, 1.0f);
      O.zoom *= 1 + a * e * (expf(-q * 9.0f) + 0.5f * expf(-fabsf(q - 0.28f) * 22.0f));
      break;
    }
    case M_FLUTTER: { float q = fmaxf(sinf(t * f), 0); T.squint = fmaxf(T.squint, 0.95f * q * q * q * e); break; }   // piscadas rapidas
    case M_PUPIL:   T.ps *= 1 + a * e * sinf(t * f); break;
    case M_SNEEZE: {
      if (p < 0.55f) { float q = ease(p / 0.55f); O.dy -= 0.55f * a * q; O.zoom *= 1 + 0.03f * q; T.squint = fmaxf(T.squint, 0.25f * q); }
      else if (p < 0.68f) { float q = ease((p - 0.55f) / 0.13f); O.dy += lerpf(-0.55f * a, 0.8f * a, q); T.squint = lerpf(0.25f, 1.0f, q); }
      else { float q = (p - 0.68f) / 0.32f; O.dy += 0.8f * a * (1 - ease(q)); T.squint = fmaxf(T.squint, 1.0f - ease(clampf(q * 1.6f, 0, 1))); }
      break;
    }
    case M_NODOFF: {                                                                       // cochila e acorda com um tranco
      if (p < 0.62f) { float q = ease(p / 0.62f); O.dy += a * q; O.rot += 3 * sd * q; T.squint = fmaxf(T.squint, 0.55f * q); }
      else if (p < 0.72f) { float q = ease((p - 0.62f) / 0.10f); O.dy += lerpf(a, -4, q); T.squint = lerpf(0.55f, 0, q); O.zoom *= 1 + 0.05f * q; }
      else { float q = (p - 0.72f) / 0.28f; O.dy += -4 * (1 - ease(q)); O.zoom *= 1 + 0.05f * (1 - ease(q)); }
      break;
    }
    case M_GLITCH: {
      static uint32_t gNext = 0; static float gdx = 0, gdy = 0, gr = 0, gg = 0, gb = 0; static bool gtint = false;
      if (now >= gNext) {
        gdx = (random(3) == 0) ? 0 : rf(-a, a); gdy = (random(3) == 0) ? 0 : rf(-a * 0.4f, a * 0.4f);
        gr = random(256); gg = random(256); gb = random(256); gtint = random(2); gNext = now + random(50, 140);
      }
      O.dx += gdx * e; O.dy += gdy * e;
      if (gtint) tintStyle(T, gr, gg, gb, 0.7f * e);
      break;
    }
    case M_FALL: {                                                                         // cai pra fora da tela e volta de cima
      if (p < 0.35f) { float q = p / 0.35f; O.dy += 340 * q * q; }
      else if (p < 0.55f) O.dy += 340;
      else { float q = (p - 0.55f) / 0.45f; O.dy += -260 * (1 - ease(q)); }
      break;
    }
    case M_POP: { float u = ease(1.0f - t / f); O.zoom *= 1 + a * u; O.dy -= a * 60 * u; break; }   // pulinho de susto no comeco
    case M_SINK:    O.dy += a * e; O.rot -= 0.8f * (a > 0 ? 1 : -1) * e; break;           // afunda (a>0) ou levanta (a<0)
    case M_HIC: {                                                                          // v9: soluco (pulinho que se repete)
      float q = fmodf(t * f, 1.0f), u = expf(-q * 9.0f);
      O.dy -= a * e * u; O.zoom *= 1 + 0.012f * a * e * u; T.ps *= 1 - 0.18f * e * u;
      break;
    }
    case M_PEEK: {                                                                         // v9: some pra baixo e espia de novo
      float q = (p < 0.42f) ? ease(p / 0.2f) : 1.0f - 0.7f * ease((p - 0.42f) / 0.18f);
      O.dy += a * q; O.zoom *= 1 - 0.06f * q;
      T.squint = fmaxf(T.squint, 0.5f * q * (p < 0.42f ? 1.0f : 0.4f));
      if (p >= 0.42f) O.rot -= 5 * sd * ease((p - 0.42f) / 0.1f);
      break;
    }
    default: break;
  }
}

// ============================ v9.1: LINHA DO TEMPO DAS REACOES NOVAS ============================
// Cada reacao nova (R-21..R-44) e os estados de um disparo so (S-01..S-03) tem uma "linha do tempo" aqui:
// p = 0..1 (quanto da reacao ja passou), e = envelope suave de entrada/saida. Os numeros sao as fases das cartelas.
static inline float rmp(float p, float a, float b) { return ease((p - a) / (b - a)); }   // rampa suave 0..1 entre a e b
static void pupTint(Style &T, float r, float g, float b, float k) {                         // cor da pupila (os dois olhos)
  k = clampf(k, 0, 1);
  T.pr = lerpf(T.pr, r, k); T.pg = lerpf(T.pg, g, k); T.pb = lerpf(T.pb, b, k);
  T.pr2 = lerpf(T.pr2, r, k); T.pg2 = lerpf(T.pg2, g, k); T.pb2 = lerpf(T.pb2, b, k);
}
static void decoCol(uint8_t r, uint8_t g, uint8_t b) { gDeco.cr = r; gDeco.cg = g; gDeco.cb = b; }

static bool gCharging = false;                    // v12: true enquanto esta carregando (CHARGE_PIN ou comando 0x0B)
static const float GRN_R = 0, GRN_G = 170, GRN_B = 0;             // verde do video
static const float ORG_R = 229, ORG_G = 63, ORG_B = 23;           // laranja do video (pupila do verde / raio)
static void chargeLook(Style &T, float k) {       // v12: deixa o rosto VERDE com pupila laranja (k 0..1); ao soltar volta pelas cores do rosto (passa por ambar)
  tintStyle(T, GRN_R, GRN_G, GRN_B, k); pupTint(T, ORG_R, ORG_G, ORG_B, k);
}
static float pulse01(float p, float a, float b, float c) {   // sobe de a a b, desce de b a c (0..1..0)
  return fminf(ease((p - a) / (b - a)), ease((c - p) / (c - b)));
}

static void customRx(uint8_t cu, float t, float d, float e, float sd, uint32_t now, Style &T, Ov &O, const Style &H) {
  float p = clampf(t / d, 0, 1);
  switch (cu) {
    case 1: {                                                  // R-21 Raiva com veia: franze, vermelho, veia, vapor
      tintStyle(T, 255, 45, 90, 0.7f * rmp(p, 0.12f, 0.40f) * e);
      gDeco.vein = rmp(p, 0.14f, 0.34f) * e;
      gDeco.steam = rmp(p, 0.38f, 0.62f) * (1.0f - rmp(p, 0.88f, 1.0f)) * e;
      break;
    }
    case 2: {                                                  // R-22 Ha?: inclina, olha pra cima, interrogacao cresce
      gDeco.quest = rmp(p, 0.16f, 0.30f) * e; gDeco.questS = 0.25f + 0.75f * rmp(p, 0.20f, 0.80f);
      gDeco.quest2 = rmp(p, 0.68f, 0.82f) * e;
      T.rx *= 1.0f + 0.05f * rmp(p, 0.4f, 0.7f); T.ry *= 1.0f + 0.05f * rmp(p, 0.4f, 0.7f);
      break;
    }
    case 3: {                                                  // R-23 Ouvindo musica: ^ ^, balanca, notas sobem
      T.arc = rmp(p, 0.12f, 0.34f) * e; T.bend = -9; morphTau = 160;
      float sw = rmp(p, 0.30f, 0.46f) * e;
      O.rot += 8.0f * sw * sinf(t * 0.0058f); O.dy += 2.0f * sw * sinf(t * 0.0116f);
      gDeco.notes = rmp(p, 0.22f, 0.36f) * (1.0f - rmp(p, 0.92f, 1.0f)) * e;
      break;
    }
    case 4: {                                                  // R-24 Emocionado: olhao, marejado, lagrimas, sorri chorando
      T.hl = rmp(p, 0.0f, 0.15f) * e;
      T.wet = rmp(p, 0.18f, 0.50f) * (1.0f - 0.25f * rmp(p, 0.8f, 1.0f)) * e;
      gDeco.tear = rmp(p, 0.46f, 0.62f) * e;
      float sm = rmp(p, 0.66f, 0.80f) * e;
      T.cheek = 0.45f * sm; T.ry *= 1.0f - 0.10f * sm; T.rot = lerpf(T.rot, H.rot * 0.6f, sm);
      gDeco.spark = sm * 0.9f; decoCol(255, 225, 250);
      O.dy += 2.0f * sm * sinf(t * 0.012f);
      break;
    }
    case 5: {                                                  // R-25 Plano maligno: roxo, estreita, pupila vira fenda, mwahaha
      float k = rmp(p, 0.10f, 0.40f);
      tintStyle(T, 205, 45, 205, 0.9f * k * e);
      pupTint(T, 252, 225, 190, k * e);
      T.pSlit = rmp(p, 0.22f, 0.46f) * e;
      T.cutBot += 0.14f * rmp(p, 0.40f, 0.60f) * e;
      gDeco.spark = rmp(p, 0.62f, 0.80f) * e; decoCol(150, 60, 235);
      break;
    }
    case 6: {                                                  // R-26 Boom!: arregala, raios explodem em volta, depois some (eco)
      float u = (t > 0.14f * d) ? ease(1.0f - (t - 0.14f * d) / 260.0f) : 0.0f;
      float big = rmp(p, 0.14f, 0.20f) * (1.0f - rmp(p, 0.55f, 0.70f));
      T.rx *= 1.0f + 0.20f * big; T.ry *= 1.0f + 0.20f * big; T.ps *= 1.0f - 0.5f * big;
      T.cutTop = 0; T.lid = 0;
      O.zoom *= 1.0f + 0.12f * u; O.dy -= 7.0f * u; O.dx += 2.2f * big * sinf(t * 0.09f);
      float eco = rmp(p, 0.55f, 0.80f);
      tintStyle(T, 255, 170, 200, 0.55f * eco * e);
      gDeco.burst = rmp(p, 0.14f, 0.20f) * (1.0f - rmp(p, 0.62f, 0.92f)) * e; gDeco.burstR = rmp(p, 0.14f, 0.50f);
      decoCol((uint8_t)lerpf(255, 150, eco), (uint8_t)lerpf(235, 140, eco), (uint8_t)lerpf(90, 95, eco));
      break;
    }
    case 7: {                                                  // R-27 Pegando fogo: esquenta, laranja, queima, inferno
      float h = rmp(p, 0.05f, 0.75f), c2 = rmp(p, 0.40f, 0.80f);
      tintStyle(T, 255.0f, lerpf(125, 55, c2), lerpf(110, 30, c2), 0.88f * rmp(p, 0.05f, 0.35f) * e);
      pupTint(T, 255, 235, 70, rmp(p, 0.05f, 0.30f) * e);
      float lk = rmp(p, 0.45f, 0.72f) * e;
      T.cutTop = lerpf(T.cutTop, 0.24f, lk); T.lid = lerpf(T.lid, -16.0f, lk);
      gDeco.fire = rmp(p, 0.10f, 0.40f) * e; gDeco.fireH = 0.3f + 0.7f * rmp(p, 0.20f, 0.80f);
      O.dx += 1.0f * h * sinf(t * 0.06f) * e;
      break;
    }
    case 8: {                                                  // R-28 Congelando: azul gelo, treme, neve, congela com rachaduras
      float cold = rmp(p, 0.05f, 0.50f), fz = rmp(p, 0.62f, 0.86f);
      tintStyle(T, 150, 205, 255, 0.7f * cold * e);
      tintStyle(T, 215, 235, 255, 0.7f * fz * e);
      pupTint(T, 195, 210, 230, fz * e);
      T.ice = fz * e; T.pa *= 1.0f - 0.5f * fz;
      float shiv = (1.0f + 4.0f * cold) * (1.0f - rmp(p, 0.60f, 0.70f));
      O.dx += 0.55f * shiv * sinf(t * 0.075f) * e; O.rot += 0.8f * shiv * sinf(t * 0.061f + 0.7f) * e;
      gDeco.snow = rmp(p, 0.10f, 0.30f) * e;
      break;
    }
    case 9: {                                                  // R-29 Eletrizado: amarelo, pupila minuscula, raios, rosto vibrando
      float k = rmp(p, 0.08f, 0.28f);
      tintStyle(T, 255, 228, 70, 0.85f * k * e);
      pupTint(T, 255, 150, 70, k * e);
      T.ps *= 1.0f - 0.55f * k;
      gDeco.bolt = rmp(p, 0.10f, 0.22f) * (1.0f - rmp(p, 0.90f, 1.0f)) * e;
      O.dx += 2.4f * k * e * (sinf(t * 0.11f) + 0.5f * sinf(t * 0.27f)); O.dy += 1.2f * k * e * sinf(t * 0.13f + 1.0f);
      gDeco.spark = rmp(p, 0.55f, 0.70f) * 0.8f * e; decoCol(255, 240, 120);
      break;
    }
    case 10: {                                                 // R-30 Dia de chuva: olha pra baixo, nuvem, chuva, olhos marejados
      tintStyle(T, 120, 100, 235, 0.55f * rmp(p, 0.08f, 0.30f) * e);
      T.wet = 0.85f * rmp(p, 0.62f, 0.92f) * e;
      gDeco.cloud = rmp(p, 0.05f, 0.22f) * e; gDeco.rain = rmp(p, 0.14f, 0.32f) * e;
      gDeco.tear = rmp(p, 0.80f, 0.92f) * 0.8f * e;
      break;
    }
    case 11: {                                                 // R-31 Boa noite: sono, escurece, fecha u u, lua + estrelas + Zzz
      float a1 = rmp(p, 0.05f, 0.50f);
      T.dim = 0.5f * a1 * e;
      T.squint = 0.62f * rmp(p, 0.12f, 0.40f) * (1.0f - rmp(p, 0.40f, 0.50f)) * e;
      T.arc = rmp(p, 0.40f, 0.60f) * e; T.bend = 9; morphTau = 200;
      tintStyle(T, 150, 70, 170, 0.5f * a1 * e);
      gDeco.moon = rmp(p, 0.50f, 0.70f) * e;
      gDeco.spark = rmp(p, 0.56f, 0.76f) * 0.8f * e; decoCol(255, 235, 120);
      gDeco.z = rmp(p, 0.68f, 0.84f) * e;
      break;
    }
    case 12: {                                                 // R-32 Bom dia: dorme, o sol nasce no topo, abre os olhos brilhantes
      T.arc = (1.0f - rmp(p, 0.28f, 0.44f)) * e; T.bend = 9; morphTau = 180;
      T.squint = 0.7f * rmp(p, 0.30f, 0.46f) * (1.0f - rmp(p, 0.50f, 0.70f)) * e;
      T.dim = 0.4f * (1.0f - rmp(p, 0.10f, 0.62f)) * e;
      float op = rmp(p, 0.72f, 0.90f) * e;
      T.rx *= 1.0f + 0.08f * op; T.ry *= 1.0f + 0.08f * op;
      gDeco.sun = e; gDeco.sunP = rmp(p, 0.04f, 0.55f);
      gDeco.spark = rmp(p, 0.80f, 0.90f) * e; decoCol(255, 225, 90);
      break;
    }
    case 13: {                                                 // R-33 Alvo travado: vigia, mira vermelha, cantoneiras fecham, TRAVOU
      float s1 = rmp(p, 0.18f, 0.30f), lock = rmp(p, 0.70f, 0.80f);
      goX = 10.0f * sinf(t * 0.0065f) * (1.0f - s1) * e; goY = 0;
      T.pCross = rmp(p, 0.20f, 0.32f) * e; pupTint(T, 255, 225, 190, T.pCross);
      tintStyle(T, 255, 55, 90, (0.35f * rmp(p, 0.20f, 0.40f) + 0.50f * rmp(p, 0.40f, 0.80f)) * e);
      T.cutTop = lerpf(T.cutTop, 0.18f, rmp(p, 0.40f, 0.60f) * e);
      gDeco.brk = rmp(p, 0.16f, 0.28f) * e; gDeco.brkK = rmp(p, 0.28f, 0.80f);
      gDeco.br = (uint8_t)lerpf(255, 255, lock); gDeco.bg = (uint8_t)lerpf(70, 255, lock); gDeco.bb = (uint8_t)lerpf(90, 255, lock);
      O.dx += 1.6f * lock * (1.0f - rmp(p, 0.84f, 0.92f)) * sinf(t * 0.1f);
      break;
    }
    case 14: {                                                 // R-34 Carregando: encolhe, vira dois circulos girando + 3 pontinhos
      float sh = rmp(p, 0.10f, 0.26f) * (1.0f - rmp(p, 0.86f, 0.96f));
      T.rx *= 1.0f - 0.58f * sh; T.ry *= 1.0f - 0.50f * sh; T.ps *= 1.0f - 0.55f * sh;
      float tail = 1.0f - rmp(p, 0.86f, 0.92f);
      T.ld = rmp(p, 0.26f, 0.36f) * tail * e;
      gDeco.dots = rmp(p, 0.30f, 0.40f) * tail * e; decoCol(215, 218, 230);
      morphTau = 70;
      break;
    }
    case 15: {                                                 // R-35 Modo hacker: liga, codigo cai, verde, varredura, invade
      float gk = rmp(p, 0.14f, 0.46f), neon = rmp(p, 0.62f, 0.84f);
      float cr = lerpf(168, lerpf(40, 0, neon), gk), cg = lerpf(158, lerpf(225, 255, neon), gk), cb = lerpf(185, lerpf(110, 90, neon), gk);
      tintStyle(T, cr, cg, cb, 0.95f * rmp(p, 0.02f, 0.12f) * e);
      pupTint(T, 4, 44, 16, rmp(p, 0.06f, 0.22f) * e);
      gDeco.code = rmp(p, 0.0f, 0.14f) * e;
      gDeco.scan = rmp(p, 0.40f, 0.52f) * e; gDeco.scanY = 52.0f + 128.0f * (0.5f + 0.5f * sinf(t * 0.0042f));
      decoCol(70, 255, 140);
      break;
    }
    case 16: {                                                 // R-36 Erro de sistema: falha, aviso, X X, glitch
      float er1 = rmp(p, 0.12f, 0.26f);
      tintStyle(T, 255, 20, 100, 0.92f * er1 * e);
      T.ps *= 1.0f - 0.4f * er1;
      gDeco.warn = rmp(p, 0.16f, 0.26f) * (1.0f - rmp(p, 0.92f, 1.0f)) * e;
      T.xEye = rmp(p, 0.50f, 0.58f) * (1.0f - rmp(p, 0.74f, 0.80f)) * e;
      float gl = rmp(p, 0.76f, 0.82f) * (1.0f - rmp(p, 0.94f, 1.0f));
      T.squint = fmaxf(T.squint, 0.55f * gl);
      gDeco.glitchL = gl * e;
      if (p < 0.14f) motion(M_GLITCH, 4, 0, t, d, e, sd, now, T, O);
      else if (p > 0.74f) motion(M_GLITCH, 8, 0, t, d, e, sd, now, T, O);
      break;
    }
    case 17: {                                                 // R-37 Foto!: enquadra, foca, trava (verde), CLIQUE (flash branco)
      float gr = rmp(p, 0.44f, 0.52f);
      gDeco.brk = rmp(p, 0.04f, 0.14f) * (1.0f - rmp(p, 0.66f, 0.70f)) * e; gDeco.brkK = rmp(p, 0.10f, 0.50f);
      gDeco.br = (uint8_t)lerpf(175, 110, gr); gDeco.bg = (uint8_t)lerpf(175, 255, gr); gDeco.bb = (uint8_t)lerpf(185, 140, gr);
      gDeco.focus = rmp(p, 0.50f, 0.56f) * (1.0f - rmp(p, 0.66f, 0.70f)) * e;
      if (p > 0.18f && p < 0.50f) T.ps *= 1.0f + 0.28f * sinf((p - 0.18f) * 17.0f) * e;
      float cl = rmp(p, 0.64f, 0.70f) * (1.0f - rmp(p, 0.86f, 0.97f));
      T.squint = fmaxf(T.squint, 0.95f * cl);
      gFlash = (p >= 0.70f) ? (1.0f - rmp(p, 0.72f, 0.90f)) : 0.0f;
      morphTau = 60;
      break;
    }
    case 18: {                                                 // R-38 Radar: varre de lado a lado, ondas de sonar, acha um alvo
      tintStyle(T, 195, 110, 235, 0.55f * rmp(p, 0.05f, 0.20f) * e);
      float found = rmp(p, 0.76f, 0.86f);
      goX = (9.0f * sinf(t * 0.0042f) * (1.0f - found) + 9.0f * found) * e; goY = -6.0f * found * e;
      gDeco.sonar = rmp(p, 0.06f, 0.16f) * e; gDeco.sonarM = 116; gDeco.sr = 40; gDeco.sg = 222; gDeco.sb = 240;
      gDeco.blip = found * e;
      break;
    }
    case 19: {                                                 // R-39 Hipnose espiral: olho clareia, pupila vira espiral que gira
      float k = rmp(p, 0.05f, 0.24f);
      tintStyle(T, 255, 172, 226, 0.88f * k * e);
      pupTint(T, 88, 14, 120, k * e);
      T.pSpiral = k * e;
      O.rot += 4.0f * sinf(t * 0.0035f) * e; O.dx += 2.0f * sinf(t * 0.0023f) * e;
      break;
    }
    case 20: {                                                 // R-40 Tontura: pupilas rodando, cabeca bamba, estrelinhas em volta
      goX = 8.0f * cosf(t * 0.012f) * e; goY = 6.5f * sinf(t * 0.012f) * e;
      float wob = sinf(t * 0.0085f);
      O.rot += 11.0f * wob * e; O.dx += 4.0f * sinf(t * 0.0085f + 1.2f) * e;
      T.scL = 1.0f - 0.10f * wob * e; T.scR = 1.0f + 0.10f * wob * e;
      T.squint += 0.08f * e;
      gDeco.orbit = rmp(p, 0.05f, 0.18f) * e;
      break;
    }
    case 21: {                                                 // R-41 Gelatina: estica e achata (squash & stretch) e vai assentando
      float amp = 1.25f * expf(-t / 820.0f) * rmp(t, 0.0f, 120.0f);
      float s = amp * cosf(t * 0.0115f - 0.4f);
      float sx = clampf(1.0f - 0.30f * s, 0.55f, 1.55f), sy = clampf(1.0f + 0.36f * s, 0.50f, 1.60f);
      T.rx *= sx; T.ry *= sy; T.prx *= sx; T.pry *= sy;
      O.dy -= 5.0f * s * e;
      tintStyle(T, 255, 40, 160, 0.5f * e); pupTint(T, 120, 225, 255, e);
      morphTau = 28;
      break;
    }
    case 22: {                                                 // R-42 Zoom: um olho cresce e o outro encolhe, troca, e os dois focam juntos
      float a = rmp(p, 0.08f, 0.30f), b = rmp(p, 0.48f, 0.70f), c = rmp(p, 0.78f, 0.92f);
      float L = lerpf(lerpf(lerpf(1.0f, 1.40f, a), 0.62f, b), 1.22f, c);
      float R = lerpf(lerpf(lerpf(1.0f, 0.60f, a), 1.40f, b), 1.22f, c);
      T.scL = 1.0f + (L - 1.0f) * e; T.scR = 1.0f + (R - 1.0f) * e;
      gDeco.spark = rmp(p, 0.84f, 0.94f) * e; decoCol(255, 255, 255);
      morphTau = 90;
      break;
    }
    case 23: {                                                 // R-43 Galaxia nos olhos: ceu roxo com nebulosa e estrelinhas que cintilam
      float k = rmp(p, 0.08f, 0.36f);
      tintStyle(T, 62, 30, 150, 0.93f * k * e);
      T.gal = k * e;
      gDeco.spark = rmp(p, 0.30f, 0.50f) * 0.9f * e; decoCol(170, 100, 255);
      break;
    }
    case 24: {                                                 // R-44 Parabens!: fecha os olhos ^ ^, balanca feliz, confete cai
      T.arc = rmp(p, 0.18f, 0.36f) * e; T.bend = -9; morphTau = 160;
      float sw = rmp(p, 0.30f, 0.44f) * e;
      O.rot += 8.0f * sw * sinf(t * 0.0068f); O.dy += 3.0f * sw * sinf(t * 0.0136f);
      gDeco.confetti = rmp(p, 0.02f, 0.14f) * (1.0f - rmp(p, 0.90f, 1.0f)) * e;
      break;
    }
    case 25: {                                                 // S-01 Bluetooth conectou: dormindo -> simbolo -> pulso azul -> feliz
      float wake = rmp(p, 0.14f, 0.38f);
      T.dim = 0.55f * (1.0f - wake); T.squint = fmaxf(T.squint, 0.5f * (1.0f - wake));
      tintStyle(T, 160, 60, 190, 0.45f * rmp(p, 0.18f, 0.34f) * (1.0f - rmp(p, 0.40f, 0.50f)));
      tintStyle(T, 205, 85, 225, 0.30f * rmp(p, 0.40f, 0.50f) * (1.0f - rmp(p, 0.66f, 0.78f)));
      gDeco.bt = rmp(p, 0.16f, 0.28f) * (1.0f - 0.45f * rmp(p, 0.66f, 0.80f)) * (1.0f - rmp(p, 0.95f, 1.0f));
      gDeco.sonar = rmp(p, 0.38f, 0.44f) * (1.0f - rmp(p, 0.66f, 0.76f)); gDeco.sonarM = 92; gDeco.sr = 60; gDeco.sg = 120; gDeco.sb = 255;
      float hp = rmp(p, 0.68f, 0.82f) * (1.0f - rmp(p, 0.94f, 1.0f));
      T.arc = hp; T.bend = -9; morphTau = 130;
      tintStyle(T, 255, 70, 190, 0.25f * hp);
      gDeco.spark = rmp(p, 0.62f, 0.76f) * (1.0f - rmp(p, 0.92f, 1.0f)); decoCol(170, 210, 255);
      break;
    }
    case 26: {                                                 // S-02 Bluetooth caiu: estranha -> simbolo riscado -> olhos cinzas -> triste
      float st = rmp(p, 0.16f, 0.30f), dull = rmp(p, 0.38f, 0.58f), sad = rmp(p, 0.64f, 0.80f);
      float fade = 1.0f - rmp(p, 0.93f, 1.0f);
      gDeco.bt = fade; gDeco.btDim = dull; gDeco.btSlash = rmp(p, 0.18f, 0.30f);
      T.rx *= 1.0f + 0.07f * st * (1.0f - dull); T.ry *= 1.0f + 0.07f * st * (1.0f - dull);
      T.ps *= 1.0f - 0.25f * st * (1.0f - dull);
      goY = -6.0f * st * (1.0f - dull);
      tintStyle(T, 170, 95, 175, 0.5f * dull);
      T.cutTop = lerpf(T.cutTop, 0.28f, dull); T.lid = lerpf(T.lid, 10.0f, dull);
      tintStyle(T, 140, 60, 170, 0.5f * sad);
      T.cutTop = lerpf(T.cutTop, 0.40f, sad); T.lid = lerpf(T.lid, 14.0f, sad);
      T.dim = 0.3f * sad; T.py += 4.0f * sad;
      O.dy += 3.0f * sad; O.rot -= 5.0f * sd * sad;
      break;
    }
    case 27: {                                                 // S-03 Procurando Bluetooth: olha pros lados, simbolo emite ondinhas
      tintStyle(T, 225, 90, 215, 0.35f * e);
      goX = 9.0f * sinf(t * 0.0030f) * e; goY = -1.0f * e;
      gDeco.bt = e; gDeco.btWaves = rmp(p, 0.06f, 0.16f) * e;
      O.rot += 3.0f * sinf(t * 0.0030f + 1.0f) * e;
      break;
    }
    case 28: {                                                 // v12 R-48 Carregando / Conectado (verde + raio), medido nos quadros 311-591 do video
      float endK = gCharging ? 1.0f : 1.0f - rmp(p, 0.90f, 1.0f);                  // no fim volta pro laranja (verde -> ambar -> laranja)
      chargeLook(T, rmp(p, 0.0f, 0.07f) * endK);
      morphTau = 90;
      float sh = rmp(p, 0.235f, 0.30f) * (1.0f - rmp(p, 0.80f, 0.86f));           // 0 = cupula | 1 = ovais do raio
      float bolt = sh * (1.0f - rmp(p, 0.50f, 0.515f) * (1.0f - rmp(p, 0.60f, 0.615f)));   // o raio some um instante e vira oval (quadros 455-481)
      float lid = fmaxf(pulse01(p, 0.215f, 0.240f, 0.285f), pulse01(p, 0.795f, 0.820f, 0.865f));   // 2 piscadas: antes e depois do raio
      gLidX = fmaxf(gLidX, lid);
      float ov = sh * (1.0f - bolt);                                                // pupila oval inclinada
      T.cutBot = lerpf(0.20f, 0.0f, sh); T.cutTop = lerpf(H.cutTop, 0.0f, sh);
      T.rx = H.rx * lerpf(1.0f, 0.90f, sh); T.ry = H.ry * lerpf(1.0f, 1.30f, sh);
      T.rot = lerpf(H.rot, 3.0f, sh); T.lid = lerpf(H.lid, 0.0f, sh);
      T.pBolt = bolt;
      T.prx = H.prx * (1.0f - 0.50f * ov); T.pry = H.pry * (1.0f + 1.10f * ov); T.prot = -14.0f * ov; T.px = H.px * (1.0f - 0.5f * sh);
      float sw = sinf(t * 0.0026f);
      O.rot += 19.0f * sh * sw; O.dx += 5.0f * sh * sinf(t * 0.0026f + 0.8f);       // balanca e inclina a cabeca
      T.scL = 1.0f + 0.13f * sh * sinf(t * 0.0026f + 0.6f); T.scR = 1.0f - 0.13f * sh * sinf(t * 0.0026f + 0.6f);   // um olho de perto, outro de longe
      float lk = (1.0f - sh) * rmp(p, 0.06f, 0.14f) * (1.0f - rmp(p, 0.20f, 0.23f));
      goX += 7.0f * sinf(t * 0.0042f) * lk;                                         // na cupula verde ele olha de um lado pro outro
      break;
    }
    default: break;
  }
}

static void applyRx(const Rx &r, float t, float d, float e, float sd, uint32_t now, Style &T, Ov &O, const Style &H) {
  T = H;
  if (r.cT > UNSET) T.cutTop = lerpf(H.cutTop, r.cT, e);
  if (r.cB > UNSET) T.cutBot = lerpf(H.cutBot, r.cB, e);
  if (r.lid > UNSET) T.lid = lerpf(H.lid, r.lid, e);
  if (r.rot > UNSET) T.rot = lerpf(H.rot, r.rot, e);
  T.squint = r.sq * e;
  T.ps = H.ps * lerpf(1, r.ps, e);
  float sc = lerpf(1, r.sc, e); T.rx = H.rx * sc; T.ry = H.ry * sc;
  T.conv = lerpf(H.conv, r.cv, e);
  T.pa = H.pa * lerpf(1, r.pa, e);
  T.py += r.py * e; T.px += r.px * e;
  if (r.band) { T.band = 110; T.bOy = 12 * KS; T.bRx = 28 * KS; T.bRy = 12 * KS; }
  if (r.arc) { T.arc = 1; T.bend = r.bend; morphTau = 160; }
  if (r.wink) {
    float p = t / d; morphTau = 60;
    if (r.wink == 1) { if (p > 0.25f && p < 0.60f) { if (sd > 0) T.winkR = 1; else T.winkL = 1; } }
    else { if (p > 0.15f && p < 0.40f) T.winkL = 1; if (p > 0.55f && p < 0.80f) T.winkR = 1; }
  }
  if (r.tk > 0) tintStyle(T, r.tr, r.tg, r.tb, r.tk * e);
  if (r.chv > 0) T.cheek = r.chv * e;                                                     // v11: bochecha curva
  if (r.hlv > 0) T.hl = r.hlv * e;                                                        // v11: brilho na pupila
  if (r.ptk > 0) {                                                                         // v9: cor da pupila
    float k = r.ptk * e;
    T.pr = lerpf(T.pr, r.ptr, k); T.pg = lerpf(T.pg, r.ptg, k); T.pb = lerpf(T.pb, r.ptb, k);
    T.pr2 = lerpf(T.pr2, r.ptr, k); T.pg2 = lerpf(T.pg2, r.ptg, k); T.pb2 = lerpf(T.pb2, r.ptb, k);
  }
  T.pSlit = (r.sh == 1) ? e : 0; T.pHeart = (r.sh == 2) ? e : 0; T.pStar = (r.sh == 3) ? e : 0;   // v9: formas especiais
  T.pDollar = (r.sh == 4) ? e : 0; T.xEye = (r.sh == 5) ? e : 0;
  if (r.rb > 0) {                                                                          // v9: modo festa (olhos mudando de cor)
    float a1, b1, c1, a2, b2, c2, a3, b3, c3, a4, b4, c4;
    T.gA = lerpf(T.gA, 0, e);
    hsv2rgb(t * r.rb, a1, b1, c1); hsv2rgb(t * r.rb + 150.0f, a2, b2, c2);
    hsv2rgb(t * r.rb + 180.0f, a3, b3, c3); hsv2rgb(t * r.rb + 330.0f, a4, b4, c4);
    T.er = lerpf(T.er, a1, e); T.eg = lerpf(T.eg, b1, e); T.eb = lerpf(T.eb, c1, e);
    T.er2 = lerpf(T.er2, a2, e); T.eg2 = lerpf(T.eg2, b2, e); T.eb2 = lerpf(T.eb2, c2, e);
    T.pr = lerpf(T.pr, lerpf(a3, 255, 0.35f), e); T.pg = lerpf(T.pg, lerpf(b3, 255, 0.35f), e); T.pb = lerpf(T.pb, lerpf(c3, 255, 0.35f), e);
    T.pr2 = lerpf(T.pr2, lerpf(a4, 255, 0.35f), e); T.pg2 = lerpf(T.pg2, lerpf(b4, 255, 0.35f), e); T.pb2 = lerpf(T.pb2, lerpf(c4, 255, 0.35f), e);
    morphTau = 70;
  }
  if (r.boot) {                                                                            // v9: reiniciando (fecha, tela branca de boot, volta)
    float p = t / d; morphTau = 70;
    if (p < 0.25f) T.squint = 0.95f * ease(p / 0.12f);
    else if (p < 0.70f) { T.squint = 0; T.pa = 0; tintStyle(T, 210, 235, 255, 0.75f); }
    else { float q = ease((p - 0.70f) / 0.15f); T.squint = 0; T.pa = H.pa * q; tintStyle(T, 210, 235, 255, 0.75f * (1 - q)); }
    gDeco.dots = (p < 0.70f) ? e : 0; gDeco.cr = r.dr; gDeco.cg = r.dg; gDeco.cb = r.db;
  }
  if (r.deco && !r.boot) {                                                                 // v9: enfeites
    if (r.deco & D_SPARK) gDeco.spark = e;
    if (r.deco & D_HEART) gDeco.heart = e;
    if (r.deco & D_TEAR)  gDeco.tear = e;
    if (r.deco & D_Z)     gDeco.z = e;
    if (r.deco & D_SWEAT) gDeco.sweat = e;
    if (r.deco & D_BULB)  gDeco.bulb = e;
    if (r.deco & D_SCAN)  gDeco.scan = e;
    if (r.deco & D_DOTS)  gDeco.dots = e;
    if (r.deco & D_BANG)  gDeco.bang = e;
    gDeco.cr = r.dr; gDeco.cg = r.dg; gDeco.cb = r.db;
  }
  switch (r.gm) {                                                                          // movimento dos olhos
    case G_CIRCLE: goX = r.ga * cosf(t * r.gf) * e; goY = 0.8f * r.ga * sinf(t * r.gf) * e; break;
    case G_SCAN:   goX = r.ga * sinf(t * r.gf) * e; break;
    case G_VSCAN:  goY = r.ga * sinf(t * r.gf) * e; break;
    case G_SPIRAL: { float A = r.ga * expf(-t * 0.0009f); goX = A * cosf(t * r.gf); goY = 0.8f * A * sinf(t * r.gf); break; }
    case G_DART: {
      static uint32_t nd = 0; static float dX = 0, dY = 0;
      if (now >= nd) { dX = rf(-1, 1) * r.ga; dY = rf(-1, 1) * r.ga * 0.7f; nd = now + random(160, 420); }
      goX = dX * e; goY = dY * e; break;
    }
    default: break;
  }
  if (r.deco & D_SCAN) gDeco.scanY = 120.0f + goY * 4.0f;                                   // v9: linha de varredura acompanha o olhar
  motion(r.m1, r.a1, r.f1, t, d, e, sd, now, T, O);
  motion(r.m2, r.a2, r.f2, t, d, e, sd, now, T, O);
  if (r.cu) customRx(r.cu, t, d, e, sd, now, T, O, H);                                     // v9.1: linha do tempo propria (R-21..R-44, S-01..S-03)
}

// ---- reacoes do v5 (ids 1..15), agora usando as cores do rosto atual ----
static void setSurprise(Style &T, const Style &H) {      // olho arregalado, pupila pequena (antes era o AMARELO)
  T = H; T.cutTop = 0; T.cutBot = 0; T.lid = 0; T.rot = 3; T.rx = H.rx * 1.12f; T.ry = H.ry * 1.12f;
  T.ps = 0.62f; T.py = H.py * 0.45f; T.px = H.px * 0.3f; T.prot = 0;
}
static void setAngry(Style &T, const Style &H, float cut, float lid) {   // olho bravo: palpebra reta + brilho embaixo, sem pupila
  T = H; T.cutTop = cut; T.lid = lid; T.rot = 0; T.rx = H.rx * 1.09f; T.ry = H.ry * 0.77f; T.pa = 0;
  T.band = 110; T.bOy = 12 * KS; T.bRx = 28 * KS; T.bRy = 12 * KS;
}

// v7: reacoes CALMAS "pestanejam" ao comecar e ao terminar, para a troca de expressao nao dar um tranco.
// (susto, cambalhota, troca de rosto, glitch, olho fechado ^ ^ etc. ja tem a propria transicao e ficam de fora)
static bool softEdge(Act a) {
  if (a == A_SURPRISE || a == A_SPIN || a == A_MORPH || a == A_SLEEPY || a == A_YAWN || a == A_LAUGH || a == A_WINK || a == ACT_CHARGE) return false;
  if (a >= A_RX0 && a < A_COUNT) {
    int i = a - A_RX0;
    if (i >= 82 && i < 109) {                                   // v9.1: as que tem a propria transicao (olho fechado, susto, glitch, flash...) nao pestanejam
      int cu = i - 81;
      return !(cu == 3 || cu == 6 || cu == 11 || cu == 12 || cu == 14 || cu == 16 || cu == 17 || cu == 21 || cu == 24 || cu == 25);
    }
    if (RXT[i].arc) return false;
    if (i == 8 || i == 13 || i == 14 || i == 22 || i == 31 || i == 32 || i == 40 || i == 43 || i == 49 || i == 53 || i == 60 ||
        i == 71 || i == 72 || i == 73 || i == 81) return false;   // v9: soluco, reiniciando, espiando e X X tem a propria transicao
  }
  return true;
}

static void startAction(Act a, uint32_t now) {
  if (softEdge(a) && !blinkOn) startBlink(now);
  act = a; lastAct = a; actT0 = now; actSide = rsign(); gazeLock = true;
  switch (a) {
    case A_GRIN:     actDur = random(2200, 3800); gazeLock = false; break;
    case A_SMIRK:    actDur = random(1800, 3000); gazeTo(actSide * LOOK_X * 0.8f, -2, now); break;
    case A_THINK:    actDur = random(2400, 3600); gazeTo(actSide * LOOK_X * 0.7f, -LOOK_Y, now); break;
    case A_YAWN:     actDur = 2600; gazeTo(0, 2, now); break;
    case A_LAUGH:    actDur = random(2200, 3200); gazeTo(0, 0, now); break;
    case A_SAD:      actDur = random(2400, 3600); gazeTo(0, LOOK_Y * 0.9f, now); break;
    case A_SURPRISE: actDur = random(1100, 1700); gazeTo(0, 0, now); break;
    case A_SPIN:     spinDir = rsign(); spinTurns = (random(100) < 15) ? 2 : 1;
                     actDur = 420 + (spinTurns == 1 ? 1300 : 1900) + 1100 + 650; gazeTo(0, 0, now); break;
    case A_NO:       actDur = 1800; gazeTo(0, 0, now); break;
    case A_YES:      actDur = 1900; gazeTo(0, 0, now); break;
    case A_CURIOUS:  actDur = random(2200, 3200); gazeTo(actSide * LOOK_X * 0.6f, -LOOK_Y * 0.4f, now); break;
    case A_WINK:     actDur = 1400; gazeTo(0, 0, now); break;
    case A_CROSS:    actDur = 1900; gazeTo(0, 0, now); break;
    case A_MUMBLE:   actDur = random(2200, 3400); gazeLock = false; nextMum = 0; break;
    case A_SLEEPY:   actDur = 3200; gazeTo(0, 3, now); break;
    case A_MORPH: {                                                      // treme, faz puff e troca de rosto
      actDur = MORPH_SMOKE ? 3300 : 1700; gazeTo(0, 0, now); morphSwapped = false;
      do { morphTo = random(NFACES); } while (morphTo == baseSt);
      nextMorph = now + actDur + random(MORPH_MIN, MORPH_MAX);
      break;
    }
    default:
      if (a >= A_RX0 && a < A_COUNT) {
        const Rx &r = RXT[a - A_RX0];
        actDur = r.dur + random(0, 400);
        if (r.gm == G_FREE) gazeLock = false;
        else if (r.gm == G_TARGET) gazeTo(actSide * r.gx * 0.1f * LOOK_X, r.gy * 0.1f * LOOK_Y, now);
        else gazeTo(0, 0, now);
      }
      break;
  }
}

static void endAction(uint32_t now) {
  if (act == A_SPIN) lastSpin = now;
  if ((act == A_YAWN || act == A_SLEEPY) && !blinkOn) nextBlink = now + 100;
  else if (softEdge(act) && !blinkOn && now + 260 < nextBlink) nextBlink = now + 60;   // v7: pestaneja ao voltar ao normal
  act = A_NONE; gazeLock = false;
  nextAct = now + random(ACT_MIN, ACT_MAX);
  nextSacc = now + random(500, 1300);
  gazeTo(0, 0, now);
}

static Act pickAction(uint32_t now) {
  //                           NONE GRIN SMRK THNK YAWN LAUG SAD  SURP SPIN NO   YES  CURI WINK CROS MUMB SLEE
  static const uint8_t W[16] = {0, 14,  10,  12,  5,   8,   6,   6,   10,  5,   6,   10,  8,   4,   8,   4};
  int w[A_COUNT], total = 0;
  w[0] = 0;
  for (int i = 1; i < A_COUNT; i++) {
    int x = (i < 16) ? W[i] : (i == A_MORPH ? 0 : RXT[i - A_RX0].w);
    if (i == (int)lastAct) x = 0;                                  // nao repete a mesma duas vezes
    if (i == A_SPIN && (now - lastSpin) < SPIN_COOLDOWN) x = 0;
    w[i] = x; total += x;
  }
  int r = random(total);
  for (int i = 1; i < A_COUNT; i++) { if (r < w[i]) return (Act)i; r -= w[i]; }
  return A_GRIN;
}

// monta o estilo-alvo (T) e o movimento do rosto inteiro (O) da animacao atual
static void actionTick(uint32_t now, Style &T, Ov &O) {
  if (act == A_NONE) return;
  float t = (float)(now - actT0), d = (float)actDur;
  if (t >= d) { endAction(now); return; }
  float sd = (float)actSide;
  float e = env(t, d, 300, 350);
  const Style &H = STY[styleNow(now)];                       // rosto atual (as reacoes usam as cores dele)

  switch (act) {
    case A_GRIN:                                   // sorrisao: olho de baixo sobe (olho sorrindo) e pula de leve
      T = H; T.cutTop = 0; T.cutBot = 0; T.cheek = 0.55f * e; T.ry = H.ry * 0.95f; T.rot = H.rot * 0.75f; T.lid = 0;   // v11: bochecha curva
      O.dy += -3 * e * fabsf(sinf(t * 0.006f));
      break;

    case A_SMIRK:                                  // sorriso de canto: meio fechado, olhando de lado
      T = H;
      T.cheek = 0.30f * e; T.rot = H.rot + 6 * e; T.squint = 0.12f * e;
      O.rot += 4 * sd * e; O.dx += 2 * sd * e;
      break;

    case A_THINK:                                  // pensando: palpebra de cima desce de um lado, cabeca torta
      T = H;
      T.cutTop = 0.2f * e; T.lid = -14 * sd; T.rot = H.rot - 4 * e;
      O.rot += 6 * sd * e; O.dx += 3 * sd * e;
      break;

    case A_YAWN: {                                 // bocejo: fecha devagar, fica lilas
      float oe = env(t, d, 600, 500);
      T = H;
      T.squint = 0.92f * env(t, d, 500, 450); T.rot = lerpf(H.rot, -8, oe);
      tintStyle(T, 175, 120, 255, 0.55f * oe);
      O.rot += -3 * oe; O.dy += -3 * oe; O.zoom *= 1 + 0.03f * oe;
      morphTau = 80;
      break;
    }

    case A_LAUGH: {                                // risada: olhos viram ^ ^ (solidos, sem brilho) e a cabeca faz um "sim" leve (v7: sem balancar de lado)
      T = H;
      T.arc = 1; T.bend = -10;
      O.dy += 4 * e * sinf(t * 0.0046f);
      morphTau = 160;
      break;
    }

    case A_SAD:                                    // triste: encolhe, cai, fica azulado
      T = H;
      T.rot = lerpf(H.rot, -14, e); T.cutTop = 0.22f * e + H.cutTop * (1 - e); T.lid = 12; T.py += 5 * e; T.rx *= 1 - 0.08f * e; T.ry *= 1 - 0.08f * e;
      tintStyle(T, 110, 98, 255, 0.5f * e);
      O.dy += 3 * e; O.rot += -3 * sd * e;
      break;

    case A_SURPRISE: {                             // susto: arregala, pupila encolhe
      setSurprise(T, H);
      T.ps = 0.5f;
      float pop = ease(1.0f - t / 220.0f);
      O.zoom *= 1 + 0.07f * pop; O.dy -= 7 * pop;
      morphTau = 45;
      break;
    }

    case A_SPIN: {   // cambalhota: agacha, gira 360 no ar (olhos arco-iris), cai tonto, e faz "ta-da"
      const float tA = 420.0f, tS = (spinTurns == 1) ? 1300.0f : 1900.0f;
      float dirf = (float)spinDir;
      T = H;
      T.rx *= 1.06f; T.ry *= 1.06f;
      float rr, gg, bb; hsv2rgb(t * 0.45f, rr, gg, bb); T.er = rr; T.eg = gg; T.eb = bb; T.gA = 0;
      hsv2rgb(t * 0.45f + 120.0f, rr, gg, bb); T.er2 = rr; T.eg2 = gg; T.eb2 = bb;
      morphTau = 60;
      if (t < tA) {                                  // 1) se prepara
        float a = ease(t / tA);
        O.zoom *= 1.0f - 0.07f * a; O.dy += 5 * a; O.rot += -dirf * 10 * a;
      } else if (t < tA + tS) {                      // 2) GIRA
        float p = (t - tA) / tS, a = ease(p);
        float wind = -dirf * 10;
        O.rot += wind + (dirf * 360.0f * spinTurns - wind) * a;
        O.dy += lerpf(5, 0, ease(p * 4)) - 5 * sinf(3.14159f * p);
        O.zoom *= (1.0f - 0.07f * (1.0f - ease(p * 3))) + 0.02f * sinf(3.14159f * p);
      } else {                                       // 3) cai
        float q = (t - tA - tS) / 1000.0f;
        O.rot += dirf * 360.0f * spinTurns + dirf * 8 * expf(-3 * q) * sinf(q * 16);
        O.dy += 5 * expf(-6 * q);
        O.zoom *= 1.0f - 0.06f * expf(-7 * q);
        if (q < 0.75f) {                             // tonto: pupilas rodando
          float A = 10 * expf(-2.2f * q);
          goX = A * cosf(q * 14); goY = 0.8f * A * sinf(q * 14);
          T.squint = 0.1f;
        } else {                                     // "ta-da!": volta ao rosto normal
          T = H;
          O.dy -= 2.5f * fabsf(sinf((q - 0.75f) * 9));
        }
      }
      break;
    }

    case A_NO: {                                   // "nao": olho bravo balancando a cabeca
      float nx = 13 * e * sinf(t * 0.0155f);
      setAngry(T, H, 0.46f, -24);
      O.dx += nx; O.rot += 7 * e * sinf(t * 0.0155f + 0.5f); goX = -nx * 0.5f;
      break;
    }

    case A_YES: {                                  // "sim": sorrindo e balancando pra baixo e pra cima
      float ny = 7 * e * sinf(t * 0.0165f);
      T = H;
      T.cutTop = 0; T.lid = 0; T.cheek = 0.35f * e; T.ps = 1 + 0.12f * e; T.rot = 4;
      O.dy += ny; goY = -ny * 0.5f;
      break;
    }

    case A_CURIOUS:                                // curioso: pupila alta, inclina a cabeca, olhos maiores
      T = H; T.cutTop = 0; T.lid = 0; T.rot = H.rot * 0.35f;
      T.rx *= 1.07f; T.ry *= 1.07f; T.ps = 1.1f; T.pry = H.pry * 1.5f; T.py = H.py * 0.4f; T.px = H.px * 0.4f;
      O.rot += 11 * sd * e; O.dx += 4 * sd * e;
      break;

    case A_WINK: {                                 // piscadinha com um olho so
      T = H;
      T.rot = H.rot + 4 * e;
      O.rot += 5 * sd * e;
      bool w = (t > 250 && t < 850);
      if (sd > 0) T.winkR = w ? 1.0f : 0.0f; else T.winkL = w ? 1.0f : 0.0f;
      morphTau = 60;
      break;
    }

    case A_CROSS:                                  // vesgo: pupilas viram pra dentro
      T = H;
      T.conv = 1.9f; T.py += 4;
      O.rot += 3 * sinf(t * 0.009f);
      break;

    case A_MUMBLE:                                 // resmungando: olho bravo, tremendo de leve
      if (now >= nextMum) { mumT = (random(100) < 25) ? 0.0f : random(30, 101) / 100.0f; nextMum = now + random(80, 230); }
      setAngry(T, H, 0.5f - 0.06f * mumT, -26); T.ry *= 1 + 0.04f * mumT;
      O.rot += 2 * sinf(t * 0.008f); O.dy += 1.5f * mumT;
      morphTau = 50;
      break;

    case A_SLEEPY: {
      const float tD = 1700.0f;
      if (t < tD) {                                  // vai pegando no sono: o olho fecha e vira duas barrinhas...
        float a = ease(t / tD);
        T = H;
        T.arc = ease((a - 0.55f) / 0.45f); T.squint = 0.7f * a; T.bend = 9;
        O.dy += 10 * a; O.rot += 4 * sd * a;
        morphTau = 380;
      } else {                                       // ...e acorda assustado
        float q = t - tD;
        setSurprise(T, H);
        T.rx *= 1.1f / 1.12f; T.ry *= 1.1f / 1.12f;
        O.dy += (q < 110) ? lerpf(10, -4, ease(q / 110.0f)) : -4 * expf(-(q - 110) / 260.0f);
        O.rot += 4 * sd * (1.0f - ease(q / 110.0f));
        O.zoom *= 1 + 0.05f * expf(-q / 200.0f);
        morphTau = 50;
      }
      break;
    }

#if MORPH_SMOKE
    case A_MORPH: {                                // TROCA DE ROSTO: treme, comprime, PUFF de fumaca, aparece outro rosto
      const float tShake = 1500, tIn = 200, dSm = 1600, tSm = tShake + tIn, tSwap = tSm + 0.40f * dSm;
      if (!morphSwapped && t >= tSwap) { baseSt = morphTo; morphSwapped = true; snapCur = true; }
      T = STY[styleNow(now)];
      morphTau = 40;
      if (t < tShake) {                            // 1) treme cada vez mais, piscando branco
        float r = ease(t / tShake);
        T.squint = 0.12f * r;
        O.dx += (1.5f + 7.0f * r) * sinf(t * 0.075f); O.rot += 5 * r * sinf(t * 0.061f + 0.7f); O.zoom *= 1 + 0.05f * r;
        if (sinf(t * 0.05f) > 0.6f) tintStyle(T, 255, 255, 255, 0.35f * r);
      } else if (t < tSm) {                        // 2) se comprime
        float q = ease((t - tShake) / tIn);
        O.zoom *= 1 - 0.09f * q; T.squint = 0.15f;
      } else {                                     // 3) puff!
        smokeP = (t - tSm) / dSm;
        if (!morphSwapped) O.zoom *= 0.91f;
        else {                                     // rosto novo aparece com um pulinho
          float u = (t - tSwap) / 1000.0f;
          O.zoom *= 1 + 0.14f * expf(-u * 7.0f); O.dy -= 6 * expf(-u * 8.0f);
          morphTau = 60;
        }
      }
      break;
    }

#else
    case A_MORPH: {                                // v10 TROCA DE ROSTO (como no video): fecha numa linha, troca fechado, abre devagar
      const float tC = 170, tH = 230, tO = 430, tSwap = tC + 0.45f * tH;
      if (!morphSwapped && t >= tSwap) { baseSt = morphTo; morphSwapped = true; snapCur = true; }
      T = STY[styleNow(now)];
      morphTau = 40;
      if (t < tC) gLidX = ease(t / tC);                                           // fecha rapido
      else if (t < tC + tH) gLidX = 1;                                            // segura fechado (troca aqui)
      else if (t < tC + tH + tO) { float u = (t - tC - tH) / tO, v = 1.0f - u; gLidX = v * v * v; }   // abre freando
      float uo = (t - tC - tH) / 1000.0f;
      if (uo > 0) {
        O.zoom *= 1 + 0.05f * expf(-uo * 7.0f); O.dy -= 2.5f * expf(-uo * 8.0f);  // pulinho ao abrir
        if (uo < 0.9f) { gDeco.spark = 0.85f * sinf(3.14159f * uo / 0.9f); decoCol(255, 255, 255); }   // brilhinhos
      }
      break;
    }
#endif

    default:
      if (act >= A_RX0 && act < A_COUNT) applyRx(RXT[act - A_RX0], t, d, e, sd, now, T, O, H);
      break;
  }
}

// ============================ MICROFONE ============================
static int micBase = 0, micLevel = 0;
static uint32_t lastTalk = 0, talkStart = 0, lastStartle = 0, lastMs = 0;
static float listenF = 0, talkOpen = 0;
static int listenSide = 1;
static bool wasListen = false;

static int micRead() {  // amplitude (pico a pico) de 32 amostras, ~4 ms
  int mn = 4095, mx = 0;
  for (int i = 0; i < 32; i++) {
    int v = analogRead(PIN_MIC);
    if (v < mn) mn = v;
    if (v > mx) mx = v;
    delayMicroseconds(60);
  }
  return mx - mn;
}

// ============================ BLUETOOTH (controle pelo site) ============================
#define BLE_NAME  "Starboy"
#define SVC_UUID  "7a1c0001-5b1a-4c3e-9d7a-1f0e5a5e0001"
#define RX_UUID   "7a1c0002-5b1a-4c3e-9d7a-1f0e5a5e0001"   // site -> placa (comandos)
#define TX_UUID   "7a1c0003-5b1a-4c3e-9d7a-1f0e5a5e0001"   // placa -> site (estado do rosto)

static BLECharacteristic *txChar = nullptr;
static volatile bool bleConn = false;
static volatile int  pendAct = 0;
static volatile int  pendCharge = -1;   // v12: -1 nada | 0/1 = comando 0x0B (simula tirar/pôr na tomada)
static volatile int  pendStyle = -1, pendStylePerm = 0;
static volatile bool pendBlink = false;
static volatile bool autoAct = true, autoBlink = true, autoGaze = true, micReact = true;
static volatile bool manual = false, colorHold = false, extGaze = false;
static volatile uint8_t colR = 255, colG = 66, colB = 196;
static volatile float extGX = 0, extGY = 0;
// valores do modo manual (mesma ordem do v4): mW mC mS mU mL mX mY mT | tilt grow ps squint conv winkL winkR | rot dx dy zoom
// No v5 nao ha boca: so valem tilt, grow, ps, squint, conv, winkL, winkR e rot/dx/dy/zoom.
static volatile float man[19] = {22, 0, 0, 11, 11, 0, 0, 4,  9, 1, 1, 0, 1, 0, 0,  0, 0, 0, 1};
static const float MSC[19] = {0.4f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.1f, 0.3f, 0.02f, 0.02f, 0.01f, 0.02f, 0.01f, 0.01f, 0.5f, 0.4f, 0.4f, 0.005f};

static void bleCmd(const uint8_t *d, size_t n) {
  if (n < 1) return;
  switch (d[0]) {
    case 0x01: if (n >= 2 && d[1] > 0 && d[1] < A_COUNT) pendAct = d[1]; break;            // dispara uma animacao (1..129)
    case 0x0B: if (n >= 2) pendCharge = d[1] ? 1 : 0; break;                                // v12: simula "carregando" (1) / "desconectou da tomada" (0)
    case 0x02: if (n >= 2) { autoAct = d[1] & 1; autoBlink = d[1] & 2; autoGaze = d[1] & 4; micReact = d[1] & 8; } break;
    case 0x03: if (n >= 5) { colR = d[1]; colG = d[2]; colB = d[3]; colorHold = d[4] != 0; } break;   // cor do olho
    case 0x04: if (n >= 9)  for (int i = 0; i < 8;  i++) man[i]     = (int8_t)d[1 + i] * MSC[i]; break;
    case 0x05: if (n >= 12) { for (int i = 0; i < 11; i++) man[8 + i] = (int8_t)d[1 + i] * MSC[8 + i]; man[18] = 1.0f + man[18]; } break;
    case 0x06: if (n >= 2) manual = d[1] != 0; break;                                        // controle total
    case 0x07: if (n >= 4) { extGaze = d[1] != 0; extGX = (int8_t)d[2] * 0.2f; extGY = (int8_t)d[3] * 0.2f; } break;
    case 0x09: pendBlink = true; break;
    case 0x0A: if (n >= 2 && d[1] < NFACES) { pendStylePerm = (n >= 3) ? d[2] : 0; pendStyle = d[1]; } break;   // escolhe o rosto 0..75 (fixo=1 trava; fixo=0 vira o rosto de casa)
    default: break;
  }
}

class SrvCb : public BLEServerCallbacks {
  void onConnect(BLEServer *) override { bleConn = true;
#if BT_REACTIONS
    pendAct = BT_CHARGE_ANIM ? ACT_CHARGE : ACT_BT_ON;   // v12: conectou => animacao verde do raio (S-01 continua no id 123)
#endif
  }
  void onDisconnect(BLEServer *) override { bleConn = false; BLEDevice::startAdvertising();
#if BT_REACTIONS
    pendAct = ACT_BT_OFF;                      // v9.1: S-02 Bluetooth caiu
#endif
  }
};
class RxCb : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *c) override { bleCmd(c->getData(), c->getLength()); }
};

static void bleInit() {
  BLEDevice::init(BLE_NAME);
  BLEServer *srv = BLEDevice::createServer();
  srv->setCallbacks(new SrvCb());
  BLEService *svc = srv->createService(SVC_UUID);
  BLECharacteristic *rx = svc->createCharacteristic(RX_UUID, BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_WRITE_NR);
  rx->setCallbacks(new RxCb());
  txChar = svc->createCharacteristic(TX_UUID, BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ);
  txChar->addDescriptor(new BLE2902());
  svc->start();
  BLEAdvertising *adv = BLEDevice::getAdvertising();
  adv->addServiceUUID(SVC_UUID);
  adv->setScanResponse(true);
  BLEDevice::startAdvertising();
}

static inline int8_t q8(float v, float k) { int x = (int)lroundf(v / k); return (int8_t)(x < -127 ? -127 : (x > 127 ? 127 : x)); }
static inline void put16(uint8_t *p, int v) { if (v < -32767) v = -32767; if (v > 32767) v = 32767; p[0] = v & 0xFF; p[1] = (v >> 8) & 0xFF; }

// manda o estado do rosto para o site (2 pacotes de ate 20 bytes) - mesmo formato do v4 (boca fica neutra)
static void bleSend(const Style &E, float clL, float clR, float gx, float gy, float convEff, const Ov &O, int lvl, bool talking, bool listening) {
  if (!bleConn || !txChar) return;
  uint8_t a[20], b[12];
  a[0] = 0x10; a[1] = q8(22, MSC[0]); a[2] = 0; a[3] = 0; a[4] = q8(11, MSC[3]);
  a[5] = q8(11, MSC[4]); a[6] = 0; a[7] = 0; a[8] = q8(4, MSC[7]);
  a[9] = q8(E.rot * 0.6f, MSC[8]); a[10] = q8(1, MSC[9]); a[11] = q8(1, MSC[10]);
  a[12] = q8(clL, 0.01f); a[13] = q8(clR, 0.01f); a[14] = q8(gx, 0.2f); a[15] = q8(gy, 0.2f); a[16] = q8(convEff, 0.02f);
  a[17] = (uint8_t)act;
  a[18] = (talking ? 1 : 0) | (listening ? 2 : 0) | (manual ? 4 : 0);
  int m = lvl * 255 / 1000; a[19] = (uint8_t)(m < 0 ? 0 : (m > 255 ? 255 : m));
  float r = fmodf(O.rot, 360.0f); if (r > 180) r -= 360; if (r < -180) r += 360;
  b[0] = 0x11; put16(b + 1, (int)lroundf(r * 50)); put16(b + 3, (int)lroundf(O.dx * 100)); put16(b + 5, (int)lroundf(O.dy * 100));
  put16(b + 7, (int)lroundf(O.zoom * 1000));
  b[9] = (uint8_t)clampf(E.er, 0, 255); b[10] = (uint8_t)clampf(E.eg, 0, 255); b[11] = (uint8_t)clampf(E.eb, 0, 255);
  txChar->setValue(a, 20); txChar->notify();
  txChar->setValue(b, 12); txChar->notify();
}

// ============================ LOGO STARLYN INFINITE (v8.1) ============================
// A logomarca e RECRIADA 100% POR CODIGO (nenhuma imagem no arquivo, nada pesado):
//   - os dois olhos rosa = 4 ovais inclinadas (2 rosas + 2 miolos bege), medidas da logo original
//   - "STARLYN" (preto) e "INFINITE" (rosa) = contornos vetoriais (pontos), preenchidos com borda suave
// Ao ligar: fade-in a partir do branco -> fica parada -> fade-out para o branco -> comeca a bolinha.
// A figura e montada UMA vez numa memoria temporaria (57,6 KB, liberada logo depois): cada pixel guarda
// 2 bits de "tipo de mistura" + 6 bits de cobertura (borda suave). O fade so troca uma tabelinha de cores.
//   tipo 0 = branco <-> rosa | tipo 1 = rosa <-> bege | tipo 2 = branco <-> preto
static const int16_t LG_PTS[] = {
  4480, 6960, 4130, 6960, 3656, 6316, 3160, 6958, 2824, 6962, 2816, 6952, 3474, 6128, 3560, 6067,
  3656, 6049, 3752, 6068, 3834, 6128, 5960, 6965, 5592, 6964, 5208, 6634, 4848, 6635, 4839, 6960,
  4552, 6964, 4547, 6552, 4564, 6504, 4608, 6462, 4696, 6437, 5528, 6434, 5608, 6402, 5638, 6344,
  5600, 6285, 5528, 6262, 4832, 6261, 4533, 6056, 5560, 6054, 5712, 6085, 5824, 6141, 5891, 6200,
  5932, 6280, 5944, 6352, 5921, 6440, 5869, 6512, 5800, 6562, 5587, 6632, 7712, 6960, 7439, 6960,
  7433, 6576, 6896, 6056, 7232, 6053, 7280, 6066, 7584, 6348, 7904, 6066, 7960, 6054, 8297, 6056,
  7722, 6576, 1536, 6953, 400, 6954, 486, 6792, 568, 6750, 1472, 6748, 1536, 6730, 1580, 6680,
  1560, 6631, 1480, 6597, 880, 6594, 760, 6578, 656, 6546, 552, 6481, 495, 6400, 486, 6288,
  526, 6200, 592, 6141, 664, 6101, 832, 6060, 1928, 6061, 1768, 6258, 904, 6259, 832, 6275,
  799, 6304, 795, 6336, 809, 6360, 888, 6394, 1520, 6397, 1688, 6436, 1808, 6507, 1860, 6568,
  1889, 6648, 1884, 6720, 1859, 6784, 1800, 6850, 1728, 6898, 1648, 6932, 2680, 6962, 2410, 6952,
  2408, 6264, 1915, 6256, 2066, 6064, 3264, 6064, 3120, 6259, 2692, 6264, 2690, 6952, 7112, 6961,
  6280, 6958, 6184, 6939, 6128, 6905, 6084, 6840, 6067, 6768, 6067, 6064, 6348, 6064, 6349, 6600,
  6364, 6680, 6392, 6720, 6432, 6746, 6504, 6758, 7264, 6760, 7272, 6768, 7243, 6808, 9392, 6960,
  9256, 6939, 9152, 6881, 8608, 6372, 8597, 6960, 8322, 6960, 8319, 6304, 8333, 6208, 8368, 6138,
  8432, 6086, 8512, 6064, 8584, 6068, 8680, 6108, 9312, 6687, 9318, 6064, 9592, 6060, 9596, 6744,
  9585, 6824, 9553, 6888, 9504, 6931, 2736, 7825, 2576, 7818, 2296, 7519, 2289, 7816, 2272, 7825,
  2120, 7819, 2120, 7288, 2224, 7280, 2296, 7287, 2568, 7581, 2578, 7576, 2581, 7288, 2744, 7284,
  2750, 7808, 4688, 7825, 4552, 7825, 4532, 7808, 4532, 7296, 4544, 7282, 4680, 7280, 4702, 7296,
  4701, 7808, 7576, 7825, 7440, 7826, 7422, 7816, 7419, 7416, 7408, 7407, 7248, 7404, 7248, 7285,
  7704, 7280, 7776, 7288, 7776, 7401, 7616, 7407, 7598, 7416, 7595, 7808, 1464, 7825, 1320, 7825,
  1308, 7816, 1308, 7296, 1320, 7282, 1464, 7280, 1483, 7296, 1483, 7808, 3528, 7825, 3384, 7825,
  3367, 7816, 3368, 7292, 3416, 7280, 3888, 7286, 3894, 7392, 3880, 7407, 3568, 7407, 3544, 7416,
  3541, 7472, 3552, 7488, 3848, 7490, 3859, 7504, 3858, 7600, 3840, 7614, 3544, 7617, 3540, 7808,
  5888, 7825, 5744, 7825, 5728, 7817, 5448, 7518, 5439, 7816, 5424, 7825, 5280, 7821, 5271, 7800,
  5277, 7288, 5296, 7280, 5448, 7286, 5728, 7581, 5734, 7288, 5896, 7286, 5903, 7808, 6656, 7824,
  6520, 7825, 6500, 7816, 6499, 7304, 6512, 7282, 6656, 7281, 6672, 7296, 6673, 7808, 8848, 7826,
  8344, 7822, 8344, 7284, 8858, 7288, 8856, 7405, 8536, 7408, 8520, 7412, 8510, 7432, 8520, 7487,
  8800, 7488, 8818, 7496, 8821, 7600, 8808, 7615, 8520, 7617, 8511, 7624, 8511, 7680, 8544, 7696,
  8856, 7700, 8864, 7808
};
static const uint16_t LG_END[] = { 11, 38, 49, 86, 95, 111, 131, 145, 153, 166, 174, 192, 207, 215, 234 };
#define LG_NBLACK 7
#define LG_NPOLY 15

// ovais: centro x, y | semi-eixo a (largura), b (altura) | giro (graus)  [medidas em pixels da logo original 1254x1254]
static const float LG_ELL[4][5] = {
  { 507.1f, 507.8f, 137.9f, 187.1f, -4.70f },    // olho rosa ESQUERDO (levemente torto)
  { 770.7f, 473.7f, 135.8f, 200.4f, 11.30f },    // olho rosa DIREITO (mais inclinado)
  { 542.5f, 500.6f, 57.4f, 87.2f, -6.50f },    // miolo bege esquerdo
  { 740.0f, 475.9f, 58.3f, 90.8f, 13.40f }     // miolo bege direito
};
static const uint8_t LG_WHITE[3] = {255, 255, 255};
static const uint8_t LG_PINK[3]  = {255, 20, 147};
static const uint8_t LG_BEIGE[3] = {249, 229, 204};
static const uint8_t LG_BLACK[3] = {0, 0, 0};

static uint8_t *lgBuf = NULL;                 // 240*240 bytes (alocado so durante a abertura)

static void lgSpan(float *acc, float xa, float xb, float w) {   // soma cobertura (borda suave horizontal)
  if (xa < 0) xa = 0;
  if (xb > SE_W) xb = SE_W;
  if (xb <= xa) return;
  int ia = (int)xa, ib = (int)xb;
  if (ia == ib) { acc[ia] += (xb - xa) * w; return; }
  acc[ia] += (ia + 1 - xa) * w;
  for (int i = ia + 1; i < ib; i++) acc[i] += w;
  if (ib < SE_W) acc[ib] += (xb - ib) * w;
}

// Monta a logo inteira no buffer. Retorna false se faltar memoria.
static bool lgBuild() {
  const int SS = 6;                           // sub-linhas por linha (qualidade da borda)
  const float S = LOGO_SCALE;
  const float OX = 120.0f - 627.0f * S, OY = 120.0f - 627.0f * S;
  const int NP = LG_END[LG_NPOLY - 1];
  lgBuf = (uint8_t *)malloc(SE_W * SE_W);
  float *P = (float *)malloc(sizeof(float) * 2 * NP);          // pontos ja na escala da tela
  int16_t *NX = (int16_t *)malloc(sizeof(int16_t) * NP);       // NX[i] = proximo ponto do mesmo contorno
  if (!lgBuf || !P || !NX) {
    if (lgBuf) free(lgBuf);
    if (P) free(P);
    if (NX) free(NX);
    lgBuf = NULL; return false;
  }
  for (int i = 0; i < NP; i++) {
    P[2 * i]     = LG_PTS[2 * i]     * (S / 8.0f) + OX;
    P[2 * i + 1] = LG_PTS[2 * i + 1] * (S / 8.0f) + OY;
  }
  for (int q = 0; q < LG_NPOLY; q++) {
    int a = (q == 0) ? 0 : LG_END[q - 1], b = LG_END[q];
    for (int i = a; i < b; i++) NX[i] = (i + 1 < b) ? i + 1 : a;
  }
  float el[4][5];
  for (int i = 0; i < 4; i++) {
    float th = LG_ELL[i][4] * 0.017453293f;
    se_mk(el[i], LG_ELL[i][0] * S + OX, LG_ELL[i][1] * S + OY, LG_ELL[i][2] * S, LG_ELL[i][3] * S, cosf(th), sinf(th));
  }
  static float accP[SE_W], accB[SE_W], accK[SE_W];
  int16_t act[2][200]; int nAct[2];
  float xs[48];
  for (int y = 0; y < SE_W; y++) {
    for (int i = 0; i < SE_W; i++) accP[i] = accB[i] = accK[i] = 0;
    // arestas do texto que tocam esta linha (conjunto 0 = preto, 1 = rosa)
    for (int s = 0; s < 2; s++) {
      nAct[s] = 0;
      int p0 = (s == 0) ? 0 : LG_NBLACK, p1 = (s == 0) ? LG_NBLACK : LG_NPOLY;
      for (int q = p0; q < p1; q++) {
        int a = (q == 0) ? 0 : LG_END[q - 1], b = LG_END[q];
        for (int i = a; i < b; i++) {
          float ya = P[2 * i + 1], yb = P[2 * NX[i] + 1];
          float lo = ya < yb ? ya : yb, hi = ya < yb ? yb : ya;
          if (hi > y && lo < y + 1 && nAct[s] < 200) act[s][nAct[s]++] = (int16_t)i;
        }
      }
    }
    for (int k = 0; k < SS; k++) {
      float sy = y + (k + 0.5f) / SS, w = 1.0f / SS;
      for (int e = 0; e < 4; e++) {                        // ovais
        float x0, x1;
        if (se_span(el[e], sy, x0, x1)) lgSpan(e < 2 ? accP : accB, x0, x1, w);
      }
      for (int s = 0; s < 2; s++) {                        // texto (par-impar: os buracos de A, R, D funcionam)
        if (!nAct[s]) continue;
        int nx = 0;
        for (int t = 0; t < nAct[s]; t++) {
          int i = act[s][t], j = NX[i];
          float x0 = P[2 * i], y0 = P[2 * i + 1], x1 = P[2 * j], y1 = P[2 * j + 1];
          if (((y0 <= sy) && (y1 > sy)) || ((y1 <= sy) && (y0 > sy))) {
            if (nx < 48) xs[nx++] = x0 + (sy - y0) * (x1 - x0) / (y1 - y0);
          }
        }
        for (int u = 1; u < nx; u++) { float v = xs[u]; int h = u - 1; while (h >= 0 && xs[h] > v) { xs[h + 1] = xs[h]; h--; } xs[h + 1] = v; }
        for (int u = 0; u + 1 < nx; u += 2) lgSpan(s == 0 ? accK : accP, xs[u], xs[u + 1], w);
      }
    }
    uint8_t *row = lgBuf + y * SE_W;
    for (int x = 0; x < SE_W; x++) {
      float p = accP[x], bg = accB[x], k = accK[x];
      if (p > 1) p = 1;
      if (bg > 1) bg = 1;
      if (k > 1) k = 1;
      if (bg > 0.004f)      row[x] = (1 << 6) | (uint8_t)(bg * 63.0f + 0.5f);
      else if (k > 0.004f)  row[x] = (2 << 6) | (uint8_t)(k * 63.0f + 0.5f);
      else                  row[x] = (uint8_t)(p * 63.0f + 0.5f);
    }
  }
  free(P); free(NX);
  return true;
}

static inline uint8_t lgMix(uint8_t a, uint8_t b, int c) { return (uint8_t)((a * (63 - c) + b * c + 31) / 63); }

// Mostra a logo com "fade" f (0 = tela branca, 1 = logo cheia)
static void lgShow(float f) {
  static uint16_t lut[192];
  int fi = (int)(clampf(f, 0, 1) * 256.0f + 0.5f);
  for (int t = 0; t < 3; t++) {
    const uint8_t *A = (t == 2) ? LG_WHITE : (t == 1 ? LG_PINK : LG_WHITE);
    const uint8_t *B = (t == 2) ? LG_BLACK : (t == 1 ? LG_BEIGE : LG_PINK);
    for (int c = 0; c < 64; c++) {
      int col[3];
      for (int i = 0; i < 3; i++) {
        int v = lgMix(A[i], B[i], c);
        col[i] = 255 - (((255 - v) * fi) >> 8);      // mistura com o branco = fade
      }
      uint16_t v565 = se_565(col[0], col[1], col[2]);
      lut[t * 64 + c] = (v565 >> 8) | (v565 << 8);   // ja na ordem de bytes do display
    }
  }
  setWindow(0, 0, 239, 239);
  for (int y = 0; y < SE_W; y++) {
    const uint8_t *row = lgBuf + y * SE_W;
    for (int x = 0; x < SE_W; x++) sendBuf[x] = lut[row[x]];
    SPI.writeBytes((uint8_t *)sendBuf, SE_W * 2);
  }
}

static void logoFillWhite() {
  for (int x = 0; x < SE_W; x++) sendBuf[x] = 0xFFFF;
  setWindow(0, 0, 239, 239);
  for (int y = 0; y < SE_W; y++) SPI.writeBytes((uint8_t *)sendBuf, SE_W * 2);
}

static void logoIntro() {
  logoFillWhite();                                    // comeca em branco
  if (!lgBuild()) return;                             // sem memoria? pula a logo e segue o baile
  uint32_t t0 = millis();
  for (;;) {                                          // fade-in
    float u = (float)(millis() - t0) / LOGO_FADE_IN_MS;
    if (u >= 1.0f) break;
    lgShow(ease(u));
  }
  lgShow(1.0f);
  delay(LOGO_HOLD_MS);                                // fica parada
  t0 = millis();
  for (;;) {                                          // fade-out
    float u = (float)(millis() - t0) / LOGO_FADE_OUT_MS;
    if (u >= 1.0f) break;
    lgShow(1.0f - ease(u));
  }
  logoFillWhite();
  free(lgBuf); lgBuf = NULL;
}

// ============================ ANIMACAO DE LIGAR (v10.1) ============================
// 1) tela branca -> bolinha preta cai e QUICA de verdade (gravidade, rebate na borda redonda, amassa no impacto,
//    cresce a cada quique) -> infla e PREENCHE a tela toda de preto
// 2) MANCHAS CINZA aparecem no escuro, se juntam numa massa so, a massa se PARTE EM DOIS e vira os dois OLHOS
//    (que ganham cor e pupila)
// 3) ANIMACAO A: os olhos olham pra baixo na diagonal e os rostos SOBEM rapido (na diagonal) trocando varias vezes
//    (estilo caca-niquel), freiam com um tranquinho e param
// 4) ANIMACAO B: a ROLETA vai pra DIREITA, rapidissima, desacelera e o ultimo rosto fica no display
// Brilhinhos (estrelas de 4 pontas com halo) em cada chegada/troca. Tudo desenhado por codigo.
static int bootStyle = (BOOT_FINAL_FACE >= 0 ? BOOT_FINAL_FACE : 0), bootF0 = 0;

// ---- ajudantes ----
static Eye &bootEye(Face &F, float cx, float cy, float rot) {       // novo "olho" de uso livre (manchas, brilhos, linhas)
  Eye &e = F.eye[F.nEyes++];
  e.cx = cx; e.cy = cy; e.rot = rot; e.cutTop = 0; e.cutBot = 0; e.lidAng = 0; e.lidAngB = 0; e.base = -1; e.n = 0; e.grad = 0;
  return e;
}
static float bootBlink(float el, float c, float h, float o) {       // piscada: fecha rapido, segura, abre freando (ms)
  if (el < 0) return 0;
  if (el < c) return ease(el / c);
  if (el < c + h) return 1;
  if (el < c + h + o) { float v = 1.0f - (el - c - h) / o; return v * v * v; }
  return 0;
}

// ---- brilhinhos (varios ao mesmo tempo, cada um nasce, brilha e some) ----
struct BGlint { float x, y, s, ang, t0, dur; uint8_t r, g, b; bool on; };
static BGlint bgl[9];
static void glintClear() { for (int i = 0; i < 9; i++) bgl[i].on = false; }
static void glintSpawn(int n, uint32_t nowm, float cx, float cy, float spread, float sMin, float sMax) {
  static const uint8_t PAL[4][3] = { {255, 255, 255}, {255, 240, 170}, {255, 205, 232}, {190, 240, 255} };
  for (int k = 0; k < n; k++) {
    int slot = 0; float oldest = 1e12f;
    for (int i = 0; i < 9; i++) {
      if (!bgl[i].on) { slot = i; break; }
      if (bgl[i].t0 < oldest) { oldest = bgl[i].t0; slot = i; }
    }
    BGlint &g = bgl[slot];
    float an = rf(0, 6.2832f), rr = spread * sqrtf(rf(0.12f, 1.0f));
    float x = cx + rr * cosf(an), y = cy + rr * sinf(an);
    float dx = x - 120, dy = y - 120, dd = hypotf(dx, dy);
    if (dd > 104.0f) { x = 120 + dx * 104.0f / dd; y = 120 + dy * 104.0f / dd; }     // fica dentro da tela redonda
    g.x = x; g.y = y; g.s = rf(sMin, sMax); g.ang = rf(-12, 12); g.t0 = (float)nowm; g.dur = rf(520, 900);
    const uint8_t *c = PAL[random(4)]; g.r = c[0]; g.g = c[1]; g.b = c[2]; g.on = true;
  }
}
static void glintDraw(Face &F, uint32_t nowm) {
  bool any = false;
  for (int i = 0; i < 9; i++) if (bgl[i].on) { if ((float)nowm - bgl[i].t0 >= bgl[i].dur) bgl[i].on = false; else any = true; }
  if (!any || F.nEyes >= SE_MAXEYES) return;
  Eye &e = bootEye(F, 0, 0, 0);
  for (int i = 0; i < 9; i++) {
    const BGlint &g = bgl[i];
    if (!g.on) continue;
    float u = ((float)nowm - g.t0) / g.dur, tw = powf(sinf(3.14159f * u), 0.7f);   // nasce, brilha, some
    se_glint(e, g.x, g.y, g.s * (0.25f + 0.75f * tw), g.ang + 40.0f * u, g.r, g.g, g.b, (uint8_t)(255.0f * tw));
  }
}

// ---- 1) BOLINHA REBATENDO NAS PAREDES (v10.2: ~6 s, rebate serio em todas as direcoes, cresce ate encher a tela) ----
static void bootBall() {
  Face &F = gFace;
  F.bg[0] = F.bg[1] = F.bg[2] = 255; F.nEyes = 0; showFace();     // tela toda branca
  delay(LOGO_INTRO ? 200 : 600);
  const float G = 220.0f, SPD = 520.0f, R0 = 9.0f, R1 = 46.0f;      // gravidade leve, velocidade minima, raio inicial/antes de encher
  const float T_B = 5300.0f * BOOT_TIME_SCALE, T_FILL = 700.0f * BOOT_TIME_SCALE;
  float an = rf(0.4f, 1.2f) * (random(2) ? 1 : -1);
  float bx = 120, by = 120, vx = SPD * cosf(an), vy = SPD * sinf(an) - 120.0f, r = R0, sq = 0, nang = 0;
  bool fill = false, done = false; float fx = 0, fy = 0, fr = 0, tf = 0, fu = 0;
  uint32_t t0 = millis(), last = t0;
  while (!done) {
    uint32_t now = millis();
    float ts = (float)(now - t0);
    float dt = clampf((now - last) / 1000.0f, 0.001f, 0.06f) / BOOT_TIME_SCALE; last = now;
    if (!fill) {
      float tn = clampf(ts / T_B, 0, 1);
      r = R0 + (R1 - R0) * powf(tn, 1.5f);                           // cresce rebatendo
      int ns = (int)ceilf(dt / 0.004f); if (ns < 1) ns = 1;
      float h = dt / ns;
      for (int s = 0; s < ns; s++) {
        vy += G * h; bx += vx * h; by += vy * h;
        float ddx = bx - 120, ddy = by - 120, d = hypotf(ddx, ddy), lim = 120.0f - r;
        if (d > lim) {                                                // bateu na parede redonda: rebate (reto, diagonal, de raspao...)
          float nx = ddx / d, ny = ddy / d;
          bx = 120 + nx * lim; by = 120 + ny * lim;
          float vn = vx * nx + vy * ny;
          if (vn > 0) {
            vx -= 2.0f * vn * nx; vy -= 2.0f * vn * ny;
            float sp = hypotf(vx, vy);
            if (sp < SPD) { vx *= SPD / sp; vy *= SPD / sp; }         // nunca perde forca: segue rebatendo
            if (vn > 150.0f) { sq = clampf(vn / 700.0f, 0.3f, 1.0f); nang = atan2f(ny, nx) * 57.2958f; }
          }
        }
      }
      if (ts >= T_B) { fill = true; fx = bx; fy = by; fr = r; tf = ts; }
    } else {
      fu = clampf((ts - tf) / T_FILL, 0, 1);
      bx = lerpf(fx, 120, ease(fu)); by = lerpf(fy, 120, ease(fu));
      r = fr + (178.0f - fr) * powf(fu, 2.0f);                        // infla ate tomar a tela inteira
      if (fu >= 1.0f) done = true;
    }
    sq *= expf(-dt * 9.0f);
    Face &Fr = gFace; Fr.nEyes = 0; Fr.bg[0] = Fr.bg[1] = Fr.bg[2] = 255;
    Eye &e = bootEye(Fr, bx, by, 0);
    float spd = hypotf(vx, vy), rx, ry;
    if (sq > 0.12f) { e.rot = nang; rx = r * (1.0f - 0.30f * sq); ry = r * (1.0f + 0.16f * sq); }      // amassa no impacto
    else { float st = fill ? 0.0f : clampf(spd / 2600.0f, 0, 0.5f); e.rot = atan2f(vy, vx) * 57.2958f; rx = r * (1.0f + st); ry = r / sqrtf(1.0f + st); }   // estica na velocidade
    se_ell(e, 0, 0, rx, ry, 0, 0, 0, 0, 255, 0);
    showFace();
  }
  gFace.bg[0] = gFace.bg[1] = gFace.bg[2] = 0; gFace.nEyes = 0; showFace();   // tela toda preta
  delay((uint32_t)(100.0f * BOOT_TIME_SCALE));
}

// ---- 2) MANCHAS CINZA -> MASSA -> SE PARTE EM DOIS -> OLHOS ----
static void bootStains() {
  Face &F = gFace;
  bootF0 = random(NFACES);
  const Style &H = STY[bootF0];
  const float B = BOOT_TIME_SCALE;
  const float T_M0 = 700 * B, T_M1 = 1700 * B,        // as manchas se juntam
              T_S0 = 1950 * B, T_S1 = 2900 * B,       // a massa se parte em dois olhos
              T_C0 = 2900 * B, T_C1 = 3550 * B,       // o cinza ganha cor e pupila
              T_END = 3600 * B;
  const float RX_F = H.rx / 0.82f, RY_F = H.ry / 0.82f;                   // tamanho final da massa = tamanho do olho
  static const float AJ[6] = {0.9f, 2.1f, 3.3f, 4.35f, 5.4f, 0.2f};       // onde cada mancha nasce (angulo)
  static const float DJ[6] = {44, 52, 38, 56, 46, 34};                    // ... e a distancia do centro
  static const float RJ[6] = {15, 12, 17, 11, 14, 13};                    // tamanho de cada mancha solta
  bool burst1 = false, burst2 = false;
  glintClear();
  uint32_t t0 = millis();
  for (;;) {
    uint32_t nowm = millis();
    float ts = (float)(nowm - t0);
    if (ts >= T_END) break;
    float tt = ts * 0.001f;
    float m = ease((ts - T_M0) / (T_M1 - T_M0)), s = ease((ts - T_S0) / (T_S1 - T_S0));
    float lumpF = 1.0f - ease((ts - (T_S0 + 0.30f * (T_S1 - T_S0))) / (0.70f * (T_S1 - T_S0)));   // as "bolhas" vao sumindo: sobra o oval liso
    float ck = ease((ts - T_C0) / (T_C1 - T_C0));
    F.nEyes = 0; F.bg[0] = F.bg[1] = F.bg[2] = 0;
    if (ts < T_C0) {
      uint8_t g8 = (uint8_t)lerpf(64, 150, ease(ts / T_M1));              // o cinza vai clareando
      float Rm = 16.0f + 44.0f * m;
      float Rx = lerpf(Rm, RX_F, s), Ry = lerpf(Rm * 1.04f, RY_F, s);
      int nm = (s < 0.01f) ? 1 : 2;
      for (int q = 0; q < nm; q++) {
        float side = (nm == 1) ? 0.0f : (q ? 1.0f : -1.0f);
        Eye &e = bootEye(F, 120.0f + side * H.gap * s, lerpf(112.0f, H.cy, s), side * H.rot * s);
        for (int h = 0; h < 3; h++) {                                       // brilho suave em volta (glow)
          float k = 1.46f - 0.17f * h;
          se_ell(e, 0, 0, 0.82f * Rx * k, 0.82f * Ry * k, 0, g8, g8, g8, (uint8_t)((16 + 12 * h) * m * (1.0f - s)), 0);
        }
        float LX[6], LY[6], LRX[6], LRY[6]; bool LV[6];
        for (int j = 0; j < 6; j++) {                                       // 1a passada: halo e corpo das manchas
          float ap = ease((ts - j * 140.0f * B) / (520.0f * B));            // cada mancha aparece e cresce na sua vez
          LV[j] = !(ap < 0.01f && m < 0.01f);
          if (!LV[j]) continue;
          float aj = AJ[j] + tt * 0.35f * (0.4f + m) + 0.25f * sinf(tt * 1.7f + j);
          float wob = 1.0f + 0.12f * sinf(tt * 1.3f + j * 2.1f);
          float off = lerpf(DJ[j], 0.38f * Rx, m) * lumpF;
          LX[j] = off * cosf(aj); LY[j] = off * sinf(aj) * (Ry / Rx);
          LRX[j] = lerpf(RJ[j] * ap, 0.62f * Rx * wob, m); LRY[j] = lerpf(RJ[j] * ap, 0.62f * Ry * wob, m);
          se_ell(e, LX[j], LY[j], LRX[j] * 1.7f, LRY[j] * 1.7f, 0, g8, g8, g8, (uint8_t)(30.0f * ap * (1.0f - m)), 0);
        }
        se_ell(e, 0, 0, 0.82f * Rx, 0.82f * Ry, 0, g8, g8, g8, (uint8_t)(255.0f * ease(m * 1.6f)), 0);   // o oval (aparece quando juntou)
        for (int j = 0; j < 6; j++) if (LV[j]) se_ell(e, LX[j], LY[j], LRX[j], LRY[j], 0, g8, g8, g8, 255, 0);
        uint8_t ca = (uint8_t)(255.0f * ease(m) * (1.0f - ease(s * 1.25f)));   // miolo claro (some quando vira olho)
        if (ca > 2) {
          se_ell(e, 0, 0, 0.82f * Rx * 0.58f, 0.82f * Ry * 0.58f, 0, 236, 236, 240, ca, 0);
          for (int j = 0; j < 6; j++) if (LV[j]) se_ell(e, LX[j] * 0.58f, LY[j] * 0.58f, LRX[j] * 0.58f, LRY[j] * 0.58f, 0, 236, 236, 240, ca, 0);
        }
      }
    } else {                                                               // o olho cinza ganha cor e pupila
      Style T = H;
      tintStyle(T, 150, 150, 150, 1.0f - ck);
      T.pa = H.pa * ease((ck - 0.35f) / 0.65f);
      Ov O = {0, 0, 0, 1.0f + 0.06f * sinf(3.14159f * ck)};                 // "pop" ao acender
      float bl = bootBlink(ts - (T_C1 + 250.0f * B), 80, 35, 230);
      if (!burst1 && ts > T_C0 + 0.35f * (T_C1 - T_C0)) { glintSpawn(5, nowm, 120, 112, 78, 6, 12); burst1 = true; }
      if (!burst2 && ts > T_C1) { glintSpawn(4, nowm, 120, 112, 84, 5, 10); burst2 = true; }
      addEyes(F, T, bl, 0, 0, 1.0f, O, 0);
    }
    glintDraw(F, nowm);
    showFace();
  }
}

// ---- 3) e 4) FILA DE ROSTOS (caca-niquel pra cima na diagonal / roleta pra direita) ----
static float gProf[65], gProfV = 1;
static void profBuild(float ramp, float pw) {            // curva do deslocamento: arranca rapido e vai freando
  float acc = 0, vmax = 0; gProf[0] = 0;
  for (int i = 1; i <= 64; i++) {
    float u = (i - 0.5f) / 64.0f, v = fminf(u / ramp, 1.0f) * powf(1.0f - u, pw);
    acc += v; gProf[i] = acc; if (v > vmax) vmax = v;
  }
  for (int i = 1; i <= 64; i++) gProf[i] /= acc;
  gProfV = vmax / acc * 64.0f;
}
static float profAt(float u) {
  u = clampf(u, 0, 1); float f = u * 64.0f; int i = (int)f;
  if (i >= 64) return 1.0f;
  return gProf[i] + (gProf[i + 1] - gProf[i]) * (f - i);
}
static float profSpd(float u) {                          // velocidade normalizada 0..1 (para esticar os olhos e as linhas)
  u = clampf(u, 0, 0.999f); int i = (int)(u * 64.0f);
  return clampf((gProf[i + 1] - gProf[i]) * 64.0f / gProfV, 0, 1);
}
static void bootStreaks(Face &F, float pos, float spd, float ux, float uy) {   // linhas de velocidade
  if (F.nEyes >= SE_MAXEYES) return;
  Eye &e = bootEye(F, 0, 0, 0);
  float px = -uy, py = ux, len = 16.0f + 70.0f * spd, a = 120.0f * spd;
  for (int i = 0; i < 9; i++) {
    float q = (i - 4.0f) * 21.0f + 7.0f * sinf(i * 12.9898f);
    float p = fmodf(pos * 1.45f + i * 83.3f, 340.0f) - 170.0f;
    float x = 120 + ux * p + px * q, y = 118 + uy * p + py * q;
    se_seg(e, x, y, x - ux * len, y - uy * len, 1.3f, 215, 215, 225, (uint8_t)(a * (0.55f + 0.45f * sinf(i * 3.1f + 1.0f))), 0);
  }
}
static void bootMakeSeq(uint8_t *seq, int N, int first, int last) {   // sorteia os rostos da fila (sem repetir em seguida)
  seq[0] = first;
  for (int i = 1; i < N - 1; i++) { int s; do { s = random(NFACES); } while (s == seq[i - 1]); seq[i] = s; }
  if (last == seq[N - 2]) seq[N - 2] = (seq[N - 2] + 1) % NFACES;   // v12: o ultimo rosto (o que fica) nunca muda
  seq[N - 1] = last;
}
static SpinCfg bootCfgUp() {            // ANIMACAO A: olha pra baixo na diagonal, depois sobe rapido (na diagonal) trocando de rosto
  SpinCfg C; const float a = SLOT_DIAG_DEG * 0.0174533f;
  C.L = 190; C.cull = 184; C.ux = sinf(a); C.uy = -cosf(a);
  C.tWind = 550; C.tScroll = 1850; C.tSettle = 320; C.tHold = 0;
  C.ramp = 0.07f; C.pw = 2.4f; C.ovs = 10;
  C.stX = -0.08f; C.stY = 0.16f;
  C.lkX = LOOK_X * 0.85f; C.lkY = -LOOK_Y * 0.9f;
  C.wGX = -LOOK_X * 0.95f; C.wGY = LOOK_Y * 0.95f; C.wDX = -4; C.wDY = 6;
  C.lean = 3;
  return C;
}
static SpinCfg bootCfgRight() {         // ANIMACAO B: roleta rapidissima pra direita
  SpinCfg C;
  C.L = 215; C.cull = 215; C.ux = 1; C.uy = 0;
  C.tWind = 120; C.tScroll = 2700; C.tSettle = 700; C.tHold = 700;
  C.ramp = 0.06f; C.pw = 2.1f; C.ovs = 16;
  C.stX = 0.18f; C.stY = -0.10f;
  C.lkX = LOOK_X; C.lkY = 0;
  C.wGX = -LOOK_X; C.wGY = 0; C.wDX = -9; C.wDY = 0;
  C.lean = 5;
  return C;
}
static void bootSpin(const uint8_t *seq, int N, const SpinCfg &C) {
  Face &F = gFace;
  const float B = BOOT_TIME_SCALE;
  profBuild(C.ramp, C.pw);
  const float tW = C.tWind * B, tS = C.tScroll * B, tT = C.tSettle * B, tH = C.tHold * B, TOT = tW + tS + tT + tH;
  const float D = (N - 1) * C.L;
  int lastIdx = 0; bool burst = false;
  uint32_t t0 = millis();
  for (;;) {
    uint32_t nowm = millis();
    float ts = (float)(nowm - t0);
    if (ts >= TOT) break;
    float gx = 0, gy = 0, bl = 0, pos = 0, spd = 0;
    Ov O = {0, 0, 0, 1.0f};
    if (ts < tW) {                                                         // preparo: olha pra la, "agacha"
      float gk = ease(ts / fminf(tW * 0.55f, 450.0f * B));
      gx = C.wGX * gk; gy = C.wGY * gk;
      float cr = ease((ts - (tW - 200.0f * B)) / (200.0f * B));
      O.dx = C.wDX * cr; O.dy = C.wDY * cr; O.zoom = 1.0f - 0.04f * cr; O.rot = -1.2f * C.lean * gk;
      if (tW > 900.0f * B) bl = bootBlink(ts - 120.0f * B, 85, 35, 240);
    } else if (ts < tW + tS) {                                             // DISPARA: a fila corre
      float u = (ts - tW) / tS;
      pos = D * profAt(u); spd = profSpd(u);
      float gk = ease(u / 0.18f), cr = 1.0f - ease(u / 0.10f);
      gx = lerpf(C.wGX, C.lkX, gk); gy = lerpf(C.wGY, C.lkY, gk);
      O.dx = C.wDX * cr; O.dy = C.wDY * cr; O.zoom = 1.0f - 0.04f * cr;
      O.rot = C.lean * spd - 1.2f * C.lean * (1.0f - gk);
      int idx = (int)((pos + C.L * 0.5f) / C.L);                           // passou um rosto: brilhinho
      if (idx != lastIdx) { lastIdx = idx; if (idx < N - 1) glintSpawn(2, nowm, 120, 112, 80, 5, 9); }
    } else {                                                               // freia com um tranquinho, pisca e fica
      float el = ts - tW - tS, tau = el * 0.001f / B;
      pos = D + C.ovs * sinf(tau * 18.0f) * expf(-tau * 6.5f);
      float gk = ease(el / (260.0f * B));
      gx = C.lkX * (1.0f - gk); gy = C.lkY * (1.0f - gk);
      O.zoom = 1.0f + 0.05f * expf(-tau * 9.0f);
      O.rot = C.lean * 0.8f * sinf(tau * 20.0f) * expf(-tau * 8.0f);
      if (tH > 0) bl = bootBlink(el - 200.0f * B, 85, 35, 240);
      if (!burst) { burst = true; glintSpawn(6, nowm, 120, 112, 84, 6, 12); }
    }
    F.nEyes = 0; F.bg[0] = F.bg[1] = F.bg[2] = 0;
    if (spd > 0.12f) bootStreaks(F, pos, spd, C.ux, C.uy);
    for (int i = 0; i < N; i++) {
      float al = pos - i * C.L;                                            // distancia do rosto i ao centro (ao longo da direcao)
      if (fabsf(al) > C.cull) continue;
      Style S = STY[seq[i]];
      S.rx *= 1.0f + C.stX * spd; S.ry *= 1.0f + C.stY * spd;              // estica os olhos na velocidade
      Ov Oi = O; Oi.dy += al * C.uy;
      addEyes(F, S, bl, gx, gy, 1.0f, Oi, al * C.ux);
    }
    glintDraw(F, nowm);
    showFace();
  }
}

// ============================ PROGRAMA ============================
static Style cur, mid;
void setup() {
  initStyles();
#if CHARGE_PIN >= 0
  pinMode(CHARGE_PIN, INPUT_PULLUP);
#endif
  gc9a01Init();
#if LOGO_INTRO
  logoFillWhite();                    // v8: comeca em tela BRANCA (a logo aparece em fade-in sobre ela)
#else
  clearScreen();
#endif
  bleInit();
  initReacts();
  cur = STY[0];
#if LOGO_INTRO
  logoIntro();                        // v8: logo da Starlyn Infinite: fade-in -> 5 s -> fade-out
#endif
#if BOOT_INTRO
  bootBall();                         // v10.1: bolinha quica e enche a tela
  bootStains();                       // v10.1: manchas cinza -> se partem em dois -> olhos
  {
    uint8_t sa[9], sb[14];
    bootMakeSeq(sa, 9, bootF0, random(NFACES));
    bootSpin(sa, 9, bootCfgUp());                  // animacao A: olha pra baixo na diagonal e os rostos sobem trocando
    bootMakeSeq(sb, 14, sa[8], BOOT_FINAL_FACE >= 0 ? BOOT_FINAL_FACE : random(NFACES));
    bootStyle = sb[13];
    bootSpin(sb, 14, bootCfgRight());              // animacao B: roleta pra direita; o ultimo rosto fica
  }
  cur = STY[bootStyle];
#endif
  mid = cur;                          // v11: estagio intermediario da suavizacao comeca igual ao rosto atual
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
  long sum = 0;                       // calibra o silencio (fique quieto ~0,5 s ao ligar)
  for (int i = 0; i < 40; i++) { sum += micRead(); delay(10); }
  micBase = (int)(sum / 40) * 13 / 10 + 8;
  uint32_t n = millis();
  lastMs = n;
  baseSt = bootStyle;                                // o rosto que caiu na roleta FICA no display
  nextMorph = n + random(MORPH_MIN, MORPH_MAX);      // 1a troca de rosto (com fumaca)
  nextMood = n + random(MOOD_MIN, MOOD_MAX);         // v7.1: comeca no olhar normal (sem humor triste ao ligar)
  nextBlink = n + random(1200, 2500);
  nextSacc = n + random(800, 1800);
  nextMicro = n; nextFlick = n + random(4000, 9000);
  nextAct = n + random(FIRST_ACT_MIN, FIRST_ACT_MAX);
  lastSpin = n - (SPIN_COOLDOWN - 6000);   // 1a cambalhota pode sair depois de ~6 s
}

void loop() {
  uint32_t now = millis();
  float dt = (float)(now - lastMs);
  if (dt < 1) dt = 1;
  if (dt > 100) dt = 100;
  lastMs = now;

  // ---------- microfone ----------
  int raw = micRead();
  micLevel = (raw > micLevel) ? raw : (micLevel * 3 + raw) / 4;
  int lvl = micLevel - micBase; if (lvl < 0) lvl = 0;
  if (lvl > TALK_DELTA) {
    if (now - lastTalk > 300) { talkStart = now; listenSide = rsign(); }
    lastTalk = now;
  }
  bool talking = micReact && (lastTalk != 0) && (now - lastTalk < 500) && (now - talkStart > 350);
  listenF += ((talking ? 1.0f : 0.0f) - listenF) * clampf(dt / 150.0f, 0, 1);
  talkOpen += (clampf((lvl - TALK_DELTA) / (LOUD_DELTA * 0.45f), 0, 1) - talkOpen) * 0.5f;

  if (micReact && lvl > LOUD_DELTA && act != A_SPIN && now - lastStartle > 900) {   // barulho forte
    bool twice = (lastStartle != 0) && (now - lastStartle < 2600);
    lastStartle = now;
#if DOUBLE_CLAP_SPIN
    if (twice) startAction(A_SPIN, now);
    else
#endif
    if (act != A_SURPRISE) startAction(A_SURPRISE, now);
  }
  // ---------- v12: carregando (pino CHARGE_PIN ou comando 0x0B) ----------
  {
    static uint32_t chkMs = 0, nextCharge = 0; static int chgCnt = 0;
    int want = -1;
#if CHARGE_PIN >= 0
    if (now - chkMs >= 100) {                                         // le o pino a cada 100 ms e so aceita depois de 6 leituras iguais (0,6 s)
      chkMs = now;
      bool c = (digitalRead(CHARGE_PIN) == CHARGE_ACTIVE);
      if (c != gCharging) { if (++chgCnt >= 6) { want = c ? 1 : 0; chgCnt = 0; } } else chgCnt = 0;
    }
#endif
    if (pendCharge >= 0) { want = pendCharge; pendCharge = -1; }
    if (want >= 0 && (want == 1) != gCharging) {
      gCharging = (want == 1);
      if (gCharging) { pendAct = ACT_CHARGE; nextCharge = now + CHARGE_REPEAT_MS; }                // plugou: toca o raio
      else if (act == A_NONE && !blinkOn) nextBlink = now + 40;                                       // desplugou: pisca e volta ao laranja
    }
    if (gCharging && act == A_NONE && pendAct == 0 && now >= nextCharge) { pendAct = ACT_CHARGE; nextCharge = now + CHARGE_REPEAT_MS; }
  }
  if (pendAct > 0) { int pa = pendAct; pendAct = 0; startAction((Act)pa, now); }                 // comando do site
  if (pendStyle >= 0) {                                                                          // rosto escolhido pelo site
    int ps = pendStyle; pendStyle = -1;
    if (pendStylePerm) permSt = ps; else { permSt = -1; baseSt = ps; nextMorph = now + random(MORPH_MIN, MORPH_MAX); }
  }
  if (talking && act != A_NONE && act != A_SPIN && act != A_SURPRISE) endAction(now);   // parou tudo pra ouvir
  if (autoAct && !manual && permSt < 0 && act == A_NONE && now >= nextMorph && listenF < 0.3f && !talking) startAction(A_MORPH, now);   // troca de rosto
  if (autoAct && !manual && !gCharging && act == A_NONE && now >= nextAct && listenF < 0.3f && !talking) startAction(pickAction(now), now);   // v12: carregando = sem reacoes sorteadas

  // ---------- olhar ----------
  bool listenNow = listenF > 0.3f;
  if (listenNow && !wasListen) { wasListen = true; if (!gazeLock) gazeTo(0, 0, now); }
  if (listenF < 0.15f) wasListen = false;
  if (extGaze && !gazeLock && (gTX != extGX || gTY != extGY)) gazeTo(extGX, extGY, now);      // olhar controlado pelo site
  if (autoGaze && !extGaze && !gazeLock && !listenNow && now >= nextSacc) pickGaze(now);

  float gp = (float)(now - gT0) / (float)gDur;
  if (gp >= 1) { gX = gTX; gY = gTY; }
  else { float ee = gazeCurve(gp); gX = gSX + (gTX - gSX) * ee; gY = gSY + (gTY - gSY) * ee; }   // v10: acelera e freia suave

  // microssacadas (tremidinhas) e "flicks" (2-3 olhadinhas rapidas pro lado)
  if (flickN == 0 && now >= nextFlick) { flickN = 3; flickSign = rsign(); nextFlick = now + random(5000, 11000); nextMicro = now; }
  if (now >= nextMicro) {
    if (flickN > 0) { mtX = flickSign * rf(1.4f, 2.4f); mtY = rf(-0.6f, 0.6f); flickSign = -flickSign; flickN--; nextMicro = now + random(70, 115); }
    else { mtX = rf(-0.9f, 0.9f); mtY = rf(-0.6f, 0.6f); nextMicro = now + random(120, 520); }
  }
  float kM = 1.0f - expf(-dt / 28.0f);
  mcX += (mtX - mcX) * kM; mcY += (mtY - mcY) * kM;
  float trX = 0.22f * sinf(now * 0.043f) + 0.15f * sinf(now * 0.071f + 1.3f);   // tremor finissimo
  float trY = 0.18f * sinf(now * 0.057f + 0.7f) + 0.10f * sinf(now * 0.083f);

  // ---------- piscar ----------
  if (pendBlink) { pendBlink = false; if (!blinkOn) startBlink(now); }
  if (autoBlink && !blinkOn && now >= nextBlink) {
    if (act == A_SURPRISE || act == A_SPIN) nextBlink = now + 300; else startBlink(now);
  }
  float bl = blinkFactor(now);

  // ---------- estilo (rosto) + movimento do rosto ----------
  goX = 0; goY = 0; morphTau = 110; smokeP = -1; gLidX = 0;
  Style T = STY[styleNow(now)];
  if (now >= nextMood) pickMood(now);                                // humor triste que muda sozinho
  float kMd = 1.0f - expf(-dt / 650.0f);
  msCT += (mdCT - msCT) * kMd; msCB += (mdCB - msCB) * kMd; msLid += (mdLid - msLid) * kMd;
  msSq += (mdSq - msSq) * kMd; msRot += (mdRot - msRot) * kMd; msSX += (mdSX - msSX) * kMd; msSY += (mdSY - msSY) * kMd;
  if (act == A_NONE) {
    T.cutTop = clampf(T.cutTop + msCT + 0.06f * clampf(gY / LOOK_Y, 0, 1), 0, 0.6f);   // v11: olhando pra baixo a palpebra desce um tico
    T.cutBot = clampf(T.cutBot + msCB, 0.0f, 0.5f);
    T.lid += msLid; T.squint = clampf(T.squint + msSq, 0, 0.9f); T.rot += msRot;
    T.rx *= msSX; T.ry *= msSY;                                      // v12
  }
  float kH = 1.0f - expf(-dt / 240.0f);                              // cabeca acompanha o olhar com atraso
  hx += (gX * (HEAD_TURN ? 0.95f : 0.30f) - hx) * kH; hy += (gY * 0.30f - hy) * kH;   // v12: a cabeca desliza bem mais (virada de cabeca)
  gTurn = clampf(hx / (LOOK_X * 0.8f), -1.0f, 1.0f);                  // v12: perspectiva dos olhos
  Ov O;
  O.rot  = 1.2f * sinf(now * 0.00042f) + 0.7f * sinf(now * 0.00117f + 2.0f) + listenSide * 6.5f * listenF;
  O.dx   = 1.0f * sinf(now * 0.0009f + 1.0f) + hx;
  O.dy   = 1.4f * sinf(now * 0.0013f) + hy;
  O.zoom = 1.0f + 0.008f * sinf(now * 0.0013f + 0.8f);
  memset(&gDeco, 0, sizeof(gDeco));                                  // v9: enfeites desligados (a reacao liga os que quiser)
  gFlash = 0;                                                        // v9.1: flash branco desligado (a reacao Foto! liga)
  actionTick(now, T, O);
  if (gCharging && act == A_NONE) chargeLook(T, 1.0f);              // v12: enquanto carrega o Starboy fica VERDE (pupila laranja)
  bl = fmaxf(bl, gLidX);                                             // v10: animacao fechando as palpebras
  goY += BLINK_DIP * bl;                                             // v10: o olhar desce um tico ao fechar
  float br = 1.0f + 0.012f * sinf(now * 0.0013f);                    // o olho "respira"
  T.rx *= br; T.ry *= br;
  T.ps *= 1.0f + 0.020f * sinf(now * 0.0019f) + 0.012f * sinf(now * 0.0047f + 1.0f);   // v11: pupila "respira" (bem sutil)
  if (colorHold) { T.er = T.er2 = colR; T.eg = T.eg2 = colG; T.eb = T.eb2 = colB; T.gA = 0; }   // cor escolhida no site (nos dois olhos)
  if (manual) {                                                      // CONTROLE TOTAL pelo site
    T.rot = man[8] * (TILT_PINK / 9.0f); T.rx *= man[9]; T.ry *= man[9]; T.ps = man[10]; T.squint = man[11]; T.conv = man[12];
    T.winkL = man[13]; T.winkR = man[14];
    O.rot = man[15]; O.dx = man[16]; O.dy = man[17]; O.zoom = man[18]; morphTau = 60;
  }

  if (listenF > 0.02f) {                                             // ouvindo: arregala
    float lf = listenF;
    T.rx *= 1 + 0.06f * lf; T.ry *= 1 + 0.06f * lf; T.ps *= 1 + (0.10f + 0.1f * talkOpen) * lf;
    if (listenF > 0.3f && act == A_NONE) morphTau = 55;
  }
  if (snapCur) { cur = T; mid = T; snapCur = false; }                         // troca de rosto: entra de uma vez (escondido pela fumaca)
  // v7: correcao - a curvatura do olho fechado nao "vira" de u para ^ (ou ao contrario) enquanto o traco aparece/some
  if (T.arc >= 0.5f) { if (mid.arc < 0.03f) mid.bend = T.bend; if (cur.arc < 0.03f) cur.bend = T.bend; }   // vai fechar: ja comeca na curva certa
  else T.bend = cur.bend;                                          // vai abrir: mantem a curva ate o traco sumir
  float *cf = (float *)&cur, *mf = (float *)&mid; const float *tf = (const float *)&T;
  float kk = 1.0f - expf(-dt / (morphTau * 0.6f));      // v11: 2 estagios em cascata = comeca suave, acelera e freia (sem tranco)
  for (int i = 0; i < (int)(sizeof(Style) / sizeof(float)); i++) { mf[i] += (tf[i] - mf[i]) * kk; cf[i] += (mf[i] - cf[i]) * kk; }

  // ---------- desenha ----------
  float gl = hypotf(gX / 14.0f, gY / 14.0f);
  float convEff = cur.conv * (1.0f - 0.6f * clampf(gl, 0, 1));       // olhando de lado, as pupilas ficam menos viradas pra dentro
  float gx = gX + mcX + trX + goX, gy = gY + mcY + trY + goY;
  gFace.nEyes = 0; gFace.bg[0] = gFace.bg[1] = gFace.bg[2] = 0;      // FUNDO SEMPRE 100% PRETO
  gAnimT = now * 0.001f;                                              // v9.1: tempo em segundos (espiral, galaxia, loading)
  addEyes(gFace, cur, bl, gx, gy, convEff, O, 0);
  addDeco(gFace, now);                                                // v9: brilhinhos, coracoes, lagrimas, Zzz...
  if (smokeP >= 0) addSmoke(gFace, smokeP);                           // nuvem de fumaca da troca de rosto
  showFace();
  static uint32_t nextTx = 0;
  if (bleConn && now >= nextTx) {
    nextTx = now + 70;
    float clL = fmaxf(bl, fmaxf(cur.squint, cur.winkL)), clR = fmaxf(bl, fmaxf(cur.squint, cur.winkR));
    bleSend(cur, clL, clR, gx, gy, convEff, O, lvl, talking, listenF > 0.3f);
  }
  delay(1);
}
