mkdir "temp" 2> nul

del "temp\\ACDCTownScript.msg"
del "temp\\ACDCTownScript.msg.lz"

tools\TextPet ^
	Load-Plugins "plugins" ^
	Game MMBN6 ^
	Read-Text-Archives "text_compressed" --recursive --format tpl ^
	Set-Compression true ^
	Write-Text-Archives "temp\\" --format msg

tools\TextPet ^
	Load-Plugins "plugins" ^
	Game MMBN6 ^
	Set-Compression Off ^
	Read-Text-Archives "allstars\\text" --recursive --format tpl ^
	Write-Text-Archives "temp\\" --format msg

:: echo f | xcopy "temp\\ACDCTownScript.msg" "temp\\ACDCTownScript.msg.lz"

:: echo f | xcopy "temp\\ACDCTownScript.msg" "temp\\ACDCTownScript.msg.lz"

tools\armips lzpad.s
tools\lzss -ewn "temp\\ACDCTownScript.msg.lz"

tools\armips src.asm -sym "bn6f-training-mode.sym"
if errorlevel 1 pause