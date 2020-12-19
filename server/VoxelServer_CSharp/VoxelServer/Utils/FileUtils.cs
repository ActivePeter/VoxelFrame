using System;
using System.Collections.Generic;
using System.IO;
using System.Security.Cryptography;
using System.Text;

namespace Voxel.Utils
{
    class FileUtils
    {
        public static void createIfNotExist(string path)
        {
            string absPath = getAbsolutePath(path);
            if (System.IO.Directory.Exists(absPath) == false)//如果不存在就创建file文件夹
            {
                Console.WriteLine("file:\"" + path + "\" not exists\r\n"+"createdAt:"+ absPath);

                System.IO.Directory.CreateDirectory(absPath);
            }
        }
        public static string getAbsolutePath(string path)
        {
            return getPrjRootPath() + Path.DirectorySeparatorChar + path;
        }
        public static string getPrjRootPath()
        {
            return System.IO.Directory.GetCurrentDirectory();
        }
        public static void saveFile(string path,string data)
        {
            path = getAbsolutePath(path);
            if (!File.Exists(path))
            {
                File.Create(path).Close();
            }
            using (System.IO.StreamWriter file = new System.IO.StreamWriter(path, true))
            {
                file.WriteLine(data);
                file.Dispose();
            }
        }
        public static string readFile(string path)
        {
            path = getAbsolutePath(path);
            if (!File.Exists(path))
            {
                return null;
            }
            return System.IO.File.ReadAllText(path);
        }
    }
}
