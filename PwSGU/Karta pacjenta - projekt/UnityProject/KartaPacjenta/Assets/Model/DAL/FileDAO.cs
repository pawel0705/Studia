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
	/// Class used to access files from the database
	/// </summary>
    class FileDAO
    {
		/// <summary>
		/// path to the database file
		/// </summary>
		public static string dbPath;

		/// <summary>
		/// Returns an IEnumerable of all files associated with given patientId
		/// </summary>
		/// <param name="patientId"> id of the patinet whose files are to be retrieved</param>
		/// <returns>IEnumerable of patient files</returns>
		public static IEnumerable<File> GetFileForPatient(int patientId)
		{
			var files = new List<File>();
			using (var conn = new SqliteConnection(dbPath))
			{
				conn.Open();
				using (var cmd = conn.CreateCommand())
				{
					cmd.CommandType = CommandType.Text;
					cmd.CommandText = "SELECT * FROM file WHERE patientId = @PatientId;";

					cmd.Parameters.Add(new SqliteParameter
					{
						ParameterName = "@PatientId",
						Value = patientId
					});

					var reader = cmd.ExecuteReader();

					while (reader.Read())
					{
						var file = new File();
						file.Id = reader.GetInt32(0);
						file.PatientId = reader.GetInt32(1);
						file.Data = (byte[])reader[2];
						file.PosX = reader.GetFloat(3);
						file.PosY = reader.GetFloat(4);
						file.PosZ = reader.GetFloat(5);
						file.RotX = reader.GetFloat(6);
						file.RotY = reader.GetFloat(7);
						file.RotZ = reader.GetFloat(8);
						file.ScaleX = reader.GetFloat(9);
						file.ScaleY = reader.GetFloat(10);
						file.ScaleZ = reader.GetFloat(11);
						files.Add(file);
					}
				}
			}
			return files;
		}

		/// <summary>
		/// Returns File Object with a given Id
		/// </summary>
		/// <param name="fileId">id of the file to retrieve</param>
		/// <returns>Retrieved file</returns>
		public static File GetFile(int fileId)
		{
			File file = null;
			using (var conn = new SqliteConnection(dbPath))
			{
				conn.Open();
				using (var cmd = conn.CreateCommand())
				{
					cmd.CommandType = CommandType.Text;
					cmd.CommandText = "SELECT * FROM file WHERE id = @FileId;";

					cmd.Parameters.Add(new SqliteParameter
					{
						ParameterName = "@FileId",
						Value = fileId
					});

					var reader = cmd.ExecuteReader();
					if (reader.Read())
					{
						file = new File();
						file.Id = reader.GetInt32(0);
						file.PatientId = reader.GetInt32(1);
						file.Data = (byte[])reader[2];
						file.PosX = reader.GetFloat(3);
						file.PosY = reader.GetFloat(4);
						file.PosZ = reader.GetFloat(5);
						file.RotX = reader.GetFloat(6);
						file.RotY = reader.GetFloat(7);
						file.RotZ = reader.GetFloat(8);
						file.ScaleX = reader.GetFloat(9);
						file.ScaleY = reader.GetFloat(10);
						file.ScaleZ = reader.GetFloat(11);
					}
				}
			}
			return file;
		}

		/// <summary>
		/// Returns File Object with a given rowId
		/// </summary>
		/// <param name="rowId">id of the row to retrieve</param>
		/// <returns>Retrieved row</returns>
		public static File GetFileByRowId(int rowId)
		{
			File file = null;
			using (var conn = new SqliteConnection(dbPath))
			{
				conn.Open();
				using (var cmd = conn.CreateCommand())
				{
					cmd.CommandType = CommandType.Text;
					cmd.CommandText = "SELECT * FROM file WHERE rowid = @RowId;";

					cmd.Parameters.Add(new SqliteParameter
					{
						ParameterName = "@RowId",
						Value = rowId
					});

					var reader = cmd.ExecuteReader();
					if (reader.Read())
					{
						file = new File();
						file.Id = reader.GetInt32(0);
						file.PatientId = reader.GetInt32(1);
						file.Data = (byte[])reader[2];
						file.PosX = reader.GetFloat(3);
						file.PosY = reader.GetFloat(4);
						file.PosZ = reader.GetFloat(5);
						file.RotX = reader.GetFloat(6);
						file.RotY = reader.GetFloat(7);
						file.RotZ = reader.GetFloat(8);
						file.ScaleX = reader.GetFloat(9);
						file.ScaleY = reader.GetFloat(10);
						file.ScaleZ = reader.GetFloat(11);
					}
				}
			}
			return file;
		}


		/// <summary>
		/// Adds new File to the database
		/// </summary>
		/// <param name="file">file object to insert into database</param>
		/// <returns>id of newly inserted object</returns>
		public static int AddFile(File file)
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
					cmd.CommandText = "INSERT INTO file (patientId, data) " +
									  "VALUES (@PatientId, @Data);";

					cmd.Parameters.Add(new SqliteParameter
					{
						ParameterName = "@PatientId",
						Value = file.PatientId
					});

					cmd.Parameters.Add(new SqliteParameter
					{
						ParameterName = "@Data",
						Value = file.Data,
						DbType = DbType.Binary
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
				File insertedFile = GetFileByRowId(rowId);
				return insertedFile.Id;
			}

			return id;
		}

		/// <summary>
		/// Updates a file in the database
		/// </summary>
		/// <param name="file">file object to update in the database</param>
		/// <returns>whether or not the operation was successful</returns>
		public static bool UpdateFile(File file)
		{
			var queryResult = 0;
			using (var conn = new SqliteConnection(dbPath))
			{
				conn.Open();
				using (var cmd = conn.CreateCommand())
				{
					cmd.CommandType = CommandType.Text;
					cmd.CommandText = "UPDATE file " +
									  "SET " +
									  "patientId = @PatientId, " +
									  "data = @Data, " +
									  "posX = @PosX, " +
									  "posY = @PosY, " +
									  "posZ = @PosZ, " +
									  "rotX = @RotX, " +
									  "rotY = @RotY, " +
									  "rotZ = @RotZ, " +
									  "scaleX = @ScaleX, " +
									  "scaleY = @ScaleY, " +
									  "scaleZ = @ScaleZ " +
									  "WHERE Id = @Id;";

					cmd.Parameters.Add(new SqliteParameter
					{
						ParameterName = "@Id",
						Value = file.Id
					});

					cmd.Parameters.Add(new SqliteParameter
					{
						ParameterName = "@PatientId",
						Value = file.PatientId
					});

					cmd.Parameters.Add(new SqliteParameter
					{
						ParameterName = "@Data",
						Value = file.Data,
						DbType = DbType.Binary
					});

					cmd.Parameters.Add(new SqliteParameter
					{
						ParameterName = "@PosX",
						Value = file.PosX
					});
					cmd.Parameters.Add(new SqliteParameter
					{
						ParameterName = "@PosY",
						Value = file.PosY
					});
					cmd.Parameters.Add(new SqliteParameter
					{
						ParameterName = "@PosZ",
						Value = file.PosZ
					});

					cmd.Parameters.Add(new SqliteParameter
					{
						ParameterName = "@RotX",
						Value = file.RotX
					});
					cmd.Parameters.Add(new SqliteParameter
					{
						ParameterName = "@RotY",
						Value = file.RotY
					});
					cmd.Parameters.Add(new SqliteParameter
					{
						ParameterName = "@RotZ",
						Value = file.RotZ
					});

					cmd.Parameters.Add(new SqliteParameter
					{
						ParameterName = "@ScaleX",
						Value = file.ScaleX
					});
					cmd.Parameters.Add(new SqliteParameter
					{
						ParameterName = "@ScaleY",
						Value = file.ScaleY
					});
					cmd.Parameters.Add(new SqliteParameter
					{
						ParameterName = "@ScaleZ",
						Value = file.ScaleZ
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
		/// <param name="fileId"></param>
		/// <returns></returns>
		public static bool DeleteFile(int fileId)
		{
			return true;
		}
	}
}
