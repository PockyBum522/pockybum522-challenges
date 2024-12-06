using System.Diagnostics;
using System.Threading.Tasks;
using CSharpAoC2024.ApplicationLogistics;

namespace CSharpAoC2024;

internal static class Program
{
    private static string _textToWork =>  RawData.SampleData01;
    
    private static readonly Serilog.Core.Logger _logger = LoggerSetup.ConfigureLogger()
        .MinimumLevel.Debug()
        .CreateLogger();
    
    private static readonly Stopwatch _elapsedTotal = new();
    private static string[] _dataLines;

    private static void workAllLines()
    {
        var answer = 0;

        for (var y = 0; y < _dataLines.Length; y++)
        {
            for (var x = 0; x < _dataLines[y].Length; x++)
            {
                answer += numberOfXmasFromPoint(x, y);
            }
        }
        
        _logger.Warning("Answer: {BiggestScore}", answer);
    }

    private static int numberOfXmasFromPoint(int x, int y)
    {
        var returnCount = 0;

        var charAtPositon = _dataLines[y][x];
        
        if (charAtPositon is not ('S' or 'X')) return 0;

        // Search to east
        if (compareLetters(x, y, 1, 0)) returnCount++;
        
        // Search to south
        if (compareLetters(x, y, 0, 1)) returnCount++;
        
        // Search to west
        // Don't need to do this because the reversed check in east will grab them 
        
        // Search to north
        // Don't need to do this because the reversed check in south will grab them

        // Search to northeast
        if (compareLetters(x, y, 1, -1)) returnCount++;
        
        // Search to southeast
        if (compareLetters(x, y, 1, 1)) returnCount++;
        
        // Search to northwest
        // Don't need to do this because the reversed check in southeast will grab them
        
        // Search to southwest
        // Don't need to do this because the reversed check in northeast will grab them
        
        return returnCount;
    }

    private static bool compareLetters(int startX, int startY, int xIncrement, int yIncrement)
    {
        if (xIncrement == 0 && yIncrement == 0) throw new ArgumentException("xIncrement and yIncrement are both zero, this isn't going to do much. Pls fix.");
        
        var foundNormally = true;
        var foundBackwards = true;
        
        _logger.Debug("Starting checks");
        
        var indexIncrement = (xIncrement > yIncrement) ? xIncrement : yIncrement;
        
        _logger.Debug("xIncrement:{XInc}, yIncrement:{YInc}, so indexIncrement = {IndexIncrement}", xIncrement, yIncrement, indexIncrement);
        
        var checkY = startY;
        var checkX = startX;
        
        for (var i = 0; i < 4; i += indexIncrement)
        {
            var fNeedle = getXmasChars(i, false);
            var bNeedle = getXmasChars(i, true);
            
            // Now make sure we don't exceed y bounds
            if (checkY > _dataLines.Length - 1)
            {
                foundNormally = false;
                foundBackwards = false;
                break;
            }
            
            // They're both searching forwards, one is just checking the letter backwards, so we only need to make sure we stay bounded in the string forwards
            if (checkX > _dataLines[checkY].Length - 1)
            {
                foundNormally = false;
                foundBackwards = false;
                break;
            }
            
            var haystack = _dataLines[checkY][checkX];

            _logger.Debug("Comparing F:{ForwardsNeedle}, B:{BackwardsNeedle} to {Haystack}", 
                fNeedle, bNeedle, haystack);

            if (fNeedle != haystack) foundNormally = false;
            if (bNeedle != haystack) foundBackwards = false;
            
            checkY += yIncrement;
            checkX += xIncrement;
        }

        _logger.Debug("At end, normal direction found: {FoundNormally} and backwards: {FoundBackwards}", foundNormally, foundBackwards);
        
        return foundNormally || foundBackwards;
    }

    private static char getXmasChars(int index, bool reversed)
    {
        var word = "XMAS";

        switch (index)
        {
            case 0:
                return reversed ? word[3] : word[0];
                
            case 1:
                return reversed ? word[2] : word[1];
                
            case 2:
                return reversed ? word[1] : word[2];
            
            case 3:
                return reversed ? word[0] : word[3];
        }
        
        throw new IndexOutOfRangeException();
    }

    internal static async Task Main(string[] args)
    {
        await Task.Delay(1); // Keep the linter happy
        _elapsedTotal.Start();
        _logger.Fatal("Starting!"); // Fatal 'cause we ALWAYS want to see this in log

        _dataLines = _textToWork.Split('\n');

        workAllLines();

        logStopwatchFinalTimes();
    }
    
    private static void logStopwatchFinalTimes()
    {
        _elapsedTotal.Stop();

        var elapsedString = _elapsedTotal.Elapsed.ToString(@"hh\:mm\:ss\.fff");
        _logger.Fatal("Final total time elapsed hh:mm:ss.fff: {TimeString}", elapsedString);    // Fatal 'cause we ALWAYS want to see this in log
    }
}
