SET MyProgram="%~1"

REM Test 1 : ������ � ����������� ��������� � ��������
%MyProgram% "in1.txt" "%TEMP%\out.txt" || goto err
fc "%TEMP%\out.txt" "out1.txt" > nul || goto err
echo Test 1 passed
REM Test 2 : ������ � ����������� ��������� � �����������
%MyProgram% "in2.txt" "%TEMP%\out.txt" || goto err
fc "%TEMP%\out.txt" "out2.txt" > nul || goto err
echo Test 2 passed
REM Test 3 : ������ ��� ������
%MyProgram% "in3.txt" "%TEMP%\out.txt" || goto err
fc "%TEMP%\out.txt" "out3.txt" > nul || goto err
echo Test 3 passed
REM Test 4 : ������ ����
%MyProgram% "in4.txt" "%TEMP%\out.txt" || goto err
fc "%TEMP%\out.txt" "out4.txt" > nul || goto err
echo Test 4 passed
REM Test 5 : �������� ������������ ������
%MyProgram% "in5.txt" "%TEMP%\out.txt" && goto err
echo Test 5 passed
REM ����� ������ �������
exit /B 0


REM � ������ ������������ ������
:err
echo Test failed
exit /B 1