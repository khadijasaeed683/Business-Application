using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UberNew;

namespace Drivo
{
    public interface IDriverCrud
    {
        bool StoreDriver(Driver dr);
        Driver SignIn(Driver user);
        List<Driver> LoadDriversWithNullDriverID();
        bool UpdateDriverId(string dname, int did);
        bool UpdateDriverName(Driver driver, string newname);
        bool UpdateDriverPhoneNumber(Driver driver, string newPhoneNumber); //6
        List<Driver> GetAllAvailableDriversList();
        bool UpdateAvailibiltyStatus(int driverId, bool status);



    }
}
