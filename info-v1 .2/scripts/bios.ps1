# displayname: show BIOS
# tree: diverse powershell
# author: Rene Storm
# version: 1.0
# interpreter: powershell.exe

param( [string]$strComputer = "." )
 

$colItems = get-wmiobject -class "Win32_BIOS" -namespace "root\CIMV2" -computername $strComputer

 

foreach ($objItem in $colItems) {

	write-host "Name                           :" $objItem.Name

    write-host "Bios Version                   :" $objItem.BIOSVersion

	write-host "Version                        :" $objItem.Version

	write-host "Manufacturer                   :" $objItem.Manufacturer

	write-host "SMBIOSBIOS Version             :" $objItem.SMBIOSBIOSVersion
    
    write-host "BIOS ReleaseDate               :" $objItem.ReleaseDate

    write-host "BIOS SerialNumber               :" $objItem.SerialNumber
    
	write-host

}