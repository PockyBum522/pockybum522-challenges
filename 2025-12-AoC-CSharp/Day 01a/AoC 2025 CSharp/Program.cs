using Serilog.Core;

namespace AoC_2025_CSharp;

internal static class Program
{
    // ReSharper disable once InconsistentNaming because it's less annoying than having the same name as the class
    private static readonly ILogger _logger = LoggerSetup.ConfigureLogger()
            .MinimumLevel.Information()
            .CreateLogger(); 
 
    private static readonly Stopwatch ElapsedTotal = new();

    public static async Task Main()
    {
        ElapsedTotal.Start();
        _logger.Information("Starting!");
        
        var rawLines = RawData.ActualData01
            .Split(Environment.NewLine);

        var answerTotal = 0;

        var currentIndex = 50;

        foreach (var line in rawLines)
        {
            // Debug parse:
            // Console.WriteLine(line[1..]);
            
            var numberInLine = int.Parse(line[1..]);

            Console.WriteLine($"Current: {currentIndex}");
            Console.WriteLine($"Line: {line}");
            
            if (line[0] == 'L')
            {
                currentIndex -= numberInLine;
            }
            else
            {
                currentIndex += numberInLine;
            }

            while (currentIndex < 0)
            {
                currentIndex = 100 + currentIndex;
            }

            while (currentIndex > 99)
            {
                currentIndex -= 100;
            }
            
            Console.WriteLine($"After Line: {currentIndex}");
            Console.WriteLine();
            
            if (currentIndex == 0)
                answerTotal++;
        }
        
        _logger.Information("{FormattedTimeString}", StopwatchHelper.GetStopwatchFinalTimes(ElapsedTotal));
        _logger.Information("Answer: {AnswerTotal}", answerTotal);
        
        // Make sure if we log on other threads right before the program ends, we can see it
        await Log.CloseAndFlushAsync();
        await Task.Delay(500);
    }
}
