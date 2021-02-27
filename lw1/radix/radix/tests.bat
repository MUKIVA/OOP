SET MyProgram="%~1"

REM Test 1 : �� �������� ��������� � �������
%MyProgram% "10" "16" "15" > "%TEMP%\out.txt" || goto err
echo F> "output.txt"
fc "%TEMP%\out.txt" "output.txt" > nul || goto err
echo Test 1 passed
REM Test 2 : �� �������� ��������� � �������
%MyProgram% "16" "10" "F" > "%TEMP%\out.txt" || goto err
echo 15> "output.txt"
fc "%TEMP%\out.txt" "output.txt" > nul || goto err
echo Test 2 passed
REM Test 3 : ������ �������� ������
%MyProgram% "16" "10" "" > "%TEMP%\out.txt" && goto err
echo Test 3 passed
REM Test 4 : ������ �������� ������
%MyProgram% "16" "" "F" > "%TEMP%\out.txt" && goto err
echo Test 4 passed
REM Test 5 : ������ �������� ������
%MyProgram% "" "10" "F" > "%TEMP%\out.txt" && goto err
echo Test 5 passed
REM Test 6 : ���������� ������� �����
%MyProgram% "16" "10" "F" "100" > "%TEMP%\out.txt" && goto err
echo Test 6 passed
REM Test 7 : ���������� ������� ����
%MyProgram% "16" "10" > "%TEMP%\out.txt" && goto err
echo Test 7 passed
REM Test 8 : �������� �������� ����� 0
%MyProgram% "16" "10" "0" > "%TEMP%\out.txt" || goto err
fc "%TEMP%\out.txt" "zero.txt" > nul || goto err
echo Test 8 passed
REM Test 9 : ������� �������������� �����
%MyProgram% "16" "10" "-F" > "%TEMP%\out.txt" || goto err
echo -15> "output.txt"
fc "%TEMP%\out.txt" "output.txt" > nul || goto err
echo Test 9 passed
REM Test 10 : ���� ����� ��������� ��� ������
%MyProgram% "10" "16" "2147483648" > "%TEMP%\out.txt" && goto err
echo Test 10 passed
REM Test 11 : �������� �������� ��������
%MyProgram% "10" "16" "2147483647" > "%TEMP%\out.txt" || goto err
echo 7FFFFFFF> "output.txt"
fc "%TEMP%\out.txt" "output.txt" > nul || goto err
echo Test 11 passed
REM Test 12 : ������� ��������� ��������� �� ������� ������������ ���������
%MyProgram% "37" "16" "15" > "%TEMP%\out.txt" && goto err
echo Test 12 passed
REM Test 13 : �������� ������������ ������ ������� �����
%MyProgram% "10" "16" "1@5" > "%TEMP%\out.txt" && goto err
echo Test 13 passed
REM ����� ������ �������
exit /B 0


REM � ������ ������������ ������
:err
echo Test failed
exit /B 1