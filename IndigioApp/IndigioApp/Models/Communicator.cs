using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace IndigioApp.Models
{
    class Communicator
    {
        /******************************
         * Public Interface section   *
         * ***************************/
        public TransferCodes TransferStream(object something)
        {
            // Implement me
        }

        public TransferCodes TransferData(object something)
        {
            // Implement me
        }

        /******************************
         * Private operations section *
         *****************************/
        // Implement me!
    }

    public enum TransferCodes
    {
        Success,
        ServiceBusy,
        NoInternet,
        UnknownCause
    }
}
