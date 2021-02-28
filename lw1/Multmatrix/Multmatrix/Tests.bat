SET MyProgram="%~1"

REM Test 1 : Работа с целыми числами
%MyProgram% "fm1.txt" "sm.txt" > "%TEMP%\out.txt" || goto err
fc "%TEMP%\out.txt" "om1.txt" > nul || goto err
echo Test 1 passed

REM Test 2 : Работа с вещественными числами
%MyProgram% "fm2.txt" "sm.txt" > "%TEMP%\out.txt" || goto err
fc "%TEMP%\out.txt" "om2.txt" > nul || goto err
echo Test 2 passed

REM Test 3 : Число выходящее за пределы типа данных
%MyProgram% "fm3.txt" "sm.txt" > "%TEMP%\out.txt" && goto err
echo Test 3 passed

REM Test 4 : Граничное значение
%MyProgram% "fm4.txt" "sm.txt" > "%TEMP%\out.txt" || goto err
fc "%TEMP%\out.txt" "om4.txt" > nul || goto err
echo Test 4 passed

REM Test 5 : Отсутствие одного из аргументов
%MyProgram% "fm3.txt" > "%TEMP%\out.txt" && goto err
echo Test 5 passed

REM Test 6 : Один из аргументов пустой
%MyProgram% "fm3.txt" "" > "%TEMP%\out.txt" && goto err
echo Test 6 passed
echo All tests passed
exit /b 0

:err
echo Test failed
exit /B 1