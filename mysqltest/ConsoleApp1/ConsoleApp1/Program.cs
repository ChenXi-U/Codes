using MySql.Data.MySqlClient;
using MySqlX.XDevAPI.Relational;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class Program
    {
        static void Main(string[] args)
        {
            MySqlOpen();

            Console.ReadKey();
        }


        static void MySqlOpen()
        {
            //连接字符串
            string conStr = "server=127.0.0.1;port=3306;user=root;password=comeon;database=cxsqltest";
            //定义对象
            MySqlConnection con = new MySqlConnection(conStr);
            //定义命令
            MySqlCommand cmd = null;//con.CreateCommand();

            try
            {
                con.Open();


                //查询
                //string queryStr = "select * from mytable";
                //cmd = new MySqlCommand(queryStr, con);

                //MySqlDataReader reader = cmd.ExecuteReader();
                //while (reader.Read())
                //{
                //    Console.WriteLine(reader[0].ToString() + " " + reader[1].ToString());
                //}

                //增删改
                //for (int i = 0; i < 100; i++)
                //{
                //    //string insertStr = "INSERT IGNORE INTO mytable (id, username) VALUES (@id, @username)";
                //    string insertStr = "INSERT INTO mytable (id,SN, username) VALUES (@id,@SN, @username) ON DUPLICATE KEY UPDATE id=values(id),sn=values(sn), username = values(username)";
                //    cmd = new MySqlCommand(insertStr, con);
                //    cmd.Parameters.AddWithValue("@id",i);
                //    cmd.Parameters.AddWithValue("@sn", "SN" + i);
                //    cmd.Parameters.AddWithValue("@username", "username" + i);
                //    cmd.ExecuteNonQuery();
                //}
                //删除
                //string deleteStr = "delete from mytable";
                //string deleteStr = "DELETE FROM mytable WHERE BINARY SN NOT LIKE '%SN%'";
                //cmd = new MySqlCommand(deleteStr, con);
                //cmd.ExecuteNonQuery();
                //更新
                //string updateStr = "update mytable set id=1 where username='zhanghuihui'";
                //cmd = new MySqlCommand(updateStr, con);
                //cmd.ExecuteNonQuery();
                //添加一列
                //string addColumnSql = "ALTER TABLE mytable ADD COLUMN id int FIRST";
                //cmd = new MySqlCommand(addColumnSql, con);
                //cmd.ExecuteNonQuery();


                Console.WriteLine("操作完成");
                //查询
                string queryStr = "select * from mytable";
                cmd = new MySqlCommand(queryStr, con);

                MySqlDataReader reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    Console.WriteLine(reader[0].ToString() + " " + reader[1].ToString() + " " + reader[2].ToString());
                }

            }
            catch
            {
                Console.WriteLine("操作错误");
            }
            finally
            {
                cmd.Dispose();
                con.Close();
                Console.WriteLine("操作结束");
            }
        }
    }
}
