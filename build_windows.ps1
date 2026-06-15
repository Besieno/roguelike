$ErrorActionPreference = "Stop"

$root = Split-Path -Parent $MyInvocation.MyCommand.Path
$compiler = "C:\msys64\ucrt64\bin\g++.exe"
$raylibDll = "C:\msys64\ucrt64\bin\libraylib.dll"
$buildDir = Join-Path $root "build"
$output = Join-Path $buildDir "roguelike.exe"

if (!(Test-Path $compiler)) {
    throw "g++ nao encontrado em $compiler. Instale o MSYS2 UCRT64 e o pacote mingw-w64-ucrt-x86_64-gcc."
}

New-Item -ItemType Directory -Force -Path $buildDir | Out-Null

$sources = @(
    "main.cpp",
    "src\Combat.cpp",
    "src\Enemy.cpp",
    "src\Game.cpp",
    "src\Item.cpp",
    "src\Map.cpp",
    "src\NPC.cpp",
    "src\Player.cpp",
    "src\UI.cpp",
    "src\Utils.cpp"
)

Push-Location $root
try {
    & $compiler -std=c++17 -Wall -Wextra -pedantic @sources `
        -I"C:\msys64\ucrt64\include" `
        -L"C:\msys64\ucrt64\lib" `
        -lraylib -lopengl32 -lgdi32 -lwinmm `
        -o $output

    if (Test-Path $raylibDll) {
        Copy-Item $raylibDll (Join-Path $buildDir "libraylib.dll") -Force
    }

    Write-Host "Build concluido: $output"
}
finally {
    Pop-Location
}
