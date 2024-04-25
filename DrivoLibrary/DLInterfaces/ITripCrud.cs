using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UberNew;

namespace Drivo
{
    public interface ITripCrud
    {
        bool StoreTrip(Trip tr, Rider rider);

        List<Trip> LoadAllTripsToList(string con);
        List<Trip> LoadActiveTripsToList(string con);

        List<Trip> LoadActiveTripsForRiderToList(int riderId, string con);
        List<Trip> LoadInActiveTripsToList(string con);
        List<Trip> GetTripsForRider(string riderPhoneNumber, string con);
        void UpdateRideStatus(int rideId, string con);
        void DeleteRide(int rideId, string con);
        bool IsRideDeleted(int rideId, string con);
        List<Trip> GetAllPendingRides(string con);


    }
}
