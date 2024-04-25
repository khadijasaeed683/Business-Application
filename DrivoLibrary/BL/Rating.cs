
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace Drivo
{
    //Rating Class has ASSOCIATION with Trip Class
    public class Rating
    {
        private int ratingId;
        private int tripId;
        private double DriverRating;
        private double RiderRating;
        private string DriverComments;
        private string RiderComments;

        public Rating()
        {

        }
        public Rating(int ratingId, int tripId, double driverRating, double riderRating, string driverComments, string riderComments)
        {
            this.ratingId = ratingId;
            this.tripId = tripId;
            DriverRating = driverRating;
            RiderRating = riderRating;
            DriverComments = driverComments;
            RiderComments = riderComments;
        }

        public Rating(int tripId, double DriverRating, string DriverComments)
        {
            this.tripId = tripId;
            this.DriverRating = DriverRating;
            this.DriverComments = DriverComments;
        }
         public Rating(int tripId, string RiderComments, double RiderRating)
        {
            this.tripId = tripId;
            this.RiderRating = RiderRating;
            this.RiderComments = RiderComments;
        }


        public int GetRatingId()
        {
            return ratingId;
        }

        public int GetTripId()
        {
            return tripId;
        }
         
        public double GetDriverRating()
        {
            return DriverRating;
        } 
        public double GetRiderRating()
        {
            return RiderRating;
        }
       

        public string GetDriverComments()
        {
            return DriverComments;
        }
     public string GetRiderComments()
        {
            return RiderComments;
        }
    
    }
}
