using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Drivo
{
    public class Driver: Person
    {
       

        private string DriverIdCard;
     //   private int DriverID;
        private string CarModel;
        private string License;
        private bool AvailabilityStatus = true;
        private DateTime JoiningDate;

      
        public Driver(string nm, string phnNmbr, string carModel, string license, string driverIdCard):base(nm,phnNmbr)
        {
          
            this.CarModel = carModel;
            License = license;
            DriverIdCard = driverIdCard;
        } 
        public Driver(string nm, string phnNmbr, string carModel, string license, string driverIdCard, bool availstatus, int id, DateTime jd):base(id,nm,phnNmbr)
        {
          AvailabilityStatus = availstatus;
            CarModel = carModel;
            License = license;
            DriverIdCard = driverIdCard;
            JoiningDate = jd;
        } 
        public Driver(string nm, string driverIdCard):base(nm)
        {
          
            DriverIdCard = driverIdCard;
        }


        public Driver()
        {

        }
       
       /* public void setDriverID(int driverID)
        {
            this.DriverID = driverID;
        }
       */
        public void setCarModel(string carModel)
        {
            this.CarModel = carModel;
        }
        public void SetJoiningDate(DateTime JoiningDate)
        {
            this.JoiningDate = JoiningDate;
        }
        public void UpdateAvailibilityStatus(bool s)
        {
            this.AvailabilityStatus = s;
        }

       
        public DateTime getJoiningDate() { return this.JoiningDate; }
        public string getDriverIdCard()
        { return this.DriverIdCard; }
        public string getLicense() { return this.License; }
        public string getCarModel() { return this.CarModel; }
      
        public bool getAvailabilityStatus()
        {
            return this.AvailabilityStatus;
        }
        public DateTime GetJoiningDate() { return this.JoiningDate; }

    }
}
