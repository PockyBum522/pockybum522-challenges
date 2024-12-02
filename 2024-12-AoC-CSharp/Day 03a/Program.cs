using System.Diagnostics;
using CSharpAoC2024.ApplicationLogistics;

namespace CSharpAoC2024;

internal static class Program
{
    private static readonly Serilog.Core.Logger _logger = LoggerSetup.ConfigureLogger()
        .MinimumLevel.Warning()
        .CreateLogger();
    
    private static readonly Stopwatch _elapsedTotal = new();
    
    private static void workLine(string line, int lineCounter)
    {
        
    }
    
    private static void workAllLines(string[] allLinesSplit)
    {
        var answer = 0;
        
        var lineCounter = 0;
        foreach (var line in allLinesSplit)
        {
            workLine(line, lineCounter++);
        }
        
        _logger.Warning("Answer: {BiggestScore}", answer);
    }
    
    internal static async Task Main(string[] args)
    {
        await Task.Delay(1); // Keep the linter happy
        _elapsedTotal.Start();
        _logger.Fatal("Starting!"); // Fatal 'cause we ALWAYS want to see this in log
        
        var textToWork = RawData.ActualData01;

        var dataLines = textToWork.Split('\n');

        workAllLines(dataLines);

        logStopwatchFinalTimes();
    }
    
    private static void logStopwatchFinalTimes()
    {
        _elapsedTotal.Stop();

        var elapsedString = _elapsedTotal.Elapsed.ToString(@"hh\:mm\:ss\.fff");
        _logger.Fatal("Final total time elapsed hh:mm:ss.fff: {TimeString}", elapsedString);    // Fatal 'cause we ALWAYS want to see this in log
    }
}
