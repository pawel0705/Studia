using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assets.Model
{
    /// <summary>
    /// Represents a patient's file. Stores it's global position, rotation, and local scale
    /// </summary>
    class File
    {
        public int Id { get; set; }
        public int PatientId { get; set; }
        public byte[] Data { get; set; }

        public float PosX { get; set; }
        public float PosY { get; set; }
        public float PosZ { get; set; }

        public float RotX { get; set; }
        public float RotY { get; set; }
        public float RotZ { get; set; }

        public float ScaleX { get; set; }
        public float ScaleY { get; set; }
        public float ScaleZ { get; set; }
    }
}
