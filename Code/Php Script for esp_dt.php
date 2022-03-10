<!DOCTYPE html>
<html><body>
<?php

$servername = "localhost";

// REPLACE with your Database name
$dbname = "wear8563_esp_dt";
// REPLACE with Database user
$username = "wear8563_esp_dtt";
// REPLACE with Database user password
$password = "_S12@gh#1";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "SELECT SN, sensor1,sensor2, location, Temperature, Humidity, AirQuality, reading_time FROM SensorData ORDER BY id DESC";

echo '<table cellspacing="5" cellpadding="5">
      <tr> 
        <td>SN</td> 
        <td>MQ135</td> 
        <td>DHT22</td> 
        <td>Location</td> 
        <td>Temperature</td> 
        <td>Humidity</td>
        <td>AirQuality</td> 
        <td>Timestamp</td> 
      </tr>';
 
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_SN = $row["id"];
        $row_sensor1= $row["sensor1"];
        $row_sensor2 = $row["sensor2"];
        $row_location = $row["location"];
        $row_Temperature = $row["Temperature"];
        $row_Humidity = $row["Humidity"]; 
        $row_AirQuality = $row["AirQuality"]; 
        $row_reading_time = $row["reading_time"];
        // Uncomment to set timezone to - 1 hour (you can change 1 to any number)
        //$row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time - 1 hours"));
      
        // Uncomment to set timezone to + 4 hours (you can change 4 to any number)
        //$row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time + 4 hours"));
      
        echo '<tr> 
                <td>' . $row_id . '</td> 
                <td>' . $row_sensor1 . '</td> 
                <td>' . $row_location . '</td> 
                <td>' . $row_value1 . '</td> 
                <td>' . $row_value2 . '</td>
                <td>' . $row_value3 . '</td> 
                <td>' . $row_reading_time . '</td> 
              </tr>';
    }
    $result->free();
}

$conn->close();
?> 
</table>
</body>
</html>