<?php
$server = "localhost";
$base_datos = "prueba";
$usuario = "root";
$pwd = "";
// Create connection
$conexion= mysqli_connect($server, $usuario, $pwd, $base_datos);
// Check connection
if (!$conexion) {
    die("Conexion fallida: " . mysqli_connect_error());
}

$dato = $_GET["actualizar"];

$insertar="UPDATE `dato` SET `valor`='$dato' where id=1";
$conexion->query($insertar);
$conexion->close();

header("Location: control.php");

?>