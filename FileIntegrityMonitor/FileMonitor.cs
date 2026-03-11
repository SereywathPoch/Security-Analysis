// File: FileMonitor.cs
using System;
using System.IO;

class FileMonitor
{
    static void Main()
    {
        string path = @"C:\SecurityFiles";

        FileSystemWatcher watcher = new FileSystemWatcher();
        watcher.Path = path;

        watcher.NotifyFilter =
            NotifyFilters.LastWrite |
            NotifyFilters.FileName |
            NotifyFilters.DirectoryName;

        watcher.Filter = "*.*";

        watcher.Changed += OnChanged;
        watcher.Created += OnChanged;
        watcher.Deleted += OnChanged;
        watcher.Renamed += OnRenamed;

        watcher.EnableRaisingEvents = true;

        Console.WriteLine("Monitoring folder: " + path);
        Console.WriteLine("Press ENTER to exit");
        Console.ReadLine();
    }

    private static void OnChanged(object sender, FileSystemEventArgs e)
    {
        Console.WriteLine($"File {e.ChangeType}: {e.FullPath}");
        File.AppendAllText("file_events.log",
            $"{DateTime.Now} | {e.ChangeType} | {e.FullPath}\n");
    }

    private static void OnRenamed(object sender, RenamedEventArgs e)
    {
        Console.WriteLine($"File Renamed: {e.OldFullPath} -> {e.FullPath}");
        File.AppendAllText("file_events.log",
            $"{DateTime.Now} | RENAMED | {e.OldFullPath} -> {e.FullPath}\n");
    }
}
// Compile: csc FileMonitor.cs
// Run: FileMonitor.exe