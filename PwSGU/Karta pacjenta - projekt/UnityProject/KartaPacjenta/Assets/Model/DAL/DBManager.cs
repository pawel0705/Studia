using JetBrains.Annotations;
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
	/// Class that initializes the database
	/// </summary>
    class DBManager
	{
		public static string dbPath;
		public static bool isInitialized = false;
		public static void CreateSchema()
		{
			using (var conn = new SqliteConnection(dbPath))
			{
				conn.Open();
				using (var cmd = conn.CreateCommand())
				{
					cmd.CommandType = CommandType.Text;
					cmd.CommandText = "CREATE TABLE IF NOT EXISTS 'patient' ( " +
									  "  'id' INTEGER PRIMARY KEY, " +
									  "  'name' TEXT NOT NULL, " +
									  "  'surname' INTEGER NOT NULL" +
									  ");";

					var result = cmd.ExecuteNonQuery();
				}
				using (var cmd = conn.CreateCommand())
				{
					cmd.CommandType = CommandType.Text;
					cmd.CommandText = "CREATE TABLE IF NOT EXISTS 'file' ( " +
									  "  'id' INTEGER PRIMARY KEY, " +
									  "  'patientId' INTEGER NOT NULL, " +
									  "  'data' BLOB NOT NULL, " +
									  "  'posX' REAL NOT NULL, " +
									  "  'posY' REAL NOT NULL, " +
									  "  'posZ' REAL NOT NULL, " +
									  "  'rotX' REAL NOT NULL, " +
									  "  'rotY' REAL NOT NULL, " +
									  "  'rotZ' REAL NOT NULL, " +
									  "  'scaleX' REAL NOT NULL, " +
									  "  'scaleY' REAL NOT NULL, " +
									  "  'scaleZ' REAL NOT NULL " +
									  ");";

					var result = cmd.ExecuteNonQuery();
				}
			}
		}

		/// <summary>
		/// Initializes the database
		/// </summary>
		/// <param name="_dbPath"></param>
		public static void Initialize(string _dbPath)
		{
			dbPath = _dbPath;
			CreateSchema();
			PatientDAO.dbPath = dbPath;
			FileDAO.dbPath = dbPath;
			isInitialized = true;
		}
	}
}
