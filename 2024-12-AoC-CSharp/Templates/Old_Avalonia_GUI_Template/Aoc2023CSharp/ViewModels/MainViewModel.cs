using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Reactive.Concurrency;
using System.Runtime.Versioning;
using System.Threading;
using System.Threading.Tasks;
using Aoc2023CSharp.Logic;
using Avalonia.Threading;
using CommunityToolkit.Mvvm.ComponentModel;
using DynamicData;
using ReactiveUI;
using Serilog.Core;
using Bitmap = Avalonia.Media.Imaging.Bitmap;

namespace Aoc2023CSharp.ViewModels;

public partial class MainViewModel : ObservableObject
{
    [ObservableProperty] private Bitmap? _boardImage;
    
    [ObservableProperty] private int _windowWidth;
    [ObservableProperty] private int _windowHeight;
    
    private readonly ILogger _logger;
    private readonly LoggerConfiguration _loggerConfiguration;
    
    private readonly Stopwatch _elapsedTotal = new();
    
    private readonly int _maxThreads = 31;

    public MainViewModel() { throw new NotImplementedException(); }     // This method being present keeps the designer happy

    [SupportedOSPlatform("windows")]
    public MainViewModel(LoggerConfiguration loggerConfiguration)
    {
        _loggerConfiguration = loggerConfiguration;

        _logger = loggerConfiguration
            .MinimumLevel.Information()
            .CreateLogger();
        
    }

    [SupportedOSPlatform("windows")]
    private async Task RunBeams()
    {
        _elapsedTotal.Start();
        _logger.Information("Starting!");

        var answer = 0;
        
        var textToWork = RawData.ActualData01;
        
        var dataLines = textToWork.Split(Environment.NewLine);

        var counter = 0;
        foreach (var line in dataLines)
        {        
            _logger.Information("On: {ThisCount} with a total of: {TotalCount}", counter++, 0);

            
        }

        
        LogStopwatchFinalTimes();
        
        _logger.Information("Answer: {BiggestScore}", answer);
    }

    private void LogStopwatchFinalTimes()
    {
        _elapsedTotal.Stop();

        var elapsedString = _elapsedTotal.Elapsed.ToString(@"hh\:mm\:ss\.fff");
        
        _logger.Information("Threads: {MaxThreadCount}", _maxThreads);
        _logger.Information("Final total time elapsed hh:mm:ss.fff: {TimeString}", elapsedString);
    }
}
