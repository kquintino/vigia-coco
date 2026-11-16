// Configuração do Node-RED usada por este projeto (lida pelo "npm start").
module.exports = {
    // O fluxo exportado da Parte 4 é este arquivo. O que você alterar no editor e der Deploy é gravado nele.
    flowFile: 'flows.json',
    flowFilePretty: true,

    // O projeto não guarda senhas: o broker público não usa usuário nem senha.
    credentialSecret: false,

    // Só este computador abre o editor e o painel.
    // Para abrir de outro aparelho da mesma rede, troque para '0.0.0.0'.
    uiHost: '127.0.0.1',
    uiPort: process.env.PORT || 1880,

    // Necessário para o nó "Montar linha do CSV" usar fs, os e path.
    functionExternalModules: true,

    // Não envia dados de uso para o projeto Node-RED nem pergunta sobre isso ao abrir o editor.
    telemetry: { enabled: false },

    logging: {
        console: { level: 'info', metrics: false, audit: false }
    },

    editorTheme: {
        projects: { enabled: false },
        tours: false
    }
}
