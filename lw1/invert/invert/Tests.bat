SET MyProgram="%~1"

REM Test 1 : Из меньшего основания в большее
%MyProgram% "10" "16" "15" > "%TEMP%\out.txt" || goto err
echo F> "output.txt"
fc "%TEMP%\out.txt" "output.txt" > nul || goto err
echo Test 1 passed
