# File: ExportEmails.ps1
$Outlook = New-Object -ComObject Outlook.Application
$Namespace = $Outlook.GetNamespace("MAPI")
$Inbox = $Namespace.GetDefaultFolder(6)  # Inbox

$OutputFolder = "C:\Users\Apple\Downloads\Sereywath\emails"
if (-Not (Test-Path $OutputFolder)) { New-Item -ItemType Directory -Path $OutputFolder }

$i = 1
foreach ($mail in $Inbox.Items) {
    $filename = "$OutputFolder\email_$i.eml"
    $mail.SaveAs($filename, 3)  # 3 = olRFC822 format (.eml)
    $i++
}

Write-Host "Exported $i emails to $OutputFolder"