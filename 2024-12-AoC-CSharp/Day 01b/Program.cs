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
        _elapsedTotal.Start();
        _logger.Information("Starting!");

        await Task.Delay(1);
        
        var answer = 0;
        
        var textToWork = RawData.ActualData01;
        
        var dataLines = textToWork.Split(Environment.NewLine);

        var locationIds = new List<int>();
        var locations = new List<int>();
        
        var counter = 0;
        foreach (var line in dataLines)
        {
            var locationId = line.Split("   ")[0];
            var location = line.Split("   ")[1];
            
            locationIds.Add(int.Parse(locationId));
            locations.Add(int.Parse(location));
            
            
            // figure out exactly how often each number from the left list appears in the right list.
            //
            // Calculate a total similarity score by adding up each number in the left list after multiplying it by
            // the number of times that number appears in the right list.
            
            
            // _logger.Information("On: {ThisCount} with a total of: {TotalCount}", counter++, dataLines.Length);
            // _logger.Information("ID: {Id} / Loc: {Location}", locationId, location);
            //

            
        }
        
        locationIds.Sort();
        locations.Sort();
        
        for (var i = 0; i < locationIds.Count; i++)
        {
            var checkNumber = locations[i];

            var rightListCount = 0;
            for (var j = 0; j < locationIds.Count; j++)
            {
                if (locationIds[j] == checkNumber)
                    rightListCount++;
            }
            
            var thisOne = checkNumber * rightListCount;
            answer += thisOne;
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