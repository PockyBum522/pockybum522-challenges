using System.Diagnostics;
using System.Threading.Tasks;
using CSharpAoC2024.ApplicationLogistics;

namespace CSharpAoC2024;

internal static class Program
{
    private static string _textToWork =>  RawData.ActualData01;
    
    private static readonly Serilog.Core.Logger _logger = LoggerSetup.ConfigureLogger()
        .MinimumLevel.Debug()
        .CreateLogger();
    
    private static readonly Stopwatch _elapsedTotal = new();

    private const string _validStartCharacters = "mul(";

    private static void workLine(string line, int lineCounter)
    {
        var answer = 0;
        
        var currentCheckIndex = 0;

        var enabled = true;

        while (currentCheckIndex < line.Length)
        {
            var nextMulPosition = GetNextMulPosition(currentCheckIndex);
            var nextDontPosition = GetNextDontPosition(currentCheckIndex);
            var nextDoPosition = GetNextDoPosition(currentCheckIndex);

            currentCheckIndex = nextMulPosition + 1;
            
            if (nextMulPosition < 0)
            {
                break;
            }
            
            if (nextMulPosition > nextDontPosition &&
                nextDontPosition != -1)
            {
                currentCheckIndex = nextDoPosition;
                continue;
            }
            
            var rawParsed = ParseToNextParenthesis(nextMulPosition);
            
            var firstNumber = ParseNumberFrom(rawParsed, 0);
            if (firstNumber is < 0 or > 999) continue;
            
            var secondNumber = ParseNumberFrom(rawParsed, 1);
            if (secondNumber is < 0 or > 999) continue;

            Console.WriteLine($"Found {firstNumber} and {secondNumber}");
            
            answer += firstNumber * secondNumber;
        }
        
        _logger.Warning("Answer is: {Answer}", answer);
    }

    private static int GetNextDoPosition(int currentCheckIndex)
    {
        return _textToWork.IndexOf("do()", currentCheckIndex, StringComparison.Ordinal);
    }

    private static int GetNextDontPosition(int currentCheckIndex)
    {
        return _textToWork.IndexOf("don't()", currentCheckIndex, StringComparison.Ordinal);
    }

    private static int ParseNumberFrom(string rawParsed, int whichNumber)
    {
        for (var i = 0; i < rawParsed.Length; i++)
        {
            if (!isDigitOrComma(rawParsed[i])) return -1;
        }
        
        var rawNumbers = rawParsed.Split(',');
        
        if (rawNumbers.Length < 2) return -1;
        
        return int.Parse(rawNumbers[whichNumber]);
    }

    private static string ParseToNextParenthesis(int mulPosition)
    {
        var nextParenthesisPosition = _textToWork.IndexOf(')', mulPosition);

        var afterMulStartPosition = mulPosition + _validStartCharacters.Length;
        var lengthToParenthesis = nextParenthesisPosition - mulPosition - _validStartCharacters.Length;

        if (afterMulStartPosition > _textToWork.Length - 1) return "";
        
        var rawParse = _textToWork.Substring(afterMulStartPosition, lengthToParenthesis);
        
        return rawParse;
    }

    private static int GetNextMulPosition(int currentCheckIndex)
    {
        if (currentCheckIndex > _textToWork.Length - 1) return -1;
        
        return _textToWork.IndexOf(_validStartCharacters, currentCheckIndex, StringComparison.Ordinal);
    }

    private static bool isDigitOrComma(char checkCharacter)
    {
        return (checkCharacter is >= '0' and <= '9' or ',');
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

        var dataLines = _textToWork.Split('\n');

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
