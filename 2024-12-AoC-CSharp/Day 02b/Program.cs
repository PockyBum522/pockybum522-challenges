using System.Diagnostics;
using CSharpAoC2024.ApplicationLogistics;

namespace CSharpAoC2024;

internal static class Program
{
    private static readonly Serilog.Core.Logger _logger = LoggerSetup.ConfigureLogger()
        .MinimumLevel.Information()
        .CreateLogger();
    
    private static readonly Stopwatch _elapsedTotal = new();
    
    static async Task Main(string[] args)
    {
        await doWork();
    }

    private static async Task doWork()
    {
        await Task.Delay(1);        // Keep the linter happy
        _elapsedTotal.Start();
        _logger.Information("Starting!");

        var answer = 0;
        
        var textToWork = RawData.ActualData01;
        
        var dataLines = textToWork.Split(Environment.NewLine);
        
        var counter = 0;
        foreach (var line in dataLines)
        {
            // var locationId = line.Split("   ")[0];
            
            // _logger.Information("On: {ThisCount} with a total of: {TotalCount}", counter++, dataLines.Length);
            // _logger.Information("ID: {Id} / Loc: {Location}", locationId, location);
            
            
        }
        
        
        
        LogStopwatchFinalTimes();
        
        _logger.Information("Answer: {BiggestScore}", answer);
    }

    private static void LogStopwatchFinalTimes()
    {
        _elapsedTotal.Stop();

        var elapsedString = _elapsedTotal.Elapsed.ToString(@"hh\:mm\:ss\.fff");
        _logger.Information("Final total time elapsed hh:mm:ss.fff: {TimeString}", elapsedString);
    }
}