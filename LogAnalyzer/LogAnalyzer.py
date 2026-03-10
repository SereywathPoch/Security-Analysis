# File: LogAnalyzer.py
import csv
import json
from collections import defaultdict
from datetime import datetime

# -------------------------------
# Configurations
# -------------------------------
LOG_FILE = "system.log"           # Input log file
REPORT_CSV = "security_report.csv"
REPORT_JSON = "security_report.json"
FAILED_KEYWORDS = ["failed", "error", "unauthorized"]
UNUSUAL_HOURS = (0, 6)  # 12AM - 6AM

# -------------------------------
# Helper Functions
# -------------------------------
def parse_log(line):
    try:
        parts = line.split()
        ip = parts[0]
        timestamp_str = line.split("[")[1].split("]")[0]
        timestamp = datetime.strptime(timestamp_str.split()[0], "%d/%b/%Y:%H:%M:%S")
        request = line.split('"')[1]
        status = int(parts[-2])
        return {"ip": ip, "timestamp": timestamp, "request": request, "status": status, "line": line.strip()}
    except Exception:
        return None

def is_failed(entry):
    return any(k in entry["line"].lower() for k in FAILED_KEYWORDS)

def is_unusual_hour(entry):
    return UNUSUAL_HOURS[0] <= entry["timestamp"].hour <= UNUSUAL_HOURS[1]

# -------------------------------
# Analyze Logs
# -------------------------------
def analyze_logs(log_file):
    failed_logins = defaultdict(list)
    unusual_hours = []

    with open(log_file, "r") as f:
        for line in f:
            entry = parse_log(line)
            if not entry:
                continue
            if is_failed(entry):
                failed_logins[entry["ip"]].append(entry["timestamp"])
            if is_unusual_hour(entry):
                unusual_hours.append(entry)

    return failed_logins, unusual_hours

# -------------------------------
# Generate Reports
# -------------------------------
def generate_reports(failed_logins, unusual_hours):
    # CSV
    with open(REPORT_CSV, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["IP", "Failed_Attempts", "Timestamps"])
        for ip, times in failed_logins.items():
            writer.writerow([ip, len(times), "; ".join([t.strftime("%Y-%m-%d %H:%M:%S") for t in times])])
    print(f"CSV report saved: {REPORT_CSV}")

    # JSON
    report = {
        "failed_logins": {ip: [t.strftime("%Y-%m-%d %H:%M:%S") for t in times] for ip, times in failed_logins.items()},
        "unusual_hour_access": [{"ip": e["ip"], "timestamp": e["timestamp"].strftime("%Y-%m-%d %H:%M:%S"), "request": e["request"]} for e in unusual_hours]
    }
    with open(REPORT_JSON, "w") as f:
        json.dump(report, f, indent=4)
    print(f"JSON report saved: {REPORT_JSON}")

# -------------------------------
# Main
# -------------------------------
if __name__ == "__main__":
    failed_logins, unusual_hours = analyze_logs(LOG_FILE)
    generate_reports(failed_logins, unusual_hours)