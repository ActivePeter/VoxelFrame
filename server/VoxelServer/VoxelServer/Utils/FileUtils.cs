using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace VoxelServer.Utils
{
    class FileUtils
    {
        public static void createIfNotExist(String path)
        {
            String absPath = getAbsolutePath(path);
            if (System.IO.Directory.Exists(absPath) == false)//如果不存在就创建file文件夹
            {
                Console.WriteLine("file:\"" + path + "\" not exists\r\n"+"createdAt:"+ absPath);

                System.IO.Directory.CreateDirectory(absPath);
            }
        }
        public static String getAbsolutePath(String path)
        {
            return getPrjRootPath() + Path.DirectorySeparatorChar + path;
        }
        public static String getPrjRootPath()
        {
            return System.IO.Directory.GetCurrentDirectory();
        }
    }
}
