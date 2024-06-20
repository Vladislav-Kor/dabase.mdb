import pyodbc
import adodbapi
import pyodbc
import pymssql

# conn = pymssql.connect(server=r"Provider=Microsoft.ACE.OLEDB.12.0;Data Source=database.mdb;")
# conn.Open(r"Provider=Microsoft.ACE.OLEDB.12.0;Data Source=database.mdb;")
# conn = adodbapi.connect(r'Provider=Microsoft.ACE.OLEDB.12.0;Data Source=database.mdb;')
# Подключение к базе данных
conn = pyodbc.connect(r'Driver={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ=database.mdb;')
cursor = conn.cursor()

# Выполнение запроса и вывод результатов
cursor.execute("SELECT * FROM police")
rows = cursor.fetchall()

for row in rows:
    print(row)

# Закрытие соединения
cursor.close()
conn.close()