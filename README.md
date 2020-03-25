# Programmer's Notepad 2 Dialog Helper Extension

Extension for Programmer's Notepad 2 which fixes Save file dialog usability by setting focus on OK button.
![alt text](https://github.com/T800G/PN2DialogHelper/blob/master/sshot.png "screenshot")

## Minimum system requirements
Windows XP

## Install/Remove
1. Copy PNdlgHelper.dll file to the application fodler (for portable version) or some other appropriate folder (for installation version).

2. Open config.xml file in the application fodler (for portable version) or %APPDATA%\Echo Software\PN2 folder (for installation version) and add the following line before </config> tag:
    <extension path="PNdlgHelper.dll"/>
For installation version path must be full, eg. "D:\T800\Visual Studio 2008\Projects\PNdlgHelper\Release\PNdlgHelper.dll".

3. To remove the extension, delete the dll file and remove the line from config.xml file.
