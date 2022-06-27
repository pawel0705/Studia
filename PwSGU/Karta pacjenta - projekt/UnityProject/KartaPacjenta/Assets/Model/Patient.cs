using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assets.Model
{
    /// <summary>
    /// Represents a patient with their collection of files
    /// </summary>
    class Patient
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string Surname { get; set; }
        public List<File> Files { get; set; }
        public bool FilesVisible { get; set; }
    }
}
