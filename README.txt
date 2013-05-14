This is info.exe, Version 1.0

Just copy to your favorite folder and execute. You can add a shortcut to your autostart folder, if you like to.

It is a small Tool which hides in the system tray and shows some information on double click.
It is able to execute cmd batch files which are located under a script folder beneath the executable.

Batch files have to start with following information:
Example Batch:

@echo off
rem displayname: ipconfig /all
rem tree: network ipconfig
rem author: Rene Storm
rem version: 1.0
ipconfig /all


Have fun,
Rene

Changelog:
- getInterfaces() on startup wihout writing log -> SystemTrayIcon filled after startup

- Write log only on activation (raise()) to prefent writng a logfile every day

- change logfile path
	logfilePath=appPath + "\\log_" + qgetenv("USERNAME") + "_" + dt.toString("ddMMyy") + ".txt";

- Changed Working Directory
	//installPath=QDir(QDir::currentPath() + "\\scripts");
	installPath=QDir(qApp->applicationDirPath()  + "\\scripts");

- raise Window on systemtray doubleclick, Window get to focus
	//show();
	raise();