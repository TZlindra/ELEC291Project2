@echo off
::This file was created automatically by CrossIDE to compile with C51.
C:
cd "\Users\Lenovo\Desktop\ELEC 291\EFM8\JDY40\JDY40\"
"C:\Users\Lenovo\Desktop\ELEC 291\CrossIDE\CrossIDE\Call51\Bin\c51.exe" --use-stdout  "C:\Users\Lenovo\Desktop\ELEC 291\EFM8\JDY40\JDY40\EFM8_JDY40_test.c"
if not exist hex2mif.exe goto done
if exist EFM8_JDY40_test.ihx hex2mif EFM8_JDY40_test.ihx
if exist EFM8_JDY40_test.hex hex2mif EFM8_JDY40_test.hex
:done
echo done
echo Crosside_Action Set_Hex_File C:\Users\Lenovo\Desktop\ELEC 291\EFM8\JDY40\JDY40\EFM8_JDY40_test.hex
