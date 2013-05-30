rem displayname: hardware timezone
rem tree: diverse vbs
rem author: Rene Storm
rem version: 1.0
rem interpreter: cscript.exe

On Error Resume Next

strComputer = "."
Set objWMIService = GetObject("winmgmts:" _
    & "{impersonationLevel=impersonate}!\\" & strComputer & "\root\cimv2")

Set colItems = objWMIService.ExecQuery("Select * from Win32_TimeZone")

Set stdout = WScript.StdOut

For Each objItem in colItems
    stdout.WriteLine "Bias: " & objItem.Bias
    stdout.WriteLine "Caption: " & objItem.Caption
    stdout.WriteLine "Daylight Bias: " & objItem.DaylightBias
    stdout.WriteLine "Daylight Day: " & objItem.DaylightDay
    stdout.WriteLine "Daylight Day of Week: " & objItem.DaylightDayOfWeek
    stdout.WriteLine "Daylight Hour: " & objItem.DaylightHour
    stdout.WriteLine "Daylight Millisecond: " & objItem.DaylightMillisecond
    stdout.WriteLine "Daylight Minute: " & objItem.DaylightMinute
    stdout.WriteLine "Daylight Month: " & objItem.DaylightMonth
    stdout.WriteLine "Daylight Name: " & objItem.DaylightName
    stdout.WriteLine "Daylight Second: " & objItem.DaylightSecond
    stdout.WriteLine "Daylight Year: " & objItem.DaylightYear
    stdout.WriteLine "Description: " & objItem.Description
    stdout.WriteLine "Setting ID: " & objItem.SettingID
    stdout.WriteLine "Standard Bias: " & objItem.StandardBias
    stdout.WriteLine "Standard Day: " & objItem.StandardDay
    stdout.WriteLine "Standard Day of Week: " & objItem.StandardDayOfWeek
    stdout.WriteLine "Standard Hour: " & objItem.StandardHour
    stdout.WriteLine "Standard Millisecond: " & objItem.StandardMillisecond
    stdout.WriteLine "Standard Minute: " & objItem.StandardMinute
    stdout.WriteLine "Standard Month: " & objItem.StandardMonth
    stdout.WriteLine "Standard Name: " & objItem.StandardName
    stdout.WriteLine "Standard Second: " & objItem.StandardSecond
    stdout.WriteLine "Standard Year: " & objItem.StandardYear
    stdout.WriteLine
Next