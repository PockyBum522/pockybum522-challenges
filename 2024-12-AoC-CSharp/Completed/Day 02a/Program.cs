using System.Diagnostics;
using CSharpAoC2024.ApplicationLogistics;

namespace CSharpAoC2024;

internal static class Program
{
    private static readonly Serilog.Core.Logger _logger = LoggerSetup.ConfigureLogger()
        .MinimumLevel.Information()
        .CreateLogger();
    
    private static readonly Stopwatch _elapsedTotal = new();

    private static bool _allDecreasing = true;
    
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
        
        var dataLines = textToWork.Split('\n');
        
        var elementCounter = 0;
        foreach (var line in dataLines)
        {
            var reportLineIsSafe = true;
            
            var elements = line.Split(" ");
            
            _logger.Information("New elements set: {@Elems}", elements);

            _logger.Information("Starting line: {Count}", elementCounter);
            for (var i = 0; i < elements.Length; i++)
            {
                if (i < 1) continue;
                
                var elementOne = int.Parse(elements[i - 1]);
                var elementTwo = int.Parse(elements[i]);

                //_logger.Information("Currently");
                
                if (NotAllIncreasingOrDecreasing(elementOne, elementTwo, i))
                {
                    reportLineIsSafe = false;
                    _logger.Information("Failed on NotAllIncreasingOrDecreasing");
                }

                if (DiffersByLessThanOne(elementOne, elementTwo))
                {
                    reportLineIsSafe = false;
                    _logger.Information("Failed on DiffersByLessThanOne");
                }

                if (DiffersByMoreThanThree(elementOne, elementTwo))
                {
                    reportLineIsSafe = false;
                    _logger.Information("Failed on DiffersByMoreThanThree");
                }
            
                _logger.Information("Checked: {CurrentNumOne}, {CurrentNumTwo} | Currently Line is: {Safety}", elementOne, elementTwo, reportLineIsSafe);
            }
            
            if (reportLineIsSafe) answer++;
            
            _logger.Information("Finished line: {Count}", elementCounter++);
            
            // _logger.Information("On: {ThisCount} with a total of: {TotalCount}", counter++, dataLines.Length);
            // _logger.Information("ID: {Id} / Loc: {Location}", locationId, location);
        }
        
        LogStopwatchFinalTimes();
        
        _logger.Information("Answer: {BiggestScore}", answer);
    }

    private static bool DiffersByMoreThanThree(int i, int j)
    {
        return Math.Abs(i - j) > 3; 
    }

    private static bool DiffersByLessThanOne(int i, int j)
    {
        return i == j;
    }

    private static bool NotAllIncreasingOrDecreasing(int elemOne, int elemTwo, int elementCounter)
    {
        if (elementCounter == 1)
        {
            _logger.Information("NotAllIncreasingOrDecreasing NEW SET");
            
            if (elemOne > elemTwo) _allDecreasing = true;
            else _allDecreasing = false;
            
            return false;
        } 
        
        if (_allDecreasing && elemOne < elemTwo) return true;
        if (!_allDecreasing && elemOne > elemTwo) return true;

        return false;
    }

    private static void LogStopwatchFinalTimes()
    {
        _elapsedTotal.Stop();

        var elapsedString = _elapsedTotal.Elapsed.ToString(@"hh\:mm\:ss\.fff");
        _logger.Information("Final total time elapsed hh:mm:ss.fff: {TimeString}", elapsedString);
    }
}