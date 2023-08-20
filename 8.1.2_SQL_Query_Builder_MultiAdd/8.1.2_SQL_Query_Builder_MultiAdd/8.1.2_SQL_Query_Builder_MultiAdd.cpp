#include <iostream>
#include <cassert>

#include "SqlSelectQueryBuilder.h"

int main()
{

	//проверка вновь добавленных методов для задания 8.1.2, немного изменил относительно задания, заменил map на multimap
	{
		SqlSelectQueryBuilder query_builder;

		std::vector<std::string> col = { "name", "phone" };

		std::multimap<std::string, std::string> cond;
		cond.insert(std::pair("id", "42"));
		cond.insert(std::pair("name", "John"));
		cond.insert(std::pair("surname", "Ivanov"));

		query_builder.AddColumns(col);
		query_builder.AddFrom("students");
		query_builder.AddWhere(cond);

		std::string result = query_builder.BuildQuery();

		assert(result == "SELECT name, phone FROM students WHERE id = 42 AND name = John AND surname = Ivanov;");
	}

	
	{
		SqlSelectQueryBuilder query_builder;

		std::vector<std::string> col = {"name", "phone"};
		
		std::multimap<std::string, std::string> cond;
		cond.insert(std::pair("id", "42"));
		cond.insert(std::pair("id", "43"));
		cond.insert(std::pair("name", "John"));
		cond.insert(std::pair("name", "Kate"));
				
		query_builder.AddColumns(col);
		query_builder.AddFrom("students");
		query_builder.AddWhere(cond);

		std::string result = query_builder.BuildQuery();

		assert(result == "SELECT name, phone FROM students WHERE id IN(42, 43) AND name IN(John, Kate);");
	}

	return 0;
}

