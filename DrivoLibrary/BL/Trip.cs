using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Drivo
{
    public class Trip    //association with Rider, Driver 
    {
       
       
        private string PickupLocation;
        private string DropoffLocation;
        private double Fare;
        private string DriverPhoneNo;
        private string RiderPhoneNo;
        private int RideId;
       private Driver driver;
        private Rider client;
        private double DistanceCovered; 
        private bool TripStatus = true; //trip is active i.e no driver has responded yet
        private int ArrivalMinutes;
        public int getArrivalMinutes() { return ArrivalMinutes; }
        public void setArrivalMinutes(int min) { this.ArrivalMinutes = min; }



        // Composition with RiderRating
        private Rating RiderRating ; 

      
         
          public void SetRiderRating(Rating rating)
        {
            this.RiderRating = rating;
        }
          public Rating GetRiderRating( )
        {
            return this.RiderRating;
        }

      


        public int getTripId() { return RideId; }   
        public string getPickupLocation() { return PickupLocation; }
        public string getDropoffLocation() { return DropoffLocation; }
        public Driver getDriver() { return driver; }
        public Rider getRider() { return client; }
        public double getFare() { return Fare; }
        public double getDistanceCovered() { return DistanceCovered; }
        public bool getTripStatus() { return TripStatus; }
        public void setFare(double Fare) { this.Fare = Fare; }
        public void setPickupLocation(string PickupLocation) { this.PickupLocation = PickupLocation; }
        public void setDropoffLocation(string DropoffLocation) { this.DropoffLocation = DropoffLocation; }
        public void setDriver(Driver driver) { this.driver = driver; }
        public void setRider(Rider client) { this.client = client; }
        public void setTripId(int id) { this.RideId= id; }
      
        public void setTripStatus(bool status) { this.TripStatus = status; }
        public Trip()
        {
        }
        public Trip(string pickupLocation, string dropoffLocation, double fare, string driverPhoneNo, string riderPhoneNo, double distanceCovered, bool tripStatus)
        {
            PickupLocation = pickupLocation;
            DropoffLocation = dropoffLocation;
            Fare = fare;
            DriverPhoneNo = driverPhoneNo;
            RiderPhoneNo = riderPhoneNo;
            DistanceCovered = distanceCovered;
            TripStatus = tripStatus;
        }
        public Trip(string pickupLocation, string dropoffLocation, double fare)
        {
            PickupLocation = pickupLocation;
            DropoffLocation = dropoffLocation;
            Fare = fare;

        } 
     public Trip(string pickupLocation, string dropoffLocation, double fare, Rider rider)
        {
            PickupLocation = pickupLocation;
            DropoffLocation = dropoffLocation;
            Fare = fare;
           this.client  = rider;

        } 
        public Trip(string pickupLocation, string dropoffLocation, double fare, bool isact,int id)
        {
            PickupLocation = pickupLocation;
            DropoffLocation = dropoffLocation;
            Fare = fare;
            TripStatus= isact;
            RideId = id;
        }
        public Trip(string pickupLocation, string dropoffLocation, double fare, int id)
        {
            PickupLocation = pickupLocation;
            DropoffLocation = dropoffLocation;
            Fare = fare;

            RideId = id;
        }



        public void setDistanceCovered(double distance)
        {
           

           this.DistanceCovered= distance;
        }

            public double CalculateFare(double baseFarePerKm, double dis)
        {
            double fare = baseFarePerKm * dis;
            // Example fare calculation logic based on distance
           
                this.Fare = fare;
                return fare;
           

        }
        public string CheckRideStatus()
        {
            string status;
            if(this.TripStatus)
            {
                status = "Pending";
            }
            else
            {
                status = "Accepted";
            }
            return status;
        }

    }
}
