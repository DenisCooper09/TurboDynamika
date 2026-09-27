$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition
$ParentDir = [System.IO.Path]::GetFullPath((Join-Path -Path $ScriptDir -ChildPath ".."))

$TxtFile = Join-Path -Path $ScriptDir -ChildPath "ToZip.txt"

if (-not (Test-Path $TxtFile)) {
    Write-Error "Configuration file not found! Please create: $TxtFile"
    exit
}

$TargetPaths = Get-Content -Path $TxtFile | Where-Object { $_ -match '\S' }

foreach ($RelativePath in $TargetPaths) {
    $SourcePath = [System.IO.Path]::GetFullPath((Join-Path -Path $ParentDir -ChildPath $RelativePath))
    
    if (Test-Path $SourcePath) {
        $ZipDestination = "$SourcePath.zip"
        $CleanSource = (Get-Item $SourcePath).FullName
        
        Write-Host "Archiving: $RelativePath -> $(Split-Path $ZipDestination -Leaf)" -ForegroundColor Cyan
        
        Compress-Archive -Path $CleanSource -DestinationPath $ZipDestination -Force
    } else {
        Write-Warning "Target item not found relative to parent folder, skipping: $RelativePath"
    }
}

Write-Host "Compression completed successfully!" -ForegroundColor Green
