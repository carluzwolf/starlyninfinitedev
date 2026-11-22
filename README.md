# Starlyn Studio – painel do robô Karlu (Starboy v12 BLE)

Site estático (sem build). Suba estes arquivos na raiz do repositório, mantendo a pasta `assets/`:

- `index.html`, `style.css`, `app.js`, `export.js`
- `starboy_v12_ble.ino` (arquivo-base; o botão "Baixar .ino" parte dele)
- `assets/logo.png`, `assets/logo-olhos.png`

Vercel: importe o repositório como projeto estático (sem comando de build). O Bluetooth só funciona em HTTPS (a Vercel já dá) e no Google Chrome.

Ids no robô: olhos criados = 77 a 92 · reações criadas = 130 a 137.
