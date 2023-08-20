#include <iostream>
#include <cassert>

#include "SqlSelectQueryBuilder.h"
#include "AdvancedSqlSelectQueryBuilder.h"

int main()
{
	
	//проверка работы AdvancedSqlSelectQueryBuilder

	{
		AdvancedSqlSelectQueryBuilder query_builder;
		query_builder.AddColumns({ "name", "phone" });
		query_builder.AddFrom("students");
		query_builder.addWhereMoreAnd("id", "42"); // Добавляем условие id > 42
		
		std::string result = query_builder.BuildQuery();

		assert(result == "SELECT name, phone FROM students WHERE id > 42;");		
	}

	//проверка работы AdvancedSqlSelectQueryBuilder c несколькими условиями
	{
		AdvancedSqlSelectQueryBuilder query_builder;
		query_builder.AddColumns({ "name", "phone" });
		query_builder.AddFrom("students");
		query_builder.AddWhere("id", "42").AddWhere("name", "John");
		query_builder.addWhereMoreOr("id", "55"); 
		query_builder.addWhereLessAnd("id", "170");

		std::string result = query_builder.BuildQuery();

		assert(result == "SELECT name, phone FROM students WHERE id = 42 AND name = John OR id > 55 AND id < 170;");
	}
	//проверка работы AdvancedSqlSelectQueryBuilder c двумя диапазонами
	{
		AdvancedSqlSelectQueryBuilder query_builder;
		query_builder.AddColumns({ "name", "phone" });
		query_builder.AddFrom("students");
		query_builder.AddWhere("id", "42").AddWhere("name", "John");
		query_builder.addWhereMoreOr("id", "55");
		query_builder.addWhereLessAnd("id", "170");
		query_builder.addWhereLessOr("id", "500");
		query_builder.addWhereMoreAnd("id", "300");

		std::string result = query_builder.BuildQuery();

		assert(result == "SELECT name, phone FROM students WHERE id = 42 AND name = John OR id > 55 AND id < 170 OR id < 500 AND id > 300;");
	}

	//дальнейшее усложнение диапазонов потребует значительного усложнения логики BuildQuery() или переработки структуры данных...

	return 0;
}

