# Chengdu IR/OCV

This is the independent `dhsys21/IROCV_Cheungdu` repository. Inspect git status before edits, preserve unrelated changes, and keep commits separate from PRECHARGER. Do not commit IDE-local state or build outputs.

For every application code/UI modification batch, update `BaseForm.Caption` in `RVMO_main.dfm` as `IR/OCV (Ver.YYMMDD NNN)` using the Asia/Seoul date. Start at 001 on a new day; increment the three-digit revision for subsequent batches. Keep the version visible at design time. Third-party control Version properties are not the application version.

Edit translations in `LanguageCatalog.tsv`, then run `GenerateLanguages.ps1` and `TestLanguages.ps1`. Do not translate equipment commands, PLC identifiers, CSV values, or persisted diagnostic logs.
