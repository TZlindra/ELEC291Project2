@echo off
::This file was created automatically by CrossIDE to compile with C51.
C:
cd "\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\JDY40\"
"C:\CrossIDE\Call51\Bin\c51.exe" --use-stdout  "C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\JDY40\EFM8_JDY40_test.c"
if not exist hex2mif.exe goto done
if exist EFM8_JDY40_test.ihx hex2mif EFM8_JDY40_test.ihx
if exist EFM8_JDY40_test.hex hex2mif EFM8_JDY40_test.hex
:done
echo done
echo Crosside_Action Set_Hex_File C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\JDY40\EFM8_JDY40_test.hex
