<?php


$servername = "localhost";

// REPLACE with your Database name
$dbname = "wear8563_esp_dt";
// REPLACE with Database user
$username = "wear8563_esp_dtt";
// REPLACE with Database user password
$password = "_S12@gh#1";

// Keep this API Key value to be compatible with the ESP32 code provided in the project page. 
// If you change this value, the ESP32 sketch needs to match
$api_key_value = "tPmAT5Ab3j7F9";

$api_key= $sensor1 = $sensor2 = $location = $Temperature = $Humidity = $AirQuality = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = test_input($_POST["api_key"]);
    if($api_key == $api_key_value) {
        $sensor1 = test_input($_POST["sensor1"]);
        $sensor2 = test_input($_POST["sensor2"]);
        $location = test_input($_POST["location"]);
        $Temperature = test_input($_POST["value1"]);
        $Humidty = test_input($_POST["value2"]);
        $AirQuality = test_input($_POST["value3"]);
        
        // Create connection
        $conn = new mysqli($servername, $username, $password, $dbname);
        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
        
        $sql = "INSERT INTO SensorData (sensor1,sensor2, location, Temperature, Humidity, AirQuality)
        VALUES ('" . $sensor1 . "','" . $location . "', '" . $value1 . "', '" . $value2 . "', '" . $value3 . "')";
        
        if ($conn->query($sql) === TRUE) {
            echo "New record created successfully";
        } 
        else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    
        $conn->close();
    }
    else {
        echo "Wrong API Key provided.";
    }

}
else {
    echo "No data posted with HTTP POST.";
}

function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}