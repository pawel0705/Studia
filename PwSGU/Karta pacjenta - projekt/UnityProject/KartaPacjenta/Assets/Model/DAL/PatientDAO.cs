using Mono.Data.Sqlite;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assets.Model.DAL
{
	/// <summary>
	/// class used to access patient data from the database
	/// </summary>
    class PatientDAO
	{
		/// <summary>
		/// path to the database file
		/// </summary>
		public static string dbPath;

		/// <summary>
		/// Returns Patient Object with a given Id
		/// </summary>
		/// <param name="patientId">id of the patient to retrieve</param>
		/// <returns>Retrieved patient</returns>
        public static Patient GetPatient(int patientId)
        {
			Patient patient = null;
			using (var conn = new SqliteConnection(dbPath))
			{
				conn.Open();
				using (var cmd = conn.CreateCommand())
				{
					cmd.CommandType = CommandType.Text;
					cmd.CommandText = "SELECT * FROM patient WHERE id = @PatientId;";

					cmd.Parameters.Add(new SqliteParameter
					{
						ParameterName = "@PatientId",
						Value = patientId
					});

					var reader = cmd.ExecuteReader();
					if (reader.Read())
					{
						patient = new Patient();
						patient.Id = reader.GetInt32(0);
						patient.Name = reader.GetString(1);
						patient.Surname = reader.GetString(2);
						patient.FilesVisible = reader.GetBoolean(3);
					}
				}
			}
			patient.Files = FileDAO.GetFileForPatient(patientId).ToList();
			return patient;
        }

		/// <summary>
		/// Returns Patient Object with a given SQLite generated rowid
		/// </summary>
		/// <param name="rowId">id of the row to retrieve</param>
		/// <returns>Retrieved patient</returns>
		public static Patient GetPatientByRowId(int rowId)
		{
			Patient patient = null;
			using (var conn = new SqliteConnection(dbPath))
			{
				conn.Open();
				using (var cmd = conn.CreateCommand())
				{
					cmd.CommandType = CommandType.Text;
					cmd.CommandText = "SELECT * FROM patient WHERE rowid = @RowId;";

					cmd.Parameters.Add(new SqliteParameter
					{
						ParameterName = "@RowId",
						Value = rowId
					});

					var reader = cmd.ExecuteReader();
					if (reader.Read())
					{
						patient = new Patient();
						patient.Id = reader.GetInt32(0);
						patient.Name = reader.GetString(1);
						patient.Surname = reader.GetString(2);
						patient.FilesVisible = reader.GetBoolean(3);
					}
				}
			}
			patient.Files = FileDAO.GetFileForPatient(rowId).ToList();
			return patient;
		}

		/// <summary>
		/// inserts new patient to the database
		/// </summary>
		/// <param name="patient">Patient object to insert into database</param>
		/// <returns>id of newly inserted patient</returns>
        public static int AddPatient(Patient patient)
        {
			var rowId = -1;
			var id = -1;
			var queryResult = 0;
			using (var conn = new SqliteConnection(dbPath))
			{
				conn.Open();
				using (var cmd = conn.CreateCommand())
				{
					cmd.CommandType = CommandType.Text;
					cmd.CommandText = "INSERT INTO patient (name, surname) " +
									  "VALUES (@Name, @Surname);";

					cmd.Parameters.Add(new SqliteParameter
					{
						ParameterName = "@Name",
						Value = patient.Name
					});

					cmd.Parameters.Add(new SqliteParameter
					{
						ParameterName = "@Surname",
						Value = patient.Surname
					});

					queryResult = cmd.ExecuteNonQuery();
				}
				if (queryResult == 1)
				{
					using (SqliteCommand cmd = new SqliteCommand("SELECT last_insert_rowid()", conn))
					{
						rowId = (int)cmd.ExecuteScalar();
					}
				}
			}

			if (rowId >= 0)
			{
				Patient insertedPatient = GetPatientByRowId(rowId);
				return insertedPatient.Id;
			}
			
			return id;
		}


		/// <summary>
		/// Updates a patient in the database
		/// </summary>
		/// <param name="patient">patient object to update in the database</param>
		/// <returns>whether or not the operation was successful</returns>
		public static bool UpdatePatient(Patient patient)
		{
			var queryResult = 0;
			using (var conn = new SqliteConnection(dbPath))
			{
				conn.Open();
				using (var cmd = conn.CreateCommand())
				{
					cmd.CommandType = CommandType.Text;
					cmd.CommandText = "UPDATE patient " +
									  "SET " +
									  "name = @Name, " +
									  "surname = @Surname, " +
									  "filesVisible = @FilesVisible " +
									  "WHERE Id = @Id;";

					cmd.Parameters.Add(new SqliteParameter
					{
						ParameterName = "@Id",
						Value = patient.Id
					});
					cmd.Parameters.Add(new SqliteParameter
					{
						ParameterName = "@Name",
						Value = patient.Name
					});
					cmd.Parameters.Add(new SqliteParameter
					{
						ParameterName = "@Surname",
						Value = patient.Surname
					});
					cmd.Parameters.Add(new SqliteParameter
					{
						ParameterName = "@FilesVisible",
						Value = patient.FilesVisible
					});


					queryResult = cmd.ExecuteNonQuery();
				}
			}
			if (queryResult == 1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		/// <summary>
		/// Not yet implemented
		/// </summary>
		/// <param name="patientId"></param>
		/// <returns></returns>
		public static bool DeletePatient(int patientId)
        {
            return true;
        }
    }
}
