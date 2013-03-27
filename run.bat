@echo off
pushd F:\FlasCC
set FLASCC_ROOT=F:\FlasCC
set path=%path%;%FLASCC_ROOT%\cygwin\bin;%FLASCC_ROOT%\cygwin\usr\X11R6\bin

if not exist cygwin\home\flasccuser\setup.txt (
	echo cygwin setup > cygwin\home\flasccuser\setup.txt
	echo First run setup, please wait...
	cygwin\bin\mkpasswd.exe -l -c > cygwin\etc\passwd
	cygwin\bin\mkgroup.exe -l -c > cygwin\etc\group
	cygwin\bin\chmod.exe -R ug+rw cygwin
)

if [%1] == [] (
cygwin\bin\bash --login -i
) else (
:: to support automation
cygwin\bin\bash --login %*
cd D:\Workspace\Flascc\OmniDebuggerProject\OmniDebuggerSWC
)
popd

