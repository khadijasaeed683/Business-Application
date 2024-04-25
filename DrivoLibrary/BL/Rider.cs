using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Drivo
{
    public class Rider:Person
    {

        protected  List<Trip> Trips = new List<Trip>(); // association relationship between Person and Trip


        private string email;
        private string Password;
        private string HomeAddress;

        public void AddTripToList(Trip trip)
        {
            Trips.Add(trip);
        }

        public string getEmail() { return email; }
        public string getPassword() { return Password; }
        public string getAddress() { return HomeAddress; }
        public void setEmail(string emai) { email = emai; }
        public void setPassword(string password) { Password = password; }
        public void setAddress(string homeAddAddress) { HomeAddress = homeAddAddress; }
        public void setPhoneNumber(string phoneNumber) { PhoneNumber = phoneNumber; }

        public Rider()
        {

        }
        public Rider(string name, string em, string pass, string homeAdd, string PhoneNo):base(name,PhoneNo)
        {
            
            email = em;
            Password = pass;
            HomeAddress = homeAdd;
          
        }
        public Rider(string name, string em, string pass, string PhoneNo) : base(name, PhoneNo)
        {
           
            email = em;
            Password = pass;
           
        }
       public Rider(int id,string name, string em, string pass, string PhoneNo) : base(id, name, PhoneNo)
        {
           
            email = em;
            Password = pass;
           
        }
        public  List<Trip> GetTripsList()
        {
            return Trips;
        }
      
    }
}
