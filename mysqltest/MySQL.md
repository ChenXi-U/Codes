## MySQL 命令
### 基本指令
``` javascript
//数据库启动
net stop mysql
net start mysql

//数据库连接
mysql -h 127.0.0.1 -P 3306 -u root -p"comeon" --ssl-mode=DISABLE

//显示所有数据库
show databases;

//选择数据库
use mysql;

//显示库中数据表
show tables;

//显示数据表的结构
describe mytable;

//建库
create database name;
//删库
drop database name;

//建表
create table tablename (name VARCHAR(20), owner VARCHAR(20),species VARCHAR(20), sex CHAR(1), birth DATE, death DATE);
//删表
drop table table_name;

//修改表名称
rename table table_name to new_table_name;

//查询指令
select * from mytable;
select id,username from mytable;

//删除指令
delete from mytable;
DELETE FROM mytable WHERE BINARY SN NOT LIKE '%SN%';

//更新指令
update mytable set column1 = value1 where username=username;

//将表 students 中 name 为 '张三' 的记录的 class_id 更新为表 classes 中 name 为 '数学班' 的 class_id
UPDATE students
SET class_id = (SELECT id FROM classes WHERE name = '数学班')
WHERE name = '张三';

//表操作
//添加一列 ALTER
ALTER TABLE mytable ADD COLUMN id int FIRST;
//删除字段
ALTER TABLE mytable drop column_name;
//修改字段名字
ALTER TABLE mytable change old_name new_name type;
//修改字段数据类型
ALTER TABLE mytable modify column_name new_type;

```
### C#实现
```C#
//连接
string conStr = "server=127.0.0.1;port=3306;user=root;password=comeon;database=cxsqltest";
//定义对象
MySqlConnection con = new MySqlConnection(conStr);
//定义命令
MySqlCommand cmd = null;//con.CreateCommand();

con.Open();

//查询
string queryStr = "select * from mytable";
cmd = new MySqlCommand(queryStr, con);

MySqlDataReader reader = cmd.ExecuteReader();
while (reader.Read())
{
   Console.WriteLine(reader[0].ToString() + " " + reader[1].ToString());
}

// 增删改
for (int i = 0; i < 100; i++)
{
   //string insertStr = "INSERT IGNORE INTO mytable (id, username) VALUES (@id, @username)";
   string insertStr = "INSERT INTO mytable (id,SN, username) VALUES (@id,@SN, @username) ON DUPLICATE KEY UPDATE id=values(id),sn=values(sn), username = values(username)";
   cmd = new MySqlCommand(insertStr, con);
   cmd.Parameters.AddWithValue("@id",i);
   cmd.Parameters.AddWithValue("@sn", "SN" + i);
   cmd.Parameters.AddWithValue("@username", "username" + i);
   cmd.ExecuteNonQuery();
}

// 删除
// string deleteStr = "delete from mytable";
string deleteStr = "DELETE FROM mytable WHERE BINARY SN NOT LIKE '%SN%'";
cmd = new MySqlCommand(deleteStr, con);
cmd.ExecuteNonQuery();

// 更新
string updateStr = "update mytable set id=1 where username='zhanghuihui'";
cmd = new MySqlCommand(updateStr, con);
cmd.ExecuteNonQuery();

// 添加一列
string addColumnSql = "ALTER TABLE mytable ADD COLUMN id int FIRST";
cmd = new MySqlCommand(addColumnSql, con);
cmd.ExecuteNonQuery();

//结束
cmd.Dispose();
con.Close();
```




