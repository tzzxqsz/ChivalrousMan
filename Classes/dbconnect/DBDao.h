#pragma once
#ifndef __DB_INTERFACE_H__
#define __DB_INTERFACE_H__
#include"tool/PreProcess.h"
#include<mysql.h>
#include<mysqld_error.h>
#include<string>
#include<initializer_list>
#include<vector>
#include<fstream>

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"libmysql.lib")
#define QUERY 1
#define INSERT 2
#define DELETE 3
#define UPDATE 4
#define DBCFGFILE "DB.cfg"

/*
*class DBDao
*���ݿ������
*/
template<typename Model>
class DBDao
{
public:
	DBDao();

	DBDao(const std::string& host, const std::string& username, const std::string& passwd, const std::string& dbname);
	~DBDao();

	/*
	*setModel(Model md);
	*����Ҫ������ʵ����
	*@param md��ʵ�������
	*/
	void setModel(Model md);

	/*
	*queryModel();
	*��ѯʵ������
	*@return vector<Model>������ʵ�������ݼ���ʧ���򷵻ؿ�vector
	*/
	std::vector<Model> queryModel();

	/*
	*insertModel();
	*��ĳһʵ���������뵽���ݿ�
	*@return bool������true��ʾ����ɹ�������ʧ��
	*/
	bool insertModel();

	/*
	*deleteModel();
	*ɾ��ĳһʵ����
	*@return bool������true��ʾ����ɹ����������ʧ��
	*/
	bool deleteModel();

	/*
	*updateModel(const std::string& fieldName, const std::string& value);
	*����ĳһ��ֵ����ʵ����
	*@param fieldName�������ļ�ֵ��
	*@param value:�����ļ�ֵ
	*@return bool������ɹ�����true�����򷵻�false
	*/
	bool updateModel(const std::string& fieldName, const std::string& value);

	/*
	*updateModel(const std::map<std::string, std::string>& keyvls);
	*���ݶ����ֵ�Ը��±�������
	*@param keyvls���洢�����ֵ��
	*@return bool������ɹ�����true�����򷵻�false
	*/
	bool updateModel(const std::map<std::string, std::string>& keyvls);

	void close();

	void clear();
private:
	/*
	*initConnect();
	*��ʼ������
	*/
	void initConnect();

	/*
	*generateSql(int flag);
	*���ݲ�ͬ�������Sql���
	*@param  flag�����ڱ�ǲ�ͬ���
	*/
	void generateSql(int flag);

	std::string generateWhere();

	std::string generateValues();

	std::string generateUpdate();

	/*
	*initDefaultCfg()
	*��ʼ��Ĭ������
	*/
	void initDefaultCfg();

	MYSQL* m_sqlCon;   //���ݿ����Ӿ��
	std::string m_host;    //������
	std::string m_username;      //�û���
	std::string m_passwd;       //����
	std::string m_dbname;      //���ݿ���
	unsigned int m_port = 3306;     //���ݿ�������˿�
	std::string m_sql;
	Model m_md;
};

template<typename Model>
DBDao<Model>::DBDao()
{
	initDefaultCfg();
	initConnect();
}

template<typename Model>
DBDao<Model>::DBDao(const std::string& host, const std::string& username, const std::string& passwd, const std::string& dbname) :
	m_host(host),
	m_username(username),
	m_passwd(passwd),
	m_dbname(dbname)
{
	initConnect();
}

template<typename Model>
DBDao<Model>::~DBDao()
{
	close();
}

template<typename Model>
void DBDao<Model>::initDefaultCfg()
{
	std::ifstream fin;
	fin.open(DBCFGFILE, std::ios::in);
	if (fin.fail())
	{
		return;
	}
	std::string tmp;
	fin >> tmp;
	fin >> m_host;
	fin >> tmp;
	fin >> m_port;
	fin >> tmp;
	fin >> m_username;
	fin >> tmp;
	fin >> m_passwd;
	fin >> tmp;
	fin >> m_dbname;
	fin.close();
}

template<typename Model>
void DBDao<Model>::setModel(Model md)
{
	m_md = md;
}

template<typename Model>
std::vector<Model> DBDao<Model>::queryModel()
{
	std::vector<Model> resSet;
	generateSql(QUERY);
	int res=mysql_real_query(m_sqlCon, m_sql.c_str(), m_sql.length());
	if (res)
	{
		return resSet;
	}
	MYSQL_RES* result = mysql_store_result(m_sqlCon);
	if (!result)
	{
		return resSet;
	}
	MYSQL_ROW row;
	while ((row=mysql_fetch_row(result)))
	{
		Model md;
		int nums = mysql_num_fields(result);
		for (int i = 0; i <nums; ++i)
		{
			md[i + 1] = row[i];
		}
		resSet.push_back(md);
	}
	return resSet;
}

template<typename Model>
bool DBDao<Model>::insertModel()
{
	generateSql(INSERT);
	int res=mysql_real_query(m_sqlCon, m_sql.c_str(), m_sql.length());
	std::string buff = mysql_error(m_sqlCon);
	return !res;
}

template<typename Model>
bool DBDao<Model>::deleteModel()
{
	generateSql(DELETE);
	int res=mysql_real_query(m_sqlCon, m_sql.c_str(), m_sql.length());
	return !res;
}

template<typename Model>
bool DBDao<Model>::updateModel(const std::string& fieldName,const std::string& value)
{
	generateSql(UPDATE);
	m_sql.append(" where ");
	m_sql.append(fieldName);
	m_sql.append("='");
	m_sql.append(value);
	m_sql.append("'");
	int res=mysql_real_query(m_sqlCon, m_sql.c_str(), m_sql.length());
	return !res;
}

template<typename Model>
bool DBDao<Model>::updateModel(const std::map<std::string, std::string>& keyvls)
{
	generateSql(UPDATE);
	m_sql.append(" where ");
	int count = 0;
	int size = keyvls.size();
	for (auto var : keyvls)
	{
		m_sql += var.first + "='" + var.second + "'";
		count++;
		if (count < size)
			m_sql += " and ";
	}
	int res = mysql_real_query(m_sqlCon, m_sql.c_str(), m_sql.length());
	return !res;
}

template<typename Model>
inline void DBDao<Model>::close()
{
	if (m_sqlCon != nullptr)
	{
		mysql_close(m_sqlCon);
		m_sqlCon = nullptr;
	}
}

template<typename Model>
inline void DBDao<Model>::clear()
{
	m_md = Model();
}

template<typename Model>
void DBDao<Model>::initConnect()
{
	m_sqlCon = mysql_init(0);
	MYSQL* con = mysql_real_connect(m_sqlCon, m_host.c_str(), m_username.c_str(),
		m_passwd.c_str(), m_dbname.c_str(), m_port, NULL, 0);
}

template<typename Model>
void  DBDao<Model>::generateSql(int flag)
{
	switch (flag)
	{
	case QUERY:
	{
		m_sql.append("select * from ");
		m_sql.append(m_md.getName());
		m_sql.append(generateWhere());
	}
		break;
	case INSERT:
	{
		m_sql.append("insert into ");
		m_sql.append(m_md.getName());
		m_sql.append(generateValues());
	}
		break;
	case DELETE:
	{
		m_sql.append("delete from ");
		m_sql.append(m_md.getName());
		m_sql.append(generateWhere());
	}
		break;
	case UPDATE:
	{
		m_sql.append("update ");
		m_sql.append(m_md.getName());
		m_sql.append(" set ");
		m_sql.append(generateUpdate());
	}
		break;
	default:
		break;
	}
}

template<typename Model>
std::string   DBDao<Model>::generateWhere()
{
	std::string wheres = "";
	int flag = 0;
	for (int i =1; i <=m_md.getAttributeNums(); ++i)
	{
		if (flag == 0)
		{
			if (m_md[i] != "")
			{
				wheres += " where ";
				wheres += m_md.getAttributeName(i);
				wheres += "='";
				wheres += m_md[i];
				wheres += "'";
				flag = 1;
			}
		}
		else
		{
			if (m_md[i] != "")
			{
				wheres += " and ";
				wheres+= m_md.getAttributeName(i);
				wheres += "='";
				wheres += m_md[i];
				wheres += "'";
			}
		}
	}
	return wheres;
}

template<typename Model>
std::string DBDao<Model>::generateValues()
{
	std::string values = "";
	values += " values('";
	for (int i = 1; i <=m_md.getAttributeNums(); ++i)
	{
		if (i == m_md.getAttributeNums())
		{
			values.append(m_md[i]);
			values.append("')");
		}
		else
		{
			values.append(m_md[i]);
			values.append("','");
		}
	}
	return values;
}

template<typename Model>
std::string DBDao<Model>::generateUpdate()
{
	std::string updates = "";
	int flag = 0;
	for (int i = 1; i <=m_md.getAttributeNums(); ++i)
	{
		if (m_md[i] != "")
		{
			if (flag)
				updates += " , ";
			updates += m_md.getAttributeName(i);
			updates += "='";
			updates += m_md[i];
			updates += "'";
			flag = 1;
		}
	}
	return updates;
}

#endif // !__DB_INTERFACE_H__