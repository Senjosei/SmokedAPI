# Usage:
# PS ..\SmokedAPI> .\build.ps1 64 Debug

Set-Location (Get-Item $PSScriptRoot)

. ./KoalaBox/build.ps1 SmokedAPI @args

Build-Project
