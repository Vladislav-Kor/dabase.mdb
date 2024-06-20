<?php
/**
 * PHP-код, который открывает файл .mdb и выводит данные из таблицы policy с помощью SELECT-запроса:
 * 
 * mdb-export '/home/user/projects/test_mdb/dabase.mdb' 'police' > result.csv 
 */

// Установка пути к файлу .mdb
$db_path = '/home/user/projects/test_mdb/dabase.mdb';

// Установка имени ODBC-источника
$dsn = 'odbc:DRIVER={Microsoft Access Driver (*.mdb)}; DBQ=' . $db_path;
$username = 'root';
$password = 'orbita91.wxy-';

// Установка соединения с базой данных
try {
    $conn = new PDO($dsn, NULL, $password);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
} catch (PDOException $e) {
    echo 'Ошибка соединения с базой данных: ' . $e->getMessage();

    exit;
}

// Формирование SELECT-запроса
$query = 'SELECT * FROM `policy`';

// Выполнение запроса
try {
    $stmt = $conn->prepare($query);
    $stmt->execute();
} catch (PDOException $e) {
    echo 'Ошибка выполнения запроса: ' . $e->getMessage();
    exit;
}

// Вывод результатов
while ($row = $stmt->fetch()) {
    print_r($row);
    echo '<br>';
}

// Закрытие соединения
$conn = null;
?>