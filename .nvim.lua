local null_ls = require("null-ls")
local lspconfig = require("lspconfig")
local opts = { noremap = true, silent = true }
local keymap = vim.keymap.set
local capabilities = require("cmp_nvim_lsp").default_capabilities()

lspconfig.ccls.setup({
  capabilities = capabilities,
  on_attach = on_attach,
})
