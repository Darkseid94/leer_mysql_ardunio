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

$insertar="SELECT * FROM dato WHERE id='1'";
$resultado = $conexion->query($insertar);
$nombre = $resultado->fetch_array();
$id = $nombre["valor"]; ///DESDE AQUI LEE ARDUINO
echo "valor=" . $id . ";";

?>