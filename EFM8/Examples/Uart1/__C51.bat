@echo off
::This file was created automatically by CrossIDE to compile with C51.
C:
cd "\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Examples\Uart1\"
"C:\CrossIDE\Call51\Bin\c51.exe" --use-stdout  "C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Examples\Uart1\EFM8_uart1_test.c"
if not exist hex2mif.exe goto done
if exist EFM8_uart1_test.ihx hex2mif EFM8_uart1_test.ihx
if exist EFM8_uart1_test.hex hex2mif EFM8_uart1_test.hex
:done
echo done
echo Crosside_Action Set_Hex_File C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Examples\Uart1\EFM8_uart1_test.hex
