using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace IndigioApp.Models
{
    class Achievement
    {
        /******************************
         * Public Interface section   *
         * ***************************/
        public event EventHandler AchievementAccomplished;

        public void OnAchievementAccomplished(AchievementEventArgs e)
        {
            if (AchievementAccomplished != null)
                AchievementAccomplished(this, e);
        }

        /******************************
         * Private operations section *
         *****************************/
        // Implement me!
    }

    public class AchievementEventArgs : EventArgs
    {
        public int AchievementID { get; set; }
        public DateTime AchievementTime { get; set; }
    }
}
