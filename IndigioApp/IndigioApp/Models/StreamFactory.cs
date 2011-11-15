using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace IndigioApp.Models
{
    class StreamFactory
    {
        /******************************
         * Public Interface section   *
         * ***************************/
        public EncodingTypes Encoder;
   
        public bool PrepareStream(object streamin, out object streamout)
        {
            // Implement me!
        }

        /******************************
         * Private operations section *
         *****************************/
        // Implement me!
    }

    public enum EncodingTypes
    {
        H264,
        WMV,
        AVI
    }
}
