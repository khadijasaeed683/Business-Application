using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Drivo
{
    internal class RiderCrudDB:IRiderCrud
    {
        public static string con = Utils.ConnectionString();
    

        static RiderCrudDB instance;
        public static RiderCrudDB GetInstance()
        {
            if (instance == null)
            {
                instance = new RiderCrudDB();
            }


            return instance;

        }
        public RiderCrudDB()
        {

        }
        private static Rider rider=new Rider();
        public  bool StoreUser(Rider user, string connectionString)
        {
            SqlConnection connection = new SqlConnection(connectionString);
            connection.Open();
            string query = String.Format("Insert into Rider (Name, Email ,Password,Address, PhoneNumber) VALUES('{0}','{1}','{2}','{3}','{4}')", user.getName(), user.getEmail(), user.getPassword(), user.getAddress(), user.getPhoneNumber());
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
        public  Rider SignIn(Rider user, string connectionString) //check name and password from database
        {
            try
            {
                SqlConnection connection = new SqlConnection(connectionString);
                connection.Open();

                string us = user.getName();
                string pa = user.getPassword();
                string searchQuery = String.Format("Select * from Rider where Name = '{0}' and Password = '{1}'", us, pa);
                SqlCommand command = new SqlCommand(searchQuery, connection);
                SqlDataReader data = command.ExecuteReader();
                if (data.Read())
                {
                    Rider storedUser = new Rider(data.GetInt32(0), data.GetString(1), data.GetString(2), data.GetString(3), data.GetString(4));
                    connection.Close();
                    return storedUser;
                }
                connection.Close();
            }
            catch (Exception ex)
            {
                {
                    Console.WriteLine("Sign IN error: " + ex.Message);
                }
                return null;
            }
            return null;
        }
        public  Rider SearchRiderWithId(int riderid, string connectionString)
        {
            Rider rider = null;

            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                string query = "SELECT * FROM Rider WHERE Rider_id = @RiderID";

                using (SqlCommand command = new SqlCommand(query, connection))
                {
                    command.Parameters.AddWithValue("@RiderID", riderid);

                    try
                    {
                        connection.Open();
                        SqlDataReader reader = command.ExecuteReader();

                        if (reader.Read())
                        {
                            // Retrieve rider information from the database
                            int riderId = reader.GetInt32(0);
                            string name = reader.IsDBNull(1) ? null : reader.GetString(1);
                            string email = reader.IsDBNull(2) ? null : reader.GetString(2);
                            string password = reader.IsDBNull(3) ? null : reader.GetString(3);
                            string address = reader.IsDBNull(4) ? null : reader.GetString(4);
                            string phoneNumber = reader.IsDBNull(5) ? null : reader.GetString(5);

                            // Create a new Rider object
                            rider = new Rider(riderId, name, email, password, phoneNumber);
                        }

                        reader.Close();
                    }
                    catch (Exception ex)
                    {
                    }
                }
            }

            return rider;
        }

        public  void UpdateRiderName(Rider rider, string newName, string con)
        {
            using (SqlConnection connection = new SqlConnection(con))
            {
                string query = "UPDATE Rider SET Name = @NewName WHERE Rider_id = @RiderID";

                SqlCommand command = new SqlCommand(query, connection);
                command.Parameters.AddWithValue("@NewName", newName);
                command.Parameters.AddWithValue("@RiderID", rider.getID());

                try
                {
                    connection.Open();
                    command.ExecuteNonQuery();

                    // Update the Rider object
                    rider.setName(newName);

                    Console.WriteLine("Rider name updated successfully.");
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Error updating rider name: " + ex.Message);
                }
            }
        }
        public  void UpdateRiderPassword(Rider rider, string newPass, string con)
        {
            using (SqlConnection connection = new SqlConnection(con))
            {
                string query = "UPDATE Rider SET Password = @NewPass WHERE Rider_id = @RiderID";

                SqlCommand command = new SqlCommand(query, connection);
                command.Parameters.AddWithValue("@NewPass", newPass);
                command.Parameters.AddWithValue("@RiderID", rider.getID());

                try
                {
                    connection.Open();
                    command.ExecuteNonQuery();

                    // Update the Rider object
                    rider.setPassword(newPass);

                    Console.WriteLine("Rider Password updated successfully.");
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Error updating rider Password: " + ex.Message);
                }
            }
        }
        public  void UpdateRiderPhoneNumber(Rider rider, string newPhn, string con)
        {
            using (SqlConnection connection = new SqlConnection(con))
            {
                string query = "UPDATE Rider SET PhoneNumber = @NewPhn WHERE Rider_id = @RiderID";

                SqlCommand command = new SqlCommand(query, connection);
                command.Parameters.AddWithValue("@NewPhn", newPhn);
                command.Parameters.AddWithValue("@RiderID", rider.getID());

                try
                {
                    connection.Open();
                    command.ExecuteNonQuery();

                    // Update the Rider object
                    rider.setPhoneNumber(newPhn);

                    Console.WriteLine("Rider PhoneNumber updated successfully.");
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Error updating rider PhoneNumber: " + ex.Message);
                }
            }
        }  
        public  void UpdateRiderEmail(Rider rider, string newEmail, string con)
        {
            using (SqlConnection connection = new SqlConnection(con))
            {
                string query = "UPDATE Rider SET Email = @Neweml WHERE Rider_id = @RiderID";

                SqlCommand command = new SqlCommand(query, connection);
                command.Parameters.AddWithValue("@Neweml", newEmail);
                command.Parameters.AddWithValue("@RiderID", rider.getID());

                try
                {
                    connection.Open();
                    command.ExecuteNonQuery();

                    // Update the Rider object
                    rider.setEmail(newEmail);

                    Console.WriteLine("Rider email updated successfully.");
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Error updating rider email: " + ex.Message);
                }
            }
        }
        public  List<Rider> GetAllActiveRiders(string connectionString)
        {
            List<Rider> allriders = new List<Rider>();

            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                string query = "SELECT * FROM Rider where IsDeleted IS NULL";

                using (SqlCommand command = new SqlCommand(query, connection))
                {
                    try
                    {
                        connection.Open();
                        SqlDataReader reader = command.ExecuteReader();

                        while (reader.Read())
                        {
                            // Retrieve rider information from the database
                            int riderId = reader.GetInt32(0);
                            string name = reader.IsDBNull(1) ? null : reader.GetString(1);
                            string email = reader.IsDBNull(2) ? null : reader.GetString(2);
                            string password = reader.IsDBNull(3) ? null : reader.GetString(3);
                            string address = reader.IsDBNull(4) ? null : reader.GetString(4);
                            string phoneNumbe = reader.IsDBNull(5) ? null : reader.GetString(5);

                            // Create a new Rider object and add it to the list
                            Rider rid = new Rider(riderId, name, email, password, phoneNumbe);
                            rid.setPhonenumber(phoneNumbe);
                            allriders.Add(rid);
                        }

                        reader.Close();
                    }
                    catch (Exception ex)
                    {
                    }
                }
            }

            return allriders;
        }
        public bool DeleteRider(int riderid, string connectionString)
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    string query = "UPDATE Rider SET IsDeleted = 1 WHERE Rider_id = @RiderID AND (IsDeleted IS NULL OR IsDeleted = 0);";
                    using (SqlCommand command = new SqlCommand(query, connection))
                    {
                        command.Parameters.AddWithValue("@RiderID", riderid);

                        connection.Open();
                        int rowsAffected = command.ExecuteNonQuery();

                        if (rowsAffected > 0)
                        {
                            // Rider deleted successfully
                            return true;

                        }
                        else
                        {
                            // No rider found with the specified ID
                            return false;
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error deleting rider: " + ex.Message);
                return false;
            }
        }




    }
}
