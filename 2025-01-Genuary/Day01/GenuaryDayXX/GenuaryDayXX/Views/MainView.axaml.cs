using Avalonia;
using Avalonia.Controls;
using Avalonia.Controls.Shapes;
using Avalonia.Media;

namespace GenuaryDayXX.Views;

public partial class MainView : UserControl
{
    public MainView()
    {
        
        InitializeComponent();
        
        var maxHeight = 2088;
        var maxWidth = 3840;
        
        for (var x = 0; x < maxWidth; x++)
        {
            var thisLine = new Line()
            {
                StartPoint = new Point(x, x),
                EndPoint = new Point(x, maxHeight),
                Stroke = Brushes.White,
                StrokeThickness = 0.5
            };
            
            Cv1.Children.Add(thisLine);
        }
    }
}