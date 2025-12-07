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

            var goingDown = false;
            
            if (line[0] == 'L')
            {
                goingDown = true;
            }
            else
            {
                goingDown = false;
            }

            var leftToGo = numberInLine;

            while (leftToGo > 0)
            {
                if (currentIndex == 0)
                {
                    answerTotal++;
                }

                leftToGo--;
                if (goingDown)
                {
                    currentIndex--;
                    
                    if (currentIndex == -1)
                        currentIndex = 99;
                }
                else
                {
                    currentIndex++;

                    if (currentIndex == 100)
                        currentIndex = 0;
                }
            }
            
            Console.WriteLine($"After Line: {currentIndex}");
            Console.WriteLine();
        }
        
        _logger.Information("{FormattedTimeString}", StopwatchHelper.GetStopwatchFinalTimes(ElapsedTotal));
        _logger.Information("Answer: {AnswerTotal}", answerTotal);
        
        // Make sure if we log on other threads right before the program ends, we can see it
        await Log.CloseAndFlushAsync();
        await Task.Delay(500);
    }
}
