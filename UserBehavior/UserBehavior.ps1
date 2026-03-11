# File: UserBehavior.ps1

$OutputCSV = "user_activity_report.csv"

# Get login events (Event ID 4624 = successful login)
$logins = Get-WinEvent -FilterHashtable @{LogName='Security'; Id=4624} |
          Select-Object TimeCreated, @{Name='User';Expression={$_.Properties[5].Value}}

# Group by user and count logins
$report = $logins | Group-Object User | Select-Object Name,@{Name='LoginCount';Expression={$_.Count}}
$report | Export-Csv -Path $OutputCSV -NoTypeInformation

Write-Host "Report saved to $OutputCSV"

# Detect unusual login hours (e.g., midnight-6AM)
$unusual = $logins | Where-Object { ($_.TimeCreated.Hour -ge 0) -and ($_.TimeCreated.Hour -le 6) }
$unusual | Export-Csv -Path "unusual_hours.csv" -NoTypeInformation
Write-Host "Unusual login hours saved to unusual_hours.csv"