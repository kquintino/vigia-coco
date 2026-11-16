// Confere o ambiente antes de iniciar o painel (roda sozinho no "npm start").
const fs = require('fs')
const path = require('path')

const partes = process.versions.node.split('.').map(Number)
if (partes[0] < 22 || (partes[0] === 22 && partes[1] < 9)) {
  console.error('\nSeu Node.js é o ' + process.version + '. O Node-RED 5 precisa do Node.js 22.9 ou mais recente.')
  console.error('Instale a versão LTS em https://nodejs.org, feche e abra o terminal e rode "npm install" de novo.\n')
  process.exit(1)
}

const raiz = path.join(__dirname, '..')
const faltando = ['node-red', '@flowfuse/node-red-dashboard'].filter(function (modulo) {
  return !fs.existsSync(path.join(raiz, 'node_modules', modulo, 'package.json'))
})
if (faltando.length > 0) {
  console.error('\nFalta instalar: ' + faltando.join(', ') + '. Rode "npm install" nesta pasta e depois "npm start".\n')
  process.exit(1)
}

const porta = process.env.PORT || 1880
console.log('\nVigia Cocó: iniciando o Node-RED.')
console.log('  Painel: http://localhost:' + porta + '/dashboard')
console.log('  Editor: http://localhost:' + porta)
console.log('  Para parar: Ctrl+C\n')
