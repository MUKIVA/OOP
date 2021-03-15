SET MyProgram="%~1"

REM Test 1 : Работа с числами типа int
%MyProgram% "in1.txt" > "%TEMP%\out.txt" || goto err
fc "%TEMP%\out.txt" "out1.txt" > nul || goto err
echo Test 1 passed

REM Test 2 : Работа с числами типа float
%MyProgram% "in2.txt" > "%TEMP%\out.txt" || goto err
fc "%TEMP%\out.txt" "out2.txt" > nul || goto err
echo Test 2 passed

REM Test 3 : Если один из коэ-тов записан не на своем месте
%MyProgram% "in3.txt" > "%TEMP%\out.txt" && goto err
echo Test 3 passed

REM Test 4 : Если один из коэ-тов отсутствует
%MyProgram% "in4.txt" > "%TEMP%\out.txt" && goto err
echo Test 4 passed

REM Test 5 : Отсутствует аргумент
%MyProgram%  > "%TEMP%\out.txt" && goto err
echo Test 5 passed

REM Test 6 : Аргумент пустой
%MyProgram% "" > "%TEMP%\out.txt" && goto err
echo Test 6 passed

REM Test 7 : Аргумент пустой
%MyProgram% "in5.txt" > "%TEMP%\out.txt" && goto err
echo Test 7 passed



REM Тесты прошли успешно
exit /B 0
REM В случае воникновения ошибок
:err
echo Test failed
exit /B 1
