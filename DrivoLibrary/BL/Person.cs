using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Drivo
{
    public class Person 
    {

        protected int ID;
        protected   string Name;
        protected  string PhoneNumber;
        
      

        public Person(string nm, string phn)
        {
            Name = nm;
            PhoneNumber = phn;
        } 
        public Person(int id, string nm, string phn)
        {
            ID= id;
            Name = nm;
            PhoneNumber = phn;
        }
        public Person(string nm)
        {
            Name = nm;
        }
        public Person()
        {

        }
        public int getID()
        {
            return ID;
        }
        public string  getName()
        {
            return Name;
        }

        public void setName(string nm)
        {
            Name = nm;
        }
        public string getPhoneNumber()
        {
            return PhoneNumber;
        }
        public void setPhonenumber(string nmbr)
        {
            PhoneNumber = nmbr;
        }
        public void setID(int id)
        {
            ID = id;
        }
    }
}
