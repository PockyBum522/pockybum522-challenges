using System.Diagnostics;
using CSharpAoC2024.ApplicationLogistics;

namespace CSharpAoC2024;

internal static class Program
{
    private static readonly Serilog.Core.Logger _logger = LoggerSetup.ConfigureLogger()
        .MinimumLevel.Warning()
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
        _logger.Warning("Starting!");

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

            var safePassCounter = 0;
            for (var i = 0; i < elements.Length + 1; i++)
            {
                if (IsSafeWithElementRemovedAt(i, elements)) safePassCounter++;
            }
            
            if (safePassCounter > 0) answer++;
            
            _logger.Information("Finished line: {Count}", elementCounter++);
            
            // _logger.Information("On: {ThisCount} with a total of: {TotalCount}", counter++, dataLines.Length);
            // _logger.Information("ID: {Id} / Loc: {Location}", locationId, location);
        }
        
        LogStopwatchFinalTimes();
        
        _logger.Warning("Answer: {BiggestScore}", answer);
    }

    private static bool IsSafeWithElementRemovedAt(int j, string[] elements)
    {
        var tempElements = elements.ToList();
        
        if (j < elements.Length)
        {
            tempElements.RemoveAt(j);    
        }
        
        for (var i = 0; i < tempElements.Count; i++)
        {
            if (i < 1) continue;
            
            var elementOne = int.Parse(tempElements[i - 1]);
            var elementTwo = int.Parse(tempElements[i]);

            //_logger.Information("Currently");
                
            if (NotAllIncreasingOrDecreasing(elementOne, elementTwo, i))
            {
                _logger.Information("Failed on NotAllIncreasingOrDecreasing");
                return false;
            }

            if (DiffersByLessThanOne(elementOne, elementTwo))
            {
                _logger.Information("Failed on DiffersByLessThanOne");
                return false;
            }

            if (DiffersByMoreThanThree(elementOne, elementTwo))
            {
                _logger.Information("Failed on DiffersByMoreThanThree");
                return false;
            }
            
            //_logger.Information("Checked: {CurrentNumOne}, {CurrentNumTwo} | Currently Line is: {Safety}", elementOne, elementTwo, reportLineIsSafe);
        }

        return true;
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
        _logger.Warning("Final total time elapsed hh:mm:ss.fff: {TimeString}", elapsedString);
    }
}