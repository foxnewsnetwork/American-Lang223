using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace IndigioApp.Models
{
    class GameState
    {
        /****************************
         * Public Interface Section *
         * *************************/
        public GameTypes Genre { get; set; }
        public GameNames Name { get; set; }
        public bool RetrievePlayerState(out List<Dictionary<String, int>> PlayerState)
        {
            // TODO: Implement me!
            return true; // if successful, returns false otherwise
        }

        public bool RetrieveEnvironmentState(out List<Dictionary<String, int>> EnvironmentState)
        {
            // TODO: implement me!
            return true;
        }

        /*****************************
         * Private opeations section *
         * **************************/
        // Implement this section!
    }

    public enum GameNames
    {
        Unknown,
        SC2, // Starcraft 2
        LOL, // League of Legends
        TF2 // Team Fortress 2
    }

    public enum GameTypes
    {
        Unknown, // Use for pure and simple streaming
        RTS, // Real-time strategy such as Starcraft 2 or League of Legends
        FPS, // First-person shooter such as Counter-Strike and Call of Duty
        RPG // Role-playing game such as Final Fantasy
    }
}
