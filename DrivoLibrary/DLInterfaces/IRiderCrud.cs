using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UberNew;

namespace Drivo
{
    public interface IRiderCrud
    {
        bool StoreUser(Rider user, string connectionString);
        Rider SignIn(Rider user, string connectionString);
        Rider SearchRiderWithId(int riderid, string connectionString);
        void UpdateRiderName(Rider rider, string newName, string con);
        void UpdateRiderPassword(Rider rider, string newPass, string con);
        void UpdateRiderPhoneNumber(Rider rider, string newPhn, string con);
        void UpdateRiderEmail(Rider rider, string newEmail, string con);  //7
        bool DeleteRider(int riderid, string connectionString);
        List<Rider> GetAllActiveRiders(string connectionString);





    }
}
