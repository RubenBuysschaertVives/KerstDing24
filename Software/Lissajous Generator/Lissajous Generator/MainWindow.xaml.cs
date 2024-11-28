using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Vives;

namespace Lissajous_Generator
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        int _numberOfClicks = 0;
        string _path = "lissajousPoints.txt";
        StreamWriter _streamWriter;
        List<LissajousPoint> _points;
        bool _IsConstructionLine = false;

        public MainWindow()
        {
            InitializeComponent();

            _points = new List<LissajousPoint>();
            _streamWriter = new StreamWriter(_path, false);

            lblNumberOfPoints.Content = _numberOfClicks.ToString();
        }

        // Nieuw punt opslaan.
        private void Image_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            if (_points.Count < 500)
            {
                //Debug.WriteLine($"X: {e.GetPosition((Image)sender).X}, Y: {e.GetPosition((Image)sender).Y}");
                _points.Add(new LissajousPoint(e.GetPosition((Image)sender), _IsConstructionLine));
                _numberOfClicks++;
                lblNumberOfPoints.Content = _numberOfClicks.ToString();

                if (_points.Count > 1)
                {
                    Line line = new Line();
                    if(_IsConstructionLine)
                        line.Stroke = Brushes.Red;
                    else
                        line.Stroke = Brushes.Blue;
                    line.StrokeThickness = 1;
                    line.X1 = _points[_numberOfClicks - 2].Point.X;
                    line.X2 = _points[_numberOfClicks - 1].Point.X;
                    line.Y1 = _points[_numberOfClicks - 2].Point.Y;
                    line.Y2 = _points[_numberOfClicks - 1].Point.Y;
                    cnvsToDraw.Children.Add(line);
                }
            }
        }

        // Laatste klik wissen.
        private void Image_MouseRightButtonDown(object sender, MouseButtonEventArgs e)
        {
            if (_points.Count > 0)
            {
                
                if (_points.Count == 1)
                    cnvsToDraw.Children.Clear();
                else
                    cnvsToDraw.Children.RemoveAt(_points.Count - 2);

                _points.RemoveAt(_points.Count - 1);
                _numberOfClicks--;
                lblNumberOfPoints.Content = _numberOfClicks.ToString();
            }
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            _streamWriter.Close();
        }

        // C-code genereren en opslaan in tekstbestand.
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            string firmwareCodeX;
            string firmwareCodeY;
            string firmwareCodeSuppressPreviousTrack;
            _numberOfClicks = 0;

            foreach (LissajousPoint p in _points)
            {
                // Coördinaten herschalen (512 pixels -> 4096 DAC).
                firmwareCodeX = $"lissajous.points[{_numberOfClicks}].x = {Convert.ToInt32(p.Point.X * 8)};";
                firmwareCodeY = $"lissajous.points[{_numberOfClicks}].y = {4096 - Convert.ToInt32(p.Point.Y * 8)};";

                if(p.SuppressPreviousTrack)
                    firmwareCodeSuppressPreviousTrack = $"lissajous.points[{_numberOfClicks++}].suppressPreviousTrack = true;\r\n";
                else
                    firmwareCodeSuppressPreviousTrack = $"lissajous.points[{_numberOfClicks++}].suppressPreviousTrack = false;\r\n";

                //Debug.WriteLine(firmwareCodeX);
                //Debug.WriteLine(firmwareCodeY);

                _streamWriter.WriteLine(firmwareCodeX);
                _streamWriter.WriteLine(firmwareCodeY);
                _streamWriter.WriteLine(firmwareCodeSuppressPreviousTrack);
            }

            _streamWriter.Flush();
            _points.Clear();
            _numberOfClicks = 0;
            lblNumberOfPoints.Content = _numberOfClicks.ToString();
        }

        // Shift indrukken om 'constructielijn' te maken (niet zichtbare lijn).
        private void Window_PreviewKeyDown(object sender, KeyEventArgs e)
        {
            if ((e.Key == Key.LeftShift) || (e.Key == Key.LeftShift))
                _IsConstructionLine = true;

            e.Handled = true;
        }

        private void Window_PreviewKeyUp(object sender, KeyEventArgs e)
        {
            _IsConstructionLine = false;
            e.Handled = true;
        }
    }
}
