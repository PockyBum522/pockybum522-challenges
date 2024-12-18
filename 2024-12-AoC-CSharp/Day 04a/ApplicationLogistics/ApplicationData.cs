﻿namespace CSharpAoC2024.ApplicationLogistics;

public static class ApplicationData
{
    /// <summary>
    /// Full path to base folder for logs (the folder, not the log files themselves)
    /// </summary>
    public static string Name => "AocCSharp";
    
    /// <summary>
    /// Full path to the directory the app is running from, used for building log and settings directories
    /// </summary>
    public static string RootDirectory =>
        Path.GetDirectoryName(Environment.ProcessPath) ?? "ERROR GETTING APP PATH FOR AocCSharp";
}