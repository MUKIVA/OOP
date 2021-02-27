SET MyProgram="%~1"

if %MyProgram%=="" (
	echo Please specify path to program
	exit /b 1
)

REM Test 1 : Проверка простой замены
%MyProgram% InTest1.txt "%TEMP%\output.txt" "pog" "god" > nul || goto err
fc "%TEMP%\output.txt" OutTest1.txt > nul || goto err
echo Test 1 : successful
REM Test 2 : Проверка замены "pog" на "pogpog"
%MyProgram% InTest2.txt "%TEMP%\output.txt" "pog" "pogpog" > nul || goto err
fc "%TEMP%\output.txt" OutTest2.txt > nul || goto err
echo Test 2 : successful
REM Test 3 : Проверка замены "pogpog" на "pog"
%MyProgram% InTest3.txt "%TEMP%\output.txt" "pogpog" "pog" > nul || goto err
fc "%TEMP%\output.txt" OutTest3.txt > nul || goto err
echo Test 3 : successful
REM Test 4 : Проверка замены "1231234" на "u"
%MyProgram% InTest4.txt "%TEMP%\output.txt" "1231234" "u" > nul || goto err
fc "%TEMP%\output.txt" OutTest4.txt > nul || goto err
echo Test 4 : successful
REM Test 5 : Проверка на пустые аргументы
%MyProgram% InTest5.txt "%TEMP%\TheFileShouldNotExist.txt" "" "" > nul || goto err
echo Test 5 : successful
REM test 6 : Замена на самого себя
%MyProgram% InTest6.txt "%TEMP%\output.txt" "pog" "pog" > nul || goto err
fc "%TEMP%\output.txt" OutTest6.txt > nul || goto err
echo Test 6 : successful
REM test 7 : Проверка работы с пустым input файлом
%MyProgram% InTest7.txt "%TEMP%\output.txt" "pog" "god" > nul || goto err
fc "%TEMP%\output.txt" OutTest7.txt > nul || goto err
echo Test 7 : successful
REM test 8 : Проверка работы с несколькими строками
%MyProgram% InTest8.txt "%TEMP%\output.txt" "pog" "god" > nul || goto err
fc "%TEMP%\output.txt" OutTest8.txt > nul || goto err
echo Test 8 : successful
REM test 9 : Тест при отсутствии входного файла
%MyProgram% "%TEMP%\TheFileShouldNotExist.txt" "pog" "god" > nul && goto err
echo Test 9 : successful
REM test 10 : Тест на отсутсвие выходного файла
%MyProgram% Input.txt  "pog" "god" > nul && goto err
echo Test 10 : successful
REM test 11 : Тест на отсутсвие искомой подстроки
%MyProgram% input.txt "%TEMP%\TheFileShouldNotExist.txt" "god" > nul && goto err
echo Test 11 : successful
REM test 12 : Тест на отсутсвие замены
%MyProgram% input.txt "%TEMP%\TheFileShouldNotExist.txt" "pog" > nul && goto err
echo Test 12 : successful
REM test 13 : Тест на пустой input
%MyProgram% "" "%TEMP%\TheFileShouldNotExist.txt" "pog" "god"> nul && goto err
echo Test 13 : successful
REM test 14 : Тест на путой out
%MyProgram% input.txt "" "pog" "god" > nul && goto err
echo Test 14 : successful
REM Тесты завершились успешно
echo All tests successful
exit /B 0

REM Один из тестов не прошел
:err
echo Test failed
exit /B 1