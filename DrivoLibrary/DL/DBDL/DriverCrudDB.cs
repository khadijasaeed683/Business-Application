using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace Drivo
{
    public class DriverCrudDB :IDriverCrud
    {
       // static FunctionsDB con = new FunctionsDB();

        public static string con = Utils.ConnectionString();
         static DriverCrudDB instance;
        public static DriverCrudDB GetInstance()
        {
            if (instance == null)
            {
                instance = new DriverCrudDB();
            }


            return instance;

        }
        public DriverCrudDB()
        {

        }
        public  bool StoreDriver(Driver dr)
        {
            bool act = true;
            string con = Utils.ConnectionString();
            SqlConnection connection = new SqlConnection(con);
            connection.Open();
            string query = String.Format("Insert into Drivers (DriverName, DriverIdCard, PhoneNumber, CarModel,License,JoiningDate, AvailibilityStatus) VALUES ('{0}', '{1}', '{2}', '{3}', '{4}', '{5}', '{6}')", dr.getName(), dr.getDriverIdCard(), dr.getPhoneNumber(), dr.getCarModel(), dr.getLicense(), dr.GetJoiningDate(), act);
            SqlCommand command = new SqlCommand(query, connection);
            int rowsAffected = command.ExecuteNonQuery();
            connection.Close();
            if (rowsAffected > 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        
        public  Driver SignIn(Driver user) //searches user on the base of name and idcard
        {
            SqlConnection connection = new SqlConnection(con);
            connection.Open();

            string searchQuery = String.Format("Select * from Drivers where DriverName = '{0}' and DriverIdCard = '{1}'", user.getName(), user.getDriverIdCard());
            SqlCommand command = new SqlCommand(searchQuery, connection);
            SqlDataReader data = command.ExecuteReader();
            if (data.Read())

            {
                // Check if the value in the database column is NULL
                int idIndex = 3;
                int id;
                if (!data.IsDBNull(idIndex))
                {
                    id = data.GetInt32(idIndex);
                }
                else
                {
                    id = 0; // Or any other default value 
                }
                Driver storedUser = new Driver(data.GetString(0), data.GetString(2), data.GetString(4), data.GetString(5), data.GetString(1));
                storedUser.setID(id);
               
                connection.Close();
                return storedUser;
            } 
            connection.Close();
            return null;
        }
        // Method to load drivers whose DriverID is NULL
        public  List<Driver> LoadDriversWithNullDriverID() // drivers with pending requests
        {
            List<Driver> drivers = new List<Driver>();

            using (SqlConnection connection = new SqlConnection(con))
            {
                string query = "SELECT * FROM Drivers WHERE DriverID IS NULL";

                SqlCommand command = new SqlCommand(query, connection);

                try
                {
                    connection.Open();
                    SqlDataReader reader = command.ExecuteReader();

                    while (reader.Read())
                    {
                        // Retrieve column values from the database
                        string driverName = reader["DriverName"].ToString();
                        string driverIdCard = reader["DriverIdCard"].ToString();
                        string phoneNumber = reader["PhoneNumber"].ToString();
                        // Note: DriverID is NULL in the database, so we'll leave it as default (0) here
                        int driverID = 0; // Default value
                        string carModel = reader["CarModel"].ToString();
                        string license = reader["License"].ToString();
                        bool availabilityStatus = true;
                        DateTime joiningDate = DateTime.Today;

                        // Create a new Driver object and add it to the list
                        Driver driver = new Driver(driverName, phoneNumber, carModel, license, driverIdCard, availabilityStatus, driverID,   joiningDate);
                        drivers.Add(driver);
                    }

                    reader.Close();
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Error loading drivers: " + ex.Message);
                }
            }

            return drivers;
        }

        public  bool UpdateDriverId(string dname, int did)
        {
            bool done = false;
            using (SqlConnection connection = new SqlConnection(con))
            {
                string updateQuery = "UPDATE Drivers SET DriverID = @DriverID WHERE DriverName = @DriverName ";

                SqlCommand command = new SqlCommand(updateQuery, connection);

                command.Parameters.AddWithValue("@DriverName", dname);
                 command.Parameters.AddWithValue("@DriverID", did);


               // command.Parameters.AddWithValue("@DriverIdCard", dIdCard);

                try
                {
                    connection.Open();
                    int rowsAffected = command.ExecuteNonQuery();
                    if (rowsAffected > 0)
                    {
                      
                        done = true;
                    }
                    else
                    {
                    }
                }
                catch (Exception ex)
                {
                   // MessageBox.Show("Error updating driver ID: " + ex.Message);
                }
            }
            return done;
        }
        public  bool UpdateDriverName(Driver driver, string newname)
        {

            bool done = false;
            using (SqlConnection connection = new SqlConnection(con))
            {
                string updateQuery = "UPDATE Drivers SET DriverName = @NewName WHERE DriverID = @DriverID";

                SqlCommand command = new SqlCommand(updateQuery, connection);

                command.Parameters.AddWithValue("@NewName", newname);
                command.Parameters.AddWithValue("@DriverID", driver.getID());

                try
                {
                    connection.Open();
                    int rowsAffected = command.ExecuteNonQuery();
                    if (rowsAffected > 0)
                    {
                        done = true;
                    }
                    else
                    {
                      //  MessageBox.Show("Driver not found or no changes made.");
                    }
                }
                catch (Exception ex)
                {
                   // MessageBox.Show("Error updating driver name: " + ex.Message);
                }
            }
            return done;
        }


        public  bool UpdateDriverPhoneNumber(Driver driver, string newPhoneNumber)
        {
            bool done = false;
            using (SqlConnection connection = new SqlConnection(con))
            {
                string updateQuery = "UPDATE Drivers SET PhoneNumber = @NewPhoneNumber WHERE DriverID = @DriverID";

                SqlCommand command = new SqlCommand(updateQuery, connection);

                command.Parameters.AddWithValue("@NewPhoneNumber", newPhoneNumber);
                command.Parameters.AddWithValue("@DriverID", driver.getID());

                try
                {
                    connection.Open();
                    int rowsAffected = command.ExecuteNonQuery();
                    if (rowsAffected > 0)
                    {
                        done = true;
                    }
                    else
                    {
                       // MessageBox.Show("Driver not found or no changes made.");
                    }
                }
                catch (Exception ex)
                {
                  //  MessageBox.Show("Error updating driver phone number: " + ex.Message);
                }
            }
            return done;
        }

        public bool UpdateAvailibiltyStatus(int driverId, bool status)
        {
            bool done = false;

            using (SqlConnection connection = new SqlConnection(con))
            {
                string updateQuery = "UPDATE Drivers SET AvailibilityStatus = @Status WHERE DriverID = @DriverID";

                SqlCommand command = new SqlCommand(updateQuery, connection);

                command.Parameters.AddWithValue("@Status", status);
                command.Parameters.AddWithValue("@DriverID", driverId);

                try
                {
                    connection.Open();
                    int rowsAffected = command.ExecuteNonQuery();
                    if (rowsAffected > 0)
                    {
                        done = true;
                    }
                    else
                    {
                      //  MessageBox.Show("Driver not found or no changes made.");
                    }
                }
                catch (Exception ex)
                {
                    //MessageBox.Show("Error updating driver availability status: " + ex.Message);
                }
            }
            return done;
        }



        public List<Driver> GetAllAvailableDriversList( )
        {
            List<Driver> availableDrivers = new List<Driver>();

            using (SqlConnection connection = new SqlConnection(con))
            {
                string query = "SELECT * FROM Drivers WHERE AvailibilityStatus = 1 AND DriverID IS NOT NULL";

                SqlCommand command = new SqlCommand(query, connection);

                try
                {
                    connection.Open();
                    SqlDataReader reader = command.ExecuteReader();

                    while (reader.Read())
                    {
                        // Retrieve column values from the database
                        string driverName = reader["DriverName"].ToString();
                        string driverIdCard = reader["DriverIdCard"].ToString();
                        string phoneNumber = reader["PhoneNumber"].ToString();
                        int driverID = Convert.ToInt32(reader["DriverID"]);
                        string carModel = reader["CarModel"].ToString();
                        string license = reader["License"].ToString();
                        DateTime joiningDate = Convert.ToDateTime(reader["JoiningDate"]);
                        bool availabilityStatus = Convert.ToBoolean(reader["AvailibilityStatus"]);

                        // Create a new Driver object and add it to the list
                        Driver driver = new Driver(driverName, phoneNumber, carModel, license, driverIdCard, availabilityStatus, driverID, joiningDate);
                        availableDrivers.Add(driver);
                    }

                    reader.Close();
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Error retrieving available drivers: " + ex.Message);
                }
            }

            return availableDrivers;
        }

        public static Driver SearchDiverByIdCard(string idCard) //new addition
        {
            Driver rider = null;

            using (SqlConnection connection = new SqlConnection(con))
            {
                string query = "SELECT * FROM Drivers WHERE Driver_idcard = @DriverID";

                using (SqlCommand command = new SqlCommand(query, connection))
                {
                    command.Parameters.AddWithValue("@DriverID", idCard);

                    try
                    {
                        connection.Open();
                        SqlDataReader reader = command.ExecuteReader();

                        if (reader.Read())
                        {
                            // Retrieve rider information from the database
                            string name = reader.GetString(0);
                            string idcard = reader.IsDBNull(1) ? null : reader.GetString(1);
                            string phoneNumber = reader.IsDBNull(2) ? null : reader.GetString(2);
                            int driverID = reader.GetInt32(3);

                            // Create a new Driver object
                            rider = new Driver(name, idcard);
                            rider.setPhonenumber(phoneNumber);
                            rider.setID(driverID);
                        }

                        reader.Close();
                    }
                    catch (Exception ex)
                    {
                      //  MessageBox.Show("Error searching rider by ID: " + ex.Message);
                    }
                }
            }

            return rider;
        }



    }
}
