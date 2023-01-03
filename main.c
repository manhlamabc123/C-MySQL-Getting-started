#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

int main(int argc, char **argv)
{
  // Check if MySQL is installed
  printf("MySQL client version: %s\n", mysql_get_client_info());

  // Create connection
  MYSQL *con = mysql_init(NULL);
  if (con == NULL)
  {
    fprintf(stderr, "%s\n", mysql_error(con));
    exit(1);
  }

  // Connect to database
  if (mysql_real_connect(con, "localhost", "root", "20194616", "testdb", 0, NULL, 0) == NULL)
  {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
  }

  // Create database
  // if (mysql_query(con, "CREATE DATABASE testdb"))
  // {
  //   fprintf(stderr, "%s\n", mysql_error(con));
  //   // mysql_close(con);
  //   // exit(1);
  // }

  // Insert to database
  if (mysql_query(con, "DROP TABLE IF EXISTS cars"))
  {
    finish_with_error(con);
  }

  if (mysql_query(con, "CREATE TABLE cars(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(255), price INT)"))
  {
    finish_with_error(con);
  }

  if (mysql_query(con, "INSERT INTO cars VALUES(1,'Audi',52642)"))
  {
    finish_with_error(con);
  }

  if (mysql_query(con, "INSERT INTO cars VALUES(2,'Mercedes',57127)"))
  {
    finish_with_error(con);
  }

  if (mysql_query(con, "INSERT INTO cars VALUES(3,'Skoda',9000)"))
  {
    finish_with_error(con);
  }

  if (mysql_query(con, "INSERT INTO cars VALUES(4,'Volvo',29000)"))
  {
    finish_with_error(con);
  }

  if (mysql_query(con, "INSERT INTO cars VALUES(5,'Bentley',350000)"))
  {
    finish_with_error(con);
  }

  if (mysql_query(con, "INSERT INTO cars VALUES(6,'Citroen',21000)"))
  {
    finish_with_error(con);
  }

  if (mysql_query(con, "INSERT INTO cars VALUES(7,'Hummer',41400)"))
  {
    finish_with_error(con);
  }

  if (mysql_query(con, "INSERT INTO cars VALUES(8,'Volkswagen',21600)"))
  {
    finish_with_error(con);
  }

  // Retrieve from database
  if (mysql_query(con, "SELECT * FROM cars"))
  {
    finish_with_error(con);
  }

  // Create result to store query
  MYSQL_RES *result = mysql_store_result(con);
  if (result == NULL)
  {
    finish_with_error(con);
  }

  // Get number of fields
  int num_fields = mysql_num_fields(result);

  // Loop through result
  MYSQL_ROW row;
  MYSQL_FIELD *field;
  while ((row = mysql_fetch_row(result)))
  {
    for (int i = 0; i < num_fields; i++)
    {
      if (i == 0)
      {
        while (field = mysql_fetch_field(result)) // Get column'name
        {
          printf("%s ", field->name);
        }

        printf("\n");
      }
      printf("%s ", row[i] ? row[i] : "NULL");
    }

    printf("\n");
  }

  // Free result
  mysql_free_result(result);

  // Last inserted row id
  if (mysql_query(con, "DROP TABLE IF EXISTS writers"))
  {
    finish_with_error(con);
  }

  char *sql = "CREATE TABLE writers(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(255))";
  if (mysql_query(con, sql))
  {
    finish_with_error(con);
  }

  if (mysql_query(con, "INSERT INTO writers(name) VALUES('Leo Tolstoy')"))
  {
    finish_with_error(con);
  }

  if (mysql_query(con, "INSERT INTO writers(name) VALUES('Jack London')"))
  {
    finish_with_error(con);
  }

  if (mysql_query(con, "INSERT INTO writers(name) VALUES('Honore de Balzac')"))
  {
    finish_with_error(con);
  }

  // Get the last id
  int id = mysql_insert_id(con);

  printf("The last inserted row id is: %d\n", id);

  // Close connection
  mysql_close(con);
  exit(0);
}