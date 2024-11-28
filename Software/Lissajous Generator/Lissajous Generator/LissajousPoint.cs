using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Vives
{
    class LissajousPoint
    {
        public Point Point { get; set; }
        public bool SuppressPreviousTrack { get; set; }

        public LissajousPoint(Point point, bool suppressPreviousTrack)
        {
            Point = point;
            SuppressPreviousTrack = suppressPreviousTrack;
        }
    }
}
