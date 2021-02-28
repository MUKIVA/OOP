SET MyProgram="%~1"

REM Test 1 : ������ � ������ �������
%MyProgram% "fm1.txt" "sm.txt" > "%TEMP%\out.txt" || goto err
fc "%TEMP%\out.txt" "om1.txt" > nul || goto err
echo Test 1 passed

REM Test 2 : ������ � ������������� �������
%MyProgram% "fm2.txt" "sm.txt" > "%TEMP%\out.txt" || goto err
fc "%TEMP%\out.txt" "om2.txt" > nul || goto err
echo Test 2 passed

REM Test 3 : ����� ��������� �� ������� ���� ������
%MyProgram% "fm3.txt" "sm.txt" > "%TEMP%\out.txt" && goto err
echo Test 3 passed

REM Test 4 : ��������� ��������
%MyProgram% "fm4.txt" "sm.txt" > "%TEMP%\out.txt" || goto err
fc "%TEMP%\out.txt" "om4.txt" > nul || goto err
echo Test 4 passed

REM Test 5 : ���������� ������ �� ����������
%MyProgram% "fm3.txt" > "%TEMP%\out.txt" && goto err
echo Test 5 passed

REM Test 6 : ���� �� ���������� ������
%MyProgram% "fm3.txt" "" > "%TEMP%\out.txt" && goto err
echo Test 6 passed
echo All tests passed
exit /b 0

:err
echo Test failed
exit /B 1